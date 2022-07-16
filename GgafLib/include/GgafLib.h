#ifndef GGAF_LIB_H_
#define GGAF_LIB_H_
#include "GgafLibCommonHeader.h"
#include <windows.h>

HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;
/**
 * ���C������ .
 * @param argc
 * @param argv
 * @return
 */
int LibMain(int argc, char *argv[]);

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

