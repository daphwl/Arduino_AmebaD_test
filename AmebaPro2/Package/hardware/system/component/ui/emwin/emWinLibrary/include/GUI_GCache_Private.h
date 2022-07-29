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
File        : GUI_GCache_Private.h
Purpose     : Private header
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_GCACHE_PRIVATE_H
#define GUI_GCACHE_PRIVATE_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define DRIVER_CONTEXT DRIVER_CONTEXT_GCACHE

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       DRIVER_CONTEXT
*/
typedef struct {
  int x0, y0, x1, y1, IsDirty;
  int xSize, ySize;
  int CacheLocked;
  int MemSize;
  int BitsPerPixel;
  int BytesPerLine;
  //
  // Line buffer for reading operation
  //
  LCD_PIXELINDEX * pLineBuffer;
  //
  // Palette for drawing 'cache bitmap'
  //
  LCD_PIXELINDEX * pPalette;
  //
  // Cache management
  //
  void (* pfReadRect)     (GUI_DEVICE * pDevice, int _x0, int _y0, int _x1, int _y1, LCD_PIXELINDEX * pBuffer);
  void (* pfSendCacheRect)(GUI_DEVICE * pDevice);
  U32 * pVMEM;
  //
  // Drawing functions
  //
  void           (* pfDrawBitmap   )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int xsize, int ysize, int _BitsPerPixel, int _BytesPerLine, const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans);
  void           (* pfDrawHLine    )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int _x1);
  void           (* pfDrawVLine    )(GUI_DEVICE *  pDevice,  int _x , int _y0, int _y1);
  void           (* pfFillRect     )(GUI_DEVICE *  pDevice,  int _x0, int _y0, int _x1, int _y1);
  LCD_PIXELINDEX (* pfGetPixelIndex)(GUI_DEVICE *  pDevice,  int _x, int _y);
  void           (* pfSetPixelIndex)(GUI_DEVICE *  pDevice,  int _x, int _y, LCD_PIXELINDEX ColorIndex);
  void           (* pfXorPixel     )(GUI_DEVICE *  pDevice,  int _x, int _y);
  //
  // GetData function
  //
  void          *(* pfGetDevData   )(GUI_DEVICE *  pDevice,  int Index);
} DRIVER_CONTEXT;

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
GUI_DEVICE * GUI_GCACHE__CreateEx(int LayerIndex, const LCD_API_COLOR_CONV * pColorConvAPI, int BitsPerPixel);

#endif

/*************************** End of file ****************************/
