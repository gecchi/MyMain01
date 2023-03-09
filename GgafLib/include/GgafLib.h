#ifndef GGAF_LIB_H_
#define GGAF_LIB_H_
#include "GgafLibCommonHeader.h"
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

extern HINSTANCE WinMain_hInstance;
extern HINSTANCE WinMain_hPrevInstance;
extern LPTSTR WinMain_lpCmdLine;
extern int WinMain_nCmdShow;

/**
 * ���C������ .
 * @param argc
 * @param argv
 * @return
 */
void LibMain(int argc, char *argv[]);

/**
 * WinMain�̏������� .
 * @param hInstance
 * @param hPrevInstance
 * @param lpCmdLine
 * @param nCmdShow
 */
void LibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

/**
 * GgafCore::�t���[�����[�N�̃E�B���h�E�v���V�[�W������ .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void LibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



#endif /*GGAF_LIB_H_*/

