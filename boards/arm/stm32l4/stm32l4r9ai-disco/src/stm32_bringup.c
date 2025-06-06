/****************************************************************************
 * boards/arm/stm32l4/stm32l4r9ai-disco/src/stm32_bringup.c
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

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <debug.h>
#include <string.h>
#include <stdlib.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <nuttx/fs/fs.h>

#include <stm32l4.h>
#include <stm32l4_uart.h>
#include <stm32l4_uid.h>

#include <arch/board/board.h>
#include <arch/board/boardctl.h>

#include <nuttx/drivers/drivers.h>
#include <nuttx/drivers/ramdisk.h>
#include <nuttx/i2c/i2c_master.h>

#include "stm32l4r9ai-disco.h"

/* Conditional logic in stm32l4r9ai-disco.h will determine if certain
 * features are supported.  Tests for these features need to be made
 * after includingstm32l4r9ai-disco.
 */

#ifdef HAVE_RTC_DRIVER
#  include <nuttx/timers/rtc.h>
#  include "stm32l4_rtc.h"
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_I2C
#  ifdef CONFIG_STM32L4_I2C1
static struct i2c_master_s *g_i2c1;
#  endif
#  ifdef CONFIG_STM32L4_I2C3
static struct i2c_master_s *g_i2c3;
#  endif
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int stm32_bringup(void)
{
#ifdef HAVE_RTC_DRIVER
  struct rtc_lowerhalf_s *rtclower;
#endif
  int ret = OK;

#ifdef HAVE_PROC
  /* mount the proc filesystem */

  syslog(LOG_INFO, "Mounting procfs to /proc\n");

  ret = nx_mount(NULL, CONFIG_NSH_PROC_MOUNTPOINT, "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to mount the PROC filesystem: %d\n", ret);
      return ret;
    }
#endif

#ifdef HAVE_RTC_DRIVER
  /* Instantiate the STM32 lower-half RTC driver */

  rtclower = stm32l4_rtc_lowerhalf();
  if (!rtclower)
    {
      serr("ERROR: Failed to instantiate the RTC lower-half driver\n");
      return -ENOMEM;
    }
  else
    {
      /* Bind the lower half driver and register the combined RTC driver
       * as /dev/rtc0
       */

      ret = rtc_initialize(0, rtclower);
      if (ret < 0)
        {
          serr("ERROR: Failed to bind/register the RTC driver: %d\n", ret);
          return ret;
        }
    }
#endif

#ifdef CONFIG_I2C
  i2cinfo("Initializing I2C buses\n");
#ifdef CONFIG_STM32L4_I2C1
  g_i2c1 = stm32l4_i2cbus_initialize(1);
#ifdef CONFIG_I2C_DRIVER
  i2c_register(g_i2c1, 1);
#endif
#endif

#ifdef CONFIG_STM32L4_I2C3
  g_i2c3 = stm32l4_i2cbus_initialize(3);
#ifdef CONFIG_I2C_DRIVER
  i2c_register(g_i2c3, 3);
#endif
#endif
#endif /* CONFIG_I2C */

#ifdef HAVE_USBHOST
  /* Initialize USB host operation.  stm32l4_usbhost_initialize() starts a
   * thread that will monitor for USB connection and disconnection events.
   */

  ret = stm32l4_usbhost_initialize();
  if (ret != OK)
    {
      udbg("ERROR: Failed to initialize USB host: %d\n", ret);
      return ret;
    }
#endif

#ifdef HAVE_USBMONITOR
  /* Start the USB Monitor */

  ret = usbmonitor_start(0, NULL);
  if (ret != OK)
    {
      udbg("ERROR: Failed to start USB monitor: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_ADC
  ainfo("Initializing ADC\n");

  stm32l4_adc_setup();
#ifdef CONFIG_STM32L4_DFSDM
  /* Initialize DFSDM and register its filters as additional ADC devices. */

  ret = stm32_dfsdm_setup();
  if (ret < 0)
    {
      aerr("ERROR: Failed to start DFSDM: %d\n", ret);
    }
#endif
#endif /* CONFIG_ADC */

#ifdef CONFIG_DAC
  ainfo("Initializing DAC\n");

  stm32l4_dac_setup();
#endif

  return ret;
}
