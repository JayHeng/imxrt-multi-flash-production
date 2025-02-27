/*
 * Copyright 2018-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _MFB_NOR_FLASH_MXIC_H_
#define _MFB_NOR_FLASH_MXIC_H_

#include "mfb_nor_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MXIC_FLASH_BUSY_STATUS_POL    1
#define MXIC_FLASH_BUSY_STATUS_OFFSET 0

#if MXIC_DEVICE_MX25Uxx35F
#define MXIC_FLASH_QUAD_ENABLE        0x40
#define MXIC_QUAD_FLASH_DUMMY_CYCLES  0x06

//------------------------------------------------------
//    NTR     |  dummy cycles  |Quad IO Fast Read(SPI) | 
//------------------------------------------------------
//    N/A     | 6(def for SPI) |        104MHz         |
//------------------------------------------------------

#elif MXIC_DEVICE_MX25Lxx33F | MXIC_DEVICE_MX25Vxx35F
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define MXIC_FLASH_QUAD_ENABLE        0x0040
#define MXIC_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define MXIC_FLASH_QUAD_ENABLE        0x4040
#define MXIC_QUAD_FLASH_DUMMY_CYCLES  0x0A
#endif

//------------------------------------------------------
//    DC[6]   |  dummy cycles  |Quad IO Fast Read(SPI) |
//------------------------------------------------------
//   1'b0     |   6(default)   |       80/104MHz       |
//   1'b1     |      10        |        133MHz         |
//------------------------------------------------------

#elif MXIC_DEVICE_MX25Lxxx45G | MXIC_DEVICE_MX25Uxxx45G | MXIC_DEVICE_MX25Lxxx33F | MXIC_DEVICE_MX25Uxxx32F
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define MXIC_FLASH_QUAD_ENABLE        0x0740
#define MXIC_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define MXIC_FLASH_QUAD_ENABLE        0xC740
#define MXIC_QUAD_FLASH_DUMMY_CYCLES  0x0A
#endif

// Uxxx32F
//------------------------------------------------------
//   DC[7:6]  |  dummy cycles  |Quad IO Fast Read(SPI) |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//  2'b00     |   6(default)   |         84MHz         |
//  2'b01     |       4        |         66MHz         |
//  2'b10     |       8        |        104MHz         |
//  2'b11     |      10        |        133MHz         |
//------------------------------------------------------

// Lxxx45G / Lxxx33F
//------------------------------------------------------
//   DC[7:6]  |  dummy cycles  |Quad IO Fast Read(SPI) |
//------------------------------------------------------
//  2'b00     |   6(default)   |         80MHz         |
//  2'b01     |      4         |         54MHz         |
//  2'b10     |      8         |       84/104MHz       |
//  2'b11     |     10         |      120/133MHz       |
//------------------------------------------------------

// Uxxx45G
//------------------------------------------------------
//   DC[7:6]  |  dummy cycles  |Quad IO Fast Read(SPI) |
//------------------------------------------------------
//  2'b00     |   6(default)   |         80MHz         |
//  2'b01     |      4         |         70MHz         |
//  2'b10     |      8         |         104MHz        |
//  2'b11     |     10         |         133MHz        |
//------------------------------------------------------

#endif

////////////////////////////////////////////////////////////////////////////////
#define MXIC_X8_FLASH_BUS_PROTOCOL (kFlashProtocolType_OctaBus)

#if MXIC_DEVICE_MX25UMxx345
// 0x00 - SPI (default)
// 0x01 - STR OPI enable
// 0x02 - DTR OPI enable
#define MXIC_OCTAL_FLASH_ENABLE_DDR_CMD   0x02

//------------------------------------------------------
//   DC[2:0]  |  dummy cycles  | OctalI/O SDR(1S-8S-8S)|
//            |                |  Octal DDR(8D-8D-8D)  |
//            |                |        BGA24          |
//------------------------------------------------------
//  3'b000    |  20(default)   |        200MHz         |
//  3'b001    |      18        |        200MHz         |
//  3'b010    |      16        |        173MHz         |
//  3'b011    |      14        |        155MHz         |
//  3'b100    |      12        |        139MHz         |
//  3'b101    |      10        |        121MHz         |
//  3'b110    |      08        |         86MHz         |
//  3'b111    |      06        |         70MHz         |
//------------------------------------------------------
#if MFB_FLASH_OPI_MODE_DISABLE
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x05
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x0A   // 121MHz SPI SDR
#else
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x00
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x14   // 200MHz OPI DDR
#endif
#elif MXIC_DEVICE_MX25LMxx245
// 0x00 - SPI (default)
// 0x01 - STR OPI enable
// 0x02 - DTR OPI enable
#define MXIC_OCTAL_FLASH_ENABLE_DDR_CMD   0x02

//------------------------------------------------------
//   DC[2:0]  |  dummy cycles  | OctalI/O SDR(1S-8S-8S)|
//            |                |  Octal DDR(8D-8D-8D)  |
//            |                |        BGA24          |
//------------------------------------------------------
//  3'b000    |  20(default)   |        133MHz         |
//  3'b001    |      18        |        133MHz         |
//  3'b010    |      16        |        133MHz         |
//  3'b011    |      14        |        133MHz         |
//  3'b100    |      12        |        104MHz         |
//  3'b101    |      10        |        104MHz         |
//  3'b110    |      08        |         84MHz         |
//  3'b111    |      06        |         66MHz         |
//------------------------------------------------------
#if MFB_FLASH_OPI_MODE_DISABLE
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x00
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x14   // 133MHz SPI SDR
#else
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x03
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x0e   // 133MHz OPI DDR
#endif
#elif MXIC_DEVICE_MX25UWxx345
// 0x00 - SPI (default)
// 0x01 - STR OPI enable
// 0x02 - DTR OPI enable
#define MXIC_OCTAL_FLASH_ENABLE_DDR_CMD   0x02

//------------------------------------------------------
//   DC[2:0]  |  dummy cycles  | OctalI/O SDR(1S-8S-8S)|
//            |                |  Octal DDR(8D-8D-8D)  |
//            |                |        BGA24          |
//------------------------------------------------------
//  3'b000    |  20(default)   |        200MHz         |
//  3'b001    |      18        |        173MHz         |
//  3'b010    |      16        |        166MHz         |
//  3'b011    |      14        |        155MHz         |
//  3'b100    |      12        |        133MHz         |
//  3'b101    |      10        |        104MHz         |
//  3'b110    |      08        |         84MHz         |
//  3'b111    |      06        |         66MHz         |
//------------------------------------------------------
#if MFB_FLASH_OPI_MODE_DISABLE
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x06
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x08   // 84MHz SPI SDR
#else
#define MXIC_OCTAL_FLASH_SET_DUMMY_CMD     0x00
#define MXIC_OCTAL_FLASH_DUMMY_CYCLES      0x14   // 200MHz OPI DDR
#endif
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


#endif /* _MFB_NOR_FLASH_MXIC_H_ */
