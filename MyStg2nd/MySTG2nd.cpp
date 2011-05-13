// MySTG2nd.cpp : アプリケーションのエントリ ポイントを定義します。
//
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
        MessageBox(NULL, (string("config.properties のロードの失敗。\n理由：")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP);
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

    if (CFG_PROPERTY(FULL_SCREEN)) {

    } else {
        if (CFG_PROPERTY(DUAL_VIEW)) {
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
                    wRect1.left,
                    wRect1.top,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) + fw1,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) + fh1,
                    SWP_NOMOVE
            );
            ShowWindow(hWnd1, nCmdShow);
            UpdateWindow(hWnd1);

            RECT wRect2, cRect2; // ウィンドウ全体の矩形、クライアント領域の矩形
            int ww2, wh2; // ウィンドウ全体の幅、高さ
            int cw2, ch2; // クライアント領域の幅、高さ
            int fw2, fh2; // フレームの幅、高さ
            // ウィンドウ全体の幅・高さを計算
            GetWindowRect(hWnd2, &wRect2);
            ww2 = wRect2.right - wRect2.left;
            wh2 = wRect2.bottom - wRect2.top;
            // クライアント領域の幅・高さを計算
            GetClientRect(hWnd2, &cRect2);
            cw2 = cRect2.right - cRect2.left;
            ch2 = cRect2.bottom - cRect2.top;
            // クライアント領域以外に必要なサイズを計算
            fw2 = ww2 - cw2;
            fh2 = wh2 - ch2;
            // 計算した幅と高さをウィンドウに設定
            SetWindowPos(
                    hWnd2,
                    HWND_TOP,
                    wRect2.left,
                    wRect2.top,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) + fw2,
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) + fh2,
                    SWP_NOMOVE
            );

            ShowWindow(hWnd2, nCmdShow);
            UpdateWindow(hWnd2);
        } else {
            RECT wRect, cRect; // ウィンドウ全体の矩形、クライアント領域の矩形
            int ww, wh; // ウィンドウ全体の幅、高さ
            int cw, ch; // クライアント領域の幅、高さ
            int fw, fh; // フレームの幅、高さ
            // ウィンドウ全体の幅・高さを計算
            GetWindowRect(hWnd1, &wRect);
            ww = wRect.right - wRect.left;
            wh = wRect.bottom - wRect.top;
            // クライアント領域の幅・高さを計算
            GetClientRect(hWnd1, &cRect);
            cw = cRect.right - cRect.left;
            ch = cRect.bottom - cRect.top;
            // クライアント領域以外に必要なサイズを計算
            fw = ww - cw;
            fh = wh - ch;
            // 計算した幅と高さをウィンドウに設定
            SetWindowPos(
                    hWnd1,
                    HWND_TOP,
                    wRect.left,
                    wRect.top,
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) + fw,
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) + fh,
                    SWP_NOMOVE
            );
        }


        ShowWindow(hWnd1, nCmdShow);
        UpdateWindow(hWnd1);
        //hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//ショートカットロード
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
        MessageBox(NULL, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP);
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("＜致命的な例外＞"<<what);
        string message = "\n・"+what+"  \n\n恐れ入りますが、作者には予測できなかった致命的エラーです。\n誠に申し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記の致命的な例外が発生してしまいました", MB_OK|MB_ICONSTOP);
        _TRACE_("[exception]:"<<what);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }

#ifndef MY_DEBUG
    //以下のキャッチはメモリ違反をつぶす可能性があるため、DEBUG時は無効とする。
    catch( ... ) {
        _TRACE_("＜致命的な謎例外＞");
        string message = "恐れ入りますが、不明な内部エラーが発生しました。\n誠に申し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記の致命的な謎例外が発生してしまいました", MB_OK|MB_ICONSTOP);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }
#endif

    return (int) msg.wParam;
}

void myUnexpectedHandler() {
    MessageBox(NULL, "myUnexpectedHandler called.","test", MB_OK|MB_ICONSTOP);
    //std::cerr << "myUnexpectedHandler called." << std::endl;
    terminate();
}

void myTerminateHandler() {
    MessageBox(NULL, "myTerminateHandler called.","test", MB_OK|MB_ICONSTOP);
    abort;
}


ATOM MyRegisterClass_Primary(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex.lpfnWndProc = WndProc; //ウィンドウプロシージャのアドレスを指定する。
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

ATOM MyRegisterClass_Secondary(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex.lpfnWndProc = WndProc;
                       //(WNDPROC)GetWindowLong(_pHWndPrimary, GWL_WNDPROC ); //１画面目のウィンドウプロシージャを共通指定する。
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex.lpszClassName = "secondary";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //  int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {

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
                               TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                }
            }
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick) {
                // ゲームスティック協調レベルを設定する
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick->SetCooperativeLevel(hWnd, DISCL_FOREGROUND
                        | DISCL_NONEXCLUSIVE );
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
