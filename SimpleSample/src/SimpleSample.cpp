/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "GgafLib.h" //"GgafLib.h" をインクルードしてください。

#include "SimpleSample.h"
#include "SmpGod.h"

using namespace SimpleSample;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //直後に、こう呼び出して下さい。
}

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //直後に、この様に呼び出して下さい。

    //プロパティファイル読込み
    CONFIG::loadProperties("config.properties");
    //神の誕生
    SmpGod god;
    //ウィンドウ作成
    HWND hWnd1;
    god.createWindow(WndProc, "SimpleSampleWindow", hWnd1);
    //メインループ処理
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return EXIT_SUCCESS; //終了メッセージの場合、アプリ終了
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            god.be(); //このように神の be() メソッドをひたすらコールしてください。
        }
    }
    return (int)msg.wParam;
}

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}


