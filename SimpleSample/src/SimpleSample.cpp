/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "GgafLib.h" //"GgafLib::Lib.h" をインクルードしてください。

#include "SimpleSample.h"
#include "SmpCaretaker.h"

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
    LibMain(argc, argv); //直後に、この様に呼び出して下さい。
    return WinMain(WinMain_hInstance, WinMain_hPrevInstance, WinMain_lpCmdLine, WinMain_nCmdShow);
}

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}
