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
File        : Dialog.h
Purpose     : Dialog box include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef DIALOG_INTERN_H
#define DIALOG_INTERN_H

#include "WM.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {        // Make sure we have C-declarations in C++ programs
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct  GUI_WIDGET_CREATE_INFO_struct GUI_WIDGET_CREATE_INFO;
typedef WM_HWIN GUI_WIDGET_CREATE_FUNC        (const GUI_WIDGET_CREATE_INFO * pCreate, WM_HWIN hWin, int x0, int y0, WM_CALLBACK * cb);

/*********************************************************************
*
*       Structures
*
**********************************************************************
*/
struct GUI_WIDGET_CREATE_INFO_struct {
  GUI_WIDGET_CREATE_FUNC * pfCreateIndirect;
  const char             * pName;            // Text ... Not used on all widgets
  I16                      Id;               // ID ... should be unique in a dialog
  I16                      x0;               // x position
  I16                      y0;               // y position
  I16                      xSize;            // x size
  I16                      ySize;            // y size
  U16                      Flags;            // Widget specific create flags (opt.)
  I32                      Para;             // Widget specific parameter (opt.)
  U32                      NumExtraBytes;    // Number of extra bytes usable with <WIDGET>_SetUserData & <WIDGET>_GetUserData
};

/*********************************************************************
*
*       Public API functions
*
**********************************************************************
*/
WM_HWIN            GUI_CreateDialogBox   (const GUI_WIDGET_CREATE_INFO * paWidget, int NumWidgets, WM_CALLBACK * cb, WM_HWIN hParent, int x0, int y0);
void               GUI_EndDialog         (WM_HWIN hWin, int r);
int                GUI_ExecDialogBox     (const GUI_WIDGET_CREATE_INFO * paWidget, int NumWidgets, WM_CALLBACK * cb, WM_HWIN hParent, int x0, int y0);
int                GUI_ExecCreatedDialog (WM_HWIN hDialog);
WM_DIALOG_STATUS * GUI_GetDialogStatusPtr(WM_HWIN hDialog);                                    // Not to be documented
void               GUI_SetDialogStatusPtr(WM_HWIN hDialog, WM_DIALOG_STATUS * pDialogStatus);  // Not to be documented

/*********************************************************************
*
*       Obsolete
*/
LCD_COLOR          DIALOG_GetBkColor(void);
LCD_COLOR          DIALOG_SetBkColor(LCD_COLOR BkColor);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // DIALOG_INTERN_H

/*************************** End of file ****************************/
