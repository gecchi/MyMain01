#include "stdafx.h"
#include "GgafLibEntory.h"
#include "resource.h"

using namespace std;

#define MY_IDM_RESET_WINDOW_SIZE 10
#define MY_IDM_ABOUT             11
#define MAX_LOADSTRING 100
// グローバル変数:
HINSTANCE hInst; // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING]; // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING]; // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

void myUnexpectedHandler();
void myTerminateHandler();


/**
 * GNU GCC ならばエントリポイント
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv);
}

static VioletVreath::God* pGod = NULL;

/**
 * VCならばエントリポイント
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);


    // グローバル文字列を初期化しています。
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_VIOLETVREATH, szWindowClass, MAX_LOADSTRING);

    //プロパティファイル読込み
    try {
        VioletVreath::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
        MessageBox(NULL, (string("config.properties のロードの失敗。\n理由：")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VioletVreath::Properties::clean();
        _TRACE_("[GgafCriticalException]:" << e.getMsg());
        return EXIT_FAILURE;
    }
    hInst = hInstance; // グローバル変数にインスタンス処理を格納します。





    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    WNDCLASSEX wcex1;
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex1.lpfnWndProc =  (WNDPROC)WndProc; //ウィンドウプロシージャのアドレスを指定する。
    wcex1.cbClsExtra = 0;
    wcex1.cbWndExtra = 0;
    wcex1.hInstance = hInstance;
    wcex1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIOLETVREATH));
    wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    wcex1.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_VIOLETVREATH);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex1.lpszClassName = szWindowClass;
    wcex1.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));


    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";

    HWND hWnd1, hWnd2;
    GgafLibCreateWindow(wcex1, wcex2, szTitle, "secondary", hWnd1, hWnd2);

    //_CrtSetBreakAlloc(203659);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
        #else
            //特に何も無し
        #endif
    #else
        //メモリーリ－クチェックBEGIN
       // ::detectMemoryLeaksStart(std::cout);
    #endif
#else
    #ifdef _MSC_VER
        #ifdef _DEBUG
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
        #else
            //特に何も無し
        #endif
    #else
        //特に何も無し
    #endif
#endif

    MSG msg;
    try {
        //神の誕生
        pGod = NEW VioletVreath::God(hInstance, hWnd1, hWnd2);
        if (SUCCEEDED(pGod->init())) {
            // ループ・ザ・ループ
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        if (VioletVreath::God::_can_be) {
                            VioletVreath::God::_can_be = false;
                            while (pGod->_is_being) {
                                Sleep(2);
                                _TRACE_("Wait! 神 is being yet..");
                            }
                            delete pGod; //神の最期
                            pGod = NULL;
                            VioletVreath::Properties::clean();
                        }

                        ::timeEndPeriod(1);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //ダンプ
                        //_CrtDumpMemoryLeaks();
        #else
                        //特に何も無し
        #endif
    #else
                        //メモリーリ－クチェックEND
                      //  ::detectMemoryLeaksEnd(std::cout);
    #endif
#else
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //ダンプ
                        //_CrtDumpMemoryLeaks();
                        _CrtMemDumpAllObjectsSince( NULL );

        #else
                        //特に何も無し
        #endif
    #else
                        //特に何も無し
    #endif
#endif

                        return EXIT_SUCCESS;
                    }
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                } else {
                    if (VioletVreath::God::_can_be && pGod->_is_being == false) {
                        pGod->be(); //be() で、この世が動く
                    }

                }
            }
        }
    } catch (GgafCore::GgafException& e) {
        //異常終了時
        _TRACE_("＜例外＞"<<e.getMsg());
        string message = "\n・"+e.getMsg()+"  \n\nエラーにお心あたりが無い場合、本アプリのバグの可能性が高いです。\n誠に申し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_GgafException.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_GgafException.rep");
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("＜致命的な例外＞"<<what);
        string message = "\n・"+what+"  \n\n恐れ入りますが、作者には予測できなかった致命的エラーです。\n誠に申し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記の致命的な例外が発生してしまいました", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        _TRACE_("[exception]:"<<what);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_exception.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_exception.rep");
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }

#ifndef MY_DEBUG
    //以下のキャッチはDEBUG時であっても、メモリ違反をつぶす可能性があるため、DEBUG時は無効とする。
    catch( ... ) {
        _TRACE_("＜致命的な謎例外＞");
        string message = "恐れ入りますが、不明な内部エラーが発生しました。\n誠に申し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記の致命的な謎例外が発生してしまいました", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_UNKNOWN_ERROR.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_UNKNOWN_ERROR.rep");
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }
#endif

    return (int) msg.wParam;
}

void myUnexpectedHandler() {
    MessageBox(NULL, "UnexpectedHandler called.","ERROR", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Unexpected.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Unexpected.rep");
    terminate();
}

void myTerminateHandler() {
    MessageBox(NULL, "TerminateHandler called.","ERROR", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Terminate.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Terminate.rep");
    abort();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam);

    switch (message) {

        case WM_CREATE:
            // システムメニューカスタム関数を呼ぶ
            CustmizeSysMenu(hWnd);
            break;
        case WM_SYSCOMMAND:
            if ( (wParam & 0xFFF0) == SC_SCREENSAVE ) {
                return 1;
            }
            if(wParam == MY_IDM_ABOUT) {
                //バージョンダイアログ
//                dhwnd  = CreateDialog(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
                DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            } else if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //ウィンドウリサイズ
                resetWindowsize(hWnd);
            }
            break;
        default:
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// システムメニューをカスタマイズします。
BOOL CustmizeSysMenu(HWND hWnd)
{
    HMENU hMenu;
    // システムメニューのハンドルを取得
    hMenu = GetSystemMenu(hWnd, FALSE);
//    for (i = 0; i <= 5; i++)
//        //システムメニューの項目を消去
//        DeleteMenu(hMenu, 0, MF_BYPOSITION);
//    //システムメニューの項目を追加
    InsertMenu(hMenu, 5, MF_BYPOSITION | MF_SEPARATOR, NULL, "");
    InsertMenu(hMenu, 6, MF_BYPOSITION | MF_STRING, MY_IDM_RESET_WINDOW_SIZE, "Reset window size.");
    InsertMenu(hMenu, 7, MF_BYPOSITION | MF_STRING, MY_IDM_ABOUT, "about");

//    AppendMenu(hMenu, MF_STRING, IDM_ABOUT, "アバウト");
    //システムメニューを作成
    DrawMenuBar(hWnd);

    return TRUE;
}

// バージョン情報ボックスのメッセージ ハンドラです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    //g_hDlg = CreateDialog( g_hInst, _T("IDD_DIALOG1"), hWnd, DlgProc );

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR) TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR) FALSE;
            }
            break;
    }
    return (INT_PTR) FALSE;
}


//// システムメニューの挙動を記述
//LRESULT SysMenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//switch (wParam) {
//    case IDM_TEST:
//        MessageBox(hWnd, (LPCSTR)"テスト項目が選ばれました。",
//            (LPCSTR)"テスト", MB_OK);
//        return 0L;
//        break;
//    default:
//        return(DefWindowProc(hWnd, msg, wParam, lParam));
//        break;
//}
//}


