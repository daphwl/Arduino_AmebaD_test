#ifndef __RTL8721D_POWERCTRL_H__
#define __RTL8721D_POWERCTRL_H__

#ifndef __ASSEMBLY__
/*--------------------Define --------------------------------------------*/
//RPWM Definition
#define RPWM_ENTER32K_GRANT     BIT0


//CPWM Definition
#define CPWM_40M_STABLE         BIT0
#define CLK_DOWN_RDY            BIT4

#define WAIT_TXSM_STABLE_CNT            (1000)
#define WAIT_TXSM_STABLE_ONCE_TIME      (50)

#define WAIT_RPWM_STABLE_BREAK_CNT      (100)

#define WAIT_TSF_STABLE_BREAK_CNT       (5000)
#define WAIT_TSF_STABLE_CNT             (50)
#define WAIT_TSF_STABLE_ONCE_TIME       (20)
#define TSFIS32K                        1
#define TSFIS40M                        0
#define GET_TSF_STATE() ((ReadMACRegByte(REG_PLAYFORM_CLOCK) & CLK_STABLE_32K) ? TSFIS32K : TSFIS40M)

#define U1_ENABLE               BIT3
#define U2_ENABLE               BIT4

/*--------------------Define Enum---------------------------------------*/

//TxPauseReasonCode
typedef enum _TRPC_ {

	TPRC_ISSUEBTQNull_1             = 0x1,
	TPRC_ISSUEBTQNull_2             = 0x2,
	TPRC_FLEXIBLEEXTENDECISION_1    = 0x3,
	TPRC_BTTDMA03_1                 = 0x4,
	TPRC_BTTDMABCN_1                = 0x4,
	TPRC_BTTDMATBTT_1               = 0x5,
	TPRC_BTTDMA14_1                 = 0x6,
	TPRC_BTTDMATIMEOUT_1            = 0x6,
	TPRC_BTTDMA25_1                 = 0x7,
	TPRC_BTTDMATIMEOUT_2            = 0x7,
	TPRC_BTTDMA25_3                 = 0x8,
	TPRC_BTTDMATIMEOUT_3            = 0x8,
	TPRC_BTTDMA25_5                 = 0x9,
	TPRC_BTTDMATIMEOUT_4            = 0x9,
	TPRC_BTTDMA25_7                 = 0xA,
	TPRC_BTTDMATIMEOUT_5            = 0xA,
	TPRC_BTTDMA03_2                 = 0xB,
	TPRC_BTTDMATIMEOUT_6            = 0xB,
	TPRC_BTTDMA14_2                 = 0xC,
	TPRC_BTTDMATIMEOUT_7            = 0xC,
	TPRC_BTTDMA25_2                 = 0xD,
	TPRC_BTTDMATIMEOUT_8            = 0xD,
	TPRC_BTTDMA25_4                 = 0xE,
	TPRC_BTTDMATIMEOUT_9            = 0xE,
	TPRC_BTTDMA25_6                 = 0xF,
	TPRC_BTTDMATIMEOUT_10           = 0xF,
	TPRC_BTTDMA25_8                 = 0x10,
	TPRC_BTTDMATIMEOUT_11           = 0x10,
	TPRC_BACKUPANTENNA_1            = 0x11,
	TPRC_BTROLECHANGETIMER          = 0x12,
	TPRC_H2CSCAN                    = 0x13,
	TPRC_ISSUEFCSNULLDATA_1         = 0x14,
	TPRC_ISSUEFCSNULLDATA_2         = 0x15,
	TPRC_FASTCHSWITCH               = 0x16,
	TPRC_FCSDEFAULT                 = 0x17,
	TPRC_ISSUENDPA_1                = 0x18,
	TPRC_ISSUENDPA_2                = 0x19,
	TPRC_BACKUPCURRENT              = 0x1A,
	TPRC_SETPROBERATE_1             = 0x1B,
	TPRC_SETPROBERATE_2             = 0x1C,
	TPRC_WPA22_1                    = 0x1D,
	TPRC_WPA22_2                    = 0x1E,
	TPRC_P2PPSAONTS                 = 0x1F,
	TPRC_P2PPSAONTAOFF              = 0x20,
	TPRC_P2PPSAONTRF                = 0x21,
	TPRC_P2PPSSTRF                  = 0x22,
	TPRC_P2PPSSTAOFF                = 0x23,
	TPRC_P2PPSAOFFTS                = 0x24,
	TPRC_P2PPSRFTS                  = 0x25,
	TPRC_ISSUENULLDATA_1            = 0x26,
	TPRC_ISSUENULLDATA_2            = 0x27,
	TPRC_ISSUENULLDATA_3            = 0x28,
	TPRC_ISSUEQNULL_1               = 0x29,
	TPRC_ISSUEQNULL_2               = 0x2A,
	TPRC_PSS2TS3                    = 0x2B,
	TPRC_PSS0TS1                    = 0x2C,
	TPRC_PSS2TS4                    = 0x2D,
	TPRC_PSS2TS5                    = 0x2E,
	TPRC_PSS0TS6                    = 0x2F,
	TPRC_SAPPSTIMEOUT               = 0x31,
	TPRC_RLPSTBTT                   = 0x32,
	TPRC_ISSUEARP_1                 = 0x33,
	TPRC_ISSUEARP_2                 = 0x34,
	TPRC_REMOTEWAKEUPCTRL           = 0x35,
	TPRC_SCOESCO_1                  = 0x36,
	TPRC_ISSUECTS2SELF_1            = 0x36,
	TPRC_ISSUECTS2SELF_2            = 0x37,
	TPRC_ISSUECTS2SELF_3            = 0x38,
	TPRC_ISSUEPROBERSQ              = 0x38,
	TPRC_ISSUENA_1                  = 0x39,
	TPRC_ISSUENA_2                  = 0x3A,

	TPRC_ISSUENEGORSP_1             = 0x3B,
	TPRC_ISSUENEGORSP_2             = 0x3C,
	TPRC_ISSUEINVITRSP_1            = 0x3D,
	TPRC_ISSUEINVITRSP_2            = 0x3E,
	TPRC_ISSUEPDRSP_1               = 0x3F,
	TPRC_ISSUEPDRSP_2               = 0x40,
	TPRC_ISSUEDBGPKT_1              = 0x41,
	TPRC_ISSUEDBGPKT_2              = 0x42,
	TPRC_AP_OFFLOAD_MBSSID          = 0x43,
	TPRC_MACID_DROP_ACTION          = 0x44,
	TPRC_FASTCHSWITCH_2             = 0x45,
	TPRC_MACID_DROP_ACTION_2        = 0x46,
	TRPC_WAITTXSMOK_1               = 0x47,
	TRPC_WAITTXSMOK_2               = 0x48,
	TPRC_FCSDEFAULT_2               = 0x49,
	TPRC_MCCMacidAction             = 0x4A,
	TPRC_MCCMacidAction_2           = 0x4B,
	TPRC_MCCSWITCHCHANNEL_1         = 0x4C,
	TPRC_MCCSWITCHCHANNEL_2         = 0x4D,
	TPRC_MCCStateHDL_1              = 0x4E,
	TPRC_MCCStateHDL_2              = 0x4F,
	TPRC_MCCStateHDL_3              = 0x50,
	TPRC_MCCStateHDL_4              = 0x51,
	TPRC_MACID_DROP_ACTION_3        = 0x52,
	TPRC_MCCTSFSyncHDL_1			= 0x53,
	TPRC_MCCTSFSyncHDL_2			= 0x54,
	TPRC_ISSUENDPA_3				= 0x55,
	TPRC_InitPS					    = 0x56,
	TPRC_H2CHDL_TX_PAUSE_DRV_INFO	= 0x57,
	TPRC_MCCBcnEarlyHDL_1           = 0x58,
	TPRC_MCCBcnEarlyHDL_2           = 0x59,
	TRPC_WAITTXSMOK_3               = 0x5A,
	TRPC_WAITTXSMOK_4               = 0x5B,
} TRPC, *PTRPC;

//RxPauseReasonCode
typedef enum _RRPC_ {

	RPRC_SLEEPTO32K_1               = 0x1,
	RPRC_SLEEPTO32K_2               = 0x2,
	RPRC_REMOTE_WAKEUP              = 0x3,
} RRPC, *PRRPC;


//SetBeaconEarlyAndTimeoutReasonCode
typedef enum _SBEATPC_ {

	SBEATPC_H2C                     = 0x1,
	SBEATPC_RPWM                    = 0x2,
	SBEATPC_BCNADUST                = 0x3,
	SBEATPC_ENLARGE                 = 0x4,
	SBEATPC_TBTT                    = 0x5,
	SBEATPC_SAPPS                   = 0x6,
} SBEATPC, *PSBEATPC;

/*--------------------Define MACRO--------------------------------------*/

/*--------------------Define Struct---------------------------------------*/

/*--------------------Export global variable-------------------------------*/

/*--------------------Function declaration---------------------------------*/


//-------------------------------------------------------
//
//      Power Control Function
//
//-------------------------------------------------------






//-------------------------------------------------------
//
//      Power Control Function
//
//-------------------------------------------------------





#endif  //__ASSEMBLY__
#endif  //__RTL8721D_POWERCTRL_H__

