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
File        : GUI_ARRAY.h
Purpose     : Array handling routines
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_ARRAY_H
#define GUI_ARRAY_H

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public types
*
**********************************************************************
*/
typedef WM_HMEM GUI_ARRAY;

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
GUI_ARRAY GUI_ARRAY_Create          (void);
int       GUI_ARRAY_AddItem         (GUI_ARRAY hArray, const void * pNew, int Len);
void      GUI_ARRAY_Delete          (GUI_ARRAY hArray);
WM_HMEM   GUI_ARRAY_GethItem        (GUI_ARRAY hArray, unsigned int Index);
unsigned  GUI_ARRAY_GetNumItems     (GUI_ARRAY hArray);
void    * GUI_ARRAY_GetpItemLocked  (GUI_ARRAY hArray, unsigned int Index);
int       GUI_ARRAY_SethItem        (GUI_ARRAY hArray, unsigned int Index, WM_HMEM hItem);
WM_HMEM   GUI_ARRAY_SetItem         (GUI_ARRAY hArray, unsigned int Index, const void * pData, int Len);
void      GUI_ARRAY_DeleteItem      (GUI_ARRAY hArray, unsigned int Index);
char      GUI_ARRAY_InsertBlankItem (GUI_ARRAY hArray, unsigned int Index);
WM_HMEM   GUI_ARRAY_InsertItem      (GUI_ARRAY hArray, unsigned int Index, int Len);
void    * GUI_ARRAY_ResizeItemLocked(GUI_ARRAY hArray, unsigned int Index, int Len);

#endif /* GUI_WINSUPPORT */

#endif /* GUI_ARRAY_H */

/*************************** End of file ****************************/
