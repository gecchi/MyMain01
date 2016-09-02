#include "VioletVreath.h"

#include "GgafLibEntry.h"
#include "resource.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
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

/**
 * VCならばエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
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
            VioletVreath::Properties::load(VV_CONFIG_FILE);
            _TRACE_("config.properties を load しました");
        } else {
            VioletVreath::Properties::load(VV_DEFAULT_CONFIG_FILE);
            VioletVreath::Properties::save(VV_CONFIG_FILE);
            _TRACE_("＜警告＞config.properties が存在しないので、既定の '" <<VV_DEFAULT_CONFIG_FILE << "' を load しました。");
        }

    } else {
        MessageBox(nullptr, "既定設定ファイル(.default_config.properties)が見つかりません。",
                                 "Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return EXIT_FAILURE;
    }

    hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(PROPERTY::BORDER_COLOR);
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
    VioletVreath::God god = VioletVreath::God();
    try {
        //神の誕生
        god.createWindow(wcex1, wcex2, szTitle, "secondary", dwStyle, dwStyle, hWnd1, hWnd2);
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
                      //  ::detectMemoryLeaksEnd(std::cout);
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

                    if (VioletVreath::God::g_should_reboot_) {
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
                god.be(); //be() で、この世が動く
            }
        }
    } catch (GgafCore::GgafException& e) {
        //異常終了時
        _TRACE_("＜例外＞"<<e.getMsg());
        std::string message = "\n・"+e.getMsg()+"  \n\nエラーにお心あたりが無い場合、本アプリのバグの可能性が高いです。\n誠に申し訳ございません。\n";
        std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(nullptr, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_GgafException.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_GgafException.rep");
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
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

#ifndef MY_DEBUG
    //以下のキャッチはDEBUG時であっても、メモリ違反をつぶす可能性があるため、DEBUG時は無効とする。
    catch( ... ) {
        _TRACE_("＜致命的な謎例外＞");
        std::string message = "恐れ入りますが、不明な内部エラーが発生しました。\n誠に申し訳ございません。\n";
        std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(nullptr, message_dialog.c_str(),"下記の致命的な謎例外が発生してしまいました", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_UNKNOWN_ERROR.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_UNKNOWN_ERROR.rep");
        return EXIT_FAILURE;
    }
#endif
    return (int) msg.wParam;
}

void myUnexpectedHandler() {
    MessageBox(nullptr, "UnexpectedHandler called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Unexpected.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Unexpected.rep");
    std::unexpected();
}

void myTerminateHandler() {
    MessageBox(nullptr, "TerminateHandler called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Terminate.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Terminate.rep");
    std::terminate();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam);

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
//        case WM_SYSCHAR: {
//            if (LOWORD(wParam) == VK_RETURN) { //Alt + Enter
//                LONG lStyle  = GetWindowLong( hWnd, GWL_STYLE );
//                if (lStyle & WS_POPUP) {
//                    //現在ボーダレスフルスクリーンウィンドウであるので戻す。
//                    GgafDxCore::GgafDxGod::backToNomalWindow(hWnd);
//                } else {
//                    //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
//                    GgafDxCore::GgafDxGod::chengeToBorderlessFullWindow(hWnd);
//                }
//            }
//            break;
//        }
        case WM_LBUTTONDBLCLK: {
            LONG lStyle  = GetWindowLong( hWnd, GWL_STYLE );
            if (lStyle & WS_POPUP) {
                //現在ボーダレスフルスクリーンウィンドウであるので戻す。
                GgafDxCore::GgafDxGod::backToNomalWindow(hWnd);
            } else {
                //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
                GgafDxCore::GgafDxGod::chengeToBorderlessFullWindow(hWnd);
            }
            break;
        }


        case WM_SYSCOMMAND: {
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
                    GgafDxCore::GgafDxGod::backToNomalWindow(hWnd);
                } else {
                    //現在通常ウィンドウであるので、ボーダレスフルスクリーンウィンドウに切り替える。
                    GgafDxCore::GgafDxGod::chengeToBorderlessFullWindow(hWnd);
                }
            } else if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //初期ウィンドウサイズにリセット
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::DUAL_VIEW_WINDOW1_WIDTH, PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::DUAL_VIEW_WINDOW2_WIDTH, PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::SINGLE_VIEW_WINDOW_WIDTH, PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT);
                    }
                }
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE) {
                //pixel by dot ウィンドウサイズにリセット
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT);
                    }
                }
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE) {
                //pixel by 2*2dot ウィンドウサイズにリセット
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2*2, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*2);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2*2, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*2);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH*2, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*2);
                    }
                }
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE) {
                //pixel by 3*3dot ウィンドウサイズにリセット
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2*3, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*3);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::RENDER_TARGET_BUFFER_WIDTH/2*3, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*3);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::RENDER_TARGET_BUFFER_WIDTH*3, PROPERTY::RENDER_TARGET_BUFFER_HEIGHT*3);
                    }
                }
            } else if(wParam == MY_IDM_SAVE) {
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        RECT cRect1, cRect2;
                        GetClientRect(hWnd1, &cRect1);
                        GetClientRect(hWnd2, &cRect2);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        pixcoord cw2 = cRect2.right - cRect2.left;
                        pixcoord ch2 = cRect2.bottom - cRect2.top;
                        PROPERTY::DUAL_VIEW_WINDOW1_WIDTH  = cw1;
                        PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT = ch1;
                        PROPERTY::DUAL_VIEW_WINDOW2_WIDTH  = cw2;
                        PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT = ch2;
                        PROPERTY::setValue("DUAL_VIEW_WINDOW1_WIDTH" , PROPERTY::DUAL_VIEW_WINDOW1_WIDTH);
                        PROPERTY::setValue("DUAL_VIEW_WINDOW1_HEIGHT", PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT);
                        PROPERTY::setValue("DUAL_VIEW_WINDOW2_WIDTH" , PROPERTY::DUAL_VIEW_WINDOW2_WIDTH);
                        PROPERTY::setValue("DUAL_VIEW_WINDOW2_HEIGHT", PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT);

                        PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION1", PROPERTY::DUAL_VIEW_DRAW_POSITION1);
                        PROPERTY::setValue("DUAL_VIEW_DRAW_POSITION2", PROPERTY::DUAL_VIEW_DRAW_POSITION2);

                    } else {
                        RECT cRect1;
                        GetClientRect(hWnd1, &cRect1);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        PROPERTY::SINGLE_VIEW_WINDOW_WIDTH  = cw1;
                        PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT = ch1;
                        PROPERTY::setValue("SINGLE_VIEW_WINDOW_WIDTH" , PROPERTY::SINGLE_VIEW_WINDOW_WIDTH);
                        PROPERTY::setValue("SINGLE_VIEW_WINDOW_HEIGHT", PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT);

                        PROPERTY::setValue("SINGLE_VIEW_DRAW_POSITION", PROPERTY::SINGLE_VIEW_DRAW_POSITION);
                    }
                    PROPERTY::setValue("FIXED_GAME_VIEW_ASPECT", PROPERTY::FIXED_GAME_VIEW_ASPECT);

                    PROPERTY::save(VV_CONFIG_FILE); //プロパティ保存
                    PROPERTY::load(VV_CONFIG_FILE); //プロパティ再反映
                }
            } else if(wParam == MY_IDM_REBOOT) {
                //再起動実行
                int ret = MessageBox(nullptr, "Quit and Reboot. Are You Sure ?", "VioletVreath", MB_OKCANCEL|MB_SETFOREGROUND);
                if (ret == IDOK) {
                    VioletVreath::God::g_should_reboot_ = true;
                    PostQuitMessage(0);
                }
            } else if(wParam == MY_IDM_VPOS_1) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 1);
            } else if(wParam == MY_IDM_VPOS_2) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 2);
            } else if(wParam == MY_IDM_VPOS_3) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 3);
            } else if(wParam == MY_IDM_VPOS_4) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 4);
            } else if(wParam == MY_IDM_VPOS_5) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 5);
            } else if(wParam == MY_IDM_VPOS_6) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 6);
            } else if(wParam == MY_IDM_VPOS_7) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 7);
            } else if(wParam == MY_IDM_VPOS_8) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 8);
            } else if(wParam == MY_IDM_VPOS_9) {
                GgafDxCore::GgafDxGod::chengeViewPos(hWnd, 9);
            } else if(wParam == MY_IDM_ASPECT_FIXED) {
                GgafDxCore::GgafDxGod::chengeViewAspect(true);
            } else if(wParam == MY_IDM_ASPECT_STRETCH) {
                GgafDxCore::GgafDxGod::chengeViewAspect(false);
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
//    for (i = 0; i <= 5; i++)
//        //システムメニューの項目を消去
//        DeleteMenu(hMenu, 0, MF_BYPOSITION);
//    //システムメニューの項目を追加

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
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_vp    , "Game view place. >>");
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


