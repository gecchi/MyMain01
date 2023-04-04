#include "jp/ggaf/GgafLib.h"
#include <windows.h>

#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/util/WMKeyInput.h"

HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

HINSTANCE get_WinMain_hInstance() {
    WinMain_hInstance = GetModuleHandle(0);
    return WinMain_hInstance;
}

HINSTANCE get_WinMain_hPrevInstance() {
    WinMain_hPrevInstance = 0;
    return WinMain_hPrevInstance;
}

LPTSTR get_WinMain_lpCmdLine() {
    WinMain_lpCmdLine = GetCommandLine();
    //PG名除去
    while (*WinMain_lpCmdLine != ' ' && *WinMain_lpCmdLine != '\0') { ++WinMain_lpCmdLine; }
    while (*WinMain_lpCmdLine == ' ') { ++WinMain_lpCmdLine; }
    return WinMain_lpCmdLine;
}

int get_WinMain_nCmdShow() {
    STARTUPINFO StatUpInfo;
    GetStartupInfo(&StatUpInfo);
    WinMain_nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW) ? StatUpInfo.wShowWindow : SW_SHOWNORMAL;
    return WinMain_nCmdShow;
}

/**
 * フレームワークのウィンドウプロシージャ処理 .
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
            if (pCARETAKER && pCARETAKER->_pHWndPrimary) {
                if (!CONFIG::FULL_SCREEN) {
                    pCARETAKER->_adjustGameWindow = true;
                }
            }
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_SIZING: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_MOVING: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_CONTEXTMENU: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_SETFOCUS: {
            if (pCARETAKER->_pHWndPrimary) {
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
                if (GgafDx::Input::_apJoystickInputDevice[P1_JOY_STICK]) {
                    // ゲームスティック協調レベルを設定する
                    hr = GgafDx::Input::_apJoystickInputDevice[P1_JOY_STICK]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
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

//#define MOUSEEVENTF_FROMTOUCH 0xFF515700
//
//switch(uMsg){
//case WM_LBUTTONDOWN:
//    {
//        auto extra = GetMessageExtraInfo();
//        if((extra & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH){
//            if(extra & 0x80){
//                // 入力はタッチ
//            }else{
//                // 入力はペン
//            }
//        }else{
//            // 入力はマウス
//        }
//        break;
//    }
//}


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

