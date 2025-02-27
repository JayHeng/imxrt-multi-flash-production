/*
 * Copyright 2018-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _MFB_NOR_FLASH_SPANSION_H_
#define _MFB_NOR_FLASH_SPANSION_H_

#include "mfb_nor_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SPANSION_FLASH_BUSY_STATUS_POL    1
#define SPANSION_FLASH_BUSY_STATUS_OFFSET 0

#if SPANSION_DEVICE_S25FL064L
#define SPANSION_FLASH_QUAD_ENABLE           0x0200

#define SPANSION_QUAD_FLASH_DUMMY_CYCLES     0x08

#define SPANSION_QUAD_FLASH_UNIQUE_CFG       0x00

//------------------------------------------------------
// CR3NV[3:0] |  dummy cycles  |Quad IO Fast Read(SPI) |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//  4'b0001   |        1       |         35MHz         |
//  4'b0010   |        2       |         45MHz         |
//  4'b0011   |        3       |         55MHz         |
//  4'b0100   |        4       |         65MHz         |
//  4'b0101   |        5       |         75MHz         |
//  4'b0110   |        6       |         85MHz         |
//  4'b0111   |        7       |         95MHz         |
//  4'b1000   |   8(default)   |        108MHz         |
//   ...      |       ..       |        108MHz         |
//  4'b1111   |       15       |        108MHz         |
//------------------------------------------------------
#elif SPANSION_DEVICE_S25HS512T
#define SPANSION_FLASH_QUAD_ENABLE           0x0200

#define SPANSION_QUAD_FLASH_DUMMY_CYCLES     0x08

//------------------------------------------------------
// CR2NV[3:0] |  dummy cycles  |Quad IO Fast Read(SPI) |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//  4'b0000   |        0       |         43MHz         |
//  4'b0001   |        1       |         56MHz         |
//  4'b0010   |        2       |         68MHz         |
//  4'b0011   |        3       |         81MHz         |
//  4'b0100   |        4       |         93MHz         |
//  4'b0101   |        5       |        106MHz         |
//  4'b0110   |        6       |        118MHz         |
//  4'b0111   |        7       |        131MHz         |
//  4'b1000   |   8(default)   |        143MHz         |
//   ...      |       ..       |        156MHz         |
//  4'b1111   |       15       |        156MHz         |
//------------------------------------------------------

// CFR3NV[3] - Uniform or Hybrid Sector Architecture selection
#define SPANSION_QUAD_FLASH_UNIQUE_CFG       0x08
#endif

////////////////////////////////////////////////////////////////////////////////
#define SPANSION_X8_FLASH_BUS_PROTOCOL (kFlashProtocolType_OctaBus)

#if SPANSION_DEVICE_S28HS512
// CFR5N/V
// bit0 - SPI/OPI enable
// bit1 - SDR/DDR enable
// bit6 - reserved 1
#define SPANSION_OCTAL_FLASH_ENABLE_DDR_CMD     0x43

//------------------------------------------------------------------------------
//CFR2N/V[3:0]|  dummy cycles  |  Octal SDR(8S-8S-8S)   |Octal SPI SDR(1S-1S-8S)|
//            |                |  Octal DDR(8D-8D-8D)   |                       |
//            |                |        BGA24           |                       |
//-------------------------------------------------------------------------------
//    0x0     |      5/0       |        50/42MHz        |          50MHz        |
//  0x8(def)  |     20/8       |      200/178MHz        |         156MHz        |
//    0x9     |     22/9       |      200/192MHz        |         166MHz        |
//    0xf     |     28/15      |         200MHz         |         166MHz        |
//-------------------------------------------------------------------------------
// bit7 - 3B/4B addr
#if MFB_FLASH_OPI_MODE_DISABLE
#define SPANSION_OCTAL_FLASH_SET_DUMMY_CMD     0x89
#define SPANSION_OCTAL_FLASH_DUMMY_CYCLES      0x09   // 166MHz SPI SDR
#else
#define SPANSION_OCTAL_FLASH_SET_DUMMY_CMD     0x08
#define SPANSION_OCTAL_FLASH_DUMMY_CYCLES      0x14   // 200MHz OPI DDR
#endif
#endif


#if SPANSION_DEVICE_S26KS512
#define SPANSION_HYPERFLASH_BUSY_STATUS_OFFSET 7
#define SPANSION_HYPERFLASH_MIX_STATUS_MASK    0x32

#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


#endif /* _MFB_NOR_FLASH_SPANSION_H_ */
