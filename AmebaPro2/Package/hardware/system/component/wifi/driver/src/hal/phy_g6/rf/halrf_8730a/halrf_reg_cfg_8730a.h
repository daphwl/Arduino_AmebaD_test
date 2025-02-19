/******************************************************************************
 *
 * Copyright(c) 2007 - 2021  Realtek Corporation.
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
#ifndef _HALRF_REG_CFG_8730A_H_
#define _HALRF_REG_CFG_8730A_H_

#ifdef RF_8730A_SUPPORT

void halrf_cfg_rf_radio_a_8730a(struct rf_info *rf, u32 addr, u32 data);
void halrf_cfg_rf_nctl_8730a(struct rf_info *rf, u32 addr, u32 mask, u32 data);

#endif
#endif /* RTL8730A_SUPPORT*/
