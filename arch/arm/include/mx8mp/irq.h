/****************************************************************************
 * arch/arm/include/mx8mp/irq.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather, only indirectly
 * through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_MX8MP_IRQ_H
#define __ARCH_ARM_INCLUDE_MX8MP_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/irq.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* IRQ numbers.
 * The IRQ number corresponds vector number and hence map directly to
 * bits in the NVIC.  This does, however, waste several words of memory in
 * the IRQ to handle mapping tables.
 */

/* Processor Exceptions (vectors 0-15) */

#define MX8MP_IRQ_RESERVED      (0)   /* Reserved vector (only used with CONFIG_DEBUG_FEATURES)
                                       * Vector  0: Reset stack pointer value
                                       * Vector  1: Reset (not handler as an IRQ) */
#define MX8MP_IRQ_NMI           (2)   /* Vector  2: Non-Maskable Interrupt (NMI) */
#define MX8MP_IRQ_HARDFAULT     (3)   /* Vector  3: Hard fault */
#define MX8MP_IRQ_MEMFAULT      (4)   /* Vector  4: Memory management (MPU) */
#define MX8MP_IRQ_BUSFAULT      (5)   /* Vector  5: Bus fault */
#define MX8MP_IRQ_USAGEFAULT    (6)   /* Vector  6: Usage fault
                                       * Vectors 7-10: Reserved */
#define MX8MP_IRQ_SVCALL        (11)  /* Vector 11: SVC call */
#define MX8MP_IRQ_DBGMONITOR    (12)  /* Vector 12: Debug Monitor
                                       * Vector 13: Reserved */
#define MX8MP_IRQ_PENDSV        (14)  /* Vector 14: Pendable system service request */
#define MX8MP_IRQ_SYSTICK       (15)  /* Vector 15: System tick */

/* External interrupts (vectors >= 16).
 * These definitions are chip-specific
 */

#define MX8MP_IRQ_FIRST         (16)  /* Vector number of the first external interrupt */

#if defined(CONFIG_ARCH_CHIP_MX8MP)
#  include <arch/mx8mp/mx8mp_irq.h>
#else
/* The interrupt vectors for other parts are defined in other documents and
 * may or may not be the same as above (the family members are all very
 * similar).
 * This error just means that you have to look at the document and determine
 * for yourself if the vectors are the same.
 */

#  error "No IRQ numbers for this MX8Mx part"
#endif

#endif /* __ARCH_ARM_INCLUDE_MX8MP_IRQ_H */
