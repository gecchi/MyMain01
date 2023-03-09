/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "GgafLib.h" //"GgafLib::Lib.h" をインクルードし、
#include "Hogera.h"

#include "HgrCaretaker.h"
#include <scrnsave.h>
using namespace Hogera;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    //プロパティファイル読込み
    GgafLib::LibConfig::loadProperties(".\\config.properties");

    //ウィンドウ定義＆作成
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)WndProc;
    wcex1.hInstance = hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "primary";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    HWND hWnd1, hWnd2;

    HgrCaretaker crtkr;
    //ゲームループ
    MSG msg;
    try {
        //管理者の誕生
        crtkr.createWindow(wcex1, wcex2,
                         "Hogera[1]", "Hogera[2]", //タイトル文字列
                         dwStyle, dwStyle,
                         hWnd1, hWnd2); //HWNDが代入されます(戻り値)
        //ループ本体
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //次のようにひたすら管理者の present() メソッドをコールしてください。
                crtkr.present();
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "Hogera Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[エラー]:"<<what); //_TRACE_() はデバッグモード時のみ標準出力に出力されます。
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    LibMain(argc, argv); //直後に、この様に呼び出して下さい。
    return WinMain(WinMain_hInstance, WinMain_hPrevInstance, WinMain_lpCmdLine, WinMain_nCmdShow);
}


/**
 * ウィンドウプロシージャ
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    static HRGN hRgn1,hRgn2;
    switch (message) {
        case WM_CREATE: {
            SetWindowRgn(hWnd, hRgn1, 1 );
            break;
        }
        case WM_DESTROY: {
            DeleteObject(hRgn1);
            DeleteObject(hRgn2);
            break;
        }
        // クライアント領域をクリックされた場合、HTCAPTIONを返す
        case WM_NCHITTEST: {
            // クライアント領域をマウスでドラッグしてウィンドウを移動できるように
            // キャプションバーの振りをさせる
            RECT rcClient;
            POINT poClient;
            poClient.x = LOWORD ( lParam );
            poClient.y = HIWORD ( lParam );
            GetClientRect ( hWnd, &rcClient );
            ScreenToClient ( hWnd, &poClient );
            if ( PtInRect ( &rcClient, poClient )
                && GetAsyncKeyState ( VK_LBUTTON ) < 0 ) {
                return HTCAPTION;
            }
            break;
        }
        // フォームがダブルクリックされた場合最大化しない
        case WM_NCLBUTTONDBLCLK: {
            break;
        }
    }
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}


