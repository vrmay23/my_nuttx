/****************************************************************************
 * arch/x86/src/qemu/qemu_serial.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <nuttx/arch.h>
#include <nuttx/serial/uart_16550.h>

#include <arch/io.h>

#include "chip.h"
#include "x86_internal.h"

/* This is a "stub" file to support up_putc if no real serial driver is
 * configured.  Normally, drivers/serial/uart_16550.c provides the serial
 * driver for this platform.
 */

#ifdef USE_SERIALDRIVER

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: uart_getreg(), uart_putreg()
 *
 * Description:
 *   These functions must be provided by the processor-specific code in order
 *   to correctly access 16550 registers.
 *
 ****************************************************************************/

uart_datawidth_t uart_getreg(struct u16550_s *priv, unsigned int offset)
{
  return inb(priv->uartbase + offset);
}

void uart_putreg(struct u16550_s *priv,
                 unsigned int offset, uart_datawidth_t value)
{
  outb(value, priv->uartbase + offset);
}

#else /* USE_SERIALDRIVER */

/****************************************************************************
 * Name: up_putc
 *
 * Description:
 *   Provide priority, low-level access to support OS debug writes
 *
 ****************************************************************************/

void up_putc(int ch)
{
  x86_lowputc(ch);
}

#endif /* USE_SERIALDRIVER */

#ifdef USE_EARLYSERIALINIT
void x86_earlyserialinit(void)
{
  u16550_earlyserialinit();
}
#endif

#ifdef USE_SERIALDRIVER
void x86_serialinit(void)
{
  u16550_serialinit();
}
#endif
