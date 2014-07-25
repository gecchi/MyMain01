#ifndef GGAFLIBENTRY_H_
#define GGAFLIBENTRY_H_
#include "GgafDxCommonHeader.h"

#include <windows.h>
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/DefaultGod.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //無理やりリンクエラー回避 for GCC
    //VC では不要。これで良いだろうか・・・
//    uintptr_t __security_cookie;
//    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif

#ifdef  __cplusplus
};
#endif


//HWND _hWnd1_ = nullptr;
//HWND _hWnd2_ = nullptr;
HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;
//
//#include <windows.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//
//

/**
 * メイン処理 .
 * @param argc
 * @param argv
 * @return
 */
int GgafLibMain(int argc, char *argv[]) {
    STARTUPINFO StatUpInfo;
    HINSTANCE hInstance;
    HANDLE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;

    GetStartupInfo(&StatUpInfo);
    hInstance = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = GetCommandLine();
    nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW) ? StatUpInfo.wShowWindow : SW_SHOWNORMAL;

    //PG名除去
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0') { lpCmdLine++; }
    while (*lpCmdLine == ' ') { lpCmdLine++; }

    //本来のWinMainへ
    return WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

/**
 * WinMainの初期処理 .
 * @param hInstance
 * @param hPrevInstance
 * @param lpCmdLine
 * @param nCmdShow
 */
void GgafLibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    WinMain_hInstance = hInstance;
    WinMain_hPrevInstance = hPrevInstance;
    WinMain_lpCmdLine = lpCmdLine;
    WinMain_nCmdShow = nCmdShow;
}

/**
 * Ggafフレームワークのウィンドウプロシージャ処理 .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void GgafLibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZE:
            if (GgafDxCore::GgafDxGod::_can_be) {
                if (!PROPERTY::FULL_SCREEN) {
                    GgafDxCore::GgafDxGod::_adjustGameScreen = true;
                    GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = hWnd;
                }
            }
            break;
        case WM_SETFOCUS:
            HRESULT hr;
            if (GgafDxCore::GgafDxInput::_pMouseInputDevice) {
                hr = GgafDxCore::GgafDxInput::_pMouseInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    _TRACE_("GgafDxInput::initDx9Input() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました");
                }
            }
                // キーボード強調レベル設定
            if (GgafDxCore::GgafDxInput::_pKeyboardInputDevice) {
                hr = GgafDxCore::GgafDxInput::_pKeyboardInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    MessageBox(hWnd, "GgafDxInput::initDx9Input() キーボードのSetCooperativeLevelに失敗しました",
                               "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                }
            }
            if (GgafDxCore::GgafDxInput::_pJoystickInputDevice) {
                // ゲームスティック協調レベルを設定する
                hr = GgafDxCore::GgafDxInput::_pJoystickInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
                if (hr != D3D_OK) {
                    _TRACE_("GgafDxInput::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
                }
            }

            break;
        case WM_SYSCOMMAND:
            if(wParam == SC_CLOSE){
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
}


//int main(void) {
//    PIP_ADAPTER_INFO pAdapterInfo;
//    DWORD aiSize;
//    BYTE* paBuff;
//
//    GetAdaptersInfo(nullptr, &aiSize);//必要バッファサイズ取得
//    paBuff = new BYTE[aiSize];
//    pAdapterInfo = (PIP_ADAPTER_INFO) paBuff;
//
//    if (GetAdaptersInfo(pAdapterInfo, &aiSize) != ERROR_SUCCESS) {
//        printf("GetAdapterInfo呼び出し失敗\n");
//        return 1;
//    }
//    std::stringstream ss;
//
//
//    while (pAdapterInfo) {
//        //fprintf(stdout, "MACアドレス = [");
//
//        for (UINT i = 0; i < pAdapterInfo->AddressLength; i++) {
//            ss.width(2);
//            ss.fill('0');
//            ss << std::hex << (int)pAdapterInfo->Address[i];
//            //fprintf(stdout, "%.2X", (int)pAdapterInfo->Address[i]);
//
//            if (i == (pAdapterInfo->AddressLength - 1)) {
//                //fputs("]\n", stdout);
//            } else {
//                ss.width(1);
//                ss << "-";
//                //fputs("-", stdout);
//            }
//        }
//        pAdapterInfo = pAdapterInfo->Next;
//    }
//    delete[] paBuff;
//    printf("%s", ss.str().c_str());
//    return 0;
//}





#endif /*GGAFLIBENTRY_H_*/

