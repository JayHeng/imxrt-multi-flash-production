/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MIMXRT798SGAWAR_cm33_core0) || defined(CPU_MIMXRT798SGFOA_cm33_core0))

#define MIMXRT798S_cm33_core0_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT798S_cm33_core0.h"
/* CPU specific feature definitions */
#include "MIMXRT798S_cm33_core0_features.h"

#elif (defined(CPU_MIMXRT798SGAWAR_cm33_core1) || defined(CPU_MIMXRT798SGFOA_cm33_core1))

#define MIMXRT798S_cm33_core1_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT798S_cm33_core1.h"
/* CPU specific feature definitions */
#include "MIMXRT798S_cm33_core1_features.h"

#elif (defined(CPU_MIMXRT798SGAWAR_hifi4) || defined(CPU_MIMXRT798SGFOA_hifi4))

#define MIMXRT798S_hifi4_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT798S_hifi4.h"
/* CPU specific feature definitions */
#include "MIMXRT798S_hifi4_features.h"

#elif (defined(CPU_MIMXRT798SGAWAR_hifi1) || defined(CPU_MIMXRT798SGFOA_hifi1))

#define MIMXRT798S_hifi1_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT798S_hifi1.h"
/* CPU specific feature definitions */
#include "MIMXRT798S_hifi1_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
