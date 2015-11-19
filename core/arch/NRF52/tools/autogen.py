#!/usr/bin/env python





import sys

template_system_h = """/*
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

#define HW_IRQ_VECTORS %i

/* all ISRs by default are weakly linked to the default handler */
%s
#endif/*__SYSTEM_H__*/
"""

template_system_c = """/*
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
%s
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
%s
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
"""



def genFiles():

    global template_system_h


    ### Generate system.h/.c from nrf52.h ###
    try:
        print 'Processing inc/nrf52.h ...'
        f=open('inc/nrf52.h', 'r')
        data=f.readlines()
        f.close()
    except OSError, err:
        print 'ERROR: %s' % err
        sys.exit(-1)

    body_h = ''
    body_c1 = ''
    body_c2 = ''
    count = 0
    for line in data:
        line=line.split('=')
        if line[0].strip().endswith('_IRQn'):
            body_h += 'extern void %s_Handler(void);\n' % line[0].strip()
            if line[0].strip().split('_')[0].isupper() is True:
                irqNum = int(''.join(line[1:]).split(',')[0][0:5], 10)
                body_c1 += 'void UVISOR_ALIAS(isr_default_handler)\t%s_Handler(void);\n' % line[0].strip()
                body_c2 += '\t%s_Handler,%s/*  %i */\n' % (line[0].strip(), ' '*(50-len(line[0].strip())), irqNum)
            count += 1

    # Write generated file
    print 'Writing inc/system.h ...'
    f=open('inc/system.h', 'w')
    f.write(template_system_h % (count, body_h))
    f.close()

    print 'Writing src/system.c ...'
    f=open('src/system.c', 'w')
    f.write(template_system_c % (body_c1, body_c2))
    f.close()
    ### Generate system.c from nrf52.h ###


if __name__ == '__main__':
    from optparse import OptionParser



    #Populate the parser
    cliDesc  = 'Generate nRF52 interrupt routine prototypes from nRF52 MDK header files'
    cliUsage = '%prog [options]'
    cliVer   = '$Revision$'
    optparser = OptionParser(description=cliDesc, usage=cliUsage, version=cliVer)
    
    optparser.add_option('-f', '--file', action='store', dest='file', type='str', default=None, help='Parse provided MDK file (default: None)')
    #optparser.add_option('-o', action='store', dest='output', type='str', default=None, help='Write to this file')
    (options, args) = optparser.parse_args()

    # Open outfile
    genFiles()

