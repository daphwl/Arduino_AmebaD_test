/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_flags.h
   * @brief     This file is used to config app functions.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BLE_CENTRAL_APP_FLAGS_H_
#define _BLE_CENTRAL_APP_FLAGS_H_

#include "platform_opts_bt.h"
#if UPPER_STACK_VERSION == VERSION_2019
#include <bt_flags.h>
#elif UPPER_STACK_VERSION == VERSION_2021
#include "upperstack_config.h"
#endif
#include <trace_app.h>
#include <app_common_flags.h>


/** @defgroup  CENTRAL_CLIENT_Config Central Client App Configuration
    * @brief This file is used to config app functions.
    * @{
    */
/*============================================================================*
 *                              Constants
 *============================================================================*/

/** @brief  Config APP LE link number */
#if defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B)
#define BLE_CENTRAL_APP_MAX_LINKS  3
#elif defined(CONFIG_PLATFORM_8710C)
#define BLE_CENTRAL_APP_MAX_LINKS  1
#endif

/** @brief  Config the discovery table number of gcs_client */
#define BLE_CENTRAL_APP_MAX_DISCOV_TABLE_NUM 40

/** @} */ /* End of group CENTRAL_CLIENT_Config */

#endif
