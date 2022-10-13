#include "GgafLib.h"
#include "VioletVreath_launcher.h"

#include <Shlwapi.h>
#include "resource.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"

#define MY_IDM_RESET_WINDOW_SIZE  10
#define MY_IDM_CHANGE_TO_BORDERLESS_WINDOW 11
#define MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE  12
#define MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE  13
#define MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE  14
#define MY_IDM_SAVE               15
#define MY_IDM_REBOOT             16
#define MY_IDM_ABOUT              17
#define MY_IDM_VPOS_1             21
#define MY_IDM_VPOS_2             22
#define MY_IDM_VPOS_3             23
#define MY_IDM_VPOS_4             24
#define MY_IDM_VPOS_5             25
#define MY_IDM_VPOS_6             26
#define MY_IDM_VPOS_7             27
#define MY_IDM_VPOS_8             28
#define MY_IDM_VPOS_9             29
#define MY_IDM_ASPECT_FIXED       31
#define MY_IDM_ASPECT_STRETCH     32
#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst; // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING]; // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING]; // メイン ウィンドウ クラス名
HWND hWnd1, hWnd2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

void myUnexpectedHandler();
void myTerminateHandler();

/**
 * GNU GCC ならばエントリポイント
 */
int main(int argc, char *argv[]) {
    return LibMain(argc, argv);
}

/**
 * VCならばエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    LibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

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

    TCHAR current_dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_dir);
    LPTSTR command_line = GetCommandLine();
    _TRACE_("current_dir="<<current_dir);
    _TRACE_("command_line="<<command_line);
    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);

    // グローバル文字列を初期化しています。
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_VIOLETVREATH, szWindowClass, MAX_LOADSTRING);

    //プロパティファイル読込み
    if (PathFileExists(VV_DEFAULT_CONFIG_FILE)) {
        if (PathFileExists(VV_CONFIG_FILE)) {
            CONFIG::loadProperties(VV_CONFIG_FILE);
            _TRACE_("config.properties を load しました");
        } else {
            CONFIG::loadProperties(VV_DEFAULT_CONFIG_FILE);
            CONFIG::_properties.write(VV_CONFIG_FILE);
            _TRACE_("【警告】config.properties が存在しないので、既定の '" <<VV_DEFAULT_CONFIG_FILE << "' を load しました。");
        }
    } else {
        MessageBox(nullptr, "既定設定ファイル(.default_config.properties)が見つかりません。",
                                 "Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return EXIT_FAILURE;
    }

    hInst = hInstance; // グローバル変数にインスタンス処理を格納します。
    GgafCore::Rgb rgb = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    WNDCLASSEX wcex1;
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS ;
    //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。ダブルクリックあり
    wcex1.lpfnWndProc =  (WNDPROC)WndProc; //ウィンドウプロシージャのアドレスを指定する。
    wcex1.cbClsExtra = 0;
    wcex1.cbWndExtra = 0;
    wcex1.hInstance = hInstance;
    wcex1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIOLETVREATH));
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    wcex1.lpszMenuName = nullptr;//MAKEINTRESOURCE(IDC_VIOLETVREATH);//nullptr; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex1.lpszClassName = szWindowClass;
    wcex1.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    MSG msg;
#ifdef MY_DEBUG
    try {
#endif
        //管理者の誕生
        VioletVreath::Caretaker crtkr;
        crtkr.createWindow(wcex1, wcex2, szTitle, "secondary", dwStyle, dwStyle, hWnd1, hWnd2);
        // ループ・ザ・ループ
        while (true) {
            if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
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
                        //::detectMemoryLeaksEnd(std::cout);
    #endif
#else
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //ダンプ
                        //_CrtDumpMemoryLeaks();
                        _CrtMemDumpAllObjectsSince( nullptr );

        #else
                        //特に何も無し
        #endif
    #else
                        //特に何も無し
    #endif
#endif
                    if (VioletVreath::Caretaker::g_should_reboot_) {
                        //再起動
                        Sleep(2000);
                        PROCESS_INFORMATION pi;
                        STARTUPINFO si;
                        ZeroMemory(&si, sizeof(si));
                        si.cb = sizeof(si);
                        BOOL r = CreateProcess(
                                    NULL,         //LPCTSTR lpApplicationName,                 // 実行可能モジュールの名前
                                    command_line, //LPTSTR lpCommandLine,                      // コマンドラインの文字列
                                    NULL,         //LPSECURITY_ATTRIBUTES lpProcessAttributes, // セキュリティ記述子
                                    NULL,         //LPSECURITY_ATTRIBUTES lpThreadAttributes,  // セキュリティ記述子
                                    FALSE,        //BOOL bInheritHandles,                      // ハンドルの継承オプション
                                    0,            //DWORD dwCreationFlags,                     // 作成のフラグ
                                    NULL,         //LPVOID lpEnvironment,                      // 新しい環境ブロック
                                    current_dir,  //LPCTSTR lpCurrentDirectory,                // カレントディレクトリの名前
                                    &si,          //LPSTARTUPINFO lpStartupInfo,               // スタートアップ情報
                                    &pi           //LPPROCESS_INFORMATION lpProcessInformation // プロセス情報
                        );
                        if (r == 0) {
                            MessageBox(nullptr, "Cannot Reboot! \n すみません、手動で再起動してください。","orz", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
                        }
                    }
                    return EXIT_SUCCESS;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                crtkr.present(); //be() で、この世が動く
            }
        }
#ifdef MY_DEBUG
    } catch (GgafCore::Exception& e) {
        //異常終了時
        _TRACE_("＜例外＞"<<e.getMsg());
        std::string message = "\n・"+e.getMsg()+"  \n\nエラーにお心あたりが無い場合、本アプリのバグの可能性が高いです。\n誠に申し訳ございません。\n";
        std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(nullptr, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_ggaf_Exception.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_ggaf_Exception.rep");
        _TRACE_("[GgafCore::CriticalException]:"<<e.getMsg());
        return EXIT_FAILURE;
    } catch (std::exception& e2) {
        std::string what(e2.what());
        _TRACE_("＜致命的な例外＞"<<what);
        std::string message = "\n・"+what+"  \n\n恐れ入りますが、作者には予測できなかった致命的エラーです。\n誠に申し訳ございません。\n";
        std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(nullptr, message_dialog.c_str(),"下記の致命的な例外が発生してしまいました", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        _TRACE_("[exception]:"<<what);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_exception.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_exception.rep");
        return EXIT_FAILURE;
    }
#endif
//#ifndef MY_DEBUG
//    //以下のキャッチはDEBUG時であっても、メモリ違反をつぶす可能性があるため、DEBUG時は無効とする。
//    catch( ... ) {
//        _TRACE_("＜致命的な謎例外＞");
//        std::string message = "恐れ入りますが、不明な内部エラーが発生しました。\n誠に申し訳ございません。\n";
//        std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
//        MessageBox(nullptr, message_dialog.c_str(),"下記の致命的な謎例外が発生してしまいました", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
//        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_UNKNOWN_ERROR.rep");
//        VB_UI->_pRpy->outputFile("VB_UI_LAST_UNKNOWN_ERROR.rep");
//        return EXIT_FAILURE;
//    }
//#endif
    return (int) msg.wParam;
}

void myUnexpectedHandler() {
    //MessageBox(nullptr, "UnexpectedHandler was called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    _TRACE_("ERROR. UnexpectedHandler was called.");
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Unexpected.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Unexpected.rep");
    std::unexpected();
}

void myTerminateHandler() {
    //MessageBox(nullptr, "TerminateHandler was called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    _TRACE_("ERROR. TerminateHandler was called.");
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Terminate.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Terminate.rep");
    std::terminate();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam);
    VioletVreath::Caretaker* pCaretaker = pCARETAKER;
    switch (message) {
        case WM_CREATE: {
            // システムメニューカスタム関数を呼ぶ
            CustmizeSysMenu(hWnd);
            break;
        }
        case WM_SYSKEYDOWN: {
            //システムのメニューフォーカスキーを無効にする。
            //これを行っておかないと、F10を押してしまった際に、
            //フォーカスが見えないメニューへ移ってしまい、
            //キーやマウス入力を受け付けなくなってしまう。
            //ゲームでは致命的。
            if (LOWORD(wParam) == VK_F10) {
                return TRUE;
            }
            if (LOWORD(wParam) == VK_MENU) {
                return TRUE;
            }
            break;
        }
        case WM_LBUTTONDBLCLK: {
            //擬似フルスクリーンの切り替え
            LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
            if (lStyle & WS_POPUP) {
                //現在ボーダレスフルスクリーンウィンドウであるので戻す。
                pCaretaker->backToNomalWindow(hWnd);
            } else {
                //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
                pCaretaker->chengeToBorderlessFullWindow(hWnd);
            }
            break;
        }
        case WM_KEYDOWN: {
            if (wParam == VK_F11) {
                //擬似フルスクリーンの切り替え
                LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
                if (lStyle & WS_POPUP) {
                    //現在ボーダレスフルスクリーンウィンドウであるので戻す。
                    pCaretaker->backToNomalWindow(hWnd);
                } else {
                    //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
                    pCaretaker->chengeToBorderlessFullWindow(hWnd);
                }
            }
            break;
        }
        case WM_SYSCOMMAND: {
            pCaretaker->syncTimeFrame();
            if ( (wParam & 0xFFF0) == SC_SCREENSAVE ) {
                return 1;
            }
            if(wParam == MY_IDM_ABOUT) {
                //バージョンダイアログ
//                dhwnd  = CreateDialog(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
                DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            } else if(wParam == MY_IDM_CHANGE_TO_BORDERLESS_WINDOW) {
                LONG lStyle  = GetWindowLong( hWnd, GWL_STYLE );
                if (lStyle & WS_POPUP) {
                    //現在ボーダレスフルスクリーンウィンドウであるので戻す。
                    pCaretaker->backToNomalWindow(hWnd);
                } else {
                    //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
                    pCaretaker->chengeToBorderlessFullWindow(hWnd);
                }
            } else if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //初期ウィンドウサイズにリセット
                pCaretaker->resetInitWindowsize();
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE) {
                //pixel by dot ウィンドウサイズにリセット
                pCaretaker->resetDotByDotWindowsize(1);
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE) {
                //pixel by 2*2dot ウィンドウサイズにリセット
                pCaretaker->resetDotByDotWindowsize(2);
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE) {
                //pixel by 3*3dot ウィンドウサイズにリセット
                pCaretaker->resetDotByDotWindowsize(3);
            } else if(wParam == MY_IDM_SAVE) {
                if (!CONFIG::FULL_SCREEN) {
                    if (CONFIG::DUAL_VIEW) {
                        RECT cRect1, cRect2;
                        GetClientRect(hWnd1, &cRect1);
                        GetClientRect(hWnd2, &cRect2);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        pixcoord cw2 = cRect2.right - cRect2.left;
                        pixcoord ch2 = cRect2.bottom - cRect2.top;
                        CONFIG::WINDOW1_WIDTH  = cw1;
                        CONFIG::WINDOW1_HEIGHT = ch1;
                        CONFIG::WINDOW2_WIDTH  = cw2;
                        CONFIG::WINDOW2_HEIGHT = ch2;
                        CONFIG::_properties.setValue("WINDOW1_WIDTH" , CONFIG::WINDOW1_WIDTH);
                        CONFIG::_properties.setValue("WINDOW1_HEIGHT", CONFIG::WINDOW1_HEIGHT);
                        CONFIG::_properties.setValue("WINDOW2_WIDTH" , CONFIG::WINDOW2_WIDTH);
                        CONFIG::_properties.setValue("WINDOW2_HEIGHT", CONFIG::WINDOW2_HEIGHT);

                        CONFIG::_properties.setValue("PRESENT_POSITION1", CONFIG::PRESENT_POSITION1);
                        CONFIG::_properties.setValue("PRESENT_POSITION2", CONFIG::PRESENT_POSITION2);

                    } else {
                        RECT cRect1;
                        GetClientRect(hWnd1, &cRect1);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        CONFIG::WINDOW1_WIDTH  = cw1;
                        CONFIG::WINDOW1_HEIGHT = ch1;
                        CONFIG::_properties.setValue("WINDOW1_WIDTH" , CONFIG::WINDOW1_WIDTH);
                        CONFIG::_properties.setValue("WINDOW1_HEIGHT", CONFIG::WINDOW1_HEIGHT);

                        CONFIG::_properties.setValue("PRESENT_POSITION1", CONFIG::PRESENT_POSITION1);
                    }
                    CONFIG::_properties.setValue("FIXED_GAME_VIEW_ASPECT", CONFIG::FIXED_GAME_VIEW_ASPECT);

                    CONFIG::_properties.write(VV_CONFIG_FILE); //プロパティ保存
                    CONFIG::loadProperties(VV_CONFIG_FILE); //プロパティ再反映
                }
            } else if(wParam == MY_IDM_REBOOT) {
                //再起動実行
                int ret = MessageBox(nullptr, "Quit and Reboot. Are You Sure ?", "VioletVreath_launcher", MB_OKCANCEL|MB_SETFOREGROUND);
                if (ret == IDOK) {
                    VioletVreath::Caretaker::g_should_reboot_ = true;
                    PostQuitMessage(0);
                }
            } else if(wParam == MY_IDM_VPOS_1) {
                pCaretaker->chengeViewPos(hWnd, 1);
            } else if(wParam == MY_IDM_VPOS_2) {
                pCaretaker->chengeViewPos(hWnd, 2);
            } else if(wParam == MY_IDM_VPOS_3) {
                pCaretaker->chengeViewPos(hWnd, 3);
            } else if(wParam == MY_IDM_VPOS_4) {
                pCaretaker->chengeViewPos(hWnd, 4);
            } else if(wParam == MY_IDM_VPOS_5) {
                pCaretaker->chengeViewPos(hWnd, 5);
            } else if(wParam == MY_IDM_VPOS_6) {
                pCaretaker->chengeViewPos(hWnd, 6);
            } else if(wParam == MY_IDM_VPOS_7) {
                pCaretaker->chengeViewPos(hWnd, 7);
            } else if(wParam == MY_IDM_VPOS_8) {
                pCaretaker->chengeViewPos(hWnd, 8);
            } else if(wParam == MY_IDM_VPOS_9) {
                pCaretaker->chengeViewPos(hWnd, 9);
            } else if(wParam == MY_IDM_ASPECT_FIXED) {
                pCaretaker->chengeViewAspect(true);
            } else if(wParam == MY_IDM_ASPECT_STRETCH) {
                pCaretaker->chengeViewAspect(false);
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
    HMENU menu_vp = CreateMenu();
    InsertMenu(menu_vp,  0, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_7, "7");
    InsertMenu(menu_vp,  1, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp,  2, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_4, "4");
    InsertMenu(menu_vp,  3, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp,  4, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_1, "1");
    InsertMenu(menu_vp,  5, MF_STRING | MF_BYPOSITION | MF_MENUBARBREAK, MY_IDM_VPOS_8, "8");
    InsertMenu(menu_vp,  6, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp,  7, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_5, "5");
    InsertMenu(menu_vp,  8, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp,  9, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_2, "2");
    InsertMenu(menu_vp, 10, MF_STRING | MF_BYPOSITION | MF_MENUBARBREAK, MY_IDM_VPOS_9, "9");
    InsertMenu(menu_vp, 11, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp, 12, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_6, "6");
    InsertMenu(menu_vp, 13, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(menu_vp, 14, MF_STRING | MF_BYPOSITION, MY_IDM_VPOS_3, "3");

    HMENU menu_aspect = CreateMenu();
    InsertMenu(menu_aspect, 0, MF_STRING | MF_BYPOSITION, MY_IDM_ASPECT_FIXED, "Fix");
    InsertMenu(menu_aspect, 1, MF_STRING | MF_BYPOSITION, MY_IDM_ASPECT_STRETCH, "Stretch");

    HMENU reset_window_size = CreateMenu();
    InsertMenu(reset_window_size, 0, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_WINDOW_SIZE, "size of default.");
    InsertMenu(reset_window_size, 1, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE,  "size of pixel = 1*1dot.");
    InsertMenu(reset_window_size, 2, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE, "size of pixel = 2*2dot.");
    InsertMenu(reset_window_size, 3, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE, "size of pixel = 3*3dot.");

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    int i;
    i=5; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_CHANGE_TO_BORDERLESS_WINDOW ,"Change to borderless windowed.(Double Click)");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)reset_window_size, "Reset window size. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_aspect, "Game view aspect. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_vp    , "Game view position. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_SAVE ,"Save window size and view.");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_REBOOT ,"Reboot...");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_ABOUT, "About");

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


