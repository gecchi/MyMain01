/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "stdafx.h"
#include "GgafLibEntry.h" //"GgafLibEntry.h" をインクルードし、
                          //main関数 WinMain関数 ウィンドウプロシージャは
                          //１つのファイルに記述します。

#include "SmpGod.h"

using namespace SimpleSample;

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //直後に、この様に呼び出して下さい。
}


/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //直後に、この様に呼び出して下さい。

    //プロパティファイル読込み
    GgafLib::GgafLibProperties::load(".\\config.properties");

    //ウィンドウ作成
    HWND hWnd1, hWnd2;
    GgafLibCreateWindow(WndProc,
                        "SimpleSample[1]", "SimpleSample[2]",
                        hWnd1, hWnd2); //HWNDが代入されます(戻り値)

    //ゲームループ
    MSG msg;
    try {
        //神の誕生
        SmpGod* pGod = new SmpGod(hInstance, hWnd1, hWnd2);
        pGod->initDevice();
        timeBeginPeriod(1);
        //ループ本体
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //終了メッセージの場合アプリを終了
                    if (SmpGod::_can_be) {
                        SmpGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        GGAF_DELETE(pGod);
                        GgafLib::GgafLibProperties::clean(); //プロパティ解放
                    }
                    timeEndPeriod(1);
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //次のようにひたすら神の be() メソッドをコールしてください。
                if (SmpGod::_can_be) {
                    pGod->be();
                }
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "SimpleSample Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[エラー]:"<<what); //_TRACE_() はデバッグモード時のみ標準出力に出力されます。
        timeEndPeriod(1);
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

