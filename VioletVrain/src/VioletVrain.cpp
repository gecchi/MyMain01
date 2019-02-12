#include "GgafLib.h"
#include "VioletVrain.h"

#include "jp/gecchi/VioletVrain/VvGod.h"

using namespace VioletVrain;


/**
 * ウィンドウプロシージャ
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return LibMain(argc, argv); //直後に、この様に呼び出して下さい。
}

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    LibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //直後に、この様に呼び出して下さい。

    //プロパティファイル読込み
    CONFIG::loadProperties(".\\config.properties");

    VvGod god;
    MSG msg;
    HWND hWnd1;
    try {
        god.createWindow(WndProc, "VioletVrain", hWnd1);
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                god.be();
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

