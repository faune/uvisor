/*
 * Copyright (c) 2013-2015, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <uvisor.h>
#include "halt.h"
#include "unvic.h"
#include "system.h"

/* all ISRs by default are weakly linked to the default handler */
void UVISOR_ALIAS(isr_default_sys_handler) NonMaskableInt_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) HardFault_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) MemoryManagement_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) BusFault_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) UsageFault_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) SVCall_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) DebugMonitor_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) PendSV_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_sys_handler) SysTick_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	POWER_CLOCK_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	RADIO_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	UARTE0_UART0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	NFCT_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	GPIOTE_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SAADC_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TIMER0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TIMER1_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TIMER2_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	RTC0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TEMP_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	RNG_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	ECB_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	CCM_AAR_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	WDT_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	RTC1_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	QDEC_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	COMP_LPCOMP_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI0_EGU0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI1_EGU1_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI2_EGU2_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI3_EGU3_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI4_EGU4_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SWI5_EGU5_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TIMER3_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	TIMER4_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	PWM0_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	PDM_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	MWU_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	PWM1_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	PWM2_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	SPIM2_SPIS2_SPI2_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	RTC2_IRQn_Handler(void);
void UVISOR_ALIAS(isr_default_handler)	I2S_IRQn_Handler(void);

/* vector table; it will be placed in Flash */
__attribute__((section(".isr")))
const TIsrVector g_isr_vector[ISR_VECTORS] =
{
        /* initial stack pointer */
        (TIsrVector)&__stack_top__,

        /* system interrupts */
        &main_entry,                         /* -15 */
        NonMaskableInt_IRQn_Handler,         /* -14 */
        HardFault_IRQn_Handler,              /* -13 */
        MemoryManagement_IRQn_Handler,       /* -12 */
        BusFault_IRQn_Handler,               /* -11 */
        UsageFault_IRQn_Handler,             /* -10 */
        isr_default_sys_handler,             /* - 9 */
        isr_default_sys_handler,             /* - 8 */
        isr_default_sys_handler,             /* - 7 */
        isr_default_sys_handler,             /* - 6 */
        SVCall_IRQn_Handler,                 /* - 5 */
        DebugMonitor_IRQn_Handler,           /* - 4 */
        isr_default_sys_handler,             /* - 3 */
        PendSV_IRQn_Handler,                 /* - 2 */
        SysTick_IRQn_Handler,                /* - 1 */

        /* peripheral interrupts */
	POWER_CLOCK_IRQn_Handler,                                  /*  0 */
	RADIO_IRQn_Handler,                                        /*  1 */
	UARTE0_UART0_IRQn_Handler,                                 /*  2 */
	SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn_Handler,            /*  3 */
	SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn_Handler,            /*  4 */
	NFCT_IRQn_Handler,                                         /*  5 */
	GPIOTE_IRQn_Handler,                                       /*  6 */
	SAADC_IRQn_Handler,                                        /*  7 */
	TIMER0_IRQn_Handler,                                       /*  8 */
	TIMER1_IRQn_Handler,                                       /*  9 */
	TIMER2_IRQn_Handler,                                       /*  10 */
	RTC0_IRQn_Handler,                                         /*  11 */
	TEMP_IRQn_Handler,                                         /*  12 */
	RNG_IRQn_Handler,                                          /*  13 */
	ECB_IRQn_Handler,                                          /*  14 */
	CCM_AAR_IRQn_Handler,                                      /*  15 */
	WDT_IRQn_Handler,                                          /*  16 */
	RTC1_IRQn_Handler,                                         /*  17 */
	QDEC_IRQn_Handler,                                         /*  18 */
	COMP_LPCOMP_IRQn_Handler,                                  /*  19 */
	SWI0_EGU0_IRQn_Handler,                                    /*  20 */
	SWI1_EGU1_IRQn_Handler,                                    /*  21 */
	SWI2_EGU2_IRQn_Handler,                                    /*  22 */
	SWI3_EGU3_IRQn_Handler,                                    /*  23 */
	SWI4_EGU4_IRQn_Handler,                                    /*  24 */
	SWI5_EGU5_IRQn_Handler,                                    /*  25 */
	TIMER3_IRQn_Handler,                                       /*  26 */
	TIMER4_IRQn_Handler,                                       /*  27 */
	PWM0_IRQn_Handler,                                         /*  28 */
	PDM_IRQn_Handler,                                          /*  29 */
	MWU_IRQn_Handler,                                          /*  32 */
	PWM1_IRQn_Handler,                                         /*  33 */
	PWM2_IRQn_Handler,                                         /*  34 */
	SPIM2_SPIS2_SPI2_IRQn_Handler,                             /*  35 */
	RTC2_IRQn_Handler,                                         /*  36 */
	I2S_IRQn_Handler,                                          /*  37 */

};

void UVISOR_NAKED UVISOR_NORETURN isr_default_sys_handler(void)
{
        /* the multiplexer will execute the correct handler depending on the IRQn */
        vmpu_sys_mux();
}

void UVISOR_NAKED UVISOR_NORETURN isr_default_handler(void)
{
        /* the multiplexer will execute the correct handler depending on the IRQn */
        unvic_isr_mux();
}
