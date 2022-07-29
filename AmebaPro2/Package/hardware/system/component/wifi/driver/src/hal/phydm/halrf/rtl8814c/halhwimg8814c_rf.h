/******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
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

/*Image2HeaderVersion: R3 1.5.5*/
#if (RTL8814C_SUPPORT == 1)
#ifndef __INC_MP_RF_HW_IMG_8814C_H
#define __INC_MP_RF_HW_IMG_8814C_H

/* Please add following compiler flags definition (#define CONFIG_XXX_DRV_DIS)
 * into driver source code to reduce code size if necessary.
 * #define CONFIG_8814C_DRV_DIS
 * #define CONFIG_8814C_TYPE0_DRV_DIS
 * #define CONFIG_8814C_TYPE1_DRV_DIS
 * #define CONFIG_8814C_TYPE2_DRV_DIS
 * #define CONFIG_8814C_TYPE3_DRV_DIS
 * #define CONFIG_8814C_TYPE4_DRV_DIS
 * #define CONFIG_8814C_TYPE5_DRV_DIS
 * #define CONFIG_8814C_TYPE6_DRV_DIS
 * #define CONFIG_8814C_TYPE8_DRV_DIS
 */

#define CONFIG_8814C
#ifdef CONFIG_8814C_DRV_DIS
    #undef CONFIG_8814C
#endif

#define CONFIG_8814C_TYPE0
#ifdef CONFIG_8814C_TYPE0_DRV_DIS
    #undef CONFIG_8814C_TYPE0
#endif

#define CONFIG_8814C_TYPE1
#ifdef CONFIG_8814C_TYPE1_DRV_DIS
    #undef CONFIG_8814C_TYPE1
#endif

#define CONFIG_8814C_TYPE2
#ifdef CONFIG_8814C_TYPE2_DRV_DIS
    #undef CONFIG_8814C_TYPE2
#endif

#define CONFIG_8814C_TYPE3
#ifdef CONFIG_8814C_TYPE3_DRV_DIS
    #undef CONFIG_8814C_TYPE3
#endif

#define CONFIG_8814C_TYPE4
#ifdef CONFIG_8814C_TYPE4_DRV_DIS
    #undef CONFIG_8814C_TYPE4
#endif

#define CONFIG_8814C_TYPE5
#ifdef CONFIG_8814C_TYPE5_DRV_DIS
    #undef CONFIG_8814C_TYPE5
#endif

#define CONFIG_8814C_TYPE6
#ifdef CONFIG_8814C_TYPE6_DRV_DIS
    #undef CONFIG_8814C_TYPE6
#endif

#define CONFIG_8814C_TYPE8
#ifdef CONFIG_8814C_TYPE8_DRV_DIS
    #undef CONFIG_8814C_TYPE8
#endif

/******************************************************************************
 *                           radioa.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radioa(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radioa(void);

/******************************************************************************
 *                           radiob.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radiob(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radiob(void);

/******************************************************************************
 *                           radioc.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radioc(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radioc(void);

/******************************************************************************
 *                           radiod.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radiod(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radiod(void);

/******************************************************************************
 *                           radiosyn0.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radiosyn0(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radiosyn0(void);

/******************************************************************************
 *                           radiosyn1.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_radiosyn1(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_radiosyn1(void);

/******************************************************************************
 *                           txpowertrack.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack(void);

/******************************************************************************
 *                           txpowertrack_type0.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type0(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type0(void);

/******************************************************************************
 *                           txpowertrack_type1.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type1(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type1(void);

/******************************************************************************
 *                           txpowertrack_type2.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type2(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type2(void);

/******************************************************************************
 *                           txpowertrack_type3.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type3(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type3(void);

/******************************************************************************
 *                           txpowertrack_type4.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type4(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type4(void);

/******************************************************************************
 *                           txpowertrack_type5.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type5(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type5(void);

/******************************************************************************
 *                           txpowertrack_type6.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type6(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type6(void);

/******************************************************************************
 *                           txpowertrack_type8.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpowertrack_type8(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpowertrack_type8(void);

/******************************************************************************
 *                           txpwr_lmt.TXT
 ******************************************************************************/

/* tc: Test Chip, mp: mp Chip*/
void
odm_read_and_config_mp_8814c_txpwr_lmt(struct dm_struct *dm);
u32 odm_get_version_mp_8814c_txpwr_lmt(void);

#endif
#endif /* end of HWIMG_SUPPORT*/

