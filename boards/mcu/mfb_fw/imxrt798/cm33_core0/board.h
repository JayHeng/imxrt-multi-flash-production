/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"
#if defined(MIMXRT798S_cm33_core0_SERIES)
#include "fsl_xspi.h"
#include "fsl_power.h"
#include "fsl_glikey.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MIMXRT700-EVK"

/*! @brief The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE kSerialPort_Uart
#if (defined(MIMXRT798S_cm33_core0_SERIES) || defined(MIMXRT798S_hifi4_SERIES))
#define BOARD_DEBUG_UART_BASEADDR     (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE     0U
#define BOARD_DEBUG_UART_CLK_FREQ     CLOCK_GetLPFlexCommClkFreq(0)
#define BOARD_DEBUG_UART_CLK_ATTACH   kFCCLK0_to_FLEXCOMM0
#define BOARD_DEBUG_UART_FCCLK_DIV    kCLOCK_DivFcclk0Clk
#define BOARD_DEBUG_UART_FCCLK_ATTACH kOSC_CLK_to_FCCLK0
#define BOARD_UART_IRQ_HANDLER        LP_FLEXCOMM0_IRQHandler
#define BOARD_UART_IRQ                LP_FLEXCOMM0_IRQn
#elif (defined(MIMXRT798S_cm33_core1_SERIES) || defined(MIMXRT798S_hifi1_SERIES))
#define BOARD_DEBUG_UART_BASEADDR   (uint32_t) LPUART19
#define BOARD_DEBUG_UART_INSTANCE   19U
#define BOARD_DEBUG_UART_CLK_FREQ   CLOCK_GetLPFlexCommClkFreq(19)
#define BOARD_DEBUG_UART_CLK_ATTACH kSENSE_BASE_to_FLEXCOMM19
#define BOARD_DEBUG_UART_CLK_DIV    kCLOCK_DivLPFlexComm19Clk
#define BOARD_UART_IRQ_HANDLER      LP_FLEXCOMM19_IRQHandler
#define BOARD_UART_IRQ              LP_FLEXCOMM19_IRQn
#else
#error "Unsupported core!"
#endif

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/* Board RGB LED color mapping */
#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U
#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO0
#endif
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 18U
#endif
#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO0
#endif
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 17U
#endif

#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO8
#endif
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 6U
#endif

/* SSD1963 (TFT_PROTO_5) panel. */
/* RST pin. */
#define BOARD_SSD1963_RST_GPIO GPIO2
#define BOARD_SSD1963_RST_PIN  15
/* CS pin. */
#define BOARD_SSD1963_CS_GPIO GPIO2
#define BOARD_SSD1963_CS_PIN  0
/* D/C pin, also named RS pin. */
#define BOARD_SSD1963_RS_GPIO GPIO2
#define BOARD_SSD1963_RS_PIN  1
/* Touch panel. */
#define BOARD_SSD1963_TOUCH_I2C_BASEADDR   LPI2C8
#define BOARD_SSD1963_TOUCH_I2C_CLOCK_FREQ CLOCK_GetLPFlexCommClkFreq(8U)

/* MIPI panel. */
#define BOARD_MIPI_PANEL_TOUCH_I2C_BASEADDR   LPI2C8
#define BOARD_MIPI_PANEL_TOUCH_I2C_CLOCK_FREQ CLOCK_GetLPFlexCommClkFreq(8U)
/* RST pin. */
#define BOARD_MIPI_RST_GPIO GPIO3
#define BOARD_MIPI_RST_PIN  4
/* POWER pin .*/
#define BOARD_MIPI_POWER_GPIO GPIO1
#define BOARD_MIPI_POWER_PIN  10
/* Backlight pin. */
#define BOARD_MIPI_BL_GPIO GPIO1
#define BOARD_MIPI_BL_PIN  14
/* TE pin. */
#define BOARD_MIPI_TE_GPIO             GPIO3
#define BOARD_MIPI_TE_PIN              5
#define BOARD_MIPI_TE_GPIO_IRQn        GPIO30_IRQn
#define BOARD_MIPI_TE_GPIO_IRQ_Handler GPIO30_IRQHandler

#define LED_RED_INIT(output)                                           \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN)                         /*!< Enable target LED_RED */
#define LED_RED_ON()  GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN)   /*!< Turn on target LED_RED */
#define LED_RED_OFF() GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN)                  /*!< Toggle on target LED_RED1 */

#define LED_GREEN_INIT(output)                                             \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN)        /*!< Enable target LED_GREEN */
#define LED_GREEN_ON() \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN)    /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF() \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN)  /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

#define LED_BLUE_INIT(output)                                            \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN)        /*!< Enable target LED_BLUE */
#define LED_BLUE_ON()                                                                                \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN)    /*!< Turn on target LED_BLUE \
                                                                         */
#define LED_BLUE_OFF()                                                                                \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN)  /*!< Turn off target LED_BLUE \
                                                                         */
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

/* Board SW PIN */
#ifndef BOARD_SW5_GPIO /* User button 1 */
#define BOARD_SW5_GPIO GPIO0
#define BOARD_SW5_NAME "SW5"
#endif
#ifndef BOARD_SW5_GPIO_PIN
#define BOARD_SW5_GPIO_PIN 9U
#endif
#ifndef BOARD_SW6_GPIO /* User button 3 */
#define BOARD_SW6_GPIO GPIO8
#endif
#ifndef BOARD_SW6_GPIO_PIN
#define BOARD_SW6_GPIO_PIN 5U
#endif
#ifndef BOARD_SW7_GPIO /* User button 2 */
#define BOARD_SW7_GPIO GPIO1
#endif
#ifndef BOARD_SW7_GPIO_PIN
#define BOARD_SW7_GPIO_PIN 3U
#endif

/* USB PHY configuration */
#define BOARD_USB_PHY_D_CAL     (0x07U)
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#define BOARD_USB_PHY_TXCAL45DM (0x06U)

#define BOARD_ACCEL_I2C_BASEADDR LPI2C20

#define BOARD_CODEC_I2C_BASEADDR   LPI2C2
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetLPI2cClkFreq(2)
#define BOARD_CODEC_I2C_INSTANCE   2

#define BOARD_PMIC_I2C_BASEADDR   LPI2C15
#define BOARD_PMIC_I2C_CLOCK_FREQ CLOCK_GetLPI2cClkFreq(15)

/* Definitions for eRPC MU transport layer */
#if (defined(MIMXRT798S_cm33_core0_SERIES))
#define MU_BASE        MU1_MUA
#define MU_IRQ         MU1_A_IRQn
#define MU_IRQ_HANDLER MU1_A_IRQHandler
#elif (defined(MIMXRT798S_cm33_core1_SERIES))
#define MU_BASE        MU1_MUB
#define MU_IRQ         MU1_B_IRQn
#define MU_IRQ_HANDLER MU1_B_IRQHandler
#endif
#define MU_IRQ_PRIORITY (2)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(MIMXRT798S_cm33_core0_SERIES)
void BOARD_ConfigMPU(void);
void BOARD_Init16bitsPsRam(XSPI_Type *base);
/* Initializes the AHB Secure Controller, allow SRAM and Media access for masters. */
void BOARD_InitAHBSC(void);
void BOARD_XspiClockSafeConfig(void);
void GlikeyWriteEnable(GLIKEY_Type *base, uint8_t idx); /* Temporary API to unlock glikey protect. */
void GlikeyClearConfig(GLIKEY_Type *base);
AT_QUICKACCESS_SECTION_CODE(void BOARD_SetXspiClock(XSPI_Type *base, uint32_t src, uint32_t divider));
AT_QUICKACCESS_SECTION_CODE(void BOARD_DeinitXspi(XSPI_Type *base, CACHE64_CTRL_Type *cache));
AT_QUICKACCESS_SECTION_CODE(void BOARD_InitXspi(XSPI_Type *base, CACHE64_CTRL_Type *cache));
#endif

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_I2C_Send(LPI2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize);
status_t BOARD_I2C_Receive(LPI2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize);

void BOARD_PMIC_I2C_Init(void);
void BOARD_PMIC_I2C_Deinit(void);
status_t BOARD_PMIC_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_PMIC_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#if defined(MIMXRT798S_cm33_core0_SERIES)
void BOARD_MIPIPanelTouch_I2C_Init(void);
#endif
#endif /* SDK_I2C_BASED_COMPONENT_USED */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
