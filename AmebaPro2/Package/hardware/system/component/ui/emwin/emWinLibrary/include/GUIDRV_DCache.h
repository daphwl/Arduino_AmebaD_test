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
File        : GUIDRV_DCache.h
Purpose     : Interface definition for GUIDRV_DCache driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_DCACHE_H
#define GUIDRV_DCACHE_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Display driver
*/
//
// Address
//
extern const GUI_DEVICE_API GUIDRV_DCache_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_DCACHE &GUIDRV_Win_API

#else

  #define GUIDRV_DCACHE &GUIDRV_DCache_API

#endif

/*********************************************************************
*
*       Public routines
*/
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_DCache_AddDriver(pDevice, pDriver)
  #define GUIDRV_DCache_SetMode1bpp(pDevice)

#else

  void GUIDRV_DCache_AddDriver  (GUI_DEVICE * pDevice, GUI_DEVICE * pDriver);
  void GUIDRV_DCache_SetMode1bpp(GUI_DEVICE * pDevice);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* GUIDRV_DCACHE_H */

/*************************** End of file ****************************/
