#include "GgafLibEntry.h"

#include "VvvGod.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
using namespace VVViewer;

#define MY_IDM_RESET_WINDOW_SIZE  10
HWND hWnd1, hWnd2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);
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



    //神の誕生
    VvvGod god = VvvGod();
    //ゲームループ
    MSG msg;
    try {
        god.createWindow(wcex1, wcex2,
                         "VVViewer[1]", "VVViewer[2]", //タイトル文字列
                         dwStyle, dwStyle,
                         hWnd1, hWnd2);
        DragAcceptFiles(hWnd1, TRUE);
        //ループ本体
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

        case WM_CREATE: {
            // システムメニューカスタム関数を呼ぶ
            CustmizeSysMenu(hWnd);
            break;
        }
        case WM_DROPFILES: {/* ファイルがドロップされた時の処理 */
            HDROP hDrop = (HDROP)wParam;
            UINT uFileNo = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, nullptr, 0);
            for (int i = 0; i < (int)uFileNo; i++) {
                DragQueryFile(hDrop, i, VvvGod::dropfiles_, sizeof(VvvGod::dropfiles_));
                _TRACE_("VvvGod::dropfiles_="<<VvvGod::dropfiles_);
            }
            DragFinish(hDrop);
            VvvGod::is_wm_dropfiles_ = true;
            break;
        }
        case WM_SYSCOMMAND: {
            if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //初期ウィンドウサイズにリセット
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::DUAL_VIEW_WINDOW1_WIDTH, PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::DUAL_VIEW_WINDOW2_WIDTH, PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::SINGLE_VIEW_WINDOW_WIDTH, PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT);
                    }
                }
            }
            break;
        }
        case WM_SYSKEYDOWN: {
            if (LOWORD(wParam) == VK_F10) {
                return TRUE;
            }
            if (LOWORD(wParam) == VK_MENU) {
                return TRUE;
            }
            break;
        }
        default: {
            break;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// システムメニューをカスタマイズします。
BOOL CustmizeSysMenu(HWND hWnd)
{

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    int i;
    i=5; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING , MY_IDM_RESET_WINDOW_SIZE, "Reset window size.(&R)");

    //システムメニューを作成
    DrawMenuBar(hWnd);

    return TRUE;
}

