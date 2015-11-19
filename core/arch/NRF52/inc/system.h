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
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define HW_IRQ_VECTORS 46

/* all ISRs by default are weakly linked to the default handler */
extern void Reset_IRQn_Handler(void);
extern void NonMaskableInt_IRQn_Handler(void);
extern void HardFault_IRQn_Handler(void);
extern void MemoryManagement_IRQn_Handler(void);
extern void BusFault_IRQn_Handler(void);
extern void UsageFault_IRQn_Handler(void);
extern void SVCall_IRQn_Handler(void);
extern void DebugMonitor_IRQn_Handler(void);
extern void PendSV_IRQn_Handler(void);
extern void SysTick_IRQn_Handler(void);
extern void POWER_CLOCK_IRQn_Handler(void);
extern void RADIO_IRQn_Handler(void);
extern void UARTE0_UART0_IRQn_Handler(void);
extern void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn_Handler(void);
extern void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn_Handler(void);
extern void NFCT_IRQn_Handler(void);
extern void GPIOTE_IRQn_Handler(void);
extern void SAADC_IRQn_Handler(void);
extern void TIMER0_IRQn_Handler(void);
extern void TIMER1_IRQn_Handler(void);
extern void TIMER2_IRQn_Handler(void);
extern void RTC0_IRQn_Handler(void);
extern void TEMP_IRQn_Handler(void);
extern void RNG_IRQn_Handler(void);
extern void ECB_IRQn_Handler(void);
extern void CCM_AAR_IRQn_Handler(void);
extern void WDT_IRQn_Handler(void);
extern void RTC1_IRQn_Handler(void);
extern void QDEC_IRQn_Handler(void);
extern void COMP_LPCOMP_IRQn_Handler(void);
extern void SWI0_EGU0_IRQn_Handler(void);
extern void SWI1_EGU1_IRQn_Handler(void);
extern void SWI2_EGU2_IRQn_Handler(void);
extern void SWI3_EGU3_IRQn_Handler(void);
extern void SWI4_EGU4_IRQn_Handler(void);
extern void SWI5_EGU5_IRQn_Handler(void);
extern void TIMER3_IRQn_Handler(void);
extern void TIMER4_IRQn_Handler(void);
extern void PWM0_IRQn_Handler(void);
extern void PDM_IRQn_Handler(void);
extern void MWU_IRQn_Handler(void);
extern void PWM1_IRQn_Handler(void);
extern void PWM2_IRQn_Handler(void);
extern void SPIM2_SPIS2_SPI2_IRQn_Handler(void);
extern void RTC2_IRQn_Handler(void);
extern void I2S_IRQn_Handler(void);

#endif/*__SYSTEM_H__*/
