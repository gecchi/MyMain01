#include "stdafx.h"
#include "GgafLibEntry.h"

#include "VvvGod.h"

using namespace VVViewer;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv);
}

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    //プロパティファイル読込み
    GgafLib::GgafLibProperties::load(".\\config.properties");

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


    //神の誕生
    VvvGod* pGod = new VvvGod();
    //ゲームループ
    MSG msg;
    try {
        pGod->createWindow(wcex1, wcex2,
                           "VVViewer[1]", "VVViewer[2]", //タイトル文字列
                           dwStyle, dwStyle,
                           hWnd1, hWnd2);
        DragAcceptFiles(hWnd1, TRUE);
        //ループ本体
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //終了メッセージの場合アプリを終了
                    if (VvvGod::_can_be) {
                        VvvGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        delete pGod;
                        GgafLib::GgafLibProperties::clean(); //プロパティ解放
                    }
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                if (VvvGod::_can_be) {
                    pGod->be();
                }
            }
        }
    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "VVViewer Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        _TRACE_("[エラー]:"<<what); //_TRACE_() はデバッグモード時のみ標準出力に出力されます。
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    //必要があれば、メッセージ処理をココに追加記述
    switch (message) {
        case WM_DROPFILES: {/* ファイルがドロップされた時の処理 */
            HDROP  hDrop = (HDROP)wParam;
            UINT  uFileNo = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, nullptr, 0);
            for(int i = 0; i < (int)uFileNo; i++) {
                DragQueryFile(hDrop, i, VvvGod::dropfiles_, sizeof(VvvGod::dropfiles_));
                _TRACE_("VvvGod::dropfiles_="<<VvvGod::dropfiles_);
            }
            DragFinish(hDrop);
            VvvGod::is_wm_dropfiles_ = true;
            break;
        }
        default: {
            break;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

