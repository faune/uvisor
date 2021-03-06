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
#ifndef __UVISOR_LIB_BOX_CONFIG_H__
#define __UVISOR_LIB_BOX_CONFIG_H__

UVISOR_EXTERN const uint32_t __uvisor_mode;

#define UVISOR_DISABLED   0
#define UVISOR_PERMISSIVE 1
#define UVISOR_ENABLED    2

#define UVISOR_SET_MODE(mode) \
    UVISOR_SET_MODE_ACL_COUNT(mode, NULL, 0)

#define UVISOR_SET_MODE_ACL(mode, acl_list) \
    UVISOR_SET_MODE_ACL_COUNT(mode, acl_list, UVISOR_ARRAY_COUNT(acl_list))

#define UVISOR_SET_MODE_ACL_COUNT(mode, acl_list, acl_list_count) \
    uint8_t __attribute__((section(".keep.uvisor.bss.boxes"), aligned(32))) __reserved_stack[UVISOR_STACK_BAND_SIZE]; \
    \
    UVISOR_EXTERN const uint32_t __uvisor_mode = (mode); \
    \
    static const __attribute__((section(".keep.uvisor.cfgtbl"), aligned(4))) UvisorBoxConfig main_cfg = { \
        UVISOR_BOX_MAGIC, \
        UVISOR_BOX_VERSION, \
        0, \
        0, \
        acl_list, \
        acl_list_count \
    }; \
    \
    extern const __attribute__((section(".keep.uvisor.cfgtbl_ptr_first"), aligned(4))) void * const main_cfg_ptr = &main_cfg;

/* this macro selects an overloaded macro (variable number of arguments) */
#define __UVISOR_BOX_MACRO(_1, _2, _3, _4, NAME, ...) NAME

#define __UVISOR_BOX_CONFIG(box_name, acl_list, stack_size, context_size) \
    \
    uint8_t __attribute__((section(".keep.uvisor.bss.boxes"), aligned(32))) \
        box_name ## _reserved[UVISOR_STACK_SIZE_ROUND(((UVISOR_MIN_STACK(stack_size) + (context_size))*8)/6)]; \
    \
    static const __attribute__((section(".keep.uvisor.cfgtbl"), aligned(4))) UvisorBoxConfig box_name ## _cfg = { \
        UVISOR_BOX_MAGIC, \
        UVISOR_BOX_VERSION, \
        UVISOR_MIN_STACK(stack_size), \
        context_size, \
        acl_list, \
        UVISOR_ARRAY_COUNT(acl_list) \
    }; \
    \
    extern const __attribute__((section(".keep.uvisor.cfgtbl_ptr"), aligned(4))) void * const box_name ## _cfg_ptr = &box_name ## _cfg;

#define __UVISOR_BOX_CONFIG_NOCONTEXT(box_name, acl_list, stack_size) \
    __UVISOR_BOX_CONFIG(box_name, acl_list, stack_size, 0) \

#define __UVISOR_BOX_CONFIG_CONTEXT(box_name, acl_list, stack_size, context_type) \
    __UVISOR_BOX_CONFIG(box_name, acl_list, stack_size, sizeof(context_type)) \
    UVISOR_EXTERN context_type * const uvisor_ctx;

#define UVISOR_BOX_CONFIG(...) \
    __UVISOR_BOX_MACRO(__VA_ARGS__, __UVISOR_BOX_CONFIG_CONTEXT, \
                                    __UVISOR_BOX_CONFIG_NOCONTEXT)(__VA_ARGS__)

#endif /* __UVISOR_LIB_BOX_CONFIG_H__ */
