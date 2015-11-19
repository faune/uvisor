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

#define HALT_LED_PIN 17

void halt_led(THaltError reason)
{
    uint32_t toggle;
    volatile uint32_t delay;

    int flag;

    /* Configure LED pin as output */
    NRF_P0->DIRSET = (1UL << HALT_LED_PIN);

    flag = 0;
    while(1)
    {
        for(toggle = 0; toggle < 2 * (uint32_t) reason; toggle++)
        {
            /* toggle LED pin */
	    uint32_t gpio_state = NRF_P0->OUT;
	    NRF_P0->OUTSET = (1UL << (HALT_LED_PIN + (flag ? 16 : 0))) & ~gpio_state;
	    NRF_P0->OUTCLR = (1UL << (HALT_LED_PIN + (flag ? 16 : 0))) & gpio_state;
            flag = !flag;
            for(delay = 0; delay < HALT_INTRA_PATTERN_DELAY; delay++);
        }
        for(delay = 0; delay < HALT_INTER_PATTERN_DELAY; delay++);
    }
}
