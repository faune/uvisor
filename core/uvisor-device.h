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
#ifndef __UVISOR_DEVICE_H__
#define __UVISOR_DEVICE_H__

#if   defined(ARCH_EFM32GG)
#  include <em_device.h>
#elif defined(ARCH_MK64F)
#  include <MK64F12.h>
#elif defined(ARCH_STM32F4)
#  include <stm32f4xx.h>
#elif defined(ARCH_NRF52)
#  include <nrf52.h>
#else
#  error "unknown ARCH in Makefile"
#endif

#endif/*__UVISOR_DEVICE_H__*/
