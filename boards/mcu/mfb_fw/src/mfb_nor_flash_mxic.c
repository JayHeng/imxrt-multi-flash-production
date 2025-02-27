/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mfb_nor_flash_mxic.h"
#if MXIC_DEVICE_SERIES
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if MXIC_DEVICE_QUAD
const uint32_t s_customLUT_MXIC_Quad[CUSTOM_LUT_LENGTH] = {
#if !MFB_FLASH_QPI_MODE_ENABLE
    /* Fast read quad mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0xEB, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_MODE8_SDR, kFLEXSPI_4PAD, 0x00, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, MXIC_QUAD_FLASH_DUMMY_CYCLES - 2),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR,  kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
#else
    /* Fast read quad mode - QPI-SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_4PAD, 0xEB, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_MODE8_SDR, kFLEXSPI_4PAD, 0x00, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, MXIC_QUAD_FLASH_DUMMY_CYCLES - 2),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR,  kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
#endif

    /* Read status register -SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /* Write Enable -SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Erase Sector -SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x20, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

    /* Page Program - single mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Enable Quad mode */
    // QE bit in 8bit Status Register[6], there is only one Status Register
    // First byte is SR, second byte is CR
    [4 * NOR_CMD_LUT_SEQ_IDX_ENABLEQE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x01, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x02),

    /* Read configuration register */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x15, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Enter QPI mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTERQPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x35, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Read status register -QPI-SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_QPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_4PAD, 0x05, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_4PAD, 0x01),

    /* Write Enable -QPI-SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_QPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_4PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Erase Sector - QPI-SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR_QPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_4PAD, 0x20, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),

    /* Page Program - QPI-SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_4PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
};
#endif

#if MXIC_DEVICE_OCTAL
const uint32_t s_customLUT_MXIC_Octal[CUSTOM_LUT_LENGTH] = {
#if !MFB_FLASH_OPI_MODE_DISABLE
    /* OPI DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xEE, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x11),
    // Don't care the dummy value setting here, as it uses external DQS
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
#else
    /*  FAST READ4B */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x0C, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, MXIC_OCTAL_FLASH_DUMMY_CYCLES, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x04),
#endif

    /* Read status register -SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /* Write Enable - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Set Dummy cycle */
    // Configuration Register 2 address 00000300h - Dummy cycle configuration
    //   - Default dummy cycle for OPI DDR is 20, max freq is 200MHz(BGA24)/133MHz(SOP16)
    //   - To support freq 200MHz, min dummy cycle is 18
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x72, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x03),
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01),

    /* Erase Sector - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x21, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x20),

    /* 4-BYTE Page Program - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x12, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Dummy write, do nothing when AHB write command is triggered. */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Enter OPI mode */
    // Configuration Register 2 address 00000000h - I/O mode
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x72, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01), 

    /* Read status register using Octal DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xFA),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 2] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Write Enable - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x06, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xF9),

    /* Erase Sector - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x21, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xDE),
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR_OPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* 4-BYTE Page Program - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x12, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xED),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OPI + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x04),

    /* READ CONFIGURATION REGISTER */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x15, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0xEA),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* READ CONFIGURATION REGISTER 2 */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2 + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x71, kFLEXSPI_Command_DDR,       kFLEXSPI_8PAD, 0x8E),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2 + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2 + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

void mfb_flash_set_param_for_mxic(jedec_id_t *jedecID)
{
    mfb_printf(" -- MXIC Serial Flash.\r\n");
    mfb_printf("MFB: Flash Memory Type ID: 0x%x", jedecID->memoryTypeID);
    switch (jedecID->memoryTypeID)
    {
        /////////////////////////QuadSPI////////////////////////
        case 0x20:
            mfb_printf(" -- MX25L/MX66L QuadSPI 3.3V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            g_flashPropertyInfo.flashQuadEnableBytes = 2;
            break;
        case 0x23:
            mfb_printf(" -- MX25V QuadSPI 3.3V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
            g_flashPropertyInfo.flashQuadEnableBytes = 2;
            break;
        case 0x25:
            mfb_printf(" -- MX25U/MX66U QuadSPI 1.8V Series.\r\n");
#if MXIC_DEVICE_MX25Uxx35F
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
            g_flashPropertyInfo.flashQuadEnableBytes = 1;
#else
            g_flashPropertyInfo.flashHasQpiSupport = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            g_flashPropertyInfo.flashQuadEnableBytes = 2;
#endif
            break;
        case 0x28:
            mfb_printf(" -- MX25R QuadSPI 1.8-3.3V Series.\r\n");
            break;
        case 0x75:
            mfb_printf(" -- MX77L QuadSPI 3.3V Series.\r\n");
            break;
        ////////////////////////OctalSPI////////////////////////
        case 0x80:
            g_flashPropertyInfo.flashIsOctal = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_400MHz;
            mfb_printf(" -- MX25UM/MX66UM OctalSPI 1.8V Series.\r\n");
            break;
        case 0x81:
            g_flashPropertyInfo.flashIsOctal = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_400MHz;
            mfb_printf(" -- MX25UM51345G OctalSPI 1.8V Series.\r\n");
            break;
        case 0x83:
            g_flashPropertyInfo.flashIsOctal = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_400MHz;
            mfb_printf(" -- MX25UM25345G OctalSPI 1.8V Series.\r\n");
            break;
        case 0x84:
            g_flashPropertyInfo.flashIsOctal = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_400MHz;
            mfb_printf(" -- MX25UWxx345G OctalSPI 1.8V Series.\r\n");
            break;
        case 0x85:
            g_flashPropertyInfo.flashIsOctal = true;
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_266MHz;
            mfb_printf(" -- MX25LM/MX66LM OctalSPI 3.3V Series.\r\n");
            break;
        // Missing MX25LW51245G, MX66LW1G45G, MX66LW2G45G
        // Missing MX25UW6445G, MX66UW12845G, MX25UW25645G, MX25UW51245G, MX66UW1G45G, MX66UW2G45G
        // Missing MX25UW6345G, MX66LW12345G, MX66UW25345G      done                 , MX66UW2G345G
        default:
            mfb_printf(" -- Unsupported Series.\r\n");
            break;
    }
    mfb_flash_show_mem_size(jedecID->capacityID, false);
#if MXIC_DEVICE_QUAD
    if (!g_flashPropertyInfo.flashIsOctal)
    {
        g_flashPropertyInfo.mixspiPad                 = kFLEXSPI_4PAD;
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkLoopbackFromDqsPad;
        g_flashPropertyInfo.flashBusyStatusPol        = MXIC_FLASH_BUSY_STATUS_POL;
        g_flashPropertyInfo.flashBusyStatusOffset     = MXIC_FLASH_BUSY_STATUS_OFFSET;
        g_flashPropertyInfo.flashQuadEnableCfg        = MXIC_FLASH_QUAD_ENABLE;
        g_flashPropertyInfo.mixspiCustomLUTVendor     = s_customLUT_MXIC_Quad;
#if MFB_FLASH_USE_DEFAULT_DUMMY
        g_flashPropertyInfo.mixspiRootClkFreq         = kMixspiRootClkFreq_80MHz;
#endif
    }
#endif
#if MXIC_DEVICE_OCTAL
    if (g_flashPropertyInfo.flashIsOctal)
    {
        g_flashPropertyInfo.mixspiPad                 = kFLEXSPI_8PAD;
        g_flashPropertyInfo.flashBusyStatusPol        = MXIC_FLASH_BUSY_STATUS_POL;
        g_flashPropertyInfo.flashBusyStatusOffset     = MXIC_FLASH_BUSY_STATUS_OFFSET;
        g_flashPropertyInfo.flashEnableOctalCmd       = MXIC_OCTAL_FLASH_ENABLE_DDR_CMD;
        g_flashPropertyInfo.mixspiCustomLUTVendor     = s_customLUT_MXIC_Octal;
#if MFB_FLASH_OPI_MODE_DISABLE
        g_flashPropertyInfo.mixspiRootClkFreq         = kMixspiRootClkFreq_50MHz;
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkLoopbackInternally;
#else
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkExternalInputFromDqsPad;
#endif
        g_flashPropertyInfo.flashDummyValue           = MXIC_OCTAL_FLASH_SET_DUMMY_CMD;
    }
#endif
}

const uint32_t mxic_octal_cfg_reg2_addrs[] = {0x00000000u, 0x00000200, 0x00000300, 0x00000400, 0x00000500, 0x00000800, 0x00000c00, 0x00000d00, 0x00000e00, 0x00000f00, 0x40000000, 0x80000000};

void mfb_flash_show_registers_for_mxic(bool isOctalFlash)
{
#if MFB_FLASH_REGS_READBACK_ENABLE
    flash_reg_access_t regAccess;
    if (!isOctalFlash)
    {
        regAccess.regNum = 1;
        regAccess.regAddr = 0x0;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register: 0x%x\r\n", regAccess.regValue.B.reg1);
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Configuration Register: 0x%x\r\n", regAccess.regValue.B.reg1);
    }
    else
    {
        regAccess.regNum = 1;
        regAccess.regAddr = 0x0;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register: 0x%x\r\n", regAccess.regValue.B.reg1);

        regAccess.regAddr = 0x01000000;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Configuration Register (0x%x): 0x%x\r\n", regAccess.regAddr, regAccess.regValue.B.reg1);

        for (uint32_t idx = 0; idx < sizeof(mxic_octal_cfg_reg2_addrs)/sizeof(uint32_t); idx++)
        {
            regAccess.regAddr = mxic_octal_cfg_reg2_addrs[idx];
            regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG2;
            mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
            mfb_printf("MFB: Flash Configuration Register 2 (0x%x): 0x%x\r\n", regAccess.regAddr, regAccess.regValue.B.reg1);
        }
    }
#endif
}

#endif // MXIC_DEVICE_SERIES

