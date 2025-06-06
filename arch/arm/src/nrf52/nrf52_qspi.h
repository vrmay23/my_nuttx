/****************************************************************************
 * arch/arm/src/nrf52/nrf52_qspi.h
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

#ifndef __ARCH_ARM_SRC_NRF52_NRF52_QSPI_H
#define __ARCH_ARM_SRC_NRF52_NRF52_QSPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <nuttx/spi/qspi.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: nrf52_qspi_initialize
 *
 * Description:
 *   Initialize the selected QSPI port in master mode
 *
 * Input Parameters:
 *   intf - Interface number(must be zero)
 *
 * Returned Value:
 *   Valid QSPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct qspi_dev_s *nrf52_qspi_initialize(int intf);

#endif  /* __ARCH_ARM_SRC_NRF52_NRF52_QSPI_H */
