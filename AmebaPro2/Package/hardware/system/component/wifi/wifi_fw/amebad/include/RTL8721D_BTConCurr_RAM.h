#ifndef __RTL8721D_BTCONCURR_RAM_H__
#define __RTL8721D_BTCONCURR_RAM_H__

#ifndef __ASSEMBLY__

#define BTC_INTERVAL_UNDER_100      0
#define BTC_INTERVAL_OVER_100       2
#define BTC_INTERVAL_SHORT          3
#define BTC_DEFAULT_INTERVAL        100
#define BTC_SHORT_INTERVAL          50
#define BTC_BCN_EARLY               DEFAULT_PS_DRV_EARLY

#define BTC_LEAPY_AP_LIMIT 1

extern void
InitBTMailbox_8721D_RAM(
	void
);

extern void
DacSwing_8721D_RAM(
	IN u8 action
);

extern void
AOAC_ANT_SWT_8721D(
	IN  u8  TwoAnt,
	IN  u8  value,
	IN  u8  AntSwitchOutside,
	IN  u8  AntSelReverse
);


extern void
BTRoleChangeDefaultSetting_8721D(
	void
) ;


#if 0   //IS_CUT_A(CONFIG_CHIP_SEL)
extern void
AntennaSwitchCtrl_8721D(
	u8      side,
	u8      ctrl
);
#endif

extern void
BackupAntennaSetting_8721D(
	IN  u8  option
) ;

extern void
MailboxINTHDL_Patch_8721D(
	u8 cmd
) ;

#if 0 //for debug
extern void
BtcPsTdmaOnBcn(
	void
);

extern void
BT_TDMA_Wifi_Slot(
	IN	u8	slot_num
) ;


extern void
BT_TDMA_Wifi2BT_Slot(
	IN	u8	slot_num
) ;

extern void
BT_TDMA_BT_Slot(
	IN	u8	slot_num
) ;
#endif

extern u8
GenerateRandomValue(
	u8 range, u8 count
);

extern void
WlanRandomSlotLength(
	void
);

extern void
BT_TDMA_Slot_Operation_0and3_8721D(
	IN	u8	slot_num
) ;

extern void
BT_TDMA_Slot_Operation_1and4_8721D(
	IN	u8	slot_num
) ;

extern void
BT_TDMA_Slot_Operation_2and5_8721D(
	IN	u8	slot_num
) ;

extern u8
BTypeTDMAMultiSlots_8721D(
	void
);

extern void
BTypeTDMABCNEarly_8721D(
	void
) ;

extern void
BTypeTDMATBTThdl_8721D(
	void
);

extern void
BTypeTDMATimeOuthdl_8721D(
	void
);

extern void
LeapyAPExtension(
	IN	u8	slot_num
);

extern void
LeapyAPCount(
	void
);

extern void
FlexibleExtensionDecision_8721D(
	void
);

#endif

#endif
