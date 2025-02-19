/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
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
#ifndef __STA_INFO_H_
#define __STA_INFO_H_

#define IBSS_START_MAC_ID	2

#if 0 //move to wifi.h
#if defined(PLATFORM_ECOS)
#define NUM_STA 10	//Decrease STA due to memory limitation - Alex Fang
#elif defined(PLATFORM_FREERTOS)
//Decrease STA due to memory limitation - Alex Fang
#ifdef CONFIG_AP_MODE
#define NUM_STA (2 + AP_STA_NUM)	//2 + supported clients
#else
#define NUM_STA 2	//Client mode sta for AP and broadcast
#endif
#else
#define NUM_STA 32
#endif
#endif

#define NUM_ACL 16

//if mode ==0, then the sta is allowed once the addr is hit.
//if mode ==1, then the sta is rejected once the addr is non-hit.
struct rtw_wlan_acl_node {
        _list		        list;
        u8       addr[ETH_ALEN];
        u8       valid;
};

//mode=0, disable
//mode=1, accept unless in deny list
//mode=2, deny unless in accept list
struct wlan_acl_pool {
	int mode;
	int num;
	struct rtw_wlan_acl_node aclnode[NUM_ACL];
	_queue	acl_node_q;
};

typedef struct _RSSI_STA{
	s32	UndecoratedSmoothedPWDB;
	s32	UndecoratedSmoothedCCK;
	s32	UndecoratedSmoothedOFDM;
	u64	PacketMap;
	u8	ValidBit;
}RSSI_STA, *PRSSI_STA;

struct	stainfo_stats	{

	//u64	rx_pkts;
	u64 rx_mgnt_pkts;
	u64 rx_ctrl_pkts;
	u64 rx_data_pkts;

	//u64	last_rx_pkts;
	u64	last_rx_mgnt_pkts;
	u64	last_rx_ctrl_pkts;
	u64	last_rx_data_pkts;
	
	u64	rx_bytes;
//	u64	rx_drops;

	u64	tx_pkts;
	u64	tx_bytes;
//	u64  tx_drops;

};

#ifdef CONFIG_TDLS
struct TDLS_PeerKey {
	u8 kck[16]; /* TPK-KCK */
	u8 tk[16]; /* TPK-TK; only CCMP will be used */
} ;
#endif //CONFIG_TDLS

struct sta_info {

	_lock	lock;
	_list	list; //free_sta_queue
	_list	hash_list; //sta_hash
	//_list asoc_list; //20061114
	//_list sleep_list;//sleep_q
	//_list wakeup_list;//wakeup_q
	_adapter *padapter;
	
	struct sta_xmit_priv sta_xmitpriv;
	struct sta_recv_priv sta_recvpriv;
	
	_queue sleep_q;
	unsigned int sleepq_len;
	
	uint state;
	uint aid;
	uint mac_id;
	uint qos_option;
	u8	hwaddr[ETH_ALEN];

	uint	ieee8021x_blocked;	//0: allowed, 1:blocked 
	uint	dot118021XPrivacy; //aes, tkip...
	union Keytype	dot11tkiptxmickey;
	union Keytype	dot11tkiprxmickey;
	union Keytype	dot118021x_UncstKey;	
	union pn48		dot11txpn;			// PN48 used for Unicast xmit.
	union pn48		dot11rxpn;			// PN48 used for Unicast recv.


	u8	bssrateset[16];
	u32	bssratelen;
	s32  rssi;
	s32	signal_quality;
	
	u8	cts2self;
	u8	rtsen;

	u8	raid;
	u8 	init_rate;
	u32	ra_mask;
	u8	wireless_mode;	// NETWORK_TYPE
	struct stainfo_stats sta_stats;

#ifdef CONFIG_TDLS
	u32	tdls_sta_state;
	u8	dialog;
	u8	SNonce[32];
	u8	ANonce[32];
	u32	TDLS_PeerKey_Lifetime;
	u16	TPK_count;
	_timer	TPK_timer;
	struct TDLS_PeerKey	tpk;
	u16	stat_code;
	u8	off_ch;
	u16	ch_switch_time;
	u16	ch_switch_timeout;
	u8	option;
	_timer	option_timer;
	_timer	base_ch_timer;
	_timer	off_ch_timer;

	_timer handshake_timer;
	_timer alive_timer1;
	_timer alive_timer2;
	u8 timer_flag;
	u8 alive_count;
#endif //CONFIG_TDLS

	//for A-MPDU TX, ADDBA timeout check	
	_timer addba_retry_timer;
#ifdef CONFIG_RECV_REORDERING_CTRL
	//for A-MPDU Rx reordering buffer control 
	struct recv_reorder_ctrl recvreorder_ctrl[16];
#endif
	//for A-MPDU Tx
	//unsigned char		ampdu_txen_bitmap;
	u16	BA_starting_seqctrl[16];
	

#ifdef CONFIG_80211N_HT
	struct ht_priv	htpriv;	
#endif
	
	//Notes:	
	//STA_Mode:
	//curr_network(mlme_priv/security_priv/qos/ht) + sta_info: (STA & AP) CAP/INFO	
	//scan_q: AP CAP/INFO

	//AP_Mode:
	//curr_network(mlme_priv/security_priv/qos/ht) : AP CAP/INFO
	//sta_info: (AP & STA) CAP/INFO
		
#ifdef CONFIG_AP_MODE

	_list asoc_list;
	_list auth_list;
	 
	unsigned int expire_to;
	unsigned int auth_seq;
	unsigned int authalg;
	unsigned char chg_txt[128];

	u16 capability;	
	u32 flags;	

	int dot8021xalg;//0:disable, 1:psk, 2:802.1x
	int wpa_psk;//0:disable, bit(0): WPA, bit(1):WPA2
	int wpa_group_cipher;
	int wpa2_group_cipher;
	int wpa_pairwise_cipher;
	int wpa2_pairwise_cipher;	

	u8 bpairwise_key_installed;

#ifdef CONFIG_NATIVEAP_MLME
	u8 wpa_ie[32];

	u8 nonerp_set;
	u8 no_short_slot_time_set;
	u8 no_short_preamble_set;
	u8 no_ht_gf_set;
	u8 no_ht_set;
	u8 ht_20mhz_set;
#endif	// CONFIG_NATIVEAP_MLME

	unsigned int tx_ra_bitmap;
	u8 qos_info;

	u8 max_sp_len;
	u8 uapsd_bk;//BIT(0): Delivery enabled, BIT(1): Trigger enabled
	u8 uapsd_be;
	u8 uapsd_vi;
	u8 uapsd_vo;	

	u8 has_legacy_ac;
	unsigned int sleepq_ac_len;

#ifdef CONFIG_P2P
	//p2p priv data
	u8 is_p2p_device;
	u8 p2p_status_code;

	//p2p client info
	u8 dev_addr[ETH_ALEN];
	//u8 iface_addr[ETH_ALEN];//= hwaddr[ETH_ALEN]
	u8 dev_cap;
	u16 config_methods;
	u8 primary_dev_type[8];
	u8 num_of_secdev_type;
	u8 secdev_types_list[32];// 32/8 == 4;
	u16 dev_name_len;
	u8 dev_name[32];	
#endif //CONFIG_P2P

#ifdef CONFIG_TX_MCAST2UNI
	u8 under_exist_checking;
#endif	// CONFIG_TX_MCAST2UNI
	
#endif	// CONFIG_AP_MODE	

#ifdef CONFIG_IOCTL_CFG80211
	u8 *passoc_req;
	u32 assoc_req_len;
#endif

	//for DM
	RSSI_STA	 rssi_stat;
	
	//
	// ================ODM Relative Info=======================
	// Please be care, dont declare too much structure here. It will cost memory * STA support num.
	//
	//
	// 2011/10/20 MH Add for ODM STA info.	
	//
	// Driver Write
	u8		bValid;				// record the sta status link or not?
	//u8		WirelessMode;		// 
	u8		IOTPeer;			// Enum value.	HT_IOT_PEER_E
	u8		rssi_level;			//for Refresh RA mask
	// ODM Write
	//1 PHY_STATUS_INFO
	u8		RSSI_Path[4];		// 
	u8		RSSI_Ave;
	u8		RXEVM[4];
	u8		RXSNR[4];

	// ODM Write
	//1 TX_INFO (may changed by IC)
	//TX_INFO_T		pTxInfo;				// Define in IC folder. Move lower layer.
	//
	// ================ODM Relative Info=======================
	//
};

#define sta_rx_pkts(sta) \
	(sta->sta_stats.rx_mgnt_pkts \
	+ sta->sta_stats.rx_ctrl_pkts \
	+ sta->sta_stats.rx_data_pkts)

#define sta_last_rx_pkts(sta) \
	(sta->sta_stats.last_rx_mgnt_pkts \
	+ sta->sta_stats.last_rx_ctrl_pkts \
	+ sta->sta_stats.last_rx_data_pkts)

#define sta_update_last_rx_pkts(sta) \
	do { \
		sta->sta_stats.last_rx_mgnt_pkts = sta->sta_stats.rx_mgnt_pkts; \
		sta->sta_stats.last_rx_ctrl_pkts = sta->sta_stats.rx_ctrl_pkts; \
		sta->sta_stats.last_rx_data_pkts = sta->sta_stats.rx_data_pkts; \
	} while(0)

#define STA_RX_PKTS_ARG(sta) \
	sta->sta_stats.rx_mgnt_pkts \
	, sta->sta_stats.rx_ctrl_pkts \
	, sta->sta_stats.rx_data_pkts

#define STA_LAST_RX_PKTS_ARG(sta) \
	sta->sta_stats.last_rx_mgnt_pkts \
	, sta->sta_stats.last_rx_ctrl_pkts \
	, sta->sta_stats.last_rx_data_pkts

#define STA_PKTS_FMT "(m:%llu, c:%llu, d:%llu)"
	
struct	sta_priv {
	
	u8 *pallocated_stainfo_buf;
	u32 allocated_stainfo_size;
	u8 *pstainfo_buf;
	_queue	free_sta_queue;
	
	_lock sta_hash_lock;
	_list   sta_hash[NUM_STA];
	int asoc_sta_count;
	_queue sleep_q;
	_queue wakeup_q;
	
	_adapter *padapter;
	

#ifdef CONFIG_AP_MODE
	_list asoc_list;
	_list auth_list;
	_lock asoc_list_lock;
	_lock auth_list_lock;

	unsigned int auth_to;  //sec, time to expire in authenticating.
	unsigned int assoc_to; //sec, time to expire before associating.
	unsigned int expire_to; //sec , time to expire after associated.
	
	/* pointers to STA info; based on allocated AID or NULL if AID free
	 * AID is in the range 1-2007, so sta_aid[0] corresponders to AID 1
	 * and so on
	 */
	struct sta_info *sta_aid[NUM_STA];

	u16 sta_dz_bitmap;//only support 15 stations, staion aid bitmap for sleeping sta.
	u16 tim_bitmap;//only support 15 stations, aid=0~15 mapping bit0~bit15	

	u16 max_num_sta;
//TODO: AP
//	struct wlan_acl_pool acl_list;
#endif		
	
};


__inline static u32 wifi_mac_hash(u8 *mac)
{
        u32 x;

        x = mac[0];
        x = (x << 2) ^ mac[1];
        x = (x << 2) ^ mac[2];
        x = (x << 2) ^ mac[3];
        x = (x << 2) ^ mac[4];
        x = (x << 2) ^ mac[5];

        x ^= x >> 8;
        x  = x & (NUM_STA - 1);
		
        return x;
}


extern u32	_rtw_init_sta_priv(_adapter *padapter);
extern u32	_rtw_free_sta_priv(struct sta_priv *pstapriv);
extern struct sta_info *rtw_alloc_stainfo(struct	sta_priv *pstapriv, u8 *hwaddr);
extern u32	rtw_free_stainfo(_adapter *padapter , struct sta_info *psta);
extern void rtw_free_all_stainfo(_adapter *padapter);
extern struct sta_info *rtw_get_stainfo(struct sta_priv *pstapriv, u8 *hwaddr);
extern u32 rtw_init_bcmc_stainfo(_adapter* padapter);
extern struct sta_info* rtw_get_bcmc_stainfo(_adapter* padapter);
extern u8 rtw_access_ctrl(_adapter *padapter, u8 *mac_addr);

#endif //_STA_INFO_H_

