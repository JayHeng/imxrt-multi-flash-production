/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_debug_console.h"
#if defined(MIMXRT798S_cm33_core0_SERIES)
#include "fsl_cache.h"
#endif
#include "fsl_clock.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(MIMXRT798S_cm33_core0_SERIES)
#define HYPERRAM_CMD_LUT_SEQ_IDX_SYNC_READ   0
#define HYPERRAM_CMD_LUT_SEQ_IDX_SYNC_WRITE  1
#define HYPERRAM_CMD_LUT_SEQ_IDX_BURST_READ  2
#define HYPERRAM_CMD_LUT_SEQ_IDX_BURST_WRITE 3
#define HYPERRAM_CMD_LUT_SEQ_IDX_REG_READ    4
#define HYPERRAM_CMD_LUT_SEQ_IDX_REG_WRITE   5
#define HYPERRAM_CMD_LUT_SEQ_IDX_RESET       6

#define CUSTOM_LUT_LENGTH 40
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t uartClkSrcFreq;

#if (defined(MIMXRT798S_cm33_core0_SERIES) || defined(MIMXRT798S_hifi4_SERIES))
    CLOCK_AttachClk(BOARD_DEBUG_UART_FCCLK_ATTACH);
    CLOCK_SetClkDiv(BOARD_DEBUG_UART_FCCLK_DIV, 1U);

    /* attach FC0 clock to LP_FLEXCOMM (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
#else
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    CLOCK_SetClkDiv(BOARD_DEBUG_UART_CLK_DIV, 4U);
#endif

    uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

#if defined(MIMXRT798S_cm33_core0_SERIES)
AT_QUICKACCESS_SECTION_CODE(void BOARD_EnableXspiCache(CACHE64_CTRL_Type *cache))
{
    /* First, invalidate the entire cache. */
    cache->CCR |= CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while ((cache->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0x00U)
    {
    }
    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    cache->CCR &= ~(CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK);
    /* Now enable the cache. */
    cache->CCR |= CACHE64_CTRL_CCR_ENCACHE_MASK;
}

AT_QUICKACCESS_SECTION_CODE(void BOARD_DisableXspiCache(CACHE64_CTRL_Type *cache))
{
    /* First, clean XSPI cache. */
    cache->CCR |= CACHE64_CTRL_CCR_PUSHW0_MASK | CACHE64_CTRL_CCR_PUSHW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while ((cache->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0x00U)
    {
    }
    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    cache->CCR &= ~(CACHE64_CTRL_CCR_PUSHW0_MASK | CACHE64_CTRL_CCR_PUSHW1_MASK);

    /* Now disable XSPI cache. */
    cache->CCR &= ~CACHE64_CTRL_CCR_ENCACHE_MASK;
}

void BOARD_ConfigMPU(void)
{
    uint8_t attr;
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RW_m_ncache$$Base[];
    /* RW_m_ncache_unused is a auxiliary region which is used to get the whole size of noncache section */
    extern uint32_t Image$$RW_m_ncache_unused$$Base[];
    extern uint32_t Image$$RW_m_ncache_unused$$ZI$$Limit[];
    uint32_t nonCacheStart = (uint32_t)Image$$RW_m_ncache$$Base;
    uint32_t nonCacheSize  = ((uint32_t)Image$$RW_m_ncache_unused$$Base == nonCacheStart) ?
                                 0 :
                                 ((uint32_t)Image$$RW_m_ncache_unused$$ZI$$Limit - nonCacheStart);
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    uint32_t nonCacheSize  = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[];
    extern uint32_t __NCACHE_REGION_SIZE[];
    uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    uint32_t nonCacheSize  = (uint32_t)__NCACHE_REGION_SIZE;
#else
#error "Unsupported compiler"
#endif

    XCACHE_DisableCache(XCACHE0);
    XCACHE_DisableCache(XCACHE1);

    /* Disable MPU */
    ARM_MPU_Disable();

    /* Attr0: device memory. */
    ARM_MPU_SetMemAttr(0U, ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE));
    /* Attr1: non cacheable. */
    ARM_MPU_SetMemAttr(1U, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));
    /* Attr2: non transient, write through, read allocate. */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 0U, 1U, 0U);
    ARM_MPU_SetMemAttr(2U, ARM_MPU_ATTR(attr, attr));
    /* Attr3: non transient, write back, read/write allocate. */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 1U, 1U, 1U);
    ARM_MPU_SetMemAttr(3U, ARM_MPU_ATTR(attr, attr));

    /* Region 0: [0x0, 0x1FFFFFFF], non-shareable, read/write, any privileged, executable. Attr 2 (write through). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x1FFFFFFFU, 2U));
    /* Region 2 (Peripherals): [0x40000000, 0x5FFFFFFF], non-shareable, read/write, non-privileged, executable. Attr 0
     * (device). */
    ARM_MPU_SetRegion(2U, ARM_MPU_RBAR(0x40000000U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x5FFFFFFF, 0U));

    if (nonCacheSize != 0)
    {
        /* The MPU region size should a granularity of 32 bytes. */
        assert((nonCacheSize & 0x1FU) == 0x0U);

        /* Region 1 setting : outter-shareable, read-write,  non-privileged, executable. Attr 1. (non-cacheable) */
        ARM_MPU_SetRegion(1U, ARM_MPU_RBAR(nonCacheStart, ARM_MPU_SH_OUTER, 0U, 1U, 0U),
                          ARM_MPU_RLAR(nonCacheStart + nonCacheSize - 1, 1U));
    }

    /*
     * Enable MPU and HFNMIENA feature
     * HFNMIENA ensures the core uses MPU configuration when in hard fault, NMI, and FAULTMASK handlers,
     * otherwise all memory regions are accessed without MPU protection.
     */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);

    /* Enable code & system cache */
    XCACHE_EnableCache(XCACHE0);
    XCACHE_EnableCache(XCACHE1);

    /* flush pipeline */
    __DSB();
    __ISB();
}

void BOARD_DeinitXspi(XSPI_Type *base, CACHE64_CTRL_Type *cache)
{
    if (base == XSPI0)
    {
        /* Enable clock again. */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_CLR_XSPI0_MASK;
    }
    else if (base == XSPI1)
    {
        /* Enable clock again. */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_CLR_XSPI1_MASK;
    }
    else
    {
    }

    base->MCR &= ~XSPI_MCR_MDIS_MASK;
    if ((cache->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK) != 0x00U)
    {
        BOARD_DisableXspiCache(cache);
    }
    /* Wait until XSPI is not busy */
    while ((base->SR & XSPI_SR_BUSY_MASK) != 0U)
    {
    }
    /* Disable module. */
    base->MCR |= XSPI_MCR_MDIS_MASK;
}

void BOARD_InitXspi(XSPI_Type *base, CACHE64_CTRL_Type *cache)
{
    /* Enable XSPI module */
    base->MCR |= XSPI_MCR_MDIS_MASK;

    base->MCR |= XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK;
    for (uint32_t i = 0; i < 6; i++)
    {
        __NOP();
    }
    base->MCR &= ~(XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK);
    base->MCR |= XSPI_MCR_IPS_TG_RST_MASK | XSPI_MCR_MDIS_MASK;
    base->MCR &= ~XSPI_MCR_ISD3FA_MASK;
    base->MCR &= ~XSPI_MCR_MDIS_MASK;
    base->MCR |= XSPI_MCR_MDIS_MASK;
    base->MCR |= XSPI_MCR_ISD3FA_MASK;
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    base->MCR |= XSPI_MCR_MDIS_MASK;
    base->SMPR = 0x04000000;
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    base->DLLCR[0] = 0xc240001d;
    while (!(((base->DLLSR & XSPI_DLLSR_SLVA_LOCK_MASK) == XSPI_DLLSR_SLVA_LOCK_MASK) &&
             ((base->DLLSR & XSPI_DLLSR_DLLA_LOCK_MASK) == XSPI_DLLSR_DLLA_LOCK_MASK)))
        ;

    if ((cache->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK) == 0x00U)
    {
        BOARD_EnableXspiCache(cache);
        /* flush pipeline */
        __DSB();
        __ISB();
    }
}

/* BOARD_SetXspiClock run in RAM used to configure XSPI clock source and divider when XIP. */
void BOARD_SetXspiClock(XSPI_Type *base, uint32_t src, uint32_t divider)
{
    if (base == XSPI0)
    {
        if ((CLKCTL0->XSPI0FCLKSEL != CLKCTL0_XSPI0FCLKSEL_SEL(src)) ||
            ((CLKCTL0->XSPI0FCLKDIV & CLKCTL0_XSPI0FCLKDIV_DIV_MASK) != (divider - 1)))
        {
            /* Always deinit XSPI and init XSPI for the flash to make sure the flash works correctly after the
             XSPI root clock changed as the default XSPI configuration may does not work for the new root clock
             frequency. */
            BOARD_DeinitXspi(base, CACHE64_CTRL0);

            /* Disable clock before changing clock source */
            CLKCTL0->PSCCTL1_CLR = CLKCTL0_PSCCTL1_CLR_XSPI0_MASK;
            /* Update XSPI clock. */
            CLKCTL0->XSPI0FCLKSEL = CLKCTL0_XSPI0FCLKSEL_SEL(src) | CLKCTL0_XSPI0FCLKSEL_SEL_EN_MASK;
            CLKCTL0->XSPI0FCLKDIV = CLKCTL0_XSPI0FCLKDIV_DIV(divider - 1);
            while ((CLKCTL0->XSPI0FCLKDIV) & CLKCTL0_XSPI0FCLKDIV_REQFLAG_MASK)
            {
            }
            /* Enable XSPI clock again */
            CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI0_MASK;

            BOARD_InitXspi(base, CACHE64_CTRL0);
        }
    }
    else if (base == XSPI1)
    {
        if ((CLKCTL0->XSPI1FCLKSEL != CLKCTL0_XSPI1FCLKSEL_SEL(src)) ||
            ((CLKCTL0->XSPI1FCLKDIV & CLKCTL0_XSPI1FCLKDIV_DIV_MASK) != (divider - 1)))
        {
            /* Always deinit XSPI and init XSPI for the flash to make sure the flash works correctly after the
             XSPI root clock changed as the default XSPI configuration may does not work for the new root clock
             frequency. */
            BOARD_DeinitXspi(base, CACHE64_CTRL1);

            /* Disable clock before changing clock source */
            CLKCTL0->PSCCTL1_CLR = CLKCTL0_PSCCTL1_CLR_XSPI1_MASK;
            /* Update XSPI clock. */
            CLKCTL0->XSPI1FCLKSEL = CLKCTL0_XSPI1FCLKSEL_SEL(src) | CLKCTL0_XSPI1FCLKSEL_SEL_EN_MASK;
            CLKCTL0->XSPI1FCLKDIV = CLKCTL0_XSPI1FCLKDIV_DIV(divider - 1);
            while ((CLKCTL0->XSPI1FCLKDIV) & CLKCTL0_XSPI1FCLKDIV_REQFLAG_MASK)
            {
            }
            /* Enable XSPI clock again */
            CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI1_MASK;

            BOARD_InitXspi(base, CACHE64_CTRL1);
        }
    }
    else
    {
        return;
    }
}

void BOARD_XspiClockSafeConfig(void)
{
    BOARD_SetXspiClock(XSPI0, 0U, 1U);
    BOARD_SetXspiClock(XSPI1, 0U, 1U);
}

void BOARD_Init16bitsPsRam(XSPI_Type *base)
{
    xspi_config_t config;

    const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
        /* Memory Read */
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_READ] =
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0xA0, kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x18),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_READ + 1] =
            XSPI_LUT_SEQ(kXSPI_Command_CADDR_DDR, kXSPI_8PAD, 0x10, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD,
                         13), /*Dummy cycles -> 7  = 1 + 4 + 2*/
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_READ + 2] =
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0x04, kXSPI_Command_STOP, kXSPI_1PAD, 0x0),

        /* Memory Write */
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_WRITE] =
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x20, kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x18),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_WRITE + 1] =
            XSPI_LUT_SEQ(kXSPI_Command_CADDR_DDR, kXSPI_8PAD, 0x10, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD,
                         13), /*Dummy cycles -> 7  = 1 + 4 + 2*/
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_BURST_WRITE + 2] =
            XSPI_LUT_SEQ(kXSPI_Command_WRITE_DDR, kXSPI_8PAD, 0x04, kXSPI_Command_STOP, kXSPI_1PAD, 0X0),

        /* Register Read */
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_READ] =
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0xE0, kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x18),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_READ + 1] =
            XSPI_LUT_SEQ(kXSPI_Command_CADDR_DDR, kXSPI_8PAD, 0x10, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD,
                         13), /*Dummy cycles -> 7  = 1 + 4 + 2*/
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_READ + 2] =
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0x04, kXSPI_Command_STOP, kXSPI_1PAD, 0x0),

        /* Register write */
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_WRITE] =
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x60, kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x18),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_WRITE + 1] =
            XSPI_LUT_SEQ(kXSPI_Command_CADDR_DDR, kXSPI_8PAD, 0x10, kXSPI_Command_WRITE_DDR, kXSPI_8PAD, 0x02),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_REG_WRITE + 2] =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, kXSPI_1PAD, 0x0, kXSPI_Command_STOP, kXSPI_1PAD, 0x0),

        /* reset */
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_RESET] =
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0xFF, kXSPI_Command_DDR, kXSPI_8PAD, 0xFF),
        [5 * HYPERRAM_CMD_LUT_SEQ_IDX_RESET + 1] XSPI_LUT_SEQ(kXSPI_Command_STOP, kXSPI_8PAD, 0x0, kXSPI_Command_STOP,
                                                              kXSPI_8PAD, 0x0),
    };

    xspi_device_config_t deviceconfig = {
        .flashA1Size                      = 0x8000U, /* 256Mb/KByte */
        .sampleTimeRef                    = kXSPI_2xFlashHalfClock,
        .CSHoldTime                       = 3,
        .CSSetupTime                      = 3,
        .columnSpace                      = 3, /*!< Column space size. */
        .AWRSeqIndex                      = HYPERRAM_CMD_LUT_SEQ_IDX_BURST_WRITE,
        .ARDSeqIndex                      = HYPERRAM_CMD_LUT_SEQ_IDX_BURST_READ,
        .enableDdr                        = true,
        .dllConfig.dllMode                = kXSPI_AutoUpdateMode,
        .dllConfig.useRefValue            = true,
        .smprConfig.delayWithRef          = kXSPI_SameWithDqs,
        .smprConfig.enableAtInvertedClock = 0,
        .enable4BWordAddress              = true, /*!< 4B Word addressable memory. */
        .enableX16Mode                    = true,
        .xspiRootClk                      = 500000000,
    };

    if (base == XSPI2)
    {
        POWER_DisablePD(kPDRUNCFG_APD_XSPI2);
        POWER_DisablePD(kPDRUNCFG_PPD_XSPI2);
        POWER_ApplyPD();

        CLOCK_AttachClk(kMAIN_PLL_PFD3_to_XSPI2);
        CLOCK_SetClkDiv(kCLOCK_DivXspi2Clk, 1U);
#if (defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        CLOCK_EnableClock(kCLOCK_Xspi2);
#endif
    }
    else
    {
        POWER_DisablePD(kPDRUNCFG_APD_XSPI1);
        POWER_DisablePD(kPDRUNCFG_PPD_XSPI1);
        POWER_ApplyPD();

        CLOCK_AttachClk(kAUDIO_PLL_PFD1_to_XSPI1);
        CLOCK_SetClkDiv(kCLOCK_DivXspi1Clk, 1U);
#if (defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        CLOCK_EnableClock(kCLOCK_Xspi1);
#endif
    }

    /* Get XSPI default settings and configure the xspi. */
    XSPI_GetDefaultConfig(base, &config, &deviceconfig);
    config.rxSampleClock = kXSPI_ReadSampleClkExternalInputFromDqsPad;
    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch = false;
    config.enableDqsOut                = true;

    XSPI_Init(base, &config);
    /* Configure flash settings according to serial flash feature. */
    XSPI_SetFlashConfig(base, &deviceconfig);

    /* Update LUT table. */
    XSPI_UpdateLUT(base, 0, customLUT, CUSTOM_LUT_LENGTH);
}

void GlikeyWriteEnable(GLIKEY_Type *base, uint8_t idx)
{
    (void)GLIKEY_SyncReset(base);

    (void)GLIKEY_StartEnable(base, idx);
    (void)GLIKEY_ContinueEnable(base, GLIKEY_CODEWORD_STEP1);
    (void)GLIKEY_ContinueEnable(base, GLIKEY_CODEWORD_STEP2);
    (void)GLIKEY_ContinueEnable(base, GLIKEY_CODEWORD_STEP3);
    (void)GLIKEY_ContinueEnable(base, GLIKEY_CODEWORD_STEP_EN);
}

void GlikeyClearConfig(GLIKEY_Type *base)
{
    (void)GLIKEY_SyncReset(base);
}

/* Disable the secure check for AHBSC and enable periperhals/sram access for masters */
void BOARD_InitAHBSC(void)
{
    GlikeyWriteEnable(GLIKEY0, 1U);
    AHBSC0->MISC_CTRL_DP_REG = 0x000086aa;
    AHBSC0->MISC_CTRL_REG    = 0x000086aa; /* AHBSC0 MISC_CTRL_REG, disable Privilege & Secure checking. */

    GlikeyWriteEnable(GLIKEY1, 1U);
    AHBSC3->MISC_CTRL_DP_REG = 0x000086aa;
    AHBSC3->MISC_CTRL_REG    = 0x000086aa; /* AHBSC3 MISC_CTRL_REG, disable Privilege & Secure checking.*/

    GlikeyWriteEnable(GLIKEY0, 7U);
    /* Enable arbiter0 accessing SRAM */
    AHBSC0->COMPUTE_ARB0RAM_ACCESS_ENABLE = 0x3FFFFFFF;
    AHBSC0->SENSE_ARB0RAM_ACCESS_ENABLE   = 0x3FFFFFFF;
    AHBSC0->MEDIA_ARB0RAM_ACCESS_ENABLE   = 0x3FFFFFFF;
    AHBSC0->NPU_ARB0RAM_ACCESS_ENABLE     = 0x3FFFFFFF;
    AHBSC0->HIFI4_ARB0RAM_ACCESS_ENABLE   = 0x3FFFFFFF;

    GlikeyWriteEnable(GLIKEY1, 9U);
    /* Enable arbiter1 accessing SRAM */
    AHBSC3->COMPUTE_ARB1RAM_ACCESS_ENABLE = 0x3FFFFFFF;
    AHBSC3->SENSE_ARB1RAM_ACCESS_ENABLE   = 0x3FFFFFFF;
    AHBSC3->MEDIA_ARB1RAM_ACCESS_ENABLE   = 0x3FFFFFFF;
    AHBSC3->NPU_ARB1RAM_ACCESS_ENABLE     = 0x3FFFFFFF;
    AHBSC3->HIFI4_ARB1RAM_ACCESS_ENABLE   = 0x3FFFFFFF;
    AHBSC3->HIFI1_ARB1RAM_ACCESS_ENABLE   = 0x3FFFFFFF;

    GlikeyWriteEnable(GLIKEY1, 8U);
    /* Access enable for COMPUTE domain masters to common APB peripherals.*/
    AHBSC3->COMPUTE_APB_PERIPHERAL_ACCESS_ENABLE = 0xffffffff;
    AHBSC3->SENSE_APB_PERIPHERAL_ACCESS_ENABLE   = 0xffffffff;
    GlikeyWriteEnable(GLIKEY1, 7U);
    AHBSC3->COMPUTE_AIPS_PERIPHERAL_ACCESS_ENABLE = 0xffffffff;
    AHBSC3->SENSE_AIPS_PERIPHERAL_ACCESS_ENABLE   = 0xffffffff;

    GlikeyWriteEnable(GLIKEY2, 1U);
    /*Disable secure and secure privilege checking. */
    AHBSC4->MISC_CTRL_DP_REG = 0x000086aa;
    AHBSC4->MISC_CTRL_REG    = 0x000086aa;

    GlikeyClearConfig(GLIKEY0);
    GlikeyClearConfig(GLIKEY1);
    GlikeyClearConfig(GLIKEY2);
}
#endif /* MIMXRT798S_cm33_core0_SERIES */

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz)
{
    lpi2c_master_config_t i2cConfig = {0};

    LPI2C_MasterGetDefaultConfig(&i2cConfig);
    LPI2C_MasterInit(base, &i2cConfig, clkSrc_Hz);
}

status_t BOARD_I2C_Send(LPI2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    lpi2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    return LPI2C_MasterTransferBlocking(base, &masterXfer);
}

status_t BOARD_I2C_Receive(LPI2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    return LPI2C_MasterTransferBlocking(base, &masterXfer);
}

void BOARD_PMIC_I2C_Init(void)
{
    BOARD_I2C_Init(BOARD_PMIC_I2C_BASEADDR, BOARD_PMIC_I2C_CLOCK_FREQ);
}

void BOARD_PMIC_I2C_Deinit(void)
{
    LPI2C_MasterDeinit(BOARD_PMIC_I2C_BASEADDR);
}

status_t BOARD_PMIC_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_I2C_Send(BOARD_PMIC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                          txBuffSize);
}

status_t BOARD_PMIC_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_I2C_Receive(BOARD_PMIC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
}

#if defined(MIMXRT798S_cm33_core0_SERIES)
void BOARD_MIPIPanelTouch_I2C_Init(void)
{
    CLOCK_AttachClk(kOSC_CLK_to_FCCLK0);
    CLOCK_AttachClk(kFCCLK0_to_FLEXCOMM8);
    CLOCK_EnableClock(kCLOCK_LPFlexComm8);
    BOARD_I2C_Init(BOARD_MIPI_PANEL_TOUCH_I2C_BASEADDR, BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_FREQ);
}
#endif
#endif
