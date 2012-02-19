#ifndef GGAFLIBENTORY_H_
#define GGAFLIBENTORY_H_
#include "GgafDxCommonHeader.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //無理やりリンクエラー回避 for GCC
    //VC では不要。良い方法がないものか・・・
    uintptr_t __security_cookie;
    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif

#ifdef  __cplusplus
};
#endif


HWND _hWnd1_ = NULL;
HWND _hWnd2_ = NULL;
HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

void resetWindowsize(HWND hWnd, int client_width, int client_height) {
    RECT wRect1, cRect1; // ウィンドウ全体の矩形、クライアント領域の矩形
    int ww1, wh1; // ウィンドウ全体の幅、高さ
    int cw1, ch1; // クライアント領域の幅、高さ
    int fw1, fh1; // フレームの幅、高さ
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

void resetWindowsize(HWND hWnd) {
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            if (hWnd == _hWnd2_) {
                resetWindowsize(hWnd, GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else if (hWnd == _hWnd1_) {
                resetWindowsize(hWnd, GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
            }
        } else {
            resetWindowsize(hWnd, GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
        }
    }
}

void GgafLibMain(int argc, char *argv[]) {
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

    /* GetCommandLineからプログラム名を抜きます。 */
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0')
        lpCmdLine++;
    while (*lpCmdLine == ' ')
        lpCmdLine++;
    cout << lpCmdLine << endl;

    //本来のWinMainへ
    WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

void GgafLibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    WinMain_hInstance = hInstance;
    WinMain_hPrevInstance = hPrevInstance;
    WinMain_lpCmdLine = lpCmdLine;
    WinMain_nCmdShow = nCmdShow;
}


void GgafLibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZE:
            if (GgafDxCore::GgafDxGod::_can_be) {
                if (!GGAF_PROPERTY(FULL_SCREEN)) {
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

void GgafLibCreateWindow(WNDCLASSEX& wndclass1, WNDCLASSEX& wndclass2,
                         const char* title1, const char* title2,
                         HWND& out_hWnd1, HWND& out_hWnd2) {

    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    wndclass1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));

    // ウインドウの生成
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            //フルスクリーンモード・２画面使用
            RegisterClassEx(&wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        wndclass1.lpszClassName, //WINDOW_CLASS,
                        title1,//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        wndclass1.hInstance,
                        NULL
                    );

            RegisterClassEx(&wndclass2);
            _hWnd2_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        wndclass2.lpszClassName, //WINDOW_CLASS,
                        title2,//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        wndclass2.hInstance,
                        NULL
                    );

        } else {
            //フルスクリーンモード・１画面使用
            RegisterClassEx(&wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        wndclass1.lpszClassName, //WINDOW_CLASS,
                        title1,//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH),
                        GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        wndclass1.hInstance,
                        NULL
                    );

        }
    } else {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            RegisterClassEx(&wndclass1);
            _hWnd1_ = CreateWindow(
                    wndclass1.lpszClassName, //WINDOW_CLASS,          // ウインドウクラス名
                    title1,//WINDOW_TITLE,             // ウインドウのタイトル名
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), // ウィンドウの幅
                    GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    wndclass1.hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );

            RegisterClassEx(&wndclass2);
            _hWnd2_ = CreateWindow(
                    wndclass2.lpszClassName, //WINDOW_CLASS,
                    title2,//WINDOW_TITLE,
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ウインドウスタイル
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), // ウィンドウの幅
                    GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    wndclass2.hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );
        } else {
            RegisterClassEx(&wndclass1);
            _hWnd1_ = CreateWindow(
                    wndclass1.lpszClassName, //WINDOW_CLASS,          // ウインドウクラス名
                    title1,//WINDOW_TITLE,             // ウインドウのタイトル名
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), // ウィンドウの幅
                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    wndclass1.hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );
        }
    }

    out_hWnd1 = _hWnd1_;
    out_hWnd2 = _hWnd2_;

    if (!_hWnd1_) {
        cout << "can't CreateWindow " << endl;
    }

    //ウィンドウ時、
    //クライアント領域を所望の大きさにするため、
    //タイトルバー、リサイズボーダーの厚さを考慮し、再設定。
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            resetWindowsize(_hWnd1_, GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
            resetWindowsize(_hWnd2_, GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
        } else {
            resetWindowsize(_hWnd1_, GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
        }
    }

    //アクティブに
    ShowWindow(_hWnd1_, WinMain_nCmdShow);
    UpdateWindow(_hWnd1_);
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        ShowWindow(_hWnd2_, WinMain_nCmdShow);
        UpdateWindow(_hWnd2_);
    }
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
//    GetAdaptersInfo(NULL, &aiSize);//必要バッファサイズ取得
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





























#endif /*GGAFLIBENTORY_H_*/

