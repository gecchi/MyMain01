/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "jp/ggaf/GgafLib.h" //"GgafLib::Lib.h" をインクルードし、
#include "Mogera.h"

#include "MgrCaretaker.h"
#include <scrnsave.h>
using namespace Mogera;

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
    wcex1.lpszClassName = "Mogera";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    //管理者の誕生
    MgrCaretaker caretkr;
    //ゲームループ
    MSG msg;
    try {
        //ウィンドウ生成
        caretkr.createWindow(wcex1, "Mogera", dwStyle);
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
                caretkr.present();
            }
        }
    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "Mogera Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[エラー]:"<<what); //_TRACE_() はデバッグモード時のみ標準出力に出力されます。
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return CALL_WinMain();
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
    }
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}


