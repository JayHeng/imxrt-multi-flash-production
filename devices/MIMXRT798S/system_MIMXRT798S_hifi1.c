/*
** ###################################################################
**     Processors:          MIMXRT798SGAWAR_hifi1
**                          MIMXRT798SGFOA_hifi1
**
**     Compiler:            Xtensa Compiler
**     Reference manual:    iMXRT700RM Rev.1, 08/2022
**     Version:             rev. 1.0, 2022-09-15
**     Build:               b231207
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2022-09-15)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MIMXRT798S
 * @version 1.0
 * @date 2023-12-07
 * @brief Device specific configuration file for MIMXRT798S
 *  (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInit (void)
{
    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void)
{
    /* iMXRT7xx systemCoreClockUpdate */
	/* TBD */


}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void)
{
    /* Void implementation of the weak function. */
}
