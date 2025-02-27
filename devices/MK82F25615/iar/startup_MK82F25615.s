; -------------------------------------------------------------------------
;  @file:    startup_MK82F25615.s
;  @purpose: CMSIS Cortex-M4 Core Device Startup File
;            MK82F25615
;  @version: 1.2
;  @date:    2015-7-29
;  @build:   b200320
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2020 NXP
; All rights reserved.
;
; SPDX-License-Identifier: BSD-3-Clause
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__iar_init$$done:              ; The vector table is not needed
                      ; until after copy initialization is done

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler                                   ;NMI Handler
        DCD     HardFault_Handler                             ;Hard Fault Handler
        DCD     MemManage_Handler                             ;MPU Fault Handler
        DCD     BusFault_Handler                              ;Bus Fault Handler
        DCD     UsageFault_Handler                            ;Usage Fault Handler
__vector_table_0x1c
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     SVC_Handler                                   ;SVCall Handler
        DCD     DebugMon_Handler                              ;Debug Monitor Handler
        DCD     0                                             ;Reserved
        DCD     PendSV_Handler                                ;PendSV Handler
        DCD     SysTick_Handler                               ;SysTick Handler

                                                              ;External Interrupts
        DCD     DMA0_DMA16_IRQHandler                         ;DMA channel 0,16 transfer complete
        DCD     DMA1_DMA17_IRQHandler                         ;DMA channel 1,17 transfer complete
        DCD     DMA2_DMA18_IRQHandler                         ;DMA channel 2,18 transfer complete
        DCD     DMA3_DMA19_IRQHandler                         ;DMA channel 3,19 transfer complete
        DCD     DMA4_DMA20_IRQHandler                         ;DMA channel 4,20 transfer complete
        DCD     DMA5_DMA21_IRQHandler                         ;DMA channel 5,21 transfer complete
        DCD     DMA6_DMA22_IRQHandler                         ;DMA channel 6,22 transfer complete
        DCD     DMA7_DMA23_IRQHandler                         ;DMA channel 7,23 transfer complete
        DCD     DMA8_DMA24_IRQHandler                         ;DMA channel 8,24 transfer complete
        DCD     DMA9_DMA25_IRQHandler                         ;DMA channel 9,25 transfer complete
        DCD     DMA10_DMA26_IRQHandler                        ;DMA channel 10,26 transfer complete
        DCD     DMA11_DMA27_IRQHandler                        ;DMA channel 11,27 transfer complete
        DCD     DMA12_DMA28_IRQHandler                        ;DMA channel 12,28 transfer complete
        DCD     DMA13_DMA29_IRQHandler                        ;DMA channel 13,29 transfer complete
        DCD     DMA14_DMA30_IRQHandler                        ;DMA channel 14,30 transfer complete
        DCD     DMA15_DMA31_IRQHandler                        ;DMA channel 15,31 transfer complete
        DCD     DMA_Error_IRQHandler                          ;DMA channel 0 - 31 error
        DCD     MCM_IRQHandler                                ;MCM normal interrupt
        DCD     FTFA_IRQHandler                               ;FTFA command complete
        DCD     Read_Collision_IRQHandler                     ;FTFA read collision
        DCD     LVD_LVW_IRQHandler                            ;PMC controller low-voltage detect, low-voltage warning
        DCD     LLWU_IRQHandler                               ;Low leakage wakeup unit
        DCD     WDOG_EWM_IRQHandler                           ;Single interrupt vector for  WDOG and EWM
        DCD     TRNG0_IRQHandler                              ;True randon number generator
        DCD     I2C0_IRQHandler                               ;Inter-integrated circuit 0
        DCD     I2C1_IRQHandler                               ;Inter-integrated circuit 1
        DCD     SPI0_IRQHandler                               ;Serial peripheral Interface 0
        DCD     SPI1_IRQHandler                               ;Serial peripheral Interface 1
        DCD     I2S0_Tx_IRQHandler                            ;Integrated interchip sound 0 transmit interrupt
        DCD     I2S0_Rx_IRQHandler                            ;Integrated interchip sound 0 receive interrupt
        DCD     LPUART0_IRQHandler                            ;LPUART0 receive/transmit/error interrupt
        DCD     LPUART1_IRQHandler                            ;LPUART1 receive/transmit/error interrupt
        DCD     LPUART2_IRQHandler                            ;LPUART2 receive/transmit/error interrupt
        DCD     LPUART3_IRQHandler                            ;LPUART3 receive/transmit/error interrupt
        DCD     LPUART4_IRQHandler                            ;LPUART4 receive/transmit/error interrupt
        DCD     Reserved51_IRQHandler                         ;Reserved interrupt
        DCD     Reserved52_IRQHandler                         ;Reserved interrupt
        DCD     EMVSIM0_IRQHandler                            ;EMVSIM0 common interrupt
        DCD     EMVSIM1_IRQHandler                            ;EMVSIM1 common interrupt
        DCD     ADC0_IRQHandler                               ;Analog-to-digital converter 0
        DCD     CMP0_IRQHandler                               ;Comparator 0
        DCD     CMP1_IRQHandler                               ;Comparator 1
        DCD     FTM0_IRQHandler                               ;FlexTimer module 0 fault, overflow and channels interrupt
        DCD     FTM1_IRQHandler                               ;FlexTimer module 1 fault, overflow and channels interrupt
        DCD     FTM2_IRQHandler                               ;FlexTimer module 2 fault, overflow and channels interrupt
        DCD     CMT_IRQHandler                                ;Carrier modulator transmitter
        DCD     RTC_IRQHandler                                ;Real time clock
        DCD     RTC_Seconds_IRQHandler                        ;Real time clock seconds
        DCD     PIT0CH0_IRQHandler                            ;Periodic interrupt timer 0 channel 0
        DCD     PIT0CH1_IRQHandler                            ;Periodic interrupt timer 0 channel 1
        DCD     PIT0CH2_IRQHandler                            ;Periodic interrupt timer 0 channel 2
        DCD     PIT0CH3_IRQHandler                            ;Periodic interrupt timer 0 channel 3
        DCD     PDB0_IRQHandler                               ;Programmable delay block
        DCD     USB0_IRQHandler                               ;USB OTG interrupt
        DCD     USBDCD_IRQHandler                             ;USB charger detect
        DCD     Reserved71_IRQHandler                         ;Reserved interrupt
        DCD     DAC0_IRQHandler                               ;Digital-to-analog converter 0
        DCD     MCG_IRQHandler                                ;Multipurpose clock generator
        DCD     LPTMR0_LPTMR1_IRQHandler                      ;Single interrupt vector for  Low Power Timer 0 and 1
        DCD     PORTA_IRQHandler                              ;Port A pin detect interrupt
        DCD     PORTB_IRQHandler                              ;Port B pin detect interrupt
        DCD     PORTC_IRQHandler                              ;Port C pin detect interrupt
        DCD     PORTD_IRQHandler                              ;Port D pin detect interrupt
        DCD     PORTE_IRQHandler                              ;Port E pin detect interrupt
        DCD     SWI_IRQHandler                                ;Software interrupt
        DCD     SPI2_IRQHandler                               ;Serial peripheral Interface 2
        DCD     Reserved82_IRQHandler                         ;Reserved interrupt
        DCD     Reserved83_IRQHandler                         ;Reserved interrupt
        DCD     Reserved84_IRQHandler                         ;Reserved interrupt
        DCD     Reserved85_IRQHandler                         ;Reserved interrupt
        DCD     FLEXIO0_IRQHandler                            ;FLEXIO0
        DCD     FTM3_IRQHandler                               ;FlexTimer module 3 fault, overflow and channels interrupt
        DCD     Reserved88_IRQHandler                         ;Reserved interrupt
        DCD     Reserved89_IRQHandler                         ;Reserved interrupt
        DCD     I2C2_IRQHandler                               ;Inter-integrated circuit 2
        DCD     Reserved91_IRQHandler                         ;Reserved interrupt
        DCD     Reserved92_IRQHandler                         ;Reserved interrupt
        DCD     Reserved93_IRQHandler                         ;Reserved interrupt
        DCD     Reserved94_IRQHandler                         ;Reserved interrupt
        DCD     Reserved95_IRQHandler                         ;Reserved interrupt
        DCD     Reserved96_IRQHandler                         ;Reserved interrupt
        DCD     SDHC_IRQHandler                               ;Secured digital host controller
        DCD     Reserved98_IRQHandler                         ;Reserved interrupt
        DCD     Reserved99_IRQHandler                         ;Reserved interrupt
        DCD     Reserved100_IRQHandler                        ;Reserved interrupt
        DCD     Reserved101_IRQHandler                        ;Reserved interrupt
        DCD     Reserved102_IRQHandler                        ;Reserved interrupt
        DCD     TSI0_IRQHandler                               ;Touch Sensing Input
        DCD     TPM1_IRQHandler                               ;TPM1 single interrupt vector for all sources
        DCD     TPM2_IRQHandler                               ;TPM2 single interrupt vector for all sources
        DCD     Reserved106_IRQHandler                        ;Reserved interrupt
        DCD     I2C3_IRQHandler                               ;Inter-integrated circuit 3
        DCD     Reserved108_IRQHandler                        ;Reserved interrupt
        DCD     Reserved109_IRQHandler                        ;Reserved interrupt
        DCD     Reserved110_IRQHandler                        ;Reserved interrupt
        DCD     Reserved111_IRQHandler                        ;Reserved interrupt
        DCD     Reserved112_IRQHandler                        ;Reserved interrupt
        DCD     Reserved113_IRQHandler                        ;Reserved interrupt
        DCD     Reserved114_IRQHandler                        ;Reserved interrupt
        DCD     Reserved115_IRQHandler                        ;Reserved interrupt
        DCD     QuadSPI0_IRQHandler                           ;qspi
        DCD     Reserved117_IRQHandler                        ;Reserved interrupt
        DCD     Reserved118_IRQHandler                        ;Reserved interrupt
        DCD     Reserved119_IRQHandler                        ;Reserved interrupt
        DCD     LTC0_IRQHandler                               ;LP Trusted Cryptography
        DCD     Reserved121_IRQHandler                        ;Reserved interrupt
        DCD     Reserved122_IRQHandler                        ;Reserved interrupt
        DCD     DefaultISR                                    ;123
        DCD     DefaultISR                                    ;124
        DCD     DefaultISR                                    ;125
        DCD     DefaultISR                                    ;126
        DCD     DefaultISR                                    ;127
        DCD     DefaultISR                                    ;128
        DCD     DefaultISR                                    ;129
        DCD     DefaultISR                                    ;130
        DCD     DefaultISR                                    ;131
        DCD     DefaultISR                                    ;132
        DCD     DefaultISR                                    ;133
        DCD     DefaultISR                                    ;134
        DCD     DefaultISR                                    ;135
        DCD     DefaultISR                                    ;136
        DCD     DefaultISR                                    ;137
        DCD     DefaultISR                                    ;138
        DCD     DefaultISR                                    ;139
        DCD     DefaultISR                                    ;140
        DCD     DefaultISR                                    ;141
        DCD     DefaultISR                                    ;142
        DCD     DefaultISR                                    ;143
        DCD     DefaultISR                                    ;144
        DCD     DefaultISR                                    ;145
        DCD     DefaultISR                                    ;146
        DCD     DefaultISR                                    ;147
        DCD     DefaultISR                                    ;148
        DCD     DefaultISR                                    ;149
        DCD     DefaultISR                                    ;150
        DCD     DefaultISR                                    ;151
        DCD     DefaultISR                                    ;152
        DCD     DefaultISR                                    ;153
        DCD     DefaultISR                                    ;154
        DCD     DefaultISR                                    ;155
        DCD     DefaultISR                                    ;156
        DCD     DefaultISR                                    ;157
        DCD     DefaultISR                                    ;158
        DCD     DefaultISR                                    ;159
        DCD     DefaultISR                                    ;160
        DCD     DefaultISR                                    ;161
        DCD     DefaultISR                                    ;162
        DCD     DefaultISR                                    ;163
        DCD     DefaultISR                                    ;164
        DCD     DefaultISR                                    ;165
        DCD     DefaultISR                                    ;166
        DCD     DefaultISR                                    ;167
        DCD     DefaultISR                                    ;168
        DCD     DefaultISR                                    ;169
        DCD     DefaultISR                                    ;170
        DCD     DefaultISR                                    ;171
        DCD     DefaultISR                                    ;172
        DCD     DefaultISR                                    ;173
        DCD     DefaultISR                                    ;174
        DCD     DefaultISR                                    ;175
        DCD     DefaultISR                                    ;176
        DCD     DefaultISR                                    ;177
        DCD     DefaultISR                                    ;178
        DCD     DefaultISR                                    ;179
        DCD     DefaultISR                                    ;180
        DCD     DefaultISR                                    ;181
        DCD     DefaultISR                                    ;182
        DCD     DefaultISR                                    ;183
        DCD     DefaultISR                                    ;184
        DCD     DefaultISR                                    ;185
        DCD     DefaultISR                                    ;186
        DCD     DefaultISR                                    ;187
        DCD     DefaultISR                                    ;188
        DCD     DefaultISR                                    ;189
        DCD     DefaultISR                                    ;190
        DCD     DefaultISR                                    ;191
        DCD     DefaultISR                                    ;192
        DCD     DefaultISR                                    ;193
        DCD     DefaultISR                                    ;194
        DCD     DefaultISR                                    ;195
        DCD     DefaultISR                                    ;196
        DCD     DefaultISR                                    ;197
        DCD     DefaultISR                                    ;198
        DCD     DefaultISR                                    ;199
        DCD     DefaultISR                                    ;200
        DCD     DefaultISR                                    ;201
        DCD     DefaultISR                                    ;202
        DCD     DefaultISR                                    ;203
        DCD     DefaultISR                                    ;204
        DCD     DefaultISR                                    ;205
        DCD     DefaultISR                                    ;206
        DCD     DefaultISR                                    ;207
        DCD     DefaultISR                                    ;208
        DCD     DefaultISR                                    ;209
        DCD     DefaultISR                                    ;210
        DCD     DefaultISR                                    ;211
        DCD     DefaultISR                                    ;212
        DCD     DefaultISR                                    ;213
        DCD     DefaultISR                                    ;214
        DCD     DefaultISR                                    ;215
        DCD     DefaultISR                                    ;216
        DCD     DefaultISR                                    ;217
        DCD     DefaultISR                                    ;218
        DCD     DefaultISR                                    ;219
        DCD     DefaultISR                                    ;220
        DCD     DefaultISR                                    ;221
        DCD     DefaultISR                                    ;222
        DCD     DefaultISR                                    ;223
        DCD     DefaultISR                                    ;224
        DCD     DefaultISR                                    ;225
        DCD     DefaultISR                                    ;226
        DCD     DefaultISR                                    ;227
        DCD     DefaultISR                                    ;228
        DCD     DefaultISR                                    ;229
        DCD     DefaultISR                                    ;230
        DCD     DefaultISR                                    ;231
        DCD     DefaultISR                                    ;232
        DCD     DefaultISR                                    ;233
        DCD     DefaultISR                                    ;234
        DCD     DefaultISR                                    ;235
        DCD     DefaultISR                                    ;236
        DCD     DefaultISR                                    ;237
        DCD     DefaultISR                                    ;238
        DCD     DefaultISR                                    ;239
__Vectors_End

        SECTION FlashConfig:CODE
__FlashConfig
        DCD 0xFFFFFFFF
        DCD 0xFFFFFFFF
        DCD 0xFFFFFFFF
        DCD 0xFFFF3DFE
__FlashConfig_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =SystemInit
        BLX     R0
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK DMA0_DMA16_IRQHandler
        PUBWEAK DMA0_DMA16_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA0_DMA16_IRQHandler
        LDR     R0, =DMA0_DMA16_DriverIRQHandler
        BX      R0

        PUBWEAK DMA1_DMA17_IRQHandler
        PUBWEAK DMA1_DMA17_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA1_DMA17_IRQHandler
        LDR     R0, =DMA1_DMA17_DriverIRQHandler
        BX      R0

        PUBWEAK DMA2_DMA18_IRQHandler
        PUBWEAK DMA2_DMA18_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA2_DMA18_IRQHandler
        LDR     R0, =DMA2_DMA18_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_DMA19_IRQHandler
        PUBWEAK DMA3_DMA19_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_DMA19_IRQHandler
        LDR     R0, =DMA3_DMA19_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_DMA20_IRQHandler
        PUBWEAK DMA4_DMA20_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_DMA20_IRQHandler
        LDR     R0, =DMA4_DMA20_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_DMA21_IRQHandler
        PUBWEAK DMA5_DMA21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_DMA21_IRQHandler
        LDR     R0, =DMA5_DMA21_DriverIRQHandler
        BX      R0

        PUBWEAK DMA6_DMA22_IRQHandler
        PUBWEAK DMA6_DMA22_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA6_DMA22_IRQHandler
        LDR     R0, =DMA6_DMA22_DriverIRQHandler
        BX      R0

        PUBWEAK DMA7_DMA23_IRQHandler
        PUBWEAK DMA7_DMA23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA7_DMA23_IRQHandler
        LDR     R0, =DMA7_DMA23_DriverIRQHandler
        BX      R0

        PUBWEAK DMA8_DMA24_IRQHandler
        PUBWEAK DMA8_DMA24_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA8_DMA24_IRQHandler
        LDR     R0, =DMA8_DMA24_DriverIRQHandler
        BX      R0

        PUBWEAK DMA9_DMA25_IRQHandler
        PUBWEAK DMA9_DMA25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA9_DMA25_IRQHandler
        LDR     R0, =DMA9_DMA25_DriverIRQHandler
        BX      R0

        PUBWEAK DMA10_DMA26_IRQHandler
        PUBWEAK DMA10_DMA26_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA10_DMA26_IRQHandler
        LDR     R0, =DMA10_DMA26_DriverIRQHandler
        BX      R0

        PUBWEAK DMA11_DMA27_IRQHandler
        PUBWEAK DMA11_DMA27_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA11_DMA27_IRQHandler
        LDR     R0, =DMA11_DMA27_DriverIRQHandler
        BX      R0

        PUBWEAK DMA12_DMA28_IRQHandler
        PUBWEAK DMA12_DMA28_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA12_DMA28_IRQHandler
        LDR     R0, =DMA12_DMA28_DriverIRQHandler
        BX      R0

        PUBWEAK DMA13_DMA29_IRQHandler
        PUBWEAK DMA13_DMA29_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA13_DMA29_IRQHandler
        LDR     R0, =DMA13_DMA29_DriverIRQHandler
        BX      R0

        PUBWEAK DMA14_DMA30_IRQHandler
        PUBWEAK DMA14_DMA30_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA14_DMA30_IRQHandler
        LDR     R0, =DMA14_DMA30_DriverIRQHandler
        BX      R0

        PUBWEAK DMA15_DMA31_IRQHandler
        PUBWEAK DMA15_DMA31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA15_DMA31_IRQHandler
        LDR     R0, =DMA15_DMA31_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Error_IRQHandler
        PUBWEAK DMA_Error_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Error_IRQHandler
        LDR     R0, =DMA_Error_DriverIRQHandler
        BX      R0

        PUBWEAK MCM_IRQHandler
        PUBWEAK FTFA_IRQHandler
        PUBWEAK Read_Collision_IRQHandler
        PUBWEAK LVD_LVW_IRQHandler
        PUBWEAK LLWU_IRQHandler
        PUBWEAK WDOG_EWM_IRQHandler
        PUBWEAK TRNG0_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C0_IRQHandler
        LDR     R0, =I2C0_DriverIRQHandler
        BX      R0

        PUBWEAK I2C1_IRQHandler
        PUBWEAK I2C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C1_IRQHandler
        LDR     R0, =I2C1_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_IRQHandler
        LDR     R0, =SPI0_DriverIRQHandler
        BX      R0

        PUBWEAK SPI1_IRQHandler
        PUBWEAK SPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_IRQHandler
        LDR     R0, =SPI1_DriverIRQHandler
        BX      R0

        PUBWEAK I2S0_Tx_IRQHandler
        PUBWEAK I2S0_Tx_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2S0_Tx_IRQHandler
        LDR     R0, =I2S0_Tx_DriverIRQHandler
        BX      R0

        PUBWEAK I2S0_Rx_IRQHandler
        PUBWEAK I2S0_Rx_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2S0_Rx_IRQHandler
        LDR     R0, =I2S0_Rx_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART0_IRQHandler
        PUBWEAK LPUART0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART0_IRQHandler
        LDR     R0, =LPUART0_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART1_IRQHandler
        PUBWEAK LPUART1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART1_IRQHandler
        LDR     R0, =LPUART1_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART2_IRQHandler
        PUBWEAK LPUART2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART2_IRQHandler
        LDR     R0, =LPUART2_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART3_IRQHandler
        PUBWEAK LPUART3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART3_IRQHandler
        LDR     R0, =LPUART3_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART4_IRQHandler
        PUBWEAK LPUART4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART4_IRQHandler
        LDR     R0, =LPUART4_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved51_IRQHandler
        PUBWEAK Reserved52_IRQHandler
        PUBWEAK EMVSIM0_IRQHandler
        PUBWEAK EMVSIM1_IRQHandler
        PUBWEAK ADC0_IRQHandler
        PUBWEAK CMP0_IRQHandler
        PUBWEAK CMP1_IRQHandler
        PUBWEAK FTM0_IRQHandler
        PUBWEAK FTM1_IRQHandler
        PUBWEAK FTM2_IRQHandler
        PUBWEAK CMT_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_Seconds_IRQHandler
        PUBWEAK PIT0CH0_IRQHandler
        PUBWEAK PIT0CH1_IRQHandler
        PUBWEAK PIT0CH2_IRQHandler
        PUBWEAK PIT0CH3_IRQHandler
        PUBWEAK PDB0_IRQHandler
        PUBWEAK USB0_IRQHandler
        PUBWEAK USBDCD_IRQHandler
        PUBWEAK Reserved71_IRQHandler
        PUBWEAK DAC0_IRQHandler
        PUBWEAK MCG_IRQHandler
        PUBWEAK LPTMR0_LPTMR1_IRQHandler
        PUBWEAK PORTA_IRQHandler
        PUBWEAK PORTB_IRQHandler
        PUBWEAK PORTC_IRQHandler
        PUBWEAK PORTD_IRQHandler
        PUBWEAK PORTE_IRQHandler
        PUBWEAK SWI_IRQHandler
        PUBWEAK SPI2_IRQHandler
        PUBWEAK SPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_IRQHandler
        LDR     R0, =SPI2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved82_IRQHandler
        PUBWEAK Reserved83_IRQHandler
        PUBWEAK Reserved84_IRQHandler
        PUBWEAK Reserved85_IRQHandler
        PUBWEAK FLEXIO0_IRQHandler
        PUBWEAK FLEXIO0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO0_IRQHandler
        LDR     R0, =FLEXIO0_DriverIRQHandler
        BX      R0

        PUBWEAK FTM3_IRQHandler
        PUBWEAK Reserved88_IRQHandler
        PUBWEAK Reserved89_IRQHandler
        PUBWEAK I2C2_IRQHandler
        PUBWEAK I2C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C2_IRQHandler
        LDR     R0, =I2C2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved91_IRQHandler
        PUBWEAK Reserved92_IRQHandler
        PUBWEAK Reserved93_IRQHandler
        PUBWEAK Reserved94_IRQHandler
        PUBWEAK Reserved95_IRQHandler
        PUBWEAK Reserved96_IRQHandler
        PUBWEAK SDHC_IRQHandler
        PUBWEAK SDHC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SDHC_IRQHandler
        LDR     R0, =SDHC_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved98_IRQHandler
        PUBWEAK Reserved99_IRQHandler
        PUBWEAK Reserved100_IRQHandler
        PUBWEAK Reserved101_IRQHandler
        PUBWEAK Reserved102_IRQHandler
        PUBWEAK TSI0_IRQHandler
        PUBWEAK TPM1_IRQHandler
        PUBWEAK TPM2_IRQHandler
        PUBWEAK Reserved106_IRQHandler
        PUBWEAK I2C3_IRQHandler
        PUBWEAK I2C3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C3_IRQHandler
        LDR     R0, =I2C3_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved108_IRQHandler
        PUBWEAK Reserved109_IRQHandler
        PUBWEAK Reserved110_IRQHandler
        PUBWEAK Reserved111_IRQHandler
        PUBWEAK Reserved112_IRQHandler
        PUBWEAK Reserved113_IRQHandler
        PUBWEAK Reserved114_IRQHandler
        PUBWEAK Reserved115_IRQHandler
        PUBWEAK QuadSPI0_IRQHandler
        PUBWEAK QuadSPI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QuadSPI0_IRQHandler
        LDR     R0, =QuadSPI0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved117_IRQHandler
        PUBWEAK Reserved118_IRQHandler
        PUBWEAK Reserved119_IRQHandler
        PUBWEAK LTC0_IRQHandler
        PUBWEAK Reserved121_IRQHandler
        PUBWEAK Reserved122_IRQHandler
        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA0_DMA16_DriverIRQHandler
DMA1_DMA17_DriverIRQHandler
DMA2_DMA18_DriverIRQHandler
DMA3_DMA19_DriverIRQHandler
DMA4_DMA20_DriverIRQHandler
DMA5_DMA21_DriverIRQHandler
DMA6_DMA22_DriverIRQHandler
DMA7_DMA23_DriverIRQHandler
DMA8_DMA24_DriverIRQHandler
DMA9_DMA25_DriverIRQHandler
DMA10_DMA26_DriverIRQHandler
DMA11_DMA27_DriverIRQHandler
DMA12_DMA28_DriverIRQHandler
DMA13_DMA29_DriverIRQHandler
DMA14_DMA30_DriverIRQHandler
DMA15_DMA31_DriverIRQHandler
DMA_Error_DriverIRQHandler
MCM_IRQHandler
FTFA_IRQHandler
Read_Collision_IRQHandler
LVD_LVW_IRQHandler
LLWU_IRQHandler
WDOG_EWM_IRQHandler
TRNG0_IRQHandler
I2C0_DriverIRQHandler
I2C1_DriverIRQHandler
SPI0_DriverIRQHandler
SPI1_DriverIRQHandler
I2S0_Tx_DriverIRQHandler
I2S0_Rx_DriverIRQHandler
LPUART0_DriverIRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
Reserved51_IRQHandler
Reserved52_IRQHandler
EMVSIM0_IRQHandler
EMVSIM1_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT0CH0_IRQHandler
PIT0CH1_IRQHandler
PIT0CH2_IRQHandler
PIT0CH3_IRQHandler
PDB0_IRQHandler
USB0_IRQHandler
USBDCD_IRQHandler
Reserved71_IRQHandler
DAC0_IRQHandler
MCG_IRQHandler
LPTMR0_LPTMR1_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
PORTE_IRQHandler
SWI_IRQHandler
SPI2_DriverIRQHandler
Reserved82_IRQHandler
Reserved83_IRQHandler
Reserved84_IRQHandler
Reserved85_IRQHandler
FLEXIO0_DriverIRQHandler
FTM3_IRQHandler
Reserved88_IRQHandler
Reserved89_IRQHandler
I2C2_DriverIRQHandler
Reserved91_IRQHandler
Reserved92_IRQHandler
Reserved93_IRQHandler
Reserved94_IRQHandler
Reserved95_IRQHandler
Reserved96_IRQHandler
SDHC_DriverIRQHandler
Reserved98_IRQHandler
Reserved99_IRQHandler
Reserved100_IRQHandler
Reserved101_IRQHandler
Reserved102_IRQHandler
TSI0_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
Reserved106_IRQHandler
I2C3_DriverIRQHandler
Reserved108_IRQHandler
Reserved109_IRQHandler
Reserved110_IRQHandler
Reserved111_IRQHandler
Reserved112_IRQHandler
Reserved113_IRQHandler
Reserved114_IRQHandler
Reserved115_IRQHandler
QuadSPI0_DriverIRQHandler
Reserved117_IRQHandler
Reserved118_IRQHandler
Reserved119_IRQHandler
LTC0_IRQHandler
Reserved121_IRQHandler
Reserved122_IRQHandler
DefaultISR
        B DefaultISR

        END
