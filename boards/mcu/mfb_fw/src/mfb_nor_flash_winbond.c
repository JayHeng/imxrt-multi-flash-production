/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mfb_nor_flash_winbond.h"
#if WINBOND_DEVICE_SERIES
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/

#if WINBOND_DEVICE_QUAD
const uint32_t s_customLUT_WINBOND_Quad[CUSTOM_LUT_LENGTH] = {
    /* Fast read quad mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0xEB, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_MODE8_SDR, kFLEXSPI_4PAD, 0xF0, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, WINBOND_QUAD_FLASH_DUMMY_CYCLES - 2),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR,  kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Read status register - 1 */
    // opcode 0x05/0x35/0x15 to read Status Registers (1/2/3)
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /* Write Enable - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Erase Sector - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x20, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

    /* Page Program - single mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Enable Quad mode */
    // QE bit in 8bit Status Register-2[1], there are three Status Registers (1/2/3)
    // opcode 0x01/0x31/0x11 to write Status Registers (1/2/3)
    // opcode 0x01 to write Status Registers (1&2)
    [4 * NOR_CMD_LUT_SEQ_IDX_ENABLEQE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x31, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01),

    /* Set Drive strength */
    // DRV[1:0] in 8bit Status Register-3[6:5], there are three Status Registers (1/2/3)
    // opcode 0x01/0x31/0x11 to write Status Registers (1/2/3)
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDRIVE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x11, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01),

    /* Set Dummy cycle */
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0xC0, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01),

    /* Read status register - 2 */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x35, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /* Read status register - 3 */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x15, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Enter QPI mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTERQPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x38, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
};
#endif

#if WINBOND_DEVICE_OCTAL
const uint32_t s_customLUT_WINBOND_Octal[CUSTOM_LUT_LENGTH] = {
#if !MFB_FLASH_OPI_MODE_DISABLE
    /*  DDR OCTAL I/O FAST READ */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0xFD, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
    // Don't care the dummy value setting here, as it uses external DQS
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x06, kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x04),
#else
    /*  4-BYTE OCTAL I/O FAST READ */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0xCC, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_8PAD, 0x08, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_8PAD, 0x04),
#endif

    /* Read status register - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR,  kFLEXSPI_1PAD, 0x01),

    /* Write Enable - SPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Set Dummy cycle */
    // Volatile Configuration Register address 000001h - Dummy cycle configuration
    //   - Default dummy cycle for OPI DDR is 16, max freq is 143MHz (for random start addr)
    //   - To support freq 200MHz, min dummy cycle is 22
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x81, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x01),
    [4 * NOR_CMD_LUT_SEQ_IDX_SETDUMMY + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

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
    // Volatile Configuration Register address 000000h - I/O mode
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x81, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00, kFLEXSPI_Command_SDR,       kFLEXSPI_1PAD, 0x00),
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Read status register using Octal DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 1] = 
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Write Enable - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x06, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* Erase Sector - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x21, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),

    /* 4-BYTE Page Program - OPI */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x12, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),

    /* READ VOLATILE CONFIGURATION REGISTER */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x85, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01),

    /* READ FLAG STATUS REGISTER */
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR,       kFLEXSPI_8PAD, 0x70, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x10),
    [4 * NOR_CMD_LUT_SEQ_IDX_READREG2 + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR,  kFLEXSPI_8PAD, 0x01, kFLEXSPI_Command_STOP,      kFLEXSPI_1PAD, 0x00),
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

void mfb_flash_set_param_for_winbond(jedec_id_t *jedecID)
{
    mfb_printf(" -- Winbond Serial Flash.\r\n");
    mfb_printf("MFB: Flash Memory Type ID: 0x%x", jedecID->memoryTypeID);
    switch (jedecID->memoryTypeID)
    {
        /////////////////////////QuadSPI////////////////////////
        case 0x30:
            mfb_printf(" -- W25X DualSPI 3.3V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
            break;
        case 0x40:
            mfb_printf(" -- W25QxxxDV/FV/BV/CL/JV(-IQ/JQ) QuadlSPI 3.3V Series.\r\n");
#if WINBOND_DEVICE_W25QxxxJV
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            //g_flashPropertyInfo.flashDriveStrength = WINBOND_FLASH_DRVIE_STRENGTH_025P;
#elif WINBOND_DEVICE_W25QxxxDV
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_80MHz;
#else
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
#endif
            break;
        case 0x60:
            mfb_printf(" -- W25QxxxJW/FW/EW/NW(-IQ/IN) QuadlSPI 1.8V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
#if WINBOND_DEVICE_W25QxxxNW
#if !MFB_FLASH_USE_DEFAULT_DUMMY
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            g_flashPropertyInfo.flashDummyValue = WINBOND_QUAD_FLASH_SET_DUMMY_CMD;
#endif
#endif
            break;
        case 0x61:
            mfb_printf(" -- W25MxxxJW QuadlSPI 1.8V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
            break;
        case 0x65:
            mfb_printf(" -- W25QxxxNE QuadlSPI 1.2V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
#if WINBOND_DEVICE_W25QxxxNE
            g_flashPropertyInfo.flashDriveStrength = WINBOND_FLASH_DRVIE_STRENGTH_100P;
#endif
            break;
        case 0x70:
            mfb_printf(" -- W25QxxxJV(-IM/JM) QuadlSPI 3.3V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            break;
        case 0x80:
            mfb_printf(" -- W25QxxxJW/NW(-IM) QuadlSPI 1.8V Series.\r\n");
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_100MHz;
#if WINBOND_DEVICE_W25QxxxNW
#if !MFB_FLASH_USE_DEFAULT_DUMMY
            g_flashPropertyInfo.mixspiRootClkFreq = kMixspiRootClkFreq_133MHz;
            g_flashPropertyInfo.flashDummyValue = WINBOND_QUAD_FLASH_SET_DUMMY_CMD;
#endif
#endif
            break;
        ////////////////////////OctalSPI////////////////////////
        case 0x5B:
            g_flashPropertyInfo.flashIsOctal = true;
            mfb_printf(" -- W35TxxxNW OctalSPI 1.8V Series.\r\n");
            break;
        // Missing W25H, W25R
        // Missing xxxJL, xxxDW, xxxRV
        default:
            mfb_printf(" -- Unsupported Series.\r\n");
            break;
    }
    mfb_flash_show_mem_size(jedecID->capacityID, false);
#if WINBOND_DEVICE_QUAD
    if (!g_flashPropertyInfo.flashIsOctal)
    {
        g_flashPropertyInfo.mixspiPad                 = kFLEXSPI_4PAD;
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkLoopbackFromDqsPad;
        g_flashPropertyInfo.flashBusyStatusPol        = WINBOND_FLASH_BUSY_STATUS_POL;
        g_flashPropertyInfo.flashBusyStatusOffset     = WINBOND_FLASH_BUSY_STATUS_OFFSET;
        g_flashPropertyInfo.flashQuadEnableCfg        = WINBOND_FLASH_QUAD_ENABLE;
        g_flashPropertyInfo.flashQuadEnableBytes      = 1;
        g_flashPropertyInfo.mixspiCustomLUTVendor     = s_customLUT_WINBOND_Quad;
    }
#endif
#if WINBOND_DEVICE_OCTAL
    if (g_flashPropertyInfo.flashIsOctal)
    {
        g_flashPropertyInfo.mixspiPad                 = kFLEXSPI_8PAD;
        g_flashPropertyInfo.flashBusyStatusPol        = WINBOND_FLASH_BUSY_STATUS_POL;
        g_flashPropertyInfo.flashBusyStatusOffset     = WINBOND_FLASH_BUSY_STATUS_OFFSET;
        g_flashPropertyInfo.flashEnableOctalCmd       = WINBOND_OCTAL_FLASH_ENABLE_DDR_CMD;
        g_flashPropertyInfo.mixspiCustomLUTVendor     = s_customLUT_WINBOND_Octal;
#if MFB_FLASH_OPI_MODE_DISABLE
        g_flashPropertyInfo.mixspiRootClkFreq         = kMixspiRootClkFreq_30MHz;
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkLoopbackFromDqsPad;
#else
        g_flashPropertyInfo.mixspiRootClkFreq         = kMixspiRootClkFreq_200MHz;
        g_flashPropertyInfo.mixspiReadSampleClock     = kFLEXSPI_ReadSampleClkExternalInputFromDqsPad;
#endif
        g_flashPropertyInfo.flashDummyValue           = WINBOND_OCTAL_FLASH_SET_DUMMY_CMD;
    }
#endif
}

void mfb_flash_show_registers_for_winbond(bool isOctalFlash)
{
#if MFB_FLASH_REGS_READBACK_ENABLE
    flash_reg_access_t regAccess;
    if (!isOctalFlash)
    {
        regAccess.regNum = 1;
        regAccess.regAddr = 0x0;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register [7:0]: 0x%x\r\n", regAccess.regValue.B.reg1);
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register [15:8]: 0x%x\r\n", regAccess.regValue.B.reg1);
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG2;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register [23:16]: 0x%x\r\n", regAccess.regValue.B.reg1);
    }
    else
    {
        regAccess.regNum = 1;
        regAccess.regAddr = 0x0;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Status Register: 0x%x\r\n", regAccess.regValue.B.reg1);

        for (uint32_t idx = 0; idx <= 0x07; idx++)
        {
            regAccess.regAddr = 0x00000000 + idx;
            regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG;
            mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
            mfb_printf("MFB: Flash Volatile Configuration Register (0x%x): 0x%x\r\n", regAccess.regAddr, regAccess.regValue.B.reg1);
        }

        regAccess.regAddr = 0x00000000;
        regAccess.regSeqIdx = NOR_CMD_LUT_SEQ_IDX_READREG2;
        mixspi_nor_read_register(EXAMPLE_MIXSPI, &regAccess);
        mfb_printf("MFB: Flash Flag Status Register: 0x%x\r\n", regAccess.regValue.B.reg1);
    }
#endif
}
#endif // WINBOND_DEVICE_SERIES

