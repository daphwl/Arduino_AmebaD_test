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

#ifndef __HALRF_TXGAPK_8730A_H__
#define __HALRF_TXGAPK_8730A_H__

#if (RTL8730A_SUPPORT == 1)
/*--------------------------Define Parameters-------------------------------*/
#define D_CLR_8730A 0
#define DIFFK_EN_8730A 1
#define TAK_EN_8730A 2
#define GAPK_RF_PATH_NUM_8730A 2
#define GAPK_BB_REG_NUM_8730A 6
#define GAPK_RF_REG_NUM_8730A 8
#define GAPK_REG_DBG_8730A 0
#define GAPK_PSD_PWR_DBG_8730A 1
#define GAPK_TRACK_TABLE_8730A 1
#define GAPK_POWER_TABLE_8730A 0 /*disable power table gapk*/

/*---------------------------End Define Parameters----------------------------*/

//void halrf_txgapk_reload_tx_gain_8730a(void *dm_void);

void halrf_txgapk_8730a(struct dm_struct *dm);

#endif /* RTL8730A_SUPPORT */
#endif /*#ifndef __HALRF_TXGAPK_8730A_H__*/
