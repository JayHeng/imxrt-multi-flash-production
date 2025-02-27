/*
 * Copyright 2018-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _MFB_NOR_FLASH_ISSI_H_
#define _MFB_NOR_FLASH_ISSI_H_

#include "mfb_nor_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ISSI_FLASH_BUSY_STATUS_POL    1
#define ISSI_FLASH_BUSY_STATUS_OFFSET 0

#if ISSI_DEVICE_IS25WP064A
#define ISSI_FLASH_QUAD_ENABLE        0x40

#define ISSI_QUAD_FLASH_SET_DUMMY_CMD 0x40
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x08
#endif

//------------------------------------------------------
//    P[6:3]  |  dummy cycles  |   Quad IO Fast Read   |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//    0x0     |    6(default)  |        104MHz         |
//    0x1     |       1        |         33MHz         |
//    0x2     |       2        |         50MHz         |
//    0x3     |       3        |         60MHz         |
//    0x4     |       4        |         70MHz         |
//    0x5     |       5        |         84MHz         |
//    0x6     |       6        |        104MHz         |
//    0x7     |       7        |        115MHz         |
//    0x8     |       8        |        133MHz         |
//    0x9     |       9        |        133MHz         |
//    0xa     |      10        |        133MHz         |
//    0xb     |      11        |        133MHz         |
//    0xc     |      12        |        133MHz         |
//    0xd     |      13        |        133MHz         |
//    0xe     |      14        |        133MHz         |
//    0xf     |      15        |        133MHz         |
//------------------------------------------------------
#elif ISSI_DEVICE_IS25WP064D | ISSI_DEVICE_IS25LP064D
#define ISSI_FLASH_QUAD_ENABLE        0x40

#define ISSI_QUAD_FLASH_SET_DUMMY_CMD 0x70
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x0E
#endif

// VDD = 2.70~3.6V, 125��C
//------------------------------------------------------
//    P[6:3]  |  dummy cycles  |   Quad IO Fast Read   |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//    0x0     |    6(default)  |         90MHz         |
//    0x1     |       1        |         33MHz         |
//    0x2     |       2        |         50MHz         |
//    0x3     |       3        |         60MHz         |
//    0x4     |       4        |         70MHz         |
//    0x5     |       5        |         80MHz         |
//    0x6     |       6        |         90MHz         |
//    0x7     |       7        |        104MHz         |
//    0x8     |       8        |        120MHz         |
//    0x9     |       9        |        133MHz         |
//    0xa     |      10        |        140MHz         |
//    0xb     |      11        |        150MHz         |
//    0xc     |      12        |        160MHz         |
//    0xd     |      13        |        166MHz         |
//    0xe     |      14        |        166MHz         |
//    0xf     |      15        |        166MHz         |
//------------------------------------------------------
// VDD = 1.70~1.95V, 105��C
//------------------------------------------------------
//    P[6:3]  |  dummy cycles  |   Quad IO Fast Read   |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//    0x0     |    6(default)  |         81MHz         |
//    0x1     |       1        |         23MHz         |
//    0x2     |       2        |         34MHz         |
//    0x3     |       3        |         46MHz         |
//    0x4     |       4        |         58MHz         |
//    0x5     |       5        |         69MHz         |
//    0x6     |       6        |         81MHz         |
//    0x7     |       7        |         93MHz         |
//    0x8     |       8        |        104MHz         |
//    0x9     |       9        |        122MHz         |
//    0xa     |      10        |        127MHz         |
//    0xb     |      11        |        139MHz         |
//    0xc     |      12        |        151MHz         |
//    0xd     |      13        |        162MHz         |
//    0xe     |      14        |        166MHz         |
//    0xf     |      15        |        166MHz         |
//------------------------------------------------------
#elif ISSI_DEVICE_IS25WP128
#define ISSI_FLASH_QUAD_ENABLE        0x40

#define ISSI_QUAD_FLASH_SET_DUMMY_CMD 0x48
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x09
#endif

//------------------------------------------------------
//    P[6:3]  |  dummy cycles  |   Quad IO Fast Read   |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//    0x0     |    6(default)  |        104MHz         |
//    0x1     |       1        |         33MHz         |
//    0x2     |       2        |         50MHz         |
//    0x3     |       3        |         60MHz         |
//    0x4     |       4        |         70MHz         |
//    0x5     |       5        |         84MHz         |
//    0x6     |       6        |        104MHz         |
//    0x7     |       7        |        115MHz         |
//    0x8     |       8        |        128MHz         |
//    0x9     |       9        |        133MHz         |
//    0xa     |      10        |        133MHz         |
//    0xb     |      11        |        133MHz         |
//    0xc     |      12        |        133MHz         |
//    0xd     |      13        |        133MHz         |
//    0xe     |      14        |        133MHz         |
//    0xf     |      15        |        133MHz         |
//------------------------------------------------------
#elif ISSI_DEVICE_IS25LP064A
#define ISSI_FLASH_QUAD_ENABLE        0x40

#define ISSI_QUAD_FLASH_SET_DUMMY_CMD 0xF0
#if MFB_FLASH_USE_DEFAULT_DUMMY
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x06
#else
#define ISSI_QUAD_FLASH_DUMMY_CYCLES  0x08
#endif

//------------------------------------------------------
//    P[4:3]  |  dummy cycles  |   Quad IO Fast Read   |
//            |                |Quad IO Fast Read(QPI) |
//------------------------------------------------------
//    0x0     |    6(default)  |        104MHz         |
//    0x1     |       4        |         84MHz         |
//    0x2     |       8        |        133MHz         |
//    0x3     |      10        |        133MHz         |
//------------------------------------------------------
#endif

#if ISSI_DEVICE_IS25WX256
// 0xFF - Extended SPI (Default)
// 0xDF - Extended SPI without DQS
// 0xE7 - Octal DDR
// 0xC7 - Octal DDR without DQS
#define ISSI_OCTAL_FLASH_ENABLE_DDR_CMD     0xE7

//------------------------------------------------------------------------------
//   DC[7:0]  |  dummy cycles  |Octal I/O DDR(1S-8D-8D) |Octal I/O SDR(1S-8S-8S)|
//            |                |  Octal DDR(8S-8D-8D)   |                       |
//            |                |        BGA24           |                       |
//-------------------------------------------------------------------------------
//   0x00     |  16(default)   |        171MHz          |         166MHz        |
//   0x01     |      01        |         N/A            |          N/A          |
//   0x02     |      02        |         N/A            |          N/A          |
//   0x03     |      03        |         16MHz          |          16MHz        |
//   0x04     |      04        |         33MHz          |          33MHz        |
//   0x05     |      05        |         50MHz          |          50MHz        |
//   0x06     |      06        |         66MHz          |          66MHz        |
//   0x07     |      07        |         83MHz          |          75MHz        |
//   0x08     |      08        |         95MHz          |          85MHz        |
//   0x09     |      09        |        105MHz          |          95MHz        |
//   0x0a     |      10        |        114MHz          |         105MHz        |
//   0x0b     |      11        |        124MHz          |         116MHz        |
//   0x0c     |      12        |        133MHz          |         125MHz        |
//   0x0d     |      13        |        143MHz          |         133MHz        |
//   0x0e     |      14        |        152MHz          |         143MHz        |
//   0x0f     |      15        |        162MHz          |         152MHz        |
//   0x10     |      16        |        171MHz          |         166MHz        |
//   0x11     |      17        |        181MHz          |         166MHz        |
//   0x12     |      18        |        191MHz          |         166MHz        |
//   0x13     |      19        |        200MHz          |         166MHz        |
//   0x14     |      20        |        200MHz          |         166MHz        |
//   ...      |      ..        |        200MHz          |         166MHz        |
//   0x1E     |      30        |        200MHz          |         166MHz        |
//   0x1F     |  16(default)   |        171MHz          |         166MHz        |
//-------------------------------------------------------------------------------
#if MFB_FLASH_OPI_MODE_DISABLE
#define ISSI_OCTAL_FLASH_SET_DUMMY_CMD     0x00
#define ISSI_OCTAL_FLASH_DUMMY_CYCLES      0x10   // 166MHz SPI SDR
#else
#define ISSI_OCTAL_FLASH_SET_DUMMY_CMD     0x14
#define ISSI_OCTAL_FLASH_DUMMY_CYCLES      0x14   // 200MHz OPI DDR
#endif
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


#endif /* _MFB_NOR_FLASH_ISSI_H_ */
