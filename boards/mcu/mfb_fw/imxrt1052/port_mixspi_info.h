/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _PORT_MIXSPI_INFO_H_
#define _PORT_MIXSPI_INFO_H_

#include "mfb_config.h"
#include "mfb_define.h"

#include "fsl_clock.h"
#include "fsl_iomuxc.h"
#include "fsl_cache.h"
#include "fsl_flexspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MFB_MIXSPI_MODULE MFB_MIXSPI_MODULE_IS_FLEXSPI

#define EXAMPLE_MIXSPI                  FLEXSPI
#define EXAMPLE_MIXSPI_AMBA_BASE        FlexSPI_AMBA_BASE
#if MFB_FLASH_HYPER_FLASH_ENABLE
#define FLASH_SIZE                      0x10000 /* 512Mb/KByte */
#define EXAMPLE_FLASH_PAGE_SIZE         512
#define EXAMPLE_FLASH_SECTOR_SIZE       0x40000 /* 256K */
#else
#define FLASH_SIZE                      0x2000  /* 64Mb/KByte */
#define EXAMPLE_FLASH_PAGE_SIZE         256
#define EXAMPLE_FLASH_SECTOR_SIZE       0x1000  /* 4K */
#endif
#define EXAMPLE_MIXSPI_CLOCK            kCLOCK_FlexSpi
#define EXAMPLE_MIXSPI_PORT             kFLEXSPI_PortA1

/*
 * If cache is enabled, this example should maintain the cache to make sure
 * CPU core accesses the memory, not cache only.
 */
#define CACHE_MAINTAIN 1

/*${macro:end}*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*${variable:start}*/
#if (defined CACHE_MAINTAIN) && (CACHE_MAINTAIN == 1)
typedef struct _flexspi_cache_status
{
    volatile bool DCacheEnableFlag;
    volatile bool ICacheEnableFlag;
} flexspi_cache_status_t;
#endif
/*${variable:end}*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void cpu_show_clock_source(void)
{
#if MFB_DEBUG_LOG_INFO_ENABLE
    // Refer to CLOCK_GetAhbFreq() in fsl_clock.c
    uint32_t periphClkSel = CCM->CBCDR & CCM_CBCDR_PERIPH_CLK_SEL_MASK;
    uint32_t periphClk2Sel = CCM->CBCMR & CCM_CBCMR_PERIPH_CLK2_SEL_MASK;
    uint32_t prePeriphClkSel = CCM->CBCMR & CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK;
    uint32_t clkDiv = 0;

    /* Periph_clk2_clk ---> Periph_clk */
    if (periphClkSel != 0U)
    {
        switch (periphClk2Sel)
        {
            /* Pll3_sw_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(0U):
                mfb_printf("MFB: CPU Clk Source from PERIPH_CLK2 2'b00 - PLL3(USB1 PLL) sw_clk %dHz.\r\n", CLOCK_GetPllFreq(kCLOCK_PllUsb1));
                break;

            /* Osc_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(1U):
                mfb_printf("MFB: CPU Clk Source from PERIPH_CLK2 2'b01 - OSC clock %dHz.\r\n", CLOCK_GetOscFreq());
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(2U):
                mfb_printf("MFB: CPU Clk Source from PERIPH_CLK2 2'b10 - PLL2(System PLL) bypass_clk %dHz.\r\n", CLOCK_GetPllFreq(kCLOCK_PllSys));
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(3U):
            default:
                mfb_printf("MFB: CPU Clk Source from PERIPH_CLK2 2'b11 - Reserved.\r\n");
                break;
        }

        clkDiv = (CCM->CBCDR & CCM_CBCDR_PERIPH_CLK2_PODF_MASK) >> CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT;
        mfb_printf("MFB: PERIPH_CLK2 Source Divider: %d.\r\n", (clkDiv + 1U));
    }
    /* Pre_Periph_clk ---> Periph_clk */
    else
    {
        switch (prePeriphClkSel)
        {
            /* PLL2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(0U):
                mfb_printf("MFB: CPU Clk Source from PRE_PERIPH_CLK 2'b00 - PLL2(System PLL) clock %dHz.\r\n", CLOCK_GetPllFreq(kCLOCK_PllSys));
                break;

            /* PLL2 PFD2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(1U):
                mfb_printf("MFB: CPU Clk Source from PRE_PERIPH_CLK 2'b01 - PLL2(System PLL) PFD2 clock %dHz.\r\n", CLOCK_GetSysPfdFreq(kCLOCK_Pfd2));
                break;

            /* PLL2 PFD0 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(2U):
                mfb_printf("MFB: CPU Clk Source from PRE_PERIPH_CLK 2'b10 - PLL2(System PLL) PFD0 clock %dHz.\r\n", CLOCK_GetSysPfdFreq(kCLOCK_Pfd0));
                break;

            /* PLL1 divided(/2) ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(3U):
                mfb_printf("MFB: CPU Clk Source from PRE_PERIPH_CLK 2'b11 - PLL1(ARM PLL) divided clock %dHz.\r\n", CLOCK_GetPllFreq(kCLOCK_PllArm) / (((CCM->CACRR & CCM_CACRR_ARM_PODF_MASK) >> CCM_CACRR_ARM_PODF_SHIFT) + 1U));
                break;

            default:
                break;
        }
    }
    
    clkDiv = (CCM->CBCDR & CCM_CBCDR_AHB_PODF_MASK) >> CCM_CBCDR_AHB_PODF_SHIFT;
    mfb_printf("MFB: CPU Clk Source Divider: %d.\r\n", (clkDiv + 1U));
    mfb_printf("MFB: CPU Clk Frequency: %dHz.\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
#endif
}

static void mixspi_port_switch(FLEXSPI_Type *base, flexspi_port_t port, flexspi_pad_t pads)
{
}

static void mixspi_pin_init(FLEXSPI_Type *base, flexspi_port_t port, flexspi_pad_t pads)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);   
    if (base == FLEXSPI)
    {
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_FLEXSPI_A_DQS, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_06_FLEXSPI_A_SS0_B, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_07_FLEXSPI_A_SCLK, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_FLEXSPI_A_DATA00, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_FLEXSPI_A_DATA1, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_10_FLEXSPI_A_DATA2, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_11_FLEXSPI_A_DATA3, 1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_05_FLEXSPI_A_DQS, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_06_FLEXSPI_A_SS0_B, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_07_FLEXSPI_A_SCLK, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_FLEXSPI_A_DATA00, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_FLEXSPI_A_DATA1, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_10_FLEXSPI_A_DATA2, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_11_FLEXSPI_A_DATA3, 0x10F1U); 

        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_FLEXSPI_B_DATA3, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_FLEXSPI_B_DATA2, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_FLEXSPI_B_DATA1, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_FLEXSPI_B_DATA0, 1U); 
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_FLEXSPI_B_SCLK, 1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_FLEXSPI_B_DATA3, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_FLEXSPI_B_DATA2, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_02_FLEXSPI_B_DATA1, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_03_FLEXSPI_B_DATA0, 0x10F1U); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_FLEXSPI_B_SCLK, 0x10F1U); 
    }
    else
    {
    }
}

static void mixspi_clock_init(FLEXSPI_Type *base, mixspi_root_clk_freq_t clkFreq)
{
    if (base == FLEXSPI)
    {
        const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};
        CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
        // 480*18/PFDx_FRAC where PFDx_FRAC is in the range 12-35.
        if (clkFreq == kMixspiRootClkFreq_30MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 30);   /* Set PLL3 PFD0 clock 288MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 7);   /* flexspi clock 36M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_50MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 22);   /* Set PLL3 PFD0 clock 392.7MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 7);   /* flexspi clock 49.1M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_60MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 18);   /* Set PLL3 PFD0 clock 480MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 7);   /* flexspi clock 60M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_80MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 18);   /* Set PLL3 PFD0 clock 480MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 5);   /* flexspi clock 80M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_100MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 13);   /* Set PLL3 PFD0 clock 664.6MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 6);   /* flexspi clock 94.9M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_120MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 18);   /* Set PLL3 PFD0 clock 480MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 3);   /* flexspi clock 120M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_133MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 33);   /* Set PLL3 PFD0 clock 261.8MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 1);   /* flexspi clock 130.9M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_166MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 26);   /* Set PLL3 PFD0 clock 332.3MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 1);   /* flexspi clock 166.1M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_200MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 22);   /* Set PLL3 PFD0 clock 392.7MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 1);   /* flexspi clock 196.3M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_240MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 18);   /* Set PLL3 PFD0 clock 480MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 1);   /* flexspi clock 240M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_266MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 33);   /* Set PLL3 PFD0 clock 261.8MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0);   /* flexspi clock 261.8M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_332MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 26);   /* Set PLL3 PFD0 clock 332.3MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0);   /* flexspi clock 332.3M. */
        }
        else if (clkFreq == kMixspiRootClkFreq_400MHz)
        {
            CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 22);   /* Set PLL3 PFD0 clock 392.7MHZ. */
            CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
            CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0);   /* flexspi clock 392.7M. */
        }
        else
        {
            mfb_printf("MFB: This FlexSPI clock freq is not set.\r\n");
        }
    }
    else
    {
    }
}

static uint32_t mixspi_get_clock(FLEXSPI_Type *base)
{
    if (base == FLEXSPI)
    {
        return CLOCK_GetClockRootFreq(kCLOCK_FlexspiClkRoot);
    }
    else
    {
        return 0;
    }
}

static void mixspi_show_clock_source(FLEXSPI_Type *base)
{
#if MFB_DEBUG_LOG_INFO_ENABLE
    uint32_t index = 0;
    uint32_t clkSel;
    uint32_t clkDiv;
    if (base == FLEXSPI)
    {
        index = 0;
        clkSel = CCM->CSCMR1 & CCM_CSCMR1_FLEXSPI_CLK_SEL_MASK;
        clkDiv = (CCM->CSCMR1 & CCM_CSCMR1_FLEXSPI_PODF_MASK) >> CCM_CSCMR1_FLEXSPI_PODF_SHIFT;
        switch (clkSel)
        {
            case CCM_CSCMR1_FLEXSPI_CLK_SEL(0):
                mfb_printf("MFB: FLEXSPI0 Clk Source from 2'b00 - semc_clk_root_pre clock %dHz.\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
                break;

            case CCM_CSCMR1_FLEXSPI_CLK_SEL(1):
                mfb_printf("MFB: FLEXSPI0 Clk Source from 2'b01 - PLL3(USB1 PLL) sw_clk %dHz.\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllClk));
                break;

            case CCM_CSCMR1_FLEXSPI_CLK_SEL(2):
                mfb_printf("MFB: FLEXSPI0 Clk Source from 2'b10 - PLL2(System PLL) PFD2 clock %dHz.\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
                break;

            case CCM_CSCMR1_FLEXSPI_CLK_SEL(3):
                mfb_printf("MFB: FLEXSPI0 Clk Source from 2'b11 - PLL3(USB1 PLL) PFD0 clock %dHz.\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk));
                break;

            default:
                break;
        }
    }
    mfb_printf("MFB: FLEXSPI%d Clk Source Divider: %d.\r\n", index, (clkDiv + 1U));
    mfb_printf("MFB: FLEXSPI%d Clk Frequency: %dHz.\r\n", index, mixspi_get_clock(EXAMPLE_MIXSPI));
#endif
}

static void mixspi_sw_delay_us(uint64_t us)
{
    uint32_t ticks_per_us = CLOCK_GetFreq(kCLOCK_CpuClk) / 1000000;
    while (us--)
    {
        register uint32_t ticks = 1 + ticks_per_us / 4;
        while (ticks--)
        {
            __NOP();
        }
    }
}

#endif /* _PORT_MIXSPI_INFO_H_ */
