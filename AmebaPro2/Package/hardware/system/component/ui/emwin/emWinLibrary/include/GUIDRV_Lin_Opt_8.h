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
File        : GUIDRV_Lin_Opt_8.h
Purpose     : Optimized routines, included by GUIDRV_Lin_..._8.c
---------------------------END-OF-HEADER------------------------------
*/

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _FillRectOpt8
*
* Purpose:
*   Optimized filling routine for 8 bpp
*/
static void _FillRectOpt8(GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1) {
  DRIVER_CONTEXT * pContext;
  U32 Data, ColorMask, AndMask, Off0, OffLine;
  int NumPixel_0, NumPixel_1, RemPixels, NumLines, RemLines, RemItems;
  LCD_PIXELINDEX ColorIndex;
  U32 * pDest;

  pContext   = (DRIVER_CONTEXT *)pDevice->u.pContext;
  ColorIndex = LCD__GetColorIndex();
  Off0       = XY2OFF32(pContext->vxSizePhys, x0, y0);
  RemPixels  = x1 - x0 + 1;
  NumLines   = y1 - y0 + 1;
  OffLine    = pContext->vxSizePhys >> 2;
  NumPixel_0 = x0 & 3;
  NumPixel_1 = x1 & 3;
  if (GUI_pContext->DrawMode & LCD_DRAWMODE_XOR) {
    //
    // First DWORD
    //
    if (NumPixel_0) {
      for (RemLines = NumLines; RemLines; RemLines--) {
        pDest   = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        AndMask = ~(0xFFFFFFFF << (8 * NumPixel_0));
        if ((RemPixels < 3) && (NumPixel_1)) {
          AndMask |= ~(0xFFFFFFFF >> (8 * (3 - NumPixel_1)));
        }
        #if (LCD_ENDIAN_BIG == 1)
          MIRROR(AndMask);
        #endif
        Data = READ_MEM32P(pDest);
        Data ^= ~AndMask;
        WRITE_MEM32P(pDest, Data);
      }
      Off0++;
      RemPixels -= (4 - NumPixel_0);
    }
    //
    // Complete DWORDS
    //
    if (RemPixels >= 4) {
      for (RemLines = NumLines; RemLines; RemLines--) {
        RemItems = RemPixels;
        pDest    = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        while (RemItems >= 4) {
          Data  = READ_MEM32P(pDest);
          Data ^= 0xFFFFFFFF;
          WRITE_MEM32P(pDest, Data);
          pDest++;
          RemItems -= 4;
        }
      }
      Off0      += (RemPixels >> 2);
      RemPixels -= (RemPixels >> 2) << 2;
    }
    //
    // Last DWORD
    //
    if (RemPixels > 0) {
      for (RemLines = NumLines; RemLines; RemLines--) {
        pDest   = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        AndMask = 0xFFFFFF00 << (8 * NumPixel_1);
        #if (LCD_ENDIAN_BIG == 1)
          MIRROR(AndMask);
        #endif
        Data = READ_MEM32P(pDest);
        Data ^= ~AndMask;
        WRITE_MEM32P(pDest, Data);
      }
    }
  } else {
    //
    // First DWORD
    //
    if (NumPixel_0) {
      for (RemLines = NumLines; RemLines; RemLines--) {
        pDest   = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        AndMask = ~(0xFFFFFFFF << (8 * NumPixel_0));
        if ((RemPixels < 3) && (NumPixel_1)) {
          AndMask |= ~(0xFFFFFFFF >> (8 * (3 - NumPixel_1)));
        }
        ColorMask = (ColorIndex * 0x01010101) & ~AndMask;
        #if (LCD_ENDIAN_BIG == 1)
          MIRROR(AndMask);
          MIRROR(ColorMask);
        #endif
        Data = READ_MEM32P(pDest);
        Data &= AndMask;
        Data |= ColorMask;
        WRITE_MEM32P(pDest, Data);
      }
      Off0++;
      RemPixels -= (4 - NumPixel_0);
    }
    //
    // Complete DWORDS
    //
    if (RemPixels >= 4) {
      ColorMask = ColorIndex * 0x01010101;
      for (RemLines = NumLines; RemLines; RemLines--) {
        RemItems = RemPixels;
        pDest    = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        while (RemItems >= 32) {
          WRITE_MEM32P(pDest    , ColorMask);
          WRITE_MEM32P(pDest + 1, ColorMask);
          WRITE_MEM32P(pDest + 2, ColorMask);
          WRITE_MEM32P(pDest + 3, ColorMask);
          WRITE_MEM32P(pDest + 4, ColorMask);
          WRITE_MEM32P(pDest + 5, ColorMask);
          WRITE_MEM32P(pDest + 6, ColorMask);
          WRITE_MEM32P(pDest + 7, ColorMask);
          pDest += 8;
          RemItems -= 32;
        }
        while (RemItems >= 4) {
          WRITE_MEM32P(pDest, ColorMask);
          pDest++;
          RemItems -= 4;
        }
      }
      Off0      += (RemPixels >> 2);
      RemPixels -= (RemPixels >> 2) << 2;
    }
    //
    // Last DWORD
    //
    if (RemPixels > 0) {
      for (RemLines = NumLines; RemLines; RemLines--) {
        pDest   = ((U32 *)pContext->VRAMAddr) + Off0 + OffLine * (RemLines - 1);
        AndMask = 0xFFFFFF00 << (8 * NumPixel_1);
        ColorMask = (ColorIndex * 0x01010101) & ~AndMask;
        #if (LCD_ENDIAN_BIG == 1)
          MIRROR(AndMask);
          MIRROR(ColorMask);
        #endif
        Data = READ_MEM32P(pDest);
        Data &= AndMask;
        Data |= ColorMask;
        WRITE_MEM32P(pDest, Data);
      }
    }
  }
}

/*************************** End of file ****************************/
