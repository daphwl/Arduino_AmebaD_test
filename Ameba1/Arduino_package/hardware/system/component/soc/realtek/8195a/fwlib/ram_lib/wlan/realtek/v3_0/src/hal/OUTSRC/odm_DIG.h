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
 
#ifndef	__ODMDIG_H__
#define    __ODMDIG_H__

#define ADAPTIVITY_VERSION	"7.1"

typedef struct _Dynamic_Initial_Gain_Threshold_
{
	BOOLEAN		bStopDIG;		// for debug
	BOOLEAN		bPauseDIG;
	BOOLEAN		bIgnoreDIG;
	BOOLEAN		bPSDInProgress;

	u1Byte		Dig_Enable_Flag;
	u1Byte		Dig_Ext_Port_Stage;
	
	int		   	RssiLowThresh;
	int		    	RssiHighThresh;

	u4Byte		FALowThresh;
	u4Byte		FAHighThresh;

	u1Byte		CurSTAConnectState;
	u1Byte		PreSTAConnectState;
	u1Byte		CurMultiSTAConnectState;

	u1Byte		PreIGValue;
	u1Byte		CurIGValue;
	u1Byte		BackupIGValue;		//MP DIG
	u1Byte		BT30_CurIGI;
	u1Byte		IGIBackup;

	s1Byte		BackoffVal;
	s1Byte		BackoffVal_range_max;
	s1Byte		BackoffVal_range_min;
	u1Byte		rx_gain_range_max;
	u1Byte		rx_gain_range_min;
	u1Byte		Rssi_val_min;

	u1Byte		PreCCK_CCAThres;
	u1Byte		CurCCK_CCAThres;
	u1Byte		PreCCKPDState;
	u1Byte		CurCCKPDState;
	u1Byte		CCKPDBackup;

	u1Byte		LargeFAHit;
	u1Byte		ForbiddenIGI;
	u4Byte		Recover_cnt;

	u1Byte		DIG_Dynamic_MIN_0;
	u1Byte		DIG_Dynamic_MIN_1;
	BOOLEAN		bMediaConnect_0;
	BOOLEAN		bMediaConnect_1;

	u4Byte		AntDiv_RSSI_max;
	u4Byte		RSSI_max;

	u1Byte		*pbP2pLinkInProgress;

#if(DM_ODM_SUPPORT_TYPE & (ODM_AP|ODM_ADSL))
	BOOLEAN		bTpTarget;
	BOOLEAN		bNoiseEst;
	u4Byte		TpTrainTH_min;
	u1Byte		IGIOffset_A;
	u1Byte		IGIOffset_B;
#endif
}DIG_T,*pDIG_T;

typedef struct _FALSE_ALARM_STATISTICS{
	u4Byte	Cnt_Parity_Fail;
	u4Byte	Cnt_Rate_Illegal;
	u4Byte	Cnt_Crc8_fail;
	u4Byte	Cnt_Mcs_fail;
	u4Byte	Cnt_Ofdm_fail;
	u4Byte	Cnt_Ofdm_fail_pre;	//For RTL8881A
	u4Byte	Cnt_Cck_fail;
	u4Byte	Cnt_all;
	u4Byte	Cnt_Fast_Fsync;
	u4Byte	Cnt_SB_Search_fail;
	u4Byte	Cnt_OFDM_CCA;
	u4Byte	Cnt_CCK_CCA;
	u4Byte	Cnt_CCA_all;
	u4Byte	Cnt_BW_USC;	//Gary
	u4Byte	Cnt_BW_LSC;	//Gary
}FALSE_ALARM_STATISTICS, *PFALSE_ALARM_STATISTICS;

typedef enum tag_Dynamic_Init_Gain_Operation_Type_Definition
{
	DIG_TYPE_THRESH_HIGH	= 0,
	DIG_TYPE_THRESH_LOW	= 1,
	DIG_TYPE_BACKOFF		= 2,
	DIG_TYPE_RX_GAIN_MIN	= 3,
	DIG_TYPE_RX_GAIN_MAX	= 4,
	DIG_TYPE_ENABLE 		= 5,
	DIG_TYPE_DISABLE 		= 6,	
	DIG_OP_TYPE_MAX
}DM_DIG_OP_E;

typedef enum tag_ODM_PauseDIG_Type {
	ODM_PAUSE_DIG    		= 	BIT0,
	ODM_RESUME_DIG  		= 	BIT1
} ODM_Pause_DIG_TYPE;

typedef enum tag_ODM_PauseCCKPD_Type {
	ODM_PAUSE_CCKPD    	= 	BIT0,
	ODM_RESUME_CCKPD  	= 	BIT1
} ODM_Pause_CCKPD_TYPE;

#if (DM_ODM_SUPPORT_TYPE & (ODM_WIN|ODM_CE))
typedef enum _tag_ODM_REGULATION_Type {
	REGULATION_FCC = 0,
	REGULATION_MKK = 1,
	REGULATION_ETSI = 2,
	REGULATION_WW = 3,	
	
	MAX_REGULATION_NUM = 4
} ODM_REGULATION_TYPE;
#endif

typedef enum tag_ODM_TRx_MUX_Type
{
	ODM_SHUTDOWN			= 0,
	ODM_STANDBY_MODE		= 1,
	ODM_TX_MODE			= 2,
	ODM_RX_MODE			= 3
}ODM_Trx_MUX_Type;

typedef enum tag_ODM_MACEDCCA_Type
{
	ODM_IGNORE_EDCCA			= 0,
	ODM_DONT_IGNORE_EDCCA	= 1
}ODM_MACEDCCA_Type;

/*
typedef enum tag_CCK_Packet_Detection_Threshold_Type_Definition
{
	CCK_PD_STAGE_LowRssi = 0,
	CCK_PD_STAGE_HighRssi = 1,
	CCK_PD_STAGE_MAX = 3,
}DM_CCK_PDTH_E;

typedef enum tag_DIG_EXT_PORT_ALGO_Definition
{
	DIG_EXT_PORT_STAGE_0 = 0,
	DIG_EXT_PORT_STAGE_1 = 1,
	DIG_EXT_PORT_STAGE_2 = 2,
	DIG_EXT_PORT_STAGE_3 = 3,
	DIG_EXT_PORT_STAGE_MAX = 4,
}DM_DIG_EXT_PORT_ALG_E;

typedef enum tag_DIG_Connect_Definition
{
	DIG_STA_DISCONNECT = 0,	
	DIG_STA_CONNECT = 1,
	DIG_STA_BEFORE_CONNECT = 2,
	DIG_MultiSTA_DISCONNECT = 3,
	DIG_MultiSTA_CONNECT = 4,
	DIG_CONNECT_MAX
}DM_DIG_CONNECT_E;


#define DM_MultiSTA_InitGainChangeNotify(Event) {DM_DigTable.CurMultiSTAConnectState = Event;}

#define DM_MultiSTA_InitGainChangeNotify_CONNECT(_ADAPTER)	\
	DM_MultiSTA_InitGainChangeNotify(DIG_MultiSTA_CONNECT)

#define DM_MultiSTA_InitGainChangeNotify_DISCONNECT(_ADAPTER)	\
	DM_MultiSTA_InitGainChangeNotify(DIG_MultiSTA_DISCONNECT)
*/
#define		DM_DIG_THRESH_HIGH			40
#define		DM_DIG_THRESH_LOW			35

#define		DM_FALSEALARM_THRESH_LOW	400
#define		DM_FALSEALARM_THRESH_HIGH	1000

#define		DM_DIG_MAX_NIC				0x3e
#define		DM_DIG_MIN_NIC				0x1e //0x22//0x1c
#define		DM_DIG_MAX_OF_MIN_NIC		0x3e

#define		DM_DIG_MAX_AP					0x3e
#define		DM_DIG_MIN_AP					0x1c
#define		DM_DIG_MAX_OF_MIN			0x2A	//0x32
#define		DM_DIG_MIN_AP_DFS				0x20

#define		DM_DIG_MAX_NIC_HP			0x46
#define		DM_DIG_MIN_NIC_HP				0x2e

#define		DM_DIG_MAX_AP_HP				0x42
#define		DM_DIG_MIN_AP_HP				0x30

#if (DM_ODM_SUPPORT_TYPE & (ODM_AP|ODM_ADSL))
#define		DM_DIG_MAX_AP_COVERAGR		0x26
#define		DM_DIG_MIN_AP_COVERAGE		0x1c
#define		DM_DIG_MAX_OF_MIN_COVERAGE	0x22

#define		DM_DIG_TP_Target_TH0			500
#define		DM_DIG_TP_Target_TH1			1000
#define		DM_DIG_TP_Training_Period		10
#endif

//vivi 92c&92d has different definition, 20110504
//this is for 92c
#if (DM_ODM_SUPPORT_TYPE & ODM_CE)
	#ifdef CONFIG_SPECIAL_SETTING_FOR_FUNAI_TV
	#define		DM_DIG_FA_TH0				0x80//0x20
	#else
	#define		DM_DIG_FA_TH0				0x200//0x20
	#endif
#else
	#define		DM_DIG_FA_TH0				0x200//0x20
#endif

#define		DM_DIG_FA_TH1					0x300
#define		DM_DIG_FA_TH2					0x400
//this is for 92d
#define		DM_DIG_FA_TH0_92D				0x100
#define		DM_DIG_FA_TH1_92D				0x400
#define		DM_DIG_FA_TH2_92D				0x600

#define		DM_DIG_BACKOFF_MAX			12
#define		DM_DIG_BACKOFF_MIN			-4
#define		DM_DIG_BACKOFF_DEFAULT		10

#define 		DM_DIG_FA_TH0_LPS				4 //-> 4 in lps
#define 		DM_DIG_FA_TH1_LPS				15 //-> 15 lps
#define 		DM_DIG_FA_TH2_LPS				30 //-> 30 lps
#define 		RSSI_OFFSET_DIG				0x05


VOID
odm_CheckAdaptivity(
	IN		PVOID			pDM_VOID
	);

VOID
odm_CheckEnvironment(
	IN		PVOID					pDM_VOID
	);

VOID
ODM_ChangeDynamicInitGainThresh(
	IN		PVOID					pDM_VOID,
	IN		u4Byte  					DM_Type,
	IN		u4Byte 					DM_Value
	);

VOID
odm_NHMCounterStatisticsInit(
	IN		PVOID					pDM_VOID
	);

VOID
odm_NHMCounterStatistics(
	IN		PVOID					pDM_VOID
	);

VOID
odm_NHMBBInit(
	IN		PVOID					pDM_VOID
);

VOID
odm_NHMBB(
	IN		PVOID					pDM_VOID
);

VOID
odm_NHMCounterStatisticsReset(
	IN		PVOID			pDM_VOID
);

VOID
odm_GetNHMCounterStatistics(
	IN		PVOID			pDM_VOID
);

VOID
odm_MACEDCCAState(
	IN		PVOID					pDM_VOID,
	IN	ODM_MACEDCCA_Type		State
);

VOID 
odm_SetEDCCAThreshold(
	IN		PVOID		pDM_VOID,
	IN		s1Byte		H2L,
	IN		s1Byte		L2H
);

VOID
odm_SetTRxMux(
	IN		PVOID			pDM_VOID,
	IN		ODM_Trx_MUX_Type			txMode,
	IN		ODM_Trx_MUX_Type			rxMode
);	

BOOLEAN
odm_CalNHMcnt(
	IN		PVOID					pDM_VOID
	);

VOID
odm_SearchPwdBLowerBound(
	IN		PVOID					pDM_VOID
);

VOID 
odm_AdaptivityInit(
	IN		PVOID					pDM_VOID
	);

BOOLEAN
odm_Adaptivity(
	IN		PVOID					pDM_VOID,
	IN		u1Byte					IGI
	);

VOID
ODM_Write_DIG(
	IN		PVOID					pDM_VOID, 	
	IN		u1Byte					CurrentIGI
	);

VOID
odm_PauseDIG(
	IN		PVOID					pDM_VOID,
	IN		ODM_Pause_DIG_TYPE		PauseType,
	IN		u1Byte					IGIValue
	);

VOID
odm_DIGInit(
	IN		PVOID					pDM_VOID
	);

VOID	
odm_DIG(
	IN		PVOID					pDM_VOID
	);

VOID
odm_DIGbyRSSI_LPS(
	IN		PVOID					pDM_VOID
	);

VOID
odm_DigForBtHsMode(
	IN		PVOID					pDM_VOID
	);

VOID 
odm_FalseAlarmCounterStatistics(
	IN		PVOID					pDM_VOID
	);
#if RTL8195A_SUPPORT
VOID
odm_FAThresholdCheck(
	IN		PVOID					pDM_VOID,
	OUT		u4Byte*					dm_FA_thres
	);
#else
VOID
odm_FAThresholdCheck(
	IN		PVOID					pDM_VOID,
	IN		BOOLEAN					bDFSBand,
	IN		BOOLEAN					bPerformance,
	IN		u4Byte					RxTp,
	IN		u4Byte					TxTp,
	OUT		u4Byte*					dm_FA_thres
	);
#endif
u1Byte
odm_ForbiddenIGICheck(
	IN		PVOID					pDM_VOID,
	IN		u1Byte					DIG_Dynamic_MIN,
	IN		u1Byte					CurrentIGI
	);

VOID
odm_InbandNoiseCalculate (	
	IN		PVOID					pDM_VOID
	);

BOOLEAN 
odm_DigAbort(
	IN		PVOID					pDM_VOID
	);

VOID
odm_PauseCCKPacketDetection(
	IN		PVOID					pDM_VOID,
	IN		ODM_Pause_CCKPD_TYPE	PauseType,
	IN		u1Byte					CCKPDThreshold
	);

VOID 
odm_CCKPacketDetectionThresh(
	IN		PVOID					pDM_VOID
	);

VOID 
ODM_Write_CCK_CCA_Thres(
	IN		PVOID					pDM_VOID, 
	IN		u1Byte					CurCCK_CCAThres
	);

#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)

VOID
odm_DisableEDCCA(
	IN		PVOID					pDM_VOID
);

VOID
odm_DynamicEDCCA(
	IN		PVOID					pDM_VOID
);

VOID
odm_MPT_DIGCallback(
	PRT_TIMER						pTimer
);

VOID
odm_MPT_DIGWorkItemCallback(
    IN 		PVOID            			pContext
    );

#endif

#if (DM_ODM_SUPPORT_TYPE & (ODM_AP|ODM_ADSL))
VOID
odm_MPT_DIGCallback(
	IN		PVOID					pDM_VOID
);
#endif

#if (DM_ODM_SUPPORT_TYPE != ODM_CE)
VOID
ODM_MPT_DIG(
	IN		PVOID					pDM_VOID
);
#endif


#endif

VOID
odm_DIGInit_8195A(
	IN		PVOID					pDM_VOID
	);

VOID	
odm_DIG_8195A(
	IN		PVOID					pDM_VOID
	);

VOID 
odm_FalseAlarmCounterStatistics_8195A(
	IN		PVOID					pDM_VOID
	);

VOID 
odm_CCKPacketDetectionThresh_8195A(
	IN		PVOID					pDM_VOID
	);