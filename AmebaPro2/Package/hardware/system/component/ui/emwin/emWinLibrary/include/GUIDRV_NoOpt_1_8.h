/**********************************************************************
*                 SEGGER Software GmbH                               *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2019  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Realtek 
Semiconductor Corp. at the address: Realtek Semiconductor Corp., 
Hsinchu Science Park, Innovation Rd. II 2, 300 Hsinchu city, Taiwan for 
the purposes  of  creating  libraries  for its Cortex-M series of 
Microcontroller Units designed, branded, marketed and manufactured by 
Realtek Semiconductor Corp. under the terms and conditions of an End 
User License Agreement supplied with the libraries.

Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Realtek Semiconductor Corp., Hsinchu Science Park, Innovation Rd. II 2, 300 Hsinchu city, Taiwan
Licensed SEGGER software: emWin
License number:           GUI-00784
License model:            emWin Buyout Agreement, signed May 15th, 2019
Licensed platform:        Cortex-M series of Microcontroller Units designed, branded, marketed and manufactured by LICENSEE
----------------------------------------------------------------------
File        : GUIDRV_NoOpt_1_8.h
Purpose     : Interface definition for non optimized drawing functions
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#ifndef GUIDRV_NOOPT_1_8_H
#define GUIDRV_NOOPT_1_8_H

void GUIDRV__NoOpt_XorPixel  (GUI_DEVICE * pDevice, int x, int y);
void GUIDRV__NoOpt_DrawHLine (GUI_DEVICE * pDevice, int x0, int y,  int x1);
void GUIDRV__NoOpt_DrawVLine (GUI_DEVICE * pDevice, int x, int y0,  int y1);
void GUIDRV__NoOpt_FillRect  (GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1);
void GUIDRV__NoOpt_DrawBitmap(GUI_DEVICE * pDevice, int x0, int y0, int xSize, int ySize, int BitsPerPixel, int BytesPerLine, const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans);

#endif

/*************************** End of file ****************************/
