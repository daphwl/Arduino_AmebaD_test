/******************************************************************************
 *
 * Copyright(c) 2007 - 2017  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#ifndef __HALRF_DPK_8723F_H__
#define __HALRF_DPK_8723F_H__

#if (RTL8723F_SUPPORT == 1)
/*--------------------------Define Parameters-------------------------------*/
#define LOSS_VALUE 1
#define GAIN_VALUE 2
#define GL_BACK_VALUE 3
#define DPK_RF_PATH_NUM_8723F 2
#define DPK_BB_REG_NUM_8723F 15
#define DPK_RF_REG_NUM_8723F 9
#define DPK_PAS_CHK_DBG_8723F 0
#define DPK_REG_DBG_8723F 0
#define DPK_PAS_DBG_8723F 0
#define DPK_LMS_DBG_8723F 1
#define DPK_SRAM_IQ_DBG_8723F 0
#define DPK_SRAM_read_DBG_8723F 0
#define DPK_SRAM_write_DBG_8723F 0
#define DPK_PATH_A_8723F 1
#define DPK_PATH_B_8723F 1
#define DPK_ALL_PATHK_8723F 1

/*---------------------------End Define Parameters----------------------------*/

void dpk_enable_disable_8723f(void *dm_void);

void dpk_reload_8723f(void *dm_void);

void do_dpk_8723f(void *dm_void);

void dpk_track_8723f(void *dm_void);

#endif /* RTL8723F_SUPPORT */

#endif /*#ifndef __HALRF_DPK_8723F_H__*/
