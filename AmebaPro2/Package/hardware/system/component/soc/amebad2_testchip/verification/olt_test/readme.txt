//////////////////////
/// How To Start ///
/////////////////////

====================  Configuration Start =========================
cd project/realtek_amebaD2_testchip_va0_example/GCC-RELEASE/project_lp
make menuconfig
	<CONFIG TEST MODE --> 
		[ * ] Select OLT
make xip

cd project/realtek_amebaD2_testchip_va0_example/GCC-RELEASE/project_hp
make menuconfig
	<CONFIG TEST MODE --> 
		[ * ] Select OLT
	<CONFIG WIFI -->
		[ * ] Enable Wifi
	<CONFIG NETWORK -->
		[ * ] Enable Network
	<SSL Config-->
		[ * ] MBEDTLS Enable
make xip

cd project/realtek_amebaD2_testchip_va0_example/GCC-RELEASE/project_ap
make menuconfig
	<CONFIG TEST MODE --> 
		[ * ] Select OLT
make xip
====================  Configuration End =========================

/////////////////////////////////
/// Command Information ///
////////////////////////////////
Other CMD
	============= Sleep CMD INFO =====================
	PG 0		1/ KM4 enters power gate state
	@CG 0		2/ KM0 enters clock gate state
	@DSLP 0		3/ System enters dslp state
	tickps dslp 1000	4/ amebaSmart enters DSLP for 1s then wakeup

	============= OLT cmd external =====================	
	olt debug info	1/ dump debug info level message
	olt debug warn	2/ dump debug warn level message : peripheral status task and audio FFT result
	~olt debug info	3/ dump CA7 debug info level

////////////////////////////////////////
/// Interface test case Description ///
////////////////////////////////////////

WIFI ����
	¯�ڣ�	MP ctx @5G channel for 5min�� @2.4G channel for 5min
	¯�⣺	MP ctx ��RF�ṩ���Խű�����
BT ���ԣ�TODO)
	��δ���	

�������ԣ�¯��¯��һ�£�	
	
	UART - 5Mbps	UART1 TX--UART1  RX
		UART2 TX--UART2  R
	I2C - 3.4Mbps	I2C1--I2C2 �����1.5Kohm���裩
	ADC - sample 10s	ADC2����MBIAS1
			VBAT_MEAS����MBIAS2
	USB - 480Mbps	45ŷķ��GND����Loopback
	DDR2 - 533Mbps	��д
	FLASH��MCM��	��д
	GPIO	externl loop: A3--A4;
	eMMC��SDIO��	externl loop: B25--B26;B27--B28;B29--B30;
	eMMC��SDIO��	PB31-PC1output High
	AUDIO		AMIC_N/P��LOUT��loop	
			AMIC1/2---AOUT_R
			AMIC3/5---AOUT_L
	CA7 Task		1.0GHz ��	DDR ��д����

	WDG		4s @hp
	Timer		10min�����dslp 3s wakeup

ָʾ��
	������˸		����������û��ʧ�ܵĲ�����
	����		��������ʧ�ܵ�case
	��˸		¯��¯��cease�л�


NOTE��This readme is specific for QFN144 test case