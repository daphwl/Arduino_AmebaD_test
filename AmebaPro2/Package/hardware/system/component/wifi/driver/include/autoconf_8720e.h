/******************************************************************************
 * Copyright (c) 2013-2016 Realtek Semiconductor Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#ifndef AUTOCONF_8720E_H
#define AUTOCONF_8720E_H

#ifndef CONFIG_RTL8720E
#define CONFIG_RTL8720E
#endif

#ifndef CONFIG_RTL8720E
#define CONFIG_RTL8720E
#endif
#undef RTL8720E_SUPPORT
#define RTL8720E_SUPPORT 1

/* Configure for bus */
#define CONFIG_AXI_HCI

/* For efuse or flash config start */
#define CONFIG_EFUSE_SEPARATE
/* For efuse or flash config end */

/* PHY layer band config */
#define CONFIG_DFS
#define NOT_SUPPORT_40M
/* 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160MHz, 4: 80+80MHz
* 2.4G use bit 0 ~ 3, 5G use bit 4 ~ 7
* 0x21 means enable 2.4G 40MHz & 5G 80MHz */
#define CONFIG_BW_MODE 0x00
#define SUPPORT_5G_CHANNEL
#define CONFIG_INIT_CHAN 1
/* PHY layer band config end */

/* For DM support */
#define RATE_ADAPTIVE_SUPPORT 0

/* Configurations for power saving */
#define CONFIG_WOWLAN
/* enable 1X code in lib_wlan as default (increase 380 bytes) */
#define CONFIG_EAP

/* For phydm configurations */
#define CONFIG_FW_C2H_PKT
#define PHYDM_LINUX_CODING_STYLE 1
#define PHYDM_NEW_INTERFACE 1
//#define CONFIG_BT_COEXIST
//#define CONFIG_WIFI_MESH 0

//#define RX_SHORTCUT
//#define TX_SHORTCUT

/* For 11 ax function */
#define USE_HALBB_HALRF 1  // 11 ax ic use halbb and halrf
//#define CONFIG_80211AX_HE
#ifdef CONFIG_80211AX_HE
#define MBSSID_SUPPORT
#endif

#define TXBD_PRE_MALLOC
#define RTL8720E_SPECIFIC
//#define CONFIG_SUPPORT_DYNAMIC_TXPWR  // rtw_phydm_fill_desc_dpt -> todo

/* config for AP mode */
#define AP_STA_NUM (5)  // reduce ram size, revert this when ddr or psram read
// Decrease STA due to memory limitation - Alex Fang
#define NUM_STA (2 + AP_STA_NUM)  // 2 + supported clients

#ifdef CONFIG_WIFI_VERIFY
#define DISABLE_BB_RF 1
#else
#define DISABLE_BB_RF 0
#endif

#ifdef CONFIG_MAC_LBK
#define INT_HANDLE_IN_ISR 1
#define CONFIG_LWIP_LAYER 0
#define CONFIG_WLAN_HAL_TEST
#define CONFIG_WLAN_HAL_RX_TASK
#define CONFIG_MAC_LOOPBACK_DRIVER_AMEBA 1
#endif

/* For FPGA and PXP test code */
#if defined(CONFIG_WIFI_VERIFY)
#define RTL8720E_WIFI_TEST 1  // remove this when verification complete
#endif

#define RTL8720E_WL_TODO

#define CONFIG_REG_ENABLE_KFREE 0  // 0: Depend on efuse(flash), 1: enable, 2: disable

#endif /*#ifndef AUTOCONF_8720E_H */

