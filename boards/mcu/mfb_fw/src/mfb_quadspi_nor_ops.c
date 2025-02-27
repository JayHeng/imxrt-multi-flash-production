/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "port_mixspi_info.h"
#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 *****************************************************************************/
extern uint32_t lut[FSL_FEATURE_QSPI_LUT_DEPTH];
extern qspi_dqs_config_t dqsConfig;
extern qspi_flash_config_t single_config;
/*******************************************************************************
 * Code
 ******************************************************************************/

int mfb_printf(const char *fmt_s, ...)
{
#if MFB_DEBUG_LOG_INFO_ENABLE
    PRINTF(fmt_s);
#endif
    
    return 0;
}

/* Check if serial flash erase or program finished. */
void check_if_finished(void)
{
    uint32_t val = 0;
    /* Check WIP bit */
    do
    {
        while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
        {
        }
        QSPI_ClearFifo(EXAMPLE_MIXSPI, kQSPI_RxFifo);
        QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 12U);
        while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
        {
        }
        val = EXAMPLE_MIXSPI->RBDR[0];
        /* Clear ARDB area */
        QSPI_ClearErrorFlag(EXAMPLE_MIXSPI, kQSPI_RxBufferDrain);
    } while (val & 0x1);
}

/* Write enable command */
void cmd_write_enable(void)
{
    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 4U);
}

#if defined(FLASH_ENABLE_QUAD_CMD)
/* Enable Quad mode */
void enable_quad_mode(void)
{
    uint32_t val[4] = {FLASH_ENABLE_QUAD_CMD, 0, 0, 0};

    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_SetIPCommandAddress(EXAMPLE_MIXSPI, FSL_FEATURE_QSPI_AMBA_BASE);

    /* Clear Tx FIFO */
    QSPI_ClearFifo(EXAMPLE_MIXSPI, kQSPI_TxFifo);

    /* Write enable */
    cmd_write_enable();

    /* Write data into TX FIFO, needs to write at least 16 bytes of data */
    QSPI_WriteBlocking(EXAMPLE_MIXSPI, val, 16U);

    /* Set seq id, write register */
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 20);

    /* Wait until finished */
    check_if_finished();
}
#endif

void enable_ddr_mode(void)
{
    QSPI_EnableDDRMode(EXAMPLE_MIXSPI, true);
}

#if defined(FLASH_ENABLE_OCTAL_CMD)
/* Enable Quad DDR mode */
void enable_octal_mode(void)
{
    uint32_t val[4] = {FLASH_ENABLE_OCTAL_CMD, 0, 0, 0};

    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_SetIPCommandAddress(EXAMPLE_MIXSPI, FSL_FEATURE_QSPI_AMBA_BASE);

    /* Clear Tx FIFO */
    QSPI_ClearFifo(EXAMPLE_MIXSPI, kQSPI_TxFifo);

    /* Write enable */
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 32U);

    /* Write data into TX FIFO, needs to write at least 16 bytes of data */
    QSPI_WriteBlocking(EXAMPLE_MIXSPI, val, 16U);

    /* Set seq id, write register */
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 20);

    /* Wait until finished */
    check_if_finished();
}
#endif

/*Erase sector */
void erase_sector(uint32_t addr)
{
    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_ClearFifo(EXAMPLE_MIXSPI, kQSPI_TxFifo);
    QSPI_SetIPCommandAddress(EXAMPLE_MIXSPI, addr);
    cmd_write_enable();
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 28U);
    check_if_finished();

#if defined(FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC) && (FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC)
    QSPI_ClearCache(EXAMPLE_MIXSPI);
#endif
}

/* Erase all command */
void erase_all(void)
{
    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_SetIPCommandAddress(EXAMPLE_MIXSPI, FSL_FEATURE_QSPI_AMBA_BASE);
    /* Write enable*/
    cmd_write_enable();
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 8U);
    check_if_finished();
#if defined(FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC) && (FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC)
    QSPI_ClearCache(EXAMPLE_MIXSPI);
#endif
}

/* Program page into serial flash using QSPI polling way */
void program_page(uint32_t dest_addr, uint32_t *src_addr)
{
    uint32_t leftLongWords = 0;

    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }
    QSPI_ClearFifo(EXAMPLE_MIXSPI, kQSPI_TxFifo);

    QSPI_SetIPCommandAddress(EXAMPLE_MIXSPI, dest_addr);
    cmd_write_enable();
    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & kQSPI_Busy)
    {
    }

    /* First write some data into TXFIFO to prevent from underrun */
    QSPI_WriteBlocking(EXAMPLE_MIXSPI, src_addr, FSL_FEATURE_QSPI_TXFIFO_DEPTH * 4);
    src_addr += FSL_FEATURE_QSPI_TXFIFO_DEPTH;

    /* Start the program */
    QSPI_SetIPCommandSize(EXAMPLE_MIXSPI, EXAMPLE_FLASH_PAGE_SIZE);
    QSPI_ExecuteIPCommand(EXAMPLE_MIXSPI, 16U);

    leftLongWords = EXAMPLE_FLASH_PAGE_SIZE - 16 * sizeof(uint32_t);
    QSPI_WriteBlocking(EXAMPLE_MIXSPI, src_addr, leftLongWords);

    /* Wait until flash finished program */
    check_if_finished();
    while (QSPI_GetStatusFlags(EXAMPLE_MIXSPI) & (kQSPI_Busy | kQSPI_IPAccess))
    {
    }

#if defined(FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC) && (FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC)
    QSPI_ClearCache(EXAMPLE_MIXSPI);
#endif
}

void qspi_nor_flash_init(QuadSPI_Type *base)
{
    uint32_t clockSourceFreq = 0;
    qspi_config_t config     = {0};

    /*Get QSPI default settings and configure the qspi */
    QSPI_GetDefaultQspiConfig(&config);

    /*Set AHB buffer size for reading data through AHB bus */
    if (EXAMPLE_FLASH_PAGE_SIZE <= FSL_FEATURE_QSPI_AHB_BUFFER_SIZE)
    {
        config.AHBbufferSize[3] = EXAMPLE_FLASH_PAGE_SIZE;
    }
    else
    {
        config.AHBbufferSize[3] = FSL_FEATURE_QSPI_AHB_BUFFER_SIZE;
    }
    clockSourceFreq = mixspi_get_clock(EXAMPLE_MIXSPI);

    QSPI_Init(base, &config, clockSourceFreq);

#if defined(FLASH_NEED_DQS)
    /* Set DQS config */
    QSPI_SetDqsConfig(base, &dqsConfig);
#endif

    /*According to serial flash feature to configure flash settings */
    QSPI_SetFlashConfig(base, &single_config);

#if defined(FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC) && (FSL_FEATURE_QSPI_SOCCR_HAS_CLR_LPCAC)
    QSPI_ClearCache(base);
#endif
}
