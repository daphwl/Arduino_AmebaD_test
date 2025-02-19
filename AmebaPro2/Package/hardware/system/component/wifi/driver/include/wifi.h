/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef _WIFI_H_
#define _WIFI_H_

#include <rtw_byteorder.h>
#include <wlan_basic_types.h>


#ifdef BIT
//#error	"BIT define occurred earlier elsewhere!\n"
#undef BIT
#endif
#define BIT(x)	(1U << (x))

#ifdef CONFIG_CONCURRENT_MODE
#define MACID_NUM_SW_LIMIT ((NUM_STA) + 2)
#else
#define MACID_NUM_SW_LIMIT NUM_STA
#endif //CONFIG_CONCURRENT_MODE

#define WLAN_ETHHDR_LEN		14
#define WLAN_ETHADDR_LEN	6
#define WLAN_IEEE_OUI_LEN	3
#define WLAN_ADDR_LEN		6
#define WLAN_CRC_LEN		4
#define WLAN_BSSID_LEN		6
#define WLAN_BSS_TS_LEN		8
#define WLAN_HDR_A3_LEN		24
#define WLAN_HDR_A4_LEN		30
#define WLAN_HDR_A3_QOS_LEN	26
#define WLAN_HDR_A4_QOS_LEN	32
#define WLAN_SSID_MAXLEN	32
#define WLAN_DATA_MAXLEN	2312

#define WLAN_A3_PN_OFFSET	24
#define WLAN_A4_PN_OFFSET	30

#ifdef CONFIG_RTK_MESH
// Define mesh header length, But 11s data 11s mgt frame header length different, So have two type.
#define WLAN_HDR_A4_MESH_DATA_LEN 34		// WLAN_HDR_A4_LEN + MeshHeader_Len(4 bytes)
#define WLAN_HDR_A6_MESH_DATA_LEN 46		// WLAN_HDR_A4_LEN + MeshHeader_Len(16 bytes)
#define WLAN_HDR_A4_MESH_DATA_LEN_QOS 36	// WLAN_HDR_A4_LEN + MeshHeader_Len(4 bytes) + QOS
#define WLAN_HDR_A6_MESH_DATA_LEN_QOS 48	// WLAN_HDR_A4_LEN + MeshHeader_Len(16 bytes) + QOS
// #define WLAN_HDR_A4_MESH_MGT_LEN 34		// always processed by daemon (raw socket)

#define WLAN_HDR_MAX_MESH_HDR_LEN	18
#endif // CONFIG_RTK_MESH

#define WLAN_MIN_ETHFRM_LEN	60
#if WIFI_LOGO_CERTIFICATION
#define WLAN_MAX_ETHFRM_LEN	4000
#else
#define WLAN_MAX_ETHFRM_LEN	1514
#endif
#define WLAN_ETHHDR_LEN		14
#define WLAN_SNAP_HEADER	8
#define WLAN_MAX_IV_LEN		8
#define WLAN_MAX_ICV_LEN	8
#define WLAN_MAX_MIC_LEN	8
#ifdef CONFIG_RTK_MESH
#define WLAN_MAX_PROTOCOL_OVERHEAD (WLAN_HDR_A4_QOS_LEN+WLAN_MAX_IV_LEN\
						+WLAN_HDR_MAX_MESH_HDR_LEN+WLAN_SNAP_HEADER+WLAN_MAX_MIC_LEN+WLAN_MAX_ICV_LEN)	//=64+18
#else
#define WLAN_MAX_PROTOCOL_OVERHEAD (WLAN_HDR_A4_QOS_LEN+WLAN_MAX_IV_LEN\
						+WLAN_SNAP_HEADER+WLAN_MAX_MIC_LEN+WLAN_MAX_ICV_LEN)	//=64
#endif

#define P80211CAPTURE_VERSION	0x80211001

// This value is tested by WiFi 11n Test Plan 5.2.3.
// This test verifies the WLAN NIC can update the NAV through sending the CTS with large duration.
#define	WiFiNavUpperUs				30000	// 30 ms
// enum WLAN_IDX{
// 	WLAN0_IDX = 0,
// 	WLAN1_IDX,
// 	WLAN_UNDEF = -1
// };

#ifdef GREEN_HILL
#pragma pack(1)
#endif

enum WIFI_FRAME_TYPE {
	WIFI_MGT_TYPE  =	(0),
	WIFI_CTRL_TYPE =	(BIT(2)),
	WIFI_DATA_TYPE =	(BIT(3)),
	WIFI_QOS_DATA_TYPE	= (BIT(7) | BIT(3)),	//!< QoS Data
#ifdef CONFIG_RTK_MESH
	// Hardware of 8186 doesn't support it. Confirm by David, 2007/1/5
	WIFI_EXT_TYPE  =	(BIT(2) | BIT(3))	///< 11 is 802.11S Extended Type
#endif
};

enum WIFI_FRAME_SUBTYPE {

	// below is for mgt frame
	WIFI_ASSOCREQ       = (0 | WIFI_MGT_TYPE),
	WIFI_ASSOCRSP       = (BIT(4) | WIFI_MGT_TYPE),
	WIFI_REASSOCREQ     = (BIT(5) | WIFI_MGT_TYPE),
	WIFI_REASSOCRSP     = (BIT(5) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_PROBEREQ       = (BIT(6) | WIFI_MGT_TYPE),
	WIFI_PROBERSP       = (BIT(6) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_BEACON         = (BIT(7) | WIFI_MGT_TYPE),
	WIFI_ATIM           = (BIT(7) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_DISASSOC       = (BIT(7) | BIT(5) | WIFI_MGT_TYPE),
	WIFI_AUTH           = (BIT(7) | BIT(5) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_DEAUTH         = (BIT(7) | BIT(6) | WIFI_MGT_TYPE),
	WIFI_ACTION         = (BIT(7) | BIT(6) | BIT(4) | WIFI_MGT_TYPE),
#ifdef CONFIG_RTK_MESH
	WIFI_MULTIHOP_ACTION 	= (BIT(7) | BIT(6) | BIT(5) | BIT(4) | WIFI_MGT_TYPE),	// (Refer: Draft 1.06, Page 8, 7.1.3.1.2, Table 7-1, 2007/08/13 by popen)
#endif

	// below is for control frame
	WIFI_PSPOLL         = (BIT(7) | BIT(5) | WIFI_CTRL_TYPE),
	WIFI_RTS            = (BIT(7) | BIT(5) | BIT(4) | WIFI_CTRL_TYPE),
	WIFI_CTS            = (BIT(7) | BIT(6) | WIFI_CTRL_TYPE),
	WIFI_ACK            = (BIT(7) | BIT(6) | BIT(4) | WIFI_CTRL_TYPE),
	WIFI_CFEND          = (BIT(7) | BIT(6) | BIT(5) | WIFI_CTRL_TYPE),
	WIFI_CFEND_CFACK    = (BIT(7) | BIT(6) | BIT(5) | BIT(4) | WIFI_CTRL_TYPE),

	// below is for data frame
	WIFI_DATA           = (0 | WIFI_DATA_TYPE),
	WIFI_DATA_CFACK     = (BIT(4) | WIFI_DATA_TYPE),
	WIFI_DATA_CFPOLL    = (BIT(5) | WIFI_DATA_TYPE),
	WIFI_DATA_CFACKPOLL = (BIT(5) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_DATA_NULL      = (BIT(6) | WIFI_DATA_TYPE),
	WIFI_CF_ACK         = (BIT(6) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_CF_POLL        = (BIT(6) | BIT(5) | WIFI_DATA_TYPE),
	WIFI_CF_ACKPOLL     = (BIT(6) | BIT(5) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_QOS_DATA_NULL	= (BIT(6) | WIFI_QOS_DATA_TYPE),

#ifdef CONFIG_RTK_MESH    // (CAUTION!! Below not exist in D1.06!!)
	// Because hardware of RTL8186 doen's support TYPE=11, we use BIT(7) | WIFI_DATA_TYPE to
	// simulate TYPE=11, 2007/1/8
	WIFI_11S_MESH	    = (WIFI_QOS_DATA_TYPE),	// CAUTION!! Below not exist in D1.06!!
	WIFI_11S_MESH_ACTION = (BIT(5) | WIFI_11S_MESH),	///< Mesh Action
#endif
};

enum WIFI_REASON_CODE	{
	_RSON_RESERVED_					= 0,
	_RSON_UNSPECIFIED_				= 1,
	_RSON_AUTH_NO_LONGER_VALID_		= 2,
	_RSON_DEAUTH_STA_LEAVING_		= 3,
	_RSON_INACTIVITY_				= 4,
	_RSON_UNABLE_HANDLE_			= 5,
	_RSON_CLS2_						= 6,
	_RSON_CLS3_						= 7,
	_RSON_DISAOC_STA_LEAVING_		= 8,
	_RSON_ASOC_NOT_AUTH_			= 9,

	// WPA reason
	_RSON_INVALID_IE_				= 13,
	_RSON_MIC_FAILURE_				= 14,
	_RSON_4WAY_HNDSHK_TIMEOUT_		= 15,
	_RSON_GROUP_KEY_UPDATE_TIMEOUT_	= 16,
	_RSON_DIFF_IE_					= 17,
	_RSON_MLTCST_CIPHER_NOT_VALID_	= 18,
	_RSON_UNICST_CIPHER_NOT_VALID_	= 19,
	_RSON_AKMP_NOT_VALID_			= 20,
	_RSON_UNSUPPORT_RSNE_VER_		= 21,
	_RSON_INVALID_RSNE_CAP_			= 22,
	_RSON_IEEE_802DOT1X_AUTH_FAIL_	= 23,

	//belowing are Realtek definition
	_RSON_PMK_NOT_AVAILABLE_		= 24,
	_RSON_TDLS_TEAR_TOOFAR_			= 25,
	_RSON_TDLS_TEAR_UN_RSN_			= 26,
};

/* Reason codes (IEEE 802.11-2007, 7.3.1.7, Table 7-22) */
#if 0
#define WLAN_REASON_UNSPECIFIED 1
#define WLAN_REASON_PREV_AUTH_NOT_VALID 2
#define WLAN_REASON_DEAUTH_LEAVING 3
#define WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY 4
#define WLAN_REASON_DISASSOC_AP_BUSY 5
#define WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA 6
#define WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA 7
#define WLAN_REASON_DISASSOC_STA_HAS_LEFT 8
#define WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH 9
#endif
/* IEEE 802.11h */
#define WLAN_REASON_PWR_CAPABILITY_NOT_VALID 10
#define WLAN_REASON_SUPPORTED_CHANNEL_NOT_VALID 11
#if 0
/* IEEE 802.11i */
#define WLAN_REASON_INVALID_IE 13
#define WLAN_REASON_MICHAEL_MIC_FAILURE 14
#define WLAN_REASON_4WAY_HANDSHAKE_TIMEOUT 15
#define WLAN_REASON_GROUP_KEY_UPDATE_TIMEOUT 16
#define WLAN_REASON_IE_IN_4WAY_DIFFERS 17
#define WLAN_REASON_GROUP_CIPHER_NOT_VALID 18
#define WLAN_REASON_PAIRWISE_CIPHER_NOT_VALID 19
#define WLAN_REASON_AKMP_NOT_VALID 20
#define WLAN_REASON_UNSUPPORTED_RSN_IE_VERSION 21
#define WLAN_REASON_INVALID_RSN_IE_CAPAB 22
#define WLAN_REASON_IEEE_802_1X_AUTH_FAILED 23
#define WLAN_REASON_CIPHER_SUITE_REJECTED 24
#endif

enum WIFI_STATUS_CODE {
	_STATS_SUCCESSFUL_			= 0,
	_STATS_FAILURE_				= 1,
	_STATS_CAP_FAIL_			= 10,
	_STATS_NO_ASOC_				= 11,
	_STATS_OTHER_				= 12,
	_STATS_NO_SUPP_ALG_			= 13,
	_STATS_OUT_OF_AUTH_SEQ_		= 14,
	_STATS_CHALLENGE_FAIL_		= 15,
	_STATS_AUTH_TIMEOUT_		= 16,
	_STATS_UNABLE_HANDLE_STA_	= 17,
	_STATS_RATE_FAIL_			= 18,
	_STATS_REFUSED_TEMPORARILY_ = 30,
	_STATS_SAE_HASH_TO_ELEMENT_ = 126,
};

/* Status codes (IEEE 802.11-2007, 7.3.1.9, Table 7-23) */
#if 0
#define WLAN_STATUS_SUCCESS 0
#define WLAN_STATUS_UNSPECIFIED_FAILURE 1
#define WLAN_STATUS_CAPS_UNSUPPORTED 10
#define WLAN_STATUS_REASSOC_NO_ASSOC 11
#define WLAN_STATUS_ASSOC_DENIED_UNSPEC 12
#define WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG 13
#define WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION 14
#define WLAN_STATUS_CHALLENGE_FAIL 15
#define WLAN_STATUS_AUTH_TIMEOUT 16
#define WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA 17
#define WLAN_STATUS_ASSOC_DENIED_RATES 18
#endif
//entended
/* IEEE 802.11b */
#define WLAN_STATUS_ASSOC_DENIED_NOSHORT 19
#define WLAN_STATUS_ASSOC_DENIED_NOPBCC 20
#define WLAN_STATUS_ASSOC_DENIED_NOAGILITY 21
/* IEEE 802.11h */
#define WLAN_STATUS_SPEC_MGMT_REQUIRED 22
#define WLAN_STATUS_PWR_CAPABILITY_NOT_VALID 23
#define WLAN_STATUS_SUPPORTED_CHANNEL_NOT_VALID 24
/* IEEE 802.11g */
#define WLAN_STATUS_ASSOC_DENIED_NO_SHORT_SLOT_TIME 25
#define WLAN_STATUS_ASSOC_DENIED_NO_ER_PBCC 26
#define WLAN_STATUS_ASSOC_DENIED_NO_DSSS_OFDM 27
/* IEEE 802.11w */
#define WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY 30
#define WLAN_STATUS_ROBUST_MGMT_FRAME_POLICY_VIOLATION 31
/* IEEE 802.11i */
#define WLAN_STATUS_INVALID_IE 40
#define WLAN_STATUS_GROUP_CIPHER_NOT_VALID 41
#define WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID 42
#define WLAN_STATUS_AKMP_NOT_VALID 43
#define WLAN_STATUS_UNSUPPORTED_RSN_IE_VERSION 44
#define WLAN_STATUS_INVALID_RSN_IE_CAPAB 45
#define WLAN_STATUS_CIPHER_REJECTED_PER_POLICY 46
#define WLAN_STATUS_TS_NOT_CREATED 47
#define WLAN_STATUS_DIRECT_LINK_NOT_ALLOWED 48
#define WLAN_STATUS_DEST_STA_NOT_PRESENT 49
#define WLAN_STATUS_DEST_STA_NOT_QOS_STA 50
#define WLAN_STATUS_ASSOC_DENIED_LISTEN_INT_TOO_LARGE 51
/* IEEE 802.11r */
#define WLAN_STATUS_INVALID_FT_ACTION_FRAME_COUNT 52
#define WLAN_STATUS_INVALID_PMKID 53
#define WLAN_STATUS_INVALID_MDIE 54
#define WLAN_STATUS_INVALID_FTIE 55

#define WLAN_STATUS_SAE_HASH_TO_ELEMENT 126

enum WIFI_REG_DOMAIN {
	DOMAIN_FCC		= 1,
	DOMAIN_IC		= 2,
	DOMAIN_ETSI		= 3,
	DOMAIN_SPAIN	= 4,
	DOMAIN_FRANCE	= 5,
	DOMAIN_MKK		= 6,
	DOMAIN_ISRAEL	= 7,
	DOMAIN_MKK1		= 8,
	DOMAIN_MKK2		= 9,
	DOMAIN_MKK3		= 10,
	DOMAIN_MAX
};

#define _TO_DS_		BIT(8)
#define _FROM_DS_	BIT(9)
#define _MORE_FRAG_	BIT(10)
#define _RETRY_		BIT(11)
#define _PWRMGT_	BIT(12)
#define _MORE_DATA_	BIT(13)
#define _PRIVACY_	BIT(14)
#define _ORDER_			BIT(15)

#define SetToDs(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_TO_DS_); \
	} while(0)

#define GetToDs(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_TO_DS_)) != 0)

#define ClearToDs(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_TO_DS_)); \
	} while(0)

#define SetFrDs(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_FROM_DS_); \
	} while(0)

#define GetFrDs(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_FROM_DS_)) != 0)

#define ClearFrDs(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_FROM_DS_)); \
	} while(0)

#define get_tofr_ds(pframe)	((GetToDs(pframe) << 1) | GetFrDs(pframe))


#define SetMFrag(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_MORE_FRAG_); \
	} while(0)

#define GetMFrag(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_MORE_FRAG_)) != 0)

#define ClearMFrag(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_MORE_FRAG_)); \
	} while(0)

#define SetRetry(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_RETRY_); \
	} while(0)

#define GetRetry(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_RETRY_)) != 0)

#define ClearRetry(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_RETRY_)); \
	} while(0)

#define SetPwrMgt(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_PWRMGT_); \
	} while(0)

#define GetPwrMgt(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_PWRMGT_)) != 0)

#define ClearPwrMgt(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_PWRMGT_)); \
	} while(0)

#define SetMData(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_MORE_DATA_); \
	} while(0)

#define GetMData(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_MORE_DATA_)) != 0)

#define ClearMData(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_MORE_DATA_)); \
	} while(0)

#define SetPrivacy(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(_PRIVACY_); \
	} while(0)

#define GetPrivacy(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_PRIVACY_)) != 0)

#define ClearPrivacy(pbuf)	\
	do	{	\
		*(unsigned short *)(pbuf) &= (~cpu_to_le16(_PRIVACY_)); \
	} while(0)


#define GetOrder(pbuf)	(((*(unsigned short *)(pbuf)) & le16_to_cpu(_ORDER_)) != 0)

#define GetFrameType(pbuf)	(le16_to_cpu(*(unsigned short *)(pbuf)) & (BIT(3) | BIT(2)))

#define get_frame_sub_type(pbuf)	(cpu_to_le16(*(unsigned short *)(pbuf)) & (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2)))


#define set_frame_sub_type(pbuf, type) \
	do {    \
		*(unsigned short *)(pbuf) &= cpu_to_le16(~(BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2))); \
		*(unsigned short *)(pbuf) |= cpu_to_le16(type); \
	} while (0)

#define SetFrameType(pbuf,type)	\
	do { 	\
		*(unsigned short *)(pbuf) &= cpu_to_le16(~(BIT(3) | BIT(2))); \
		*(unsigned short *)(pbuf) |= cpu_to_le16(type); \
	} while(0)

#define GetFrameSubType(pbuf)	(cpu_to_le16(*(unsigned short *)(pbuf)) & (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2)))

#define SetFrameSubType(pbuf,type) \
	do {    \
		*(unsigned short *)(pbuf) &= cpu_to_le16(~(BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2))); \
		*(unsigned short *)(pbuf) |= cpu_to_le16(type); \
	} while(0)

#define GetSequence(pbuf)	(cpu_to_le16(*(unsigned short *)((SIZE_PTR)(pbuf) + 22)) >> 4)

#define GetFragNum(pbuf)	(cpu_to_le16(*(unsigned short *)((SIZE_PTR)(pbuf) + 22)) & 0x0f)

#define GetTupleCache(pbuf)	(cpu_to_le16(*(unsigned short *)((SIZE_PTR)(pbuf) + 22)))

#define SetFragNum(pbuf, num) \
	do {    \
		*(unsigned short *)((SIZE_PTR)(pbuf) + 22) = \
			((*(unsigned short *)((SIZE_PTR)(pbuf) + 22)) & le16_to_cpu(~(0x000f))) | \
			cpu_to_le16(0x0f & (num));     \
	} while(0)

#define SetSeqNum(pbuf, num) \
	do {    \
		*(unsigned short *)((SIZE_PTR)(pbuf) + 22) = \
			((*(unsigned short *)((SIZE_PTR)(pbuf) + 22)) & le16_to_cpu((unsigned short)~0xfff0)) | \
			le16_to_cpu((unsigned short)(0xfff0 & (num << 4))); \
	} while(0)
#define GetFrameControl(pbuf)(cpu_to_le16(*(unsigned short*)((SIZE_PTR)(pbuf))))
#define GetDuration(pbuf) (cpu_to_le16(*(unsigned short*)((SIZE_PTR)(pbuf) + 2)))
#define SetDuration(pbuf, dur) \
	do {    \
		*(unsigned short *)((SIZE_PTR)(pbuf) + 2) = cpu_to_le16(0xffff & (dur)); \
	} while(0)


#define SetPriority(pbuf, tid)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16(tid & 0xf); \
	} while(0)

#define GetPriority(pbuf)	((le16_to_cpu(*(unsigned short *)(pbuf))) & 0xf)

#define SetEOSP(pbuf, eosp)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16( (eosp & 1) << 4); \
	} while(0)

#define SetAckpolicy(pbuf, ack)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16( (ack & 3) << 5); \
	} while(0)

#define GetAckpolicy(pbuf) (((le16_to_cpu(*(unsigned short *)pbuf)) >> 5) & 0x3)

#define GetAMsdu(pbuf) (((le16_to_cpu(*(unsigned short *)pbuf)) >> 7) & 0x1)

#define SetAMsdu(pbuf, amsdu)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16( (amsdu & 1) << 7); \
	} while(0)

#define GetAid(pbuf)	(cpu_to_le16(*(unsigned short *)((SIZE_PTR)(pbuf) + 2)) & 0x3fff)

#define GetTid(pbuf)	(cpu_to_le16(*(unsigned short *)((SIZE_PTR)(pbuf) + (((GetToDs(pbuf)<<1)|GetFrDs(pbuf))==3?30:24))) & 0x000f)

#define GetAddr1Ptr(pbuf)	((unsigned char *)((SIZE_PTR)(pbuf) + 4))

#define GetAddr2Ptr(pbuf)	((unsigned char *)((SIZE_PTR)(pbuf) + 10))

#define GetAddr3Ptr(pbuf)	((unsigned char *)((SIZE_PTR)(pbuf) + 16))

#define GetAddr4Ptr(pbuf)	((unsigned char *)((SIZE_PTR)(pbuf) + 24))

//WIFI_WMM
#define GetQosControl(pbuf) (unsigned char *)((SIZE_PTR)(pbuf) + (((GetToDs(pbuf)<<1)|GetFrDs(pbuf))==3?30:24))

#ifdef CONFIG_RTK_MESH

#define SetMeshControlPresent(pbuf, present)	\
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16((present & 0x1) << 8); \
	} while(0)

#define SetMeshPsLevel(pbuf, pslevel) \
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16((pslevel & 0x1) << 9); \
	} while(0)

#define SetRSPI(pbuf, rspi) \
	do	{	\
		*(unsigned short *)(pbuf) |= cpu_to_le16((rspi & 0x1) << 10); \
	} while(0)

//#define GetMeshHeaderFlagWithoutQOS(pbuf)	((unsigned char *)(pbuf) + 30)
//#define GetGetMeshHeaderFlag(pbuf)			((unsigned char *)(pbuf) + 32)
#define GetMeshHeaderFlagWithoutQOS(pbuf)	(GetQosControl(pbuf)+0)
#define GetGetMeshHeaderFlag(pbuf)			(GetQosControl(pbuf)+2)


//#define GetMeshHeaderTTLWithOutQOS(pbuf)	((unsigned char *)(pbuf) + 31)  	// mesh header ttl
//#define GetMeshHeaderTTL(pbuf)				((unsigned char *)(pbuf) + 33)  	// mesh header ttl
#define GetMeshHeaderTTLWithOutQOS(pbuf)	(GetMeshHeaderFlagWithoutQOS(pbuf)+1)
#define GetMeshHeaderTTL(pbuf)				(GetGetMeshHeaderFlag(pbuf)+1)

//#define GetMeshHeaderSeqNumWithoutQOS(pbuf)	((unsigned short *)((unsigned long)(pbuf) + 32))	// Don't use cpu_to_le16(Other not use cpu_to_le16)
//#define GetMeshHeaderSeqNum(pbuf)			((unsigned short *)((unsigned long)(pbuf) + 34))	// Don't use cpu_to_le16(Other not use cpu_to_le16)
#define GetMeshHeaderSeqNumWithoutQOS(pbuf)	((unsigned int *)(GetMeshHeaderTTLWithOutQOS(pbuf)+1))
#define GetMeshHeaderSeqNum(pbuf)			((unsigned int *)(GetMeshHeaderTTL(pbuf)+1))

/*
#define SetMeshHeaderSeqNum(pbuf, num) \
	do {    \
		*(unsigned short *)((unsigned long)(pbuf) + 34) = \
			((*(unsigned short *)((unsigned long)(pbuf) + 34)) & le16_to_cpu((unsigned short)~0xffff)) | \
			le16_to_cpu((unsigned short)(0xffff & num )); \
	} while(0)
*/
#define SetMeshHeaderSeqNum(pbuf, num)		(*GetMeshHeaderSeqNum(pbuf) = (num))



//debug note:
//(u16 *)pHeader)[0] - flow control field
//((u16 *)((u8 *)pHeader + 24/30))[0] - QoS control field
//((u8 *)pHeader)[26/32] - mesh control field (i.e pQoS+2)

#define ETHER_ADDR_EQUAL(a, b)  	(((((const u16 *)a)[0] ^ ((const u16 *)b)[0]) | (((const u16 *)a)[1] ^ ((const u16 *)b)[1]) | (((const u16 *)a)[2] ^ ((const u16 *)b)[2])) == 0)
#define HAS_A4(pHeader)             ((((u16 *)pHeader)[0] & cpu_to_le16(_TO_DS_ | _FROM_DS_)) == cpu_to_le16(_TO_DS_ | _FROM_DS_))
#define HAS_A5(pHeader)             (HAS_A4(pHeader) ? (((u8 *)pHeader)[32] & cpu_to_le16(BIT1 | BIT0) == 1):(((u8 *)pHeader)[26] & cpu_to_le16(BIT1 | BIT0) == 1))
#define HAS_A6(pHeader)             (HAS_A5(pHeader))
#define HAS_TO_DS(pHeader)          ((((u16 *)pHeader)[0] & cpu_to_le16(_TO_DS_)) != 0)
#define HAS_FR_DS(pHeader)          ((((u16 *)pHeader)[0] & cpu_to_le16(_FROM_DS_)) != 0)
#define HAS_MESH_CTL_FIELD(pHeader) (HAS_A4(pHeader) ? ((((u16 *)((u8 *)pHeader + 30))[0] & cpu_to_le16(RTW_IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT)) == cpu_to_le16(RTW_IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT)):((((u16 *)((u8 *)pHeader + 24))[0] & cpu_to_le16(RTW_IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT)) == cpu_to_le16(RTW_IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT)))
#define IS_DATA(pHeader)            ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FTYPE_DATA)) == cpu_to_le16(RTW_IEEE80211_FTYPE_DATA))
#define IS_MGMT(pHeader)            ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT))
#define IS_ACTION(pHeader)          ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE | RTW_IEEE80211_FCTL_STYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT | RTW_IEEE80211_STYPE_ACTION))
#define IS_PROBE_REQ(pHeader)       ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE | RTW_IEEE80211_FCTL_STYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT | RTW_IEEE80211_STYPE_PROBE_REQ))
#define IS_PROBE_RSP(pHeader)       ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE | RTW_IEEE80211_FCTL_STYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT | RTW_IEEE80211_STYPE_PROBE_RESP))
#define IS_BEACON(pHeader)          ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE | RTW_IEEE80211_FCTL_STYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT | RTW_IEEE80211_STYPE_BEACON))
#define IS_AUTH(pHeader)            ((((u16 *)pHeader)[0] & cpu_to_le16(RTW_IEEE80211_FCTL_FTYPE | RTW_IEEE80211_FCTL_STYPE)) == cpu_to_le16(RTW_IEEE80211_FTYPE_MGMT | RTW_IEEE80211_STYPE_AUTH))

#endif // CONFIG_RTK_MESH

#define MacAddr_isBcst(addr) \
( \
	( (addr[0] == 0xff) && (addr[1] == 0xff) && \
		(addr[2] == 0xff) && (addr[3] == 0xff) && \
		(addr[4] == 0xff) && (addr[5] == 0xff) )  ? _TRUE : _FALSE \
)

__inline static int IS_MCAST(unsigned char *da)
{
	if ((*da) & 0x01) {
		return _TRUE;
	} else {
		return _FALSE;
	}
}

__inline static unsigned char *get_ta(unsigned char *pframe)
{
	unsigned char 	*ta;
	ta = GetAddr2Ptr(pframe);
	return ta;
}

__inline static unsigned char *get_da(unsigned char *pframe)
{
	unsigned char 	*da;
	unsigned int	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	switch (to_fr_ds) {
	case 0x00:	// ToDs=0, FromDs=0
		da = GetAddr1Ptr(pframe);
		break;
	case 0x01:	// ToDs=0, FromDs=1
		da = GetAddr1Ptr(pframe);
		break;
	case 0x02:	// ToDs=1, FromDs=0
		da = GetAddr3Ptr(pframe);
		break;
	default:	// ToDs=1, FromDs=1
		da = GetAddr3Ptr(pframe);
		break;
	}

	return da;
}


__inline static unsigned char *get_sa(unsigned char *pframe)
{
	unsigned char 	*sa;
	unsigned int	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	switch (to_fr_ds) {
	case 0x00:	// ToDs=0, FromDs=0
		sa = GetAddr2Ptr(pframe);
		break;
	case 0x01:	// ToDs=0, FromDs=1
		sa = GetAddr3Ptr(pframe);
		break;
	case 0x02:	// ToDs=1, FromDs=0
		sa = GetAddr2Ptr(pframe);
		break;
	default:	// ToDs=1, FromDs=1
		sa = GetAddr4Ptr(pframe);
		break;
	}

	return sa;
}

__inline static unsigned char *get_hdr_bssid(unsigned char *pframe)
{
	unsigned char 	*sa;
	unsigned int	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	switch (to_fr_ds) {
	case 0x00:	// ToDs=0, FromDs=0
		sa = GetAddr3Ptr(pframe);
		break;
	case 0x01:	// ToDs=0, FromDs=1
		sa = GetAddr2Ptr(pframe);
		break;
	case 0x02:	// ToDs=1, FromDs=0
		sa = GetAddr1Ptr(pframe);
		break;
	case 0x03:	// ToDs=1, FromDs=1
		sa = GetAddr1Ptr(pframe);
		break;
	default:
		sa = NULL; //???????
		break;
	}

	return sa;
}


__inline static int IsFrameTypeCtrl(unsigned char *pframe)
{
	if (WIFI_CTRL_TYPE == GetFrameType(pframe)) {
		return _TRUE;
	} else {
		return _FALSE;
	}
}
/*-----------------------------------------------------------------------------
			Below is for the security related definition
------------------------------------------------------------------------------*/
#define _RESERVED_FRAME_TYPE_	0
#define _SKB_FRAME_TYPE_		2
#define _PRE_ALLOCMEM_			1
#define _PRE_ALLOCHDR_			3
#define _PRE_ALLOCLLCHDR_		4
#define _PRE_ALLOCICVHDR_		5
#define _PRE_ALLOCMICHDR_		6

#define _SIFSTIME_				((priv->pmib->dot11BssType.net_work_type&WLAN_MD_11A)?16:10)
#define _ACKCTSLNG_				14	//14 bytes long, including crclng
#define _CRCLNG_				4

#define _ASOCREQ_IE_OFFSET_		4	// excluding wlan_hdr
#define	_ASOCRSP_IE_OFFSET_		6
#define _REASOCREQ_IE_OFFSET_	10
#define _REASOCRSP_IE_OFFSET_	6
#define _PROBEREQ_IE_OFFSET_	0
#define	_PROBERSP_IE_OFFSET_	12
#define _AUTH_IE_OFFSET_		6
#define _DEAUTH_IE_OFFSET_		0
#define _BEACON_IE_OFFSET_		12
#define _PUBLIC_ACTION_IE_OFFSET_	8

#define _FIXED_IE_LENGTH_			_BEACON_IE_OFFSET_

#ifdef CONFIG_RTK_MESH
#define	_MESH_SP_OPEN_IE_OFFSET_		4 // 2(cat + action) + 2(cap)
#define	_MESH_SP_CONFIRM_IE_OFFSET_		6 // 2(cat + action) + 2(cap) + 2(AID)
#define	_MESH_SP_CLOSE_IE_OFFSET_		2 // 2(cat + action)
#define	_MESH_HEADER_WITH_AE_		16	// mesh header with AE(Address Extension)
#define	_MESH_HEADER_WITHOUT_AE_	4	// mesh header without AE(Address Extension)
#define	_MESH_ACTIVE_FIELD_OFFSET_	2	// mesh active field Category+Action length
#endif

#define _SSID_IE_				0
#define _SUPPORTEDRATES_IE_	1
#define _DSSET_IE_				3
#define _TIM_IE_					5
#define _IBSS_PARA_IE_			6
#define _COUNTRY_IE_			7
#define _CHLGETXT_IE_			16
#define _SUPPORTED_CH_IE_		36
#define _CH_SWTICH_ANNOUNCE_	37	//Secondary Channel Offset
#define	_MEAS_REQ_IE_		38
#define	_MEAS_RSP_IE_		39
#define _RSN_IE_2_				48
#define _SSN_IE_1_					221
#define _ERPINFO_IE_			42
#define _EXT_SUPPORTEDRATES_IE_	50

#define _HT_CAPABILITY_IE_			45
#define _MDIE_					54
#define _FTIE_						55
#define _TIMEOUT_ITVL_IE_			56
#define _SRC_IE_				59
#define _HT_EXTRA_INFO_IE_			61
#define _HT_ADD_INFO_IE_			61 //_HT_EXTRA_INFO_IE_
#define _WAPI_IE_					68
#define _EID_RRM_EN_CAP_IE_			70

#define _RIC_Descriptor_IE_			75
#ifdef CONFIG_IEEE80211W
#define _MME_IE_					76 /* 802.11w Management MIC element */
#endif /* CONFIG_IEEE80211W */

#define _LINK_ID_IE_					101
#define _CH_SWITCH_TIMING_		104
#define _PTI_BUFFER_STATUS_		106
#define _EXT_CAP_IE_				127
#define _VENDOR_SPECIFIC_IE_		221
#define _RSNXE_IE_					244

#define	_RESERVED47_				47

typedef	enum _ELEMENT_ID {
	EID_SsId					= 0, /* service set identifier (0:32) */
	EID_SupRates				= 1, /* supported rates (1:8) */
	EID_FHParms				= 2, /* FH parameter set (5) */
	EID_DSParms				= 3, /* DS parameter set (1) */
	EID_CFParms				= 4, /* CF parameter set (6) */
	EID_Tim						= 5, /* Traffic Information Map (4:254) */
	EID_IbssParms				= 6, /* IBSS parameter set (2) */
	EID_Country					= 7, /* */

	/* Form 7.3.2: Information elements in 802.11E/D13.0, page 46. */
	EID_QBSSLoad				= 11,
	EID_EDCAParms				= 12,
	EID_TSpec					= 13,
	EID_TClass					= 14,
	EID_Schedule				= 15,
	/*  */

	EID_Ctext					= 16, /* challenge text*/
	EID_POWER_CONSTRAINT		= 32, /* Power Constraint*/

	/* vivi for WIFITest, 802.11h AP, 20100427 */
	/* 2010/12/26 MH The definition we can declare always!! */
	EID_PowerCap				= 33,
	EID_TPC				= 35,
	EID_SupportedChannels		= 36,
	EID_ChlSwitchAnnounce		= 37,

	EID_MeasureRequest			= 38, /* Measurement Request */
	EID_MeasureReport			= 39, /* Measurement Report */

	EID_ERPInfo				= 42,

	/* Form 7.3.2: Information elements in 802.11E/D13.0, page 46. */
	EID_TSDelay				= 43,
	EID_TCLASProc				= 44,
	EID_HTCapability			= 45,
	EID_QoSCap					= 46,
	/*  */

	EID_WPA2					= 48,
	EID_ExtSupRates			= 50,

	EID_FTIE					= 55, /* Defined in 802.11r */
	EID_Timeout				= 56, /* Defined in 802.11r */

	EID_SupRegulatory			= 59, /* Supported Requlatory Classes 802.11y */
	EID_HTInfo					= 61,
	EID_SecondaryChnlOffset		= 62,

	EID_BSSCoexistence			= 72, /* 20/40 BSS Coexistence */
	EID_BSSIntolerantChlReport	= 73,
	EID_OBSS					= 74, /* Overlapping BSS Scan Parameters */

	EID_LinkIdentifier			= 101, /* Defined in 802.11z */
	EID_WakeupSchedule		= 102, /* Defined in 802.11z */
	EID_ChnlSwitchTimeing		= 104, /* Defined in 802.11z */
	EID_PTIControl				= 105, /* Defined in 802.11z */
	EID_PUBufferStatus			= 106, /* Defined in 802.11z */

	EID_EXTCapability			= 127, /* Extended Capabilities */
	/* From S19:Aironet IE and S21:AP IP address IE in CCX v1.13, p16 and p18. */
	EID_Aironet					= 133, /* 0x85: Aironet Element for Cisco CCX */
	EID_CiscoIP					= 149, /* 0x95: IP Address IE for Cisco CCX */

	EID_CellPwr					= 150, /* 0x96: Cell Power Limit IE. Ref. 0x96. */

	EID_CCKM					= 156,

	EID_Vendor					= 221, /* 0xDD: Vendor Specific */

	EID_WAPI					= 68,
	EID_VHTCapability 			= 191, /* Based on 802.11ac D2.0 */
	EID_VHTOperation 			= 192, /* Based on 802.11ac D2.0 */
	EID_AID						= 197, /* Based on 802.11ac D4.0 */
	EID_OpModeNotification		= 199, /* Based on 802.11ac D3.0 */
} ELEMENT_ID, *PELEMENT_ID;


/*-----------------------------------------------------------------------------
            Below is for mesh related definition
------------------------------------------------------------------------------*/

/*used in Multihop category */
#define _PROXY_UPDATES_ACTION_ID_         0
#define _PROXY_UPDATES_CONFIRM_ACTION_ID_ 1

#define _SECONDARY_CHANNEL_OFFSET_IE_					62
#define _WLAN_MESH_CAP_IE_			   113	// WLAN mesh configuration IE
#define _MESH_ID_IE_				   114	// MESH ID infoemation element
#define _MESH_LINK_METRIC_REPORT_IE_   115	// Local link state announcement IE
#define _MESH_PEER_MGMT_IE_            117	// MESH peering managment IE
#define _MESH_CHANNEL_SWITCH_IE_       118
#define _MESH_AWAKE_WINDOW_IE_    119 //MESH awake window
#define _MESH_GANN_IE_	               125
#define _MESH_RANN_IE_	               126
#define _MESH_PREQ_IE_	               130
#define _MESH_PREP_IE_	               131
#define _MESH_PERR_IE_	               132
#define _PROXY_UPDATE_IE_			   137
#define _PROXY_UPDATE_CONFIRM_IE_	   138
#define _MESH_AMPE_IE_					139
#define _MESH_MIC_IE_					140

// CATUTION: below ALL undefine !!
#define _OFDM_PARAMETER_SET_IE_		   200
#define _NEIGHBOR_LIST_IE_			   205	// neighbor list IE
#define _UCG_SWITCH_ANNOU_IE_		   210
#define _MDAOP_ADVERTISMENTS_IE_	   211
#define _MOAOP_SET_TEARDOWN_IE_		   212
#define _PEER_LINK_OPEN_IE_			   223
#define _PEER_LINK_CONFIRM_IE_		   224
#define _PEER_LINK_CLOSE_IE_		   225

/* ---------------------------------------------------------------------------
					Below is the fixed elements...
-----------------------------------------------------------------------------*/
#define _AUTH_ALGM_NUM_			2
#define _AUTH_SEQ_NUM_			2
#define _BEACON_ITERVAL_		2
#define _CAPABILITY_			2
#define _CURRENT_APADDR_		6
#define _LISTEN_INTERVAL_		2
#define _RSON_CODE_				2
#define _ASOC_ID_				2
#define _STATUS_CODE_			2
#define _TIMESTAMP_				8

#define AUTH_ODD_TO				0
#define AUTH_EVEN_TO			1

#define WLAN_ETHCONV_ENCAP		1
#define WLAN_ETHCONV_RFC1042	2
#define WLAN_ETHCONV_8021h		3

#define cap_ESS BIT(0)
#define cap_IBSS BIT(1)
#define cap_CFPollable BIT(2)
#define cap_CFRequest BIT(3)
#define cap_Privacy BIT(4)
#define cap_ShortPremble BIT(5)
#define cap_PBCC	BIT(6)
#define cap_ChAgility	BIT(7)
#define cap_SpecMgmt	BIT(8)
#define cap_QoS	BIT(9)
#define cap_ShortSlot	BIT(10)

/*-----------------------------------------------------------------------------
				Below is the definition for 802.11i / 802.1x
------------------------------------------------------------------------------*/
#define _IEEE8021X_MGT_			1		// WPA
#define _IEEE8021X_PSK_			2		// WPA with pre-shared key

/*
#define _NO_PRIVACY_			0
#define _WEP_40_PRIVACY_		1
#define _TKIP_PRIVACY_			2
#define _WRAP_PRIVACY_			3
#define _CCMP_PRIVACY_			4
#define _WEP_104_PRIVACY_		5
#define _WEP_WPA_MIXED_PRIVACY_ 6	// WEP + WPA
*/

#ifdef CONFIG_IEEE80211W
#define _MME_IE_LENGTH_  18
#endif /* CONFIG_IEEE80211W */

/*-----------------------------------------------------------------------------
				Below is the definition for WMM
------------------------------------------------------------------------------*/
#define _WMM_IE_Length_				7  // for WMM STA
#define _WMM_Para_Element_Length_		24

#ifdef CONFIG_RTK_MESH

typedef struct _ieee80211_rann_ie_ {
	u8 rann_flags;
	u8 rann_hopcount;
	u8 rann_ttl;
	u8 rann_addr[6];
	u32 rann_seq;
	u32 rann_interval;
	u32 rann_metric;
} ieee80211_rann_ie;

typedef struct _ieee80211_ampe_ie_ {
	u8 selected_pairwise_suite[4];
	u8 local_nonce[32];
	u8 peer_nonce[32];
} ieee80211_ampe_ie;

typedef union _mesh_formation_info_ {
	struct {
		u8 connected_to_mesh_gate : 1;
		u8 number_of_peerings : 6;
		u8 connected_to_as : 1;
	};
	u8 u8Val;
} mesh_formation_info;

typedef union _mesh_capability_ {
	struct {
		u8 accepting_additional_mesh_peerings : 1;
		u8 mcca_supported : 1;
		u8 mcca_enabled : 1;
		u8 forwarding : 1;
		u8 mbac_enabled : 1;
		u8 tbtt_adjusting : 1;
		u8 mesh_power_save_level : 1;
		u8 reserved : 1;
	};
	u8 u8Val;
} mesh_capability;

//element ID: 113, length: 7
typedef union _Mesh_Configuration_IE_ {
	struct {
		u8 active_path_selection_protocol_identifier;
		u8 active_path_selection_metric_identifier;
		u8 congestion_control_mode_identifier;
		u8 synchronization_method_identifier;
		u8 authentication_protocol_identifier;
		mesh_formation_info mesh_formation_info;
		mesh_capability mesh_capability;
	};
	u8 Octets[7];
} mesh_config_ie;

//element ID: 117, length+ID: 5, 7, 9, 21, 23, or 25 p692
typedef struct _Mesh_Peering_Management_IE_ {
	u16 mesh_peering_protocol_identifier;
	u16 local_link_id;
	u16 peer_link_id; //conditional
	u16 reason_code; //conditional
	u8 choosen_pmk[16]; //optional
} mesh_peering_management_ie;

/* Parsed Information Elements */
typedef struct rtw_ieee802_11_elems_ext {
	u8 *ssid;
	u8 ssid_len;
	u8 *supp_rates;
	u8 supp_rates_len;
	u8 *fh_params;
	u8 fh_params_len;
	u8 *ds_params;
	u8 ds_params_len;
	u8 *cf_params;
	u8 cf_params_len;
	u8 *tim;
	u8 tim_len;
	u8 *ibss_params;
	u8 ibss_params_len;
	u8 *challenge;
	u8 challenge_len;
	u8 *erp_info;
	u8 erp_info_len;
	u8 *ext_supp_rates;
	u8 ext_supp_rates_len;
	u8 *wpa_ie;
	u8 wpa_ie_len;
	u8 *rsn_ie;
	u8 rsn_ie_len;
	u8 *wme;
	u8 wme_len;
	u8 *wme_tspec;
	u8 wme_tspec_len;
	u8 *wps_ie;
	u8 wps_ie_len;
	u8 *power_cap;
	u8 power_cap_len;
	u8 *supp_channels;
	u8 supp_channels_len;
	u8 *mdie;
	u8 mdie_len;
	u8 *ftie;
	u8 ftie_len;
	u8 *timeout_int;
	u8 timeout_int_len;
	u8 *ht_capabilities;
	u8 ht_capabilities_len;
	u8 *ht_operation;
	u8 ht_operation_len;
	//u8 *vendor_ht_cap;
	//u8 vendor_ht_cap_len;
	u8 *vendor_specific;
	u8 vendor_specific_len;
#ifdef CONFIG_RTK_MESH
	u8 mesh_id_len;
	u8 *mesh_id;
	u8 mesh_configuration_len;
	mesh_config_ie *mesh_configuration;
	u8 mesh_peering_mgmnt_len;
	u8 *mesh_peering_mgmnt;
	u8 mic_len;
	u8 *mic;
#endif //CONFIG_RTK_MESH
} dot_11_IEs;
#define SAE_AUTH_COMMIT                 1
#define SAE_AUTH_CONFIRM                2
#endif //CONFIG_RTK_MESH


/**
* struct rtw_ieee80211_ht_cap - HT capabilities
*
* This structure refers to "HT capabilities element" as
* described in 802.11n draft section 7.3.2.52
*/

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct rtw_ieee80211_ht_cap {
	unsigned short 	cap_info;
	unsigned char 	ampdu_params_info;
	unsigned char 	supp_mcs_set[16];
	unsigned short 	extended_ht_cap_info;
	unsigned int		tx_BF_cap_info;
	unsigned char	       antenna_selection_info;
} RTW_PACK_STRUCT_STRUCT;
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif


/**
 * struct rtw_ieee80211_ht_cap - HT additional information
 *
 * This structure refers to "HT information element" as
 * described in 802.11n draft section 7.3.2.53
 */
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct ieee80211_ht_addt_info {
	unsigned char 	control_chan;
	unsigned char		ht_param;
	unsigned short	operation_mode;
	unsigned short	stbc_param;
	unsigned char		basic_set[16];
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct HT_caps_element {
	union {
		struct {
			unsigned short	HT_caps_info;
			unsigned char	AMPDU_para;
			unsigned char	MCS_rate[16];
			unsigned short	HT_ext_caps;
			unsigned int	Beamforming_caps;
			unsigned char	ASEL_caps;
		}
#ifdef __CC_ARM
		__attribute__((packed))
#endif
		HT_cap_element;
		unsigned char HT_cap[26];
	}
#ifdef __CC_ARM
	__attribute__((packed))
#endif
	u;
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct HT_info_element {
	unsigned char	primary_channel;
	unsigned char	infos[5];
	unsigned char	MCS_rate[16];
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif


#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct AC_param {
	unsigned char		ACI_AIFSN;
	unsigned char		CW;
	unsigned short	TXOP_limit;
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct WMM_para_element {
	unsigned char		QoS_info;
	unsigned char		reserved;
	struct AC_param	ac_param[4];
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct ADDBA_request {
	unsigned char		dialog_token;
	unsigned short	BA_para_set;
	unsigned short	BA_timeout_value;
	unsigned short	BA_starting_seqctrl;
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif

typedef enum _HT_CAP_AMPDU_FACTOR {
	MAX_AMPDU_FACTOR_8K		= 0,
	MAX_AMPDU_FACTOR_16K	= 1,
	MAX_AMPDU_FACTOR_32K	= 2,
	MAX_AMPDU_FACTOR_64K	= 3,
} HT_CAP_AMPDU_FACTOR;

/* 802.11n HT capabilities masks */
#define IEEE80211_HT_CAP_SUP_WIDTH		0x0002
#define IEEE80211_HT_CAP_SM_PS			0x000C
#define IEEE80211_HT_CAP_GRN_FLD		0x0010
#define IEEE80211_HT_CAP_SGI_20			0x0020
#define IEEE80211_HT_CAP_SGI_40			0x0040
#define IEEE80211_HT_CAP_TX_STBC			0x0080
#define IEEE80211_HT_CAP_RX_STBC		0x0300
#define IEEE80211_HT_CAP_DELAY_BA		0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU		0x0800
#define IEEE80211_HT_CAP_DSSSCCK40		0x1000
/* 802.11n HT capability AMPDU settings */
#define IEEE80211_HT_CAP_AMPDU_FACTOR		0x03
#define IEEE80211_HT_CAP_AMPDU_DENSITY		0x1C
/* 802.11n HT capability MSC set */
#define IEEE80211_SUPP_MCS_SET_UEQM		4
#define IEEE80211_HT_CAP_MAX_STREAMS		4
#define IEEE80211_SUPP_MCS_SET_LEN		10
/* maximum streams the spec allows */
#define IEEE80211_HT_CAP_MCS_TX_DEFINED		0x01
#define IEEE80211_HT_CAP_MCS_TX_RX_DIFF		0x02
#define IEEE80211_HT_CAP_MCS_TX_STREAMS		0x0C
#define IEEE80211_HT_CAP_MCS_TX_UEQM		0x10
/* 802.11n HT IE masks */
#define IEEE80211_HT_IE_CHA_SEC_OFFSET		0x03
#define IEEE80211_HT_IE_CHA_SEC_NONE	 	0x00
#define IEEE80211_HT_IE_CHA_SEC_ABOVE 		0x01
#define IEEE80211_HT_IE_CHA_SEC_BELOW 		0x03
#define IEEE80211_HT_IE_CHA_WIDTH		0x04
#define IEEE80211_HT_IE_HT_PROTECTION		0x0003
#define IEEE80211_HT_IE_NON_GF_STA_PRSNT	0x0004
#define IEEE80211_HT_IE_NON_HT_STA_PRSNT	0x0010

/* block-ack parameters */
#define IEEE80211_ADDBA_PARAM_POLICY_MASK 0x0002
#define IEEE80211_ADDBA_PARAM_TID_MASK 0x003C
#define RTW_IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK 0xFFC0
#define IEEE80211_DELBA_PARAM_TID_MASK 0xF000
#define IEEE80211_DELBA_PARAM_INITIATOR_MASK 0x0800

/*
 * A-PMDU buffer sizes
 * According to IEEE802.11n spec size varies from 8K to 64K (in powers of 2)
 */
#define IEEE80211_MIN_AMPDU_BUF 0x8
#define IEEE80211_MAX_AMPDU_BUF 0x40


/* Spatial Multiplexing Power Save Modes */
#define WLAN_HT_CAP_SM_PS_STATIC		0
#define WLAN_HT_CAP_SM_PS_DYNAMIC	1
#define WLAN_HT_CAP_SM_PS_INVALID	2
#define WLAN_HT_CAP_SM_PS_DISABLED	3


#define OP_MODE_PURE                    0
#define OP_MODE_MAY_BE_LEGACY_STAS      1
#define OP_MODE_20MHZ_HT_STA_ASSOCED    2
#define OP_MODE_MIXED                   3

#define HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK	((u8) BIT(0) | BIT(1))
#define HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE		((u8) BIT(0))
#define HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW		((u8) BIT(0) | BIT(1))
#define HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH		((u8) BIT(2))
#define HT_INFO_HT_PARAM_RIFS_MODE			((u8) BIT(3))
#define HT_INFO_HT_PARAM_CTRL_ACCESS_ONLY		((u8) BIT(4))
#define HT_INFO_HT_PARAM_SRV_INTERVAL_GRANULARITY	((u8) BIT(5))

#define HT_INFO_OPERATION_MODE_OP_MODE_MASK	\
		((u16) (0x0001 | 0x0002))
#define HT_INFO_OPERATION_MODE_OP_MODE_OFFSET		0
#define HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT	((u8) BIT(2))
#define HT_INFO_OPERATION_MODE_TRANSMIT_BURST_LIMIT	((u8) BIT(3))
#define HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT	((u8) BIT(4))

#define HT_INFO_STBC_PARAM_DUAL_BEACON			((u16) BIT(6))
#define HT_INFO_STBC_PARAM_DUAL_STBC_PROTECT		((u16) BIT(7))
#define HT_INFO_STBC_PARAM_SECONDARY_BCN		((u16) BIT(8))
#define HT_INFO_STBC_PARAM_LSIG_TXOP_PROTECT_ALLOWED	((u16) BIT(9))
#define HT_INFO_STBC_PARAM_PCO_ACTIVE			((u16) BIT(10))
#define HT_INFO_STBC_PARAM_PCO_PHASE			((u16) BIT(11))



//#endif

//	===============WPS Section===============
//	For WPSv1.0
#define WPSOUI							0x0050f204
//	WPS attribute ID
#define WPS_ATTR_VER1					0x104A
#define WPS_ATTR_SIMPLE_CONF_STATE	0x1044
#define WPS_ATTR_RESP_TYPE			0x103B
#define WPS_ATTR_UUID_E				0x1047
#define WPS_ATTR_MANUFACTURER		0x1021
#define WPS_ATTR_MODEL_NAME			0x1023
#define WPS_ATTR_MODEL_NUMBER		0x1024
#define WPS_ATTR_SERIAL_NUMBER		0x1042
#define WPS_ATTR_PRIMARY_DEV_TYPE	0x1054
#define WPS_ATTR_SEC_DEV_TYPE_LIST	0x1055
#define WPS_ATTR_DEVICE_NAME			0x1011
#define WPS_ATTR_CONF_METHOD			0x1008
#define WPS_ATTR_RF_BANDS				0x103C
#define WPS_ATTR_DEVICE_PWID			0x1012
#define WPS_ATTR_REQUEST_TYPE			0x103A
#define WPS_ATTR_ASSOCIATION_STATE	0x1002
#define WPS_ATTR_CONFIG_ERROR			0x1009
#define WPS_ATTR_VENDOR_EXT			0x1049
#define WPS_ATTR_SELECTED_REGISTRAR	0x1041

//	Value of WPS attribute "WPS_ATTR_DEVICE_NAME
#define WPS_MAX_DEVICE_NAME_LEN		32

//	Value of WPS Request Type Attribute
#define WPS_REQ_TYPE_ENROLLEE_INFO_ONLY			0x00
#define WPS_REQ_TYPE_ENROLLEE_OPEN_8021X		0x01
#define WPS_REQ_TYPE_REGISTRAR					0x02
#define WPS_REQ_TYPE_WLAN_MANAGER_REGISTRAR	0x03

//	Value of WPS Response Type Attribute
#define WPS_RESPONSE_TYPE_INFO_ONLY	0x00
#define WPS_RESPONSE_TYPE_8021X		0x01
#define WPS_RESPONSE_TYPE_REGISTRAR	0x02
#define WPS_RESPONSE_TYPE_AP			0x03

//	Value of WPS WiFi Simple Configuration State Attribute
#define WPS_WSC_STATE_NOT_CONFIG	0x01
#define WPS_WSC_STATE_CONFIG			0x02

//	Value of WPS Version Attribute
#define WPS_VERSION_1					0x10

//	Value of WPS Configuration Method Attribute
#define WPS_CONFIG_METHOD_FLASH		0x0001
#define WPS_CONFIG_METHOD_ETHERNET	0x0002
#define WPS_CONFIG_METHOD_LABEL		0x0004
#define WPS_CONFIG_METHOD_DISPLAY	0x0008
#define WPS_CONFIG_METHOD_E_NFC		0x0010
#define WPS_CONFIG_METHOD_I_NFC		0x0020
#define WPS_CONFIG_METHOD_NFC		0x0040
#define WPS_CONFIG_METHOD_PBC		0x0080
#define WPS_CONFIG_METHOD_KEYPAD	0x0100
#define WPS_CONFIG_METHOD_VPBC		0x0280
#define WPS_CONFIG_METHOD_PPBC		0x0480
#define WPS_CONFIG_METHOD_VDISPLAY	0x2008
#define WPS_CONFIG_METHOD_PDISPLAY	0x4008

//	Value of Category ID of WPS Primary Device Type Attribute
#define WPS_PDT_CID_DISPLAYS			0x0007
#define WPS_PDT_CID_MULIT_MEDIA		0x0008
#define WPS_PDT_CID_RTK_WIDI			WPS_PDT_CID_MULIT_MEDIA

//	Value of Sub Category ID of WPS Primary Device Type Attribute
#define WPS_PDT_SCID_MEDIA_SERVER	0x0005
#define WPS_PDT_SCID_RTK_DMP			WPS_PDT_SCID_MEDIA_SERVER

//	Value of Device Password ID
#define WPS_DPID_PIN					0x0000
#define WPS_DPID_USER_SPEC			0x0001
#define WPS_DPID_MACHINE_SPEC			0x0002
#define WPS_DPID_REKEY					0x0003
#define WPS_DPID_PBC					0x0004
#define WPS_DPID_REGISTRAR_SPEC		0x0005

//	Value of WPS RF Bands Attribute
#define WPS_RF_BANDS_2_4_GHZ		0x01
#define WPS_RF_BANDS_5_GHZ		0x02

//	Value of WPS Association State Attribute
#define WPS_ASSOC_STATE_NOT_ASSOCIATED			0x00
#define WPS_ASSOC_STATE_CONNECTION_SUCCESS		0x01
#define WPS_ASSOC_STATE_CONFIGURATION_FAILURE	0x02
#define WPS_ASSOC_STATE_ASSOCIATION_FAILURE		0x03
#define WPS_ASSOC_STATE_IP_FAILURE				0x04

//	=====================P2P Section=====================
//	For P2P
#define	P2POUI							0x506F9A09

//	P2P Attribute ID
#define	P2P_ATTR_STATUS					0x00
#define	P2P_ATTR_MINOR_REASON_CODE		0x01
#define	P2P_ATTR_CAPABILITY				0x02
#define	P2P_ATTR_DEVICE_ID				0x03
#define	P2P_ATTR_GO_INTENT				0x04
#define	P2P_ATTR_CONF_TIMEOUT			0x05
#define	P2P_ATTR_LISTEN_CH				0x06
#define	P2P_ATTR_GROUP_BSSID				0x07
#define	P2P_ATTR_EX_LISTEN_TIMING		0x08
#define	P2P_ATTR_INTENTED_IF_ADDR		0x09
#define	P2P_ATTR_MANAGEABILITY			0x0A
#define	P2P_ATTR_CH_LIST					0x0B
#define	P2P_ATTR_NOA						0x0C
#define	P2P_ATTR_DEVICE_INFO				0x0D
#define	P2P_ATTR_GROUP_INFO				0x0E
#define	P2P_ATTR_GROUP_ID					0x0F
#define	P2P_ATTR_INTERFACE				0x10
#define	P2P_ATTR_OPERATING_CH			0x11
#define	P2P_ATTR_INVITATION_FLAGS		0x12

//	Value of Status Attribute
#define	P2P_STATUS_SUCCESS						0x00
#define	P2P_STATUS_FAIL_INFO_UNAVAILABLE		0x01
#define	P2P_STATUS_FAIL_INCOMPATIBLE_PARAM		0x02
#define	P2P_STATUS_FAIL_LIMIT_REACHED			0x03
#define	P2P_STATUS_FAIL_INVALID_PARAM			0x04
#define	P2P_STATUS_FAIL_REQUEST_UNABLE			0x05
#define	P2P_STATUS_FAIL_PREVOUS_PROTO_ERR		0x06
#define	P2P_STATUS_FAIL_NO_COMMON_CH			0x07
#define	P2P_STATUS_FAIL_UNKNOWN_P2PGROUP		0x08
#define	P2P_STATUS_FAIL_BOTH_GOINTENT_15		0x09
#define	P2P_STATUS_FAIL_INCOMPATIBLE_PROVSION	0x0A
#define	P2P_STATUS_FAIL_USER_REJECT				0x0B

//	Value of Inviation Flags Attribute
#define	P2P_INVITATION_FLAGS_PERSISTENT			BIT(0)

#define	DMP_P2P_DEVCAP_SUPPORT	(P2P_DEVCAP_SERVICE_DISCOVERY | \
									P2P_DEVCAP_CLIENT_DISCOVERABILITY | \
									P2P_DEVCAP_CONCURRENT_OPERATION | \
									P2P_DEVCAP_INVITATION_PROC)

#define	DMP_P2P_GRPCAP_SUPPORT	(P2P_GRPCAP_INTRABSS)

//	Value of Device Capability Bitmap
#define	P2P_DEVCAP_SERVICE_DISCOVERY		BIT(0)
#define	P2P_DEVCAP_CLIENT_DISCOVERABILITY	BIT(1)
#define	P2P_DEVCAP_CONCURRENT_OPERATION	BIT(2)
#define	P2P_DEVCAP_INFRA_MANAGED			BIT(3)
#define	P2P_DEVCAP_DEVICE_LIMIT				BIT(4)
#define	P2P_DEVCAP_INVITATION_PROC			BIT(5)

//	Value of Group Capability Bitmap
#define	P2P_GRPCAP_GO							BIT(0)
#define	P2P_GRPCAP_PERSISTENT_GROUP			BIT(1)
#define	P2P_GRPCAP_GROUP_LIMIT				BIT(2)
#define	P2P_GRPCAP_INTRABSS					BIT(3)
#define	P2P_GRPCAP_CROSS_CONN				BIT(4)
#define	P2P_GRPCAP_PERSISTENT_RECONN		BIT(5)
#define	P2P_GRPCAP_GROUP_FORMATION			BIT(6)

//	P2P Public Action Frame ( Management Frame )
#define	P2P_PUB_ACTION_ACTION				0x09

//	P2P Public Action Frame Type
#define	P2P_GO_NEGO_REQ						0
#define	P2P_GO_NEGO_RESP						1
#define	P2P_GO_NEGO_CONF						2
#define	P2P_INVIT_REQ							3
#define	P2P_INVIT_RESP							4
#define	P2P_DEVDISC_REQ						5
#define	P2P_DEVDISC_RESP						6
#define	P2P_PROVISION_DISC_REQ				7
#define	P2P_PROVISION_DISC_RESP				8

//	P2P Action Frame Type
#define	P2P_NOTICE_OF_ABSENCE	0
#define	P2P_PRESENCE_REQUEST		1
#define	P2P_PRESENCE_RESPONSE	2
#define	P2P_GO_DISC_REQUEST		3


#define	P2P_MAX_PERSISTENT_GROUP_NUM		10

#define	P2P_PROVISIONING_SCAN_CNT			3

#define	P2P_WILDCARD_SSID_LEN				7

#define	P2P_FINDPHASE_EX_NONE				0	// default value, used when: (1)p2p disabed or (2)p2p enabled but only do 1 scan phase
#define	P2P_FINDPHASE_EX_FULL				1	// used when p2p enabled and want to do 1 scan phase and P2P_FINDPHASE_EX_MAX-1 find phase
#define	P2P_FINDPHASE_EX_SOCIAL_FIRST		(P2P_FINDPHASE_EX_FULL+1)
#define	P2P_FINDPHASE_EX_MAX					4
#define	P2P_FINDPHASE_EX_SOCIAL_LAST		P2P_FINDPHASE_EX_MAX

#define	P2P_PROVISION_TIMEOUT				5000	//	5 seconds timeout for sending the provision discovery request
#define	P2P_CONCURRENT_PROVISION_TIMEOUT	3000	//	3 seconds timeout for sending the provision discovery request under concurrent mode
#define	P2P_GO_NEGO_TIMEOUT					5000	//	5 seconds timeout for receiving the group negotation response
#define	P2P_CONCURRENT_GO_NEGO_TIMEOUT		3000	//	3 seconds timeout for sending the negotiation request under concurrent mode
#define	P2P_TX_PRESCAN_TIMEOUT				100		//	100ms
#define	P2P_INVITE_TIMEOUT					5000	//	5 seconds timeout for sending the invitation request
#define	P2P_CONCURRENT_INVITE_TIMEOUT		3000	//	3 seconds timeout for sending the invitation request under concurrent mode

#define	P2P_MAX_INTENT						15

#define	P2P_MAX_NOA_NUM						2

//	WPS Configuration Method
#define	WPS_CM_NONE							0x0000
#define	WPS_CM_LABEL							0x0004
#define	WPS_CM_DISPLYA						0x0008
#define	WPS_CM_EXTERNAL_NFC_TOKEN			0x0010
#define	WPS_CM_INTEGRATED_NFC_TOKEN		0x0020
#define	WPS_CM_NFC_INTERFACE					0x0040
#define	WPS_CM_PUSH_BUTTON					0x0080
#define	WPS_CM_KEYPAD						0x0100
#define	WPS_CM_SW_PUHS_BUTTON				0x0280
#define	WPS_CM_HW_PUHS_BUTTON				0x0480
#define	WPS_CM_SW_DISPLAY_PIN				0x2008
#define	WPS_CM_LCD_DISPLAY_PIN				0x4008


//wext_send_mgnt bit type
#define P2P_SEND_ACTION_AFTER_PROBE_RSP	 	1
#define RTW_SEND_AND_WAIT_ACK 				2
#define RTW_SEND_BY_HIGH_RATE				4 // IEEE80211_OFDM_RATE_54MB
#define RTW_NAV_BY_USER						8

enum gen_ie_type {
	P2PWPS_PROBE_REQ_IE = 0,
	P2PWPS_PROBE_RSP_IE,
	P2PWPS_BEACON_IE,
	P2PWPS_ASSOC_REQ_IE,
	P2PWPS_ASSOC_RSP_IE
};

enum P2P_ROLE {
	P2P_ROLE_DISABLE = 0,
	P2P_ROLE_DEVICE = 1,
	P2P_ROLE_CLIENT = 2,
	P2P_ROLE_GO = 3
};

enum P2P_STATE {
	P2P_STATE_NONE = 0,							//	P2P disable
	P2P_STATE_IDLE = 1,								//	P2P had enabled and do nothing
	P2P_STATE_LISTEN = 2,							//	In pure listen state
	P2P_STATE_SCAN = 3,							//	In scan phase
	P2P_STATE_FIND_PHASE_LISTEN = 4,				//	In the listen state of find phase
	P2P_STATE_FIND_PHASE_SEARCH = 5,				//	In the search state of find phase
	P2P_STATE_TX_PROVISION_DIS_REQ = 6,			//	In P2P provisioning discovery
	P2P_STATE_RX_PROVISION_DIS_RSP = 7,
	P2P_STATE_RX_PROVISION_DIS_REQ = 8,
	P2P_STATE_GONEGO_ING = 9,						//	Doing the group owner negoitation handshake
	P2P_STATE_GONEGO_OK = 10,						//	finish the group negoitation handshake with success
	P2P_STATE_GONEGO_FAIL = 11,					//	finish the group negoitation handshake with failure
	P2P_STATE_RECV_INVITE_REQ_MATCH = 12,		//	receiving the P2P Inviation request and match with the profile.
	P2P_STATE_PROVISIONING_ING = 13,				//	Doing the P2P WPS
	P2P_STATE_PROVISIONING_DONE = 14,			//	Finish the P2P WPS
	P2P_STATE_TX_INVITE_REQ = 15,					//	Transmit the P2P Invitation request
	P2P_STATE_RX_INVITE_RESP = 16,				//	Receiving the P2P Invitation response
	P2P_STATE_RECV_INVITE_REQ_DISMATCH = 17,	//	receiving the P2P Inviation request and dismatch with the profile.
	P2P_STATE_RECV_INVITE_REQ_GO = 18,			//	receiving the P2P Inviation request and this wifi is GO.
	P2P_STATE_RECV_INVITE_REQ_JOIN = 19,			//	receiving the P2P Inviation request to join an existing P2P Group.
	P2P_STATE_FORMATION_COMPLETE = 20,
	P2P_STATE_CONNECTED = 21,
};

enum P2P_WPSINFO {
	P2P_NO_WPSINFO						= 0,
	P2P_GOT_WPSINFO_PEER_DISPLAY_PIN	= 1,
	P2P_GOT_WPSINFO_SELF_DISPLAY_PIN	= 2,
	P2P_GOT_WPSINFO_PBC					= 3,
};

#define	P2P_PRIVATE_IOCTL_SET_LEN		64

enum P2P_PROTO_WK_ID {
	P2P_FIND_PHASE_WK = 0,
	P2P_RESTORE_STATE_WK = 1,
	P2P_PRE_TX_PROVDISC_PROCESS_WK = 2,
	P2P_PRE_TX_NEGOREQ_PROCESS_WK = 3,
	P2P_PRE_TX_INVITEREQ_PROCESS_WK = 4,
	P2P_AP_P2P_CH_SWITCH_PROCESS_WK = 5,
	P2P_RO_CH_WK = 6,
};

enum P2P_PS {
	P2P_PS_DISABLE = 0,
	P2P_PS_ENABLE = 1,
	P2P_PS_SCAN = 2,
	P2P_PS_SCAN_DONE = 3,
	P2P_PS_ALLSTASLEEP = 4, // for owner
};

//	=====================WFD Section=====================
//	For Wi-Fi Display
#define	WFD_ATTR_DEVICE_INFO			0x00
#define	WFD_ATTR_ASSOC_BSSID			0x01
#define	WFD_ATTR_COUPLED_SINK_INFO	0x06
#define	WFD_ATTR_LOCAL_IP_ADDR		0x08
#define	WFD_ATTR_SESSION_INFO		0x09
#define	WFD_ATTR_ALTER_MAC			0x0a

//	For WFD Device Information Attribute
#define	WFD_DEVINFO_SOURCE					0x0000
#define	WFD_DEVINFO_PSINK					0x0001
#define	WFD_DEVINFO_SSINK					0x0002

#define	WFD_DEVINFO_SESSION_AVAIL			0x0010
#define	WFD_DEVINFO_WSD						0x0040
#define	WFD_DEVINFO_PC_TDLS					0x0080

#ifdef CONFIG_WAPI_SUPPORT
#ifndef IW_AUTH_WAPI_VERSION_1
#define IW_AUTH_WAPI_VERSION_1		0x00000008
#endif
#ifndef IW_AUTH_KEY_MGMT_WAPI_PSK
#define IW_AUTH_KEY_MGMT_WAPI_PSK	0x04
#endif
#ifndef IW_AUTH_WAPI_ENABLED
#define IW_AUTH_WAPI_ENABLED		0x20
#endif
#ifndef IW_ENCODE_ALG_SM4
#define IW_ENCODE_ALG_SM4			0x20
#endif
#endif

#ifndef _CUSTOM_IE_TYPE_
#define _CUSTOM_IE_TYPE_
typedef enum CUSTOM_IE_TYPE {
	PROBE_REQ = BIT(0),
	PROBE_RSP = BIT(1),
	BEACON	  = BIT(2),
	ASSOC_REQ = BIT(3),
} rtw_custom_ie_type_t;
#endif /* _CUSTOM_IE_TYPE_ */

#endif // _WIFI_H_

