/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "SimpleSample.h"
#include "SmpCaretaker.h"
#include "jp/ggaf/GgafLib.h" //インクルードしてください。

using namespace SimpleSample;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    //プロパティファイル読込み
    CONFIG::loadProperties("config.properties");
    //管理者の誕生
    SmpCaretaker crtkr;
    //ウィンドウ作成
    HWND hWnd1;
    crtkr.createWindow(WndProc, "SimpleSampleWindow", hWnd1);
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
            crtkr.present(); //このように管理者の present() メソッドをひたすらコールしてください。
        }
    }
    return (int)msg.wParam;
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return CALL_WinMain(); //このマクロを記述して WinMain() を実行呼び出してください。
}

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //FW のプロシージャ処理を行います。
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}
