#ifndef GGAF_LIB_H_
#define GGAF_LIB_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

/** WinMain() を呼び出すマクロ */
#define  CALL_WinMain()  WinMain(get_WinMain_hInstance(), get_WinMain_hPrevInstance(), get_WinMain_lpCmdLine(), get_WinMain_nCmdShow())

extern HINSTANCE WinMain_hInstance;
extern HINSTANCE WinMain_hPrevInstance;
extern LPTSTR WinMain_lpCmdLine;
extern int WinMain_nCmdShow;

HINSTANCE get_WinMain_hInstance();
HINSTANCE get_WinMain_hPrevInstance();
LPTSTR get_WinMain_lpCmdLine();
int get_WinMain_nCmdShow();

/**
 * GgafCore::フレームワークのウィンドウプロシージャ処理 .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void LibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif /*GGAF_LIB_H_*/

