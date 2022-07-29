#ifndef __GT911_H
#define __GT911_H	
#include "sys.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//4.3����ݴ�����-GT9147 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved		 
////////////////////////////////////////////////////////////////////////////////// 


//IO��������	 

#define RST_PIN 				_PA_18
#define SCL_PIN				_PB_5
#define SDA_PIN				_PB_6
#define INT_PIN				_PA_17

#define GT911_RST_1()  GPIO_WriteBit(RST_PIN, 1)//PIout(8)=1	/* RST = 1 */ 
#define GT911_RST_0()  GPIO_WriteBit(RST_PIN, 0) //PIout(8)=0	/* RST = 0 */ 

#define GT911_INT_1()  	 GPIO_WriteBit(INT_PIN, 1)//PHin(7)=1/* INT = 1 */ 
#define GT911_INT_0()  	 GPIO_WriteBit(INT_PIN, 0)//PHin(7)=0/* INT = 0 */ 
 
 
 
//I2C��д����	
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		//������
  
//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  
 
 
 //һ��δʹ��
#define GT911_READ_XY_REG 					0x814E	/* ����Ĵ��� */ 
#define GT911_CLEARBUF_REG 					0x814E	/* �������Ĵ��� */ 
#define GT911_CONFIG_REG 						0x8047	/* ���ò����Ĵ��� */ 
#define GT911_COMMAND_REG 					0x8040 	/* ʵʱ���� */ 
#define GT911_PRODUCT_ID_REG 				0x8140 	/*productid*/ 
#define GT911_VENDOR_ID_REG 				0x814A 	/* ��ǰģ��ѡ����Ϣ */ 
#define GT911_CONFIG_VERSION_REG 		0x8047 	/* �����ļ��汾�� */ 
#define GT911_CONFIG_CHECKSUM_REG 	0x80FF 	/* �����ļ�У���� */ 
#define GT911_FIRMWARE_VERSION_REG	0x8144 	/* �̼��汾�� */  


#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct
{
	
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)							
	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	u8 touchtype;
}_m_tp_dev;

 
 
u8 GT911_Send_Cfg(u8 mode);
u8 GT911_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT911_RD_Reg(u16 reg,u8 *buf,u8 len); 
u8 GT911_Init(void);
u8 GT911_Scan(u8 mode); 


void GT911_Reset_Sequence(uint8_t ucAddr);//δʹ��
void GT911_Soft_Reset(void);//δʹ��
#endif













