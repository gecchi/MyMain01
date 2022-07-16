#ifndef GGAF_LIB_H_
#define GGAF_LIB_H_
#include "GgafLibCommonHeader.h"
#include <windows.h>

HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;
/**
 * メイン処理 .
 * @param argc
 * @param argv
 * @return
 */
int LibMain(int argc, char *argv[]);

/**
 * WinMainの初期処理 .
 * @param hInstance
 * @param hPrevInstance
 * @param lpCmdLine
 * @param nCmdShow
 */
void LibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

/**
 * GgafCore::フレームワークのウィンドウプロシージャ処理 .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void LibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



#endif /*GGAF_LIB_H_*/

