#include "stdafx.h"
#include "MySTG2nd.h"
#include "resource.h"
using namespace std;

#define MAX_LOADSTRING 100
// グローバル変数:
HINSTANCE hInst; // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING]; // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING]; // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM MyRegisterClass_Primary(HINSTANCE hInstance);
ATOM MyRegisterClass_Secondary(HINSTANCE hInstance);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

void myUnexpectedHandler();
void myTerminateHandler();



/**
 * GNU GCC ならばエントリポイント
 */
int main(int argc, char *argv[]) {
    STARTUPINFO StatUpInfo;
    HINSTANCE hInstance;
    HANDLE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;


    GetStartupInfo(&StatUpInfo);
    hInstance = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = GetCommandLine();
    nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW) ? StatUpInfo.wShowWindow : SW_SHOWNORMAL;
    /* GetCommandLineからプログラム名を抜きます。 */
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0')
        lpCmdLine++;
    while (*lpCmdLine == ' ')
        lpCmdLine++;
    cout << lpCmdLine << endl;
    //本来のWinMainへ
    WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
    return 0;
}

static MyStg2nd::God* pGod = NULL;

/**
 * VCならばエントリポイント
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    MSG msg;

    // グローバル文字列を初期化しています。
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    _TRACE_("szTitle = "<<szTitle);
    LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);
    _TRACE_("szWindowClass = "<<szWindowClass);

    //プロパティファイル読込み
    try {
        MyStg2nd::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
        MessageBox(NULL, (string("config.properties のロードの失敗。\n理由：")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        MyStg2nd::Properties::clean();
        _TRACE_("[GgafCriticalException]:" << e.getMsg());
        return EXIT_FAILURE;
    }
    HWND hWnd1 = NULL;
    HWND hWnd2 = NULL;
    hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

    // ウインドウの生成
    if (CFG_PROPERTY(FULL_SCREEN)) {
        if (CFG_PROPERTY(DUAL_VIEW)) {
            //フルスクリーンモード・２画面使用
            MyRegisterClass_Primary(hInstance);
            hWnd1 = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        szWindowClass, //WINDOW_CLASS,
                        szTitle,//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH),
                        CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        hInstance,
                        NULL
                    );

            MyRegisterClass_Secondary(hInstance);
            hWnd2 = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        "secondary", //WINDOW_CLASS,
                        "secondary",//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH),
                        CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        hInstance,
                        NULL
                    );

        } else {
            //フルスクリーンモード・１画面使用
            MyRegisterClass_Primary(hInstance);
            hWnd1 = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        szWindowClass, //WINDOW_CLASS,
                        szTitle,//WINDOW_TITLE,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH),
                        CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT),
                        HWND_DESKTOP,
                        NULL,
                        hInstance,
                        NULL
                    );

        }
    } else {
        if (CFG_PROPERTY(DUAL_VIEW)) {
            MyRegisterClass_Primary(hInstance);
            hWnd1 = CreateWindow(
                    szWindowClass, //WINDOW_CLASS,          // ウインドウクラス名
                    szTitle,//WINDOW_TITLE,             // ウインドウのタイトル名
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ウインドウスタイル
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), // ウィンドウの幅
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );

            MyRegisterClass_Secondary(hInstance);
            hWnd2 = CreateWindow(
                    "secondary", //WINDOW_CLASS,
                    "secondary",//WINDOW_TITLE,
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ウインドウスタイル
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), // ウィンドウの幅
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );
        } else {
            MyRegisterClass_Primary(hInstance);
            hWnd1 = CreateWindow(
                    szWindowClass, //WINDOW_CLASS,          // ウインドウクラス名
                    szTitle,//WINDOW_TITLE,             // ウインドウのタイトル名
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ウインドウスタイル
                    WS_OVERLAPPEDWINDOW, // ウインドウスタイル
                    CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
                    CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), // ウィンドウの幅
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT), // ウィンドウの幅
                    HWND_DESKTOP, // 親ウインドウ
                    NULL, // ウインドウメニュー
                    hInstance, // インスタンスハンドル
                    NULL // WM_CREATE情報
            );
        }
    }

    if (!hWnd1) {
        cout << "can't CreateWindow " << endl;
        cout << "szWindowClass=" << szWindowClass << endl;
        cout << "szTitle=" << szTitle << endl;
        return FALSE;
    }




    //ウィンドウ時、タイトルバー、リサイズの厚さを考慮。
    if (!CFG_PROPERTY(FULL_SCREEN)) {
        RECT wRect1, cRect1; // ウィンドウ全体の矩形、クライアント領域の矩形
        int ww1, wh1; // ウィンドウ全体の幅、高さ
        int cw1, ch1; // クライアント領域の幅、高さ
        int fw1, fh1; // フレームの幅、高さ
        // ウィンドウ全体の幅・高さを計算
        GetWindowRect(hWnd1, &wRect1);
        ww1 = wRect1.right - wRect1.left;
        wh1 = wRect1.bottom - wRect1.top;
        // クライアント領域の幅・高さを計算
        GetClientRect(hWnd1, &cRect1);
        cw1 = cRect1.right - cRect1.left;
        ch1 = cRect1.bottom - cRect1.top;
        // クライアント領域以外に必要なサイズを計算
        fw1 = ww1 - cw1;
        fh1 = wh1 - ch1;
        // 計算した幅と高さをウィンドウに設定
        SetWindowPos(
                hWnd1,
                HWND_TOP,
                0,
                0,
                CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) + fw1,
                CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) + fh1,
                SWP_NOMOVE
        );

        if (CFG_PROPERTY(DUAL_VIEW)) {
            SetWindowPos(
                    hWnd2,
                    HWND_TOP,
                    0,
                    0,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) + fw1,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) + fh1,
                    SWP_NOMOVE
            );
        }
    }

    //アクティブに
    ShowWindow(hWnd1, nCmdShow);
    UpdateWindow(hWnd1);
    if (CFG_PROPERTY(DUAL_VIEW)) {
        ShowWindow(hWnd2, nCmdShow);
        UpdateWindow(hWnd2);
    }

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
        #else
            //特に何も無し
        #endif
    #else
        //メモリーリ－クチェックBEGIN
        ::detectMemoryLeaksStart(std::cout);
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

    try {
        //神の誕生！
        pGod = NEW MyStg2nd::God(hInstance, hWnd1, hWnd2);
        if (SUCCEEDED(pGod->init())) {

            // ループ・ザ・ループ
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        if (MyStg2nd::God::_can_be) {
                            MyStg2nd::God::_can_be = false;
//                            pGod->_can_be = false;
                            while (pGod->_is_being) {
                                Sleep(2);
                                _TRACE_("Wait! 神 is being yet..");
                            }
                            delete pGod; //神さようなら

                            //RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
                            pGod = NULL;
                            MyStg2nd::Properties::clean();
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
                        ::detectMemoryLeaksEnd(std::cout);
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
                    if (MyStg2nd::God::_can_be && pGod->_is_being == false) {
                        pGod->be(); //神が存在したらしめる（この世が動く）
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


ATOM MyRegisterClass_Primary(HINSTANCE hInstance) {
    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(CFG_PROPERTY(BG_COLOR));
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex.lpfnWndProc =  (WNDPROC)WndProc; //ウィンドウプロシージャのアドレスを指定する。
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(
                            RGB(rgb._R, rgb._G, rgb._B)
                         );
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

ATOM MyRegisterClass_Secondary(HINSTANCE hInstance) {
    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(CFG_PROPERTY(BG_COLOR));
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex.lpfnWndProc =  (WNDPROC)WndProc;
                       //(WNDPROC)GetWindowLong(_pHWndPrimary, GWL_WNDPROC ); //１画面目のウィンドウプロシージャを共通指定する。
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(
                            RGB(rgb._R, rgb._G, rgb._B)
                         );
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex.lpszClassName = "secondary";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //  int wmId, wmEvent;
    //PAINTSTRUCT ps;
    //HDC hdc;

    switch (message) {
        case WM_CREATE:

            // システムメニューカスタム関数を呼ぶ
            CustmizeSysMenu(hWnd);
            break;
        case WM_SIZE:
            if (GgafDx9Core::GgafDx9God::_can_be) {
                if (!CFG_PROPERTY(FULL_SCREEN)) {
                    GgafDx9Core::GgafDx9God::_adjustGameScreen = true;
                    GgafDx9Core::GgafDx9God::_pHWnd_adjustScreen = hWnd;
                }
            }
            break;
        case WM_SETFOCUS:
            HRESULT hr;
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Mouse) {
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    _TRACE_("GgafDx9Input::initDx9Input() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました");
                }
            }
                // キーボード強調レベル設定
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Keyboard) {
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    MessageBox(hWnd, TEXT("GgafDx9Input::initDx9Input() キーボードのSetCooperativeLevelに失敗しました"),
                               TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                }
            }
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick) {
                // ゲームスティック協調レベルを設定する
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
                if (hr != D3D_OK) {
                    _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
                }
            }

            break;
        case WM_SYSCOMMAND:
            if ( (wParam & 0xFFF0) == SC_SCREENSAVE ) {
                return 1;
            }
            if(wParam == SC_CLOSE){
                PostQuitMessage(0);
            } else if(wParam == IDM_ABOUT) {
//                dhwnd  = CreateDialog(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
                DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
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
    InsertMenu(hMenu, 6, MF_BYPOSITION | MF_STRING, IDM_ABOUT, "reset window size");
    InsertMenu(hMenu, 7, MF_BYPOSITION | MF_STRING, IDM_ABOUT, "about");

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

//
//#include <windows.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//
//

//int main(void) {
//    PIP_ADAPTER_INFO pAdapterInfo;
//    DWORD aiSize;
//    BYTE* paBuff;
//
//    GetAdaptersInfo(NULL, &aiSize);//必要バッファサイズ取得
//    paBuff = new BYTE[aiSize];
//    pAdapterInfo = (PIP_ADAPTER_INFO) paBuff;
//
//    if (GetAdaptersInfo(pAdapterInfo, &aiSize) != ERROR_SUCCESS) {
//        printf("GetAdapterInfo呼び出し失敗\n");
//        return 1;
//    }
//    std::stringstream ss;
//
//
//    while (pAdapterInfo) {
//        //fprintf(stdout, "MACアドレス = [");
//
//        for (UINT i = 0; i < pAdapterInfo->AddressLength; i++) {
//            ss.width(2);
//            ss.fill('0');
//            ss << std::hex << (int)pAdapterInfo->Address[i];
//            //fprintf(stdout, "%.2X", (int)pAdapterInfo->Address[i]);
//
//            if (i == (pAdapterInfo->AddressLength - 1)) {
//                //fputs("]\n", stdout);
//            } else {
//                ss.width(1);
//                ss << "-";
//                //fputs("-", stdout);
//            }
//        }
//        pAdapterInfo = pAdapterInfo->Next;
//    }
//    delete[] paBuff;
//    printf("%s", ss.str().c_str());
//    return 0;
//}
