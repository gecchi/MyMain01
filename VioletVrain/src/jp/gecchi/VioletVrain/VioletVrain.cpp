#include "jp/ggaf/GgafLib.h"
#include "jp/gecchi/VioletVrain/VioletVrain.h"

#include "jp/gecchi/VioletVrain/VvCaretaker.h"

using namespace VioletVrain;


/**
 * ウィンドウプロシージャ
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    //プロパティファイル読込み
    CONFIG::loadProperties(".\\config.properties");

    VvCaretaker caretkr;
    MSG msg;
    try {
        caretkr.createWindow(WndProc, "VioletVrain");
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                caretkr.present();
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "VioletVrain Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[エラー]:"<<what);
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return CALL_WinMain(); //直後に、この様に呼び出して下さい。
}

