#include "GgafLibCommonHeader.h"
#include <windows.h>

#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/WMKeyInput.h"

extern HINSTANCE WinMain_hInstance;
extern HINSTANCE WinMain_hPrevInstance;
extern LPTSTR WinMain_lpCmdLine;
extern int WinMain_nCmdShow;

/**
 * メイン処理 .
 * @param argc
 * @param argv
 * @return
 */
int LibMain(int argc, char *argv[]) {
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
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0') { ++lpCmdLine; }
    while (*lpCmdLine == ' ') { ++lpCmdLine; }

    //本来のWinMainへ
    return ::WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

/**
 * WinMainの初期処理 .
 * @param hInstance
 * @param hPrevInstance
 * @param lpCmdLine
 * @param nCmdShow
 */
void LibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    WinMain_hInstance = hInstance;
    WinMain_hPrevInstance = hPrevInstance;
    WinMain_lpCmdLine = lpCmdLine;
    WinMain_nCmdShow = nCmdShow;
}

/**
 * GgafCore::フレームワークのウィンドウプロシージャ処理 .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void LibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CHAR: {
            GgafLib::WMKeyInput::catchWmChar(wParam);
            break;
        }
        case WM_SIZE: {
            if (pGOD && pGOD->_pHWndPrimary) {
                if (!CONFIG::FULL_SCREEN) {
                    pGOD->_adjustGameWindow = true;
                    pGOD->_pHWnd_adjustScreen = hWnd; //サイズ変更したほうのWINDOW
                }
            }
            GgafCore::God::_pGod->syncTimeFrame();
            break;
        }
        case WM_SIZING: {
            GgafCore::God::_pGod->syncTimeFrame();
            break;
        }
        case WM_MOVING: {
            GgafCore::God::_pGod->syncTimeFrame();
            break;
        }
        case WM_CONTEXTMENU: {
            GgafCore::God::_pGod->syncTimeFrame();
            break;
        }
        case WM_SETFOCUS: {
            if (pGOD->_pHWndPrimary) {
                HRESULT hr;
                // マウス強調レベル設定
                if (GgafDx::Input::_pMouseInputDevice) {
                    hr = GgafDx::Input::_pMouseInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        _TRACE_("LibWndProc() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました");
                    }
                }
                    // キーボード強調レベル設定
                if (GgafDx::Input::_pKeyboardInputDevice) {
                    hr = GgafDx::Input::_pKeyboardInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        MessageBox(hWnd, "LibWndProc() キーボードのSetCooperativeLevelに失敗しました",
                                   "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                    }
                }
                if (GgafDx::Input::_pJoystickInputDevice) {
                    // ゲームスティック協調レベルを設定する
                    hr = GgafDx::Input::_pJoystickInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
                    if (hr != D3D_OK) {
                        _TRACE_("LibWndProc() ジョイスティックSetCooperativeLevelに失敗しました");
                        // ゲームスティックデバイスの初期化を試みる
                        GgafDx::Input::initJoyStick();
                    }
                } else {
                    // ゲームスティックデバイスの初期化を試みる
                    GgafDx::Input::initJoyStick();
                }
            }
            break;
        }
        case WM_SYSCOMMAND: {
            if(wParam == SC_CLOSE) {
                PostQuitMessage(0);
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
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

