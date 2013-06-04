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


HWND _hWnd1_ = nullptr;
HWND _hWnd2_ = nullptr;
HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

/**
 * ウィンドウのサイズを再設定 .
 * @param hWnd 再設定するウィンドウのHWND
 * @param client_width クライアント領域横幅（ピクセル）
 * @param client_height クライアント領域縦幅（ピクセル）
 */
void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height) {
    RECT wRect1, cRect1; // ウィンドウ全体の矩形、クライアント領域の矩形
    pixcoord ww1, wh1; // ウィンドウ全体の幅、高さ
    pixcoord cw1, ch1; // クライアント領域の幅、高さ
    pixcoord fw1, fh1; // フレームの幅、高さ
    // ウィンドウ全体の幅・高さを計算
    GetWindowRect(hWnd, &wRect1);
    ww1 = wRect1.right - wRect1.left;
    wh1 = wRect1.bottom - wRect1.top;
    // クライアント領域の幅・高さを計算
    GetClientRect(hWnd, &cRect1);
    cw1 = cRect1.right - cRect1.left;
    ch1 = cRect1.bottom - cRect1.top;
    // クライアント領域以外に必要なサイズを計算
    fw1 = ww1 - cw1;
    fh1 = wh1 - ch1;
    // 計算した幅と高さをウィンドウに設定
    SetWindowPos(
            hWnd,
            HWND_TOP,
            0,
            0,
            client_width + fw1,
            client_height + fh1,
            SWP_NOMOVE
    );
}

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
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Mouse) {
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    _TRACE_("GgafDxInput::initDx9Input() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました");
                }
            }
                // キーボード強調レベル設定
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Keyboard) {
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    MessageBox(hWnd, TEXT("GgafDxInput::initDx9Input() キーボードのSetCooperativeLevelに失敗しました"),
                               TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                }
            }
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Joystick) {
                // ゲームスティック協調レベルを設定する
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Joystick->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
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


/**
 * ウィンドウ生成処理
 * @param prm_wndclass1 １画面目のWNDCLASSEXパラメータ
 * @param prm_wndclass2 ２画面目のWNDCLASSEXパラメータ
 * @param prm_title1 １画面目のタイトル
 * @param prm_title2 ２画面目のタイトル
 * @param prm_dwStyle1 ウィンドウモード時のウインドウ1のスタイル定数(WS_OVERLAPPEDWINDOW 等)
 * @param prm_dwStyle2 ウィンドウモード時のウインドウ2のスタイル定数(WS_OVERLAPPEDWINDOW 等)
 * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
 * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
 */
void GgafLibCreateWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                         const char* prm_title1   , const char* prm_title2,
                         DWORD       prm_dwStyle1 , DWORD       prm_dwStyle2,
                         HWND&       out_hWnd1    , HWND&       out_hWnd2) {

    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(PROPERTY::BORDER_COLOR);
    prm_wndclass1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    prm_wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));

    // ウインドウの生成
    if (PROPERTY::FULL_SCREEN) {
        if (PROPERTY::DUAL_VIEW) {
            //フルスクリーンモード・２画面使用
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH,
                        PROPERTY::DUAL_VIEW_FULL_SCREEN1_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

            RegisterClassEx(&prm_wndclass2);
            _hWnd2_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH,
                        PROPERTY::DUAL_VIEW_FULL_SCREEN2_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                      );

        } else {
            //フルスクリーンモード・１画面使用
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH,
                        PROPERTY::SINGLE_VIEW_FULL_SCREEN_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

        }
    } else {
        if (PROPERTY::DUAL_VIEW) {
            //ウインドモード・２窓使用
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::DUAL_VIEW_WINDOW1_WIDTH,
                        PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

            RegisterClassEx(&prm_wndclass2);
            _hWnd2_ = CreateWindow(
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        prm_dwStyle2,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::DUAL_VIEW_WINDOW2_WIDTH,
                        PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                      );
        } else {
            //ウインドモード・１窓使用
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        PROPERTY::SINGLE_VIEW_WINDOW_WIDTH,
                        PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );
        }
    }

    out_hWnd1 = _hWnd1_;
    out_hWnd2 = _hWnd2_;

    if (!_hWnd1_) {
        std::cout << "can't CreateWindow " << std::endl;
    }

    //ウィンドウモード時、クライアント領域を所望の大きさにするため、
    //タイトルバー、リサイズボーダーの厚さを考慮し再設定。
    if (!PROPERTY::FULL_SCREEN) {
        if (PROPERTY::DUAL_VIEW) {
            resetWindowsize(_hWnd1_, PROPERTY::DUAL_VIEW_WINDOW1_WIDTH, PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT);
            resetWindowsize(_hWnd2_, PROPERTY::DUAL_VIEW_WINDOW2_WIDTH, PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT);
        } else {
            resetWindowsize(_hWnd1_, PROPERTY::SINGLE_VIEW_WINDOW_WIDTH, PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT);
        }
    }

    //アクティブに
    ShowWindow(_hWnd1_, WinMain_nCmdShow);
    UpdateWindow(_hWnd1_);
    if (PROPERTY::DUAL_VIEW) {
        ShowWindow(_hWnd2_, WinMain_nCmdShow);
        UpdateWindow(_hWnd2_);
    }
}

/**
 * ウィンドウ生成処理 .
 * ウィンドウモード時のウインドウスタイル定数は WS_OVERLAPPEDWINDOW が設定されます。
 * @param prm_wndclass1 １画面目のWNDCLASSEXパラメータ
 * @param prm_wndclass2 ２画面目のWNDCLASSEXパラメータ
 * @param prm_title1 １画面目のタイトル
 * @param prm_title2 ２画面目のタイトル
 * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
 * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
 */
void GgafLibCreateWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                         const char* prm_title1   , const char* prm_title2,
                         HWND&       out_hWnd1    , HWND&       out_hWnd2) {

    GgafLibCreateWindow( prm_wndclass1,  prm_wndclass2,
                         prm_title1   ,  prm_title2,
                         WS_OVERLAPPEDWINDOW, WS_OVERLAPPEDWINDOW,
                         out_hWnd1   ,        out_hWnd2   );
}

/**
 * ウィンドウ生成処理 .
 * 標準的なウィンドウを作成します。
 * @param prm_WndProc ウィンドウプロシージャ関数
 * @param prm_title1 １画面目のタイトル
 * @param prm_title2 ２画面目のタイトル
 * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
 * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
 */
void GgafLibCreateWindow(WNDPROC prm_WndProc,
                         const char* prm_title1, const char* prm_title2,
                         HWND&       out_hWnd1 , HWND&       out_hWnd2  ) {
    //ウィンドウ定義＆作成
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)prm_WndProc;
    wcex1.hInstance = WinMain_hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "primary";
    WNDCLASSEX wcex2 = wcex1; //コピー
    wcex2.lpszClassName = "secondary";

    GgafLibCreateWindow( wcex1,  wcex2,
                         prm_title1   ,  prm_title2,
                         WS_OVERLAPPEDWINDOW, WS_OVERLAPPEDWINDOW,
                         out_hWnd1   ,        out_hWnd2   );
}

//
//#include <windows.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//
//

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

