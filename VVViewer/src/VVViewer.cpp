#include "jp/ggaf/GgafLib.h"
#include "VvvCaretaker.h"

#include "jp/ggaf/dx/Caretaker.h"
using namespace VVViewer;

#define MY_IDM_RESET_WINDOW_SIZE  10
HWND hWnd1, hWnd2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

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
    //管理者の誕生
    VvvCaretaker crtkr;
    //ゲームループ
    MSG msg;
    crtkr.createWindow(wcex1, wcex2,
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
            crtkr.present();
        }
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
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
    VvvCaretaker::Caretaker* pCaretaker = pCARETAKER;
    switch (message) {

        case WM_CREATE: {
            // システムメニューカスタム関数を呼ぶ
            CustmizeSysMenu(hWnd);
            break;
        }
        case WM_DROPFILES: { // ファイルがドロップされた時の処理
            HDROP hDrop = (HDROP)wParam;
            UINT uFileNo = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, nullptr, 0);
            for (int i = 0; i < (int)uFileNo; i++) {
                DragQueryFile(hDrop, i, VvvCaretaker::dropfiles_, 2048);
                _TRACE_("VvvCaretaker::dropfiles_="<<VvvCaretaker::dropfiles_);
            }
            DragFinish(hDrop);
            VvvCaretaker::is_wm_dropfiles_ = true;
            break;
        }
        case WM_SYSCOMMAND: {
            if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                pCaretaker->resetInitWindowsize();
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

