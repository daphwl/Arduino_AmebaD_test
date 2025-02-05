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
File        : HEADER_Private.h
Purpose     : Private HEADER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef HEADER_PRIVATE_H
#define HEADER_PRIVATE_H


#include "HEADER.h"
#include "WIDGET.h"
#include "WM.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  int     Width;
  I16     Align;
  WM_HMEM hDrawObj;
  char    acText[1];
} HEADER_COLUMN;

typedef struct {
  WIDGET_DRAW_ITEM_FUNC * pfDrawSkin;
} HEADER_SKIN_PRIVATE;

typedef struct {
  const GUI_FONT    * pFont;
  GUI_COLOR           BkColor;
  GUI_COLOR           TextColor;
  GUI_COLOR           ArrowColor;
  HEADER_SKIN_PRIVATE SkinPrivate;
} HEADER_PROPS;

typedef struct {
  WIDGET              Widget;
  HEADER_PROPS        Props;
  WIDGET_SKIN const * pWidgetSkin;
  GUI_ARRAY           Columns;
  int                 CapturePosX;
  int                 CaptureItem;
  int                 ScrollPos;
  int                 Sel;
  int                 DirIndicatorColumn;
  int                 DirIndicatorReverse;
  unsigned            Fixed;
  U8                  DragLimit;
} HEADER_Obj;

/*********************************************************************
*
*       Private (module internal) data
*
**********************************************************************
*/

extern HEADER_PROPS        HEADER__DefaultProps;
extern const GUI_CURSOR  * HEADER__pDefaultCursor;
extern int                 HEADER__DefaultBorderH;
extern int                 HEADER__DefaultBorderV;

extern const WIDGET_SKIN   HEADER__SkinClassic;
extern       WIDGET_SKIN   HEADER__Skin;

extern WIDGET_SKIN const * HEADER__pSkinDefault;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define HEADER_INIT_ID(p)  (p->Widget.DebugId = HEADER_ID)
#else
  #define HEADER_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  HEADER_Obj * HEADER_LockH(HEADER_Handle h);
  #define HEADER_LOCK_H(h)   HEADER_LockH(h)
#else
  #define HEADER_LOCK_H(h)   (HEADER_Obj *)GUI_LOCK_H(h)
#endif

void HEADER__SetDrawObj(HEADER_Handle hObj, unsigned Index, GUI_DRAW_HANDLE hDrawObj);


#endif // GUI_WINSUPPORT
#endif // Avoid multiple inclusion

/*************************** End of file ****************************/
