/****************************************************************************
 * arch/x86_64/include/limits.h
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

#ifndef __ARCH_X86_64_INCLUDE_LIMITS_H
#define __ARCH_X86_64_INCLUDE_LIMITS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/* Include architecture-specific limits */

#ifdef CONFIG_ARCH_INTEL64
#  include <arch/intel64/limits.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#endif /* __ARCH_X86_64_INCLUDE_LIMITS_H */
