// MySTG2nd.cpp : アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include "MySTG2nd.h"
#include "resource.h"

using namespace std;

#define MAX_LOADSTRING 100
//#define WINDOW_TITLE "MyStg2nd"
//#define WINDOW_CLASS "mogera"

// グローバル変数:
HINSTANCE hInst; // 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING]; // タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING]; // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

void adjustGameScreen(HWND);

/**
 * GNU GCC ならばエントリポイント
 */
int main(int argc, char *argv[]) {
    STARTUPINFO StatUpInfo;
    HINSTANCE hInstance;
    HANDLE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;
    //WNDCLASS	wc;
    //	HWND		hWnd;
    //	MSG			msg;

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
    /* ここからが、本来の処理 */
    //wc.lpszClassName = "MySTG2nd";
    /* 二重起動防止 (バグあり...)*/
    //	if((hWnd=FindWindow(WINDOW_CLASS, NULL))!=0) {
    //		if (IsIconic(hWnd)) {
    //			ShowWindow(hWnd, SW_RESTORE);
    //		}
    //		SetForegroundWindow(hWnd);
    //		return 0;
    //	}

    //本来のWinMainへ
    WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
    return 0;
}

static MyStg2nd::God* pGod = NULL;
static bool can_be_god = true;

/**
 * VCならばエントリポイント
 */
int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{

	//_CrtSetBreakAlloc(95299);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    //	HACCEL hAccelTable;

    // グローバル文字列を初期化しています。
    //	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //	LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);
    //LoadStringができん！
    strcpy(szTitle,"MyStg2nd"); //無理やり
    strcpy(szWindowClass,"MYSTG2ND"); //ですよ！


    //プロパティファイル読込み
    try {
        MyStg2nd::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
		MessageBox(NULL, (string("config.properties のロードの失敗。\n理由：")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP);
        MyStg2nd::Properties::clean();
        GgafCore::GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
        return EXIT_FAILURE;
    }

    MyRegisterClass(hInstance);
    HWND hWnd;
    hInst = hInstance; // グローバル変数にインスタンス処理を格納します。
    hWnd = CreateWindow(
            szWindowClass, //WINDOW_CLASS,			// ウインドウクラス名
            szTitle,//WINDOW_TITLE,				// ウインドウのタイトル名
            WS_OVERLAPPEDWINDOW, // ウインドウスタイル
            CW_USEDEFAULT, // ウィンドウの表示Ｘ座標
            CW_USEDEFAULT, // ウィンドウの表示Ｙ座標
            GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH), // ウィンドウの幅
            GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT), // ウィンドウの幅
            NULL, // 親ウインドウ
            NULL, // ウインドウメニュー
            hInstance, // インスタンスハンドル
            NULL // WM_CREATE情報
    );

    if (!hWnd) {
        cout << "can't CreateWindow " << endl;
        cout << "szWindowClass=" << szWindowClass << endl;
        cout << "szTitle=" << szTitle << endl;
        return FALSE;
    }

    RECT wRect, cRect; // ウィンドウ全体の矩形、クライアント領域の矩形
    int ww, wh; // ウィンドウ全体の幅、高さ
    int cw, ch; // クライアント領域の幅、高さ
    int fw, fh; // フレームの幅、高さ
    // ウィンドウ全体の幅・高さを計算
    GetWindowRect(hWnd, &wRect);
    ww = wRect.right - wRect.left;
    wh = wRect.bottom - wRect.top;
    // クライアント領域の幅・高さを計算
    GetClientRect(hWnd, &cRect);
    cw = cRect.right - cRect.left;
    ch = cRect.bottom - cRect.top;
    // クライアント領域以外に必要なサイズを計算
    fw = ww - cw;
    fh = wh - ch;
    // 計算した幅と高さをウィンドウに設定
    SetWindowPos(
            hWnd,
            HWND_TOP,
            wRect.left,
            wRect.top,
            GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) + fw,
            GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) + fh,
            SWP_NOMOVE
    );

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    //hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//ショートカットロード

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            //特に何も無し
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
            //特に何も無し
        #else
            //特に何も無し
        #endif
    #else
        //特に何も無し
    #endif
#endif

    try {
        //神の誕生！
        pGod = NEW MyStg2nd::God(hInstance, hWnd);
        if (SUCCEEDED(pGod->init())) {
            adjustGameScreen(hWnd);

            // ループ・ザ・ループ
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        can_be_god = false;
                        SetActiveWindow(hWnd);
                        SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS );
                        //優先度上げる理由。
                        //非アクティブになると解放が著しく遅くなってしまうのを回避しようとした。

                        delete pGod; //神さようなら
                        MyStg2nd::Properties::clean();

                        ::timeEndPeriod(1);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //ダンプ
                        _CrtDumpMemoryLeaks();
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
                    if (can_be_god) {
                        pGod->be(); //神が存在したらしめる（この世が動く）
                    }

                }
            }
        }
    } catch (GgafCore::GgafCriticalException& e) {
        //異常終了時
        _TRACE_("＜例外＞"<<e.getMsg());
        string message = "\n・"+e.getMsg()+"  \n\nお心あたりが無いメッセージの場合、当方のバグの可能\性があります。\n誠に申\し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP);
        GgafCore::GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("＜致命的な例外＞"<<what);
        string message = "\n・"+what+"  \n\n恐れ入りますが、作者には予\測できなかったエラーです。\n誠に申\し訳ございません。\n";
        string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
        MessageBox(NULL, message_dialog.c_str(),"下記の致命的な例外が発生してしまいました", MB_OK|MB_ICONSTOP);
        GgafCore::GgafLogger::write("[exception]:"+what);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }
    /*
     } catch (...) {
     _TRACE_("＜原因不明例外＞たぶんアクセス違反");
     string message = "原因不明例外が発生しました。心あたりが無いメッセージの場合、当方のバグと思われます。\nご迷惑をおかけしましたことをお詫びいたします。";
     MessageBox(NULL, message.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP);
     GgafCore::GgafLogger::write("＜原因不明例外＞たぶんアクセス違反");
     ::timeEndPeriod(1);
     try { god->_pUniverse->dump();       } catch (...) { GgafCore::GgafLogger::write("god->_pUniverse->dump() 不可"); } //エラー無視
     try { delete god;                 } catch (...) { GgafCore::GgafLogger::write("delete god; 不可"); } //エラー無視
     try { GgafDx9Core::MyStg2nd::Properties::clean(); } catch (...) { GgafCore::GgafLogger::write("MyStg2nd::Properties::clean(); 不可"); } //エラー無視
     return EXIT_SUCCESS;
     }
     */
    //_CrtDumpMemoryLeaks();	// この時点で解放されていないメモリの情報の表示
    return (int) msg.wParam;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
    wcex.lpfnWndProc = WndProc; //ウィンドウプロシージャのアドレスを指定する。
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
/*
 BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
 {
 HWND hWnd;

 hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

 hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
 CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

 if (!hWnd)
 {
 return FALSE;
 }

 ShowWindow(hWnd, nCmdShow);
 UpdateWindow(hWnd);

 return TRUE;
 }
 */

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //	int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
        /*
         case WM_COMMAND:
         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam);
         // 選択されたメニューの解析:
         switch (wmId)
         {
         case IDM_ABOUT:
         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
         break;
         case IDM_EXIT:
         DestroyWindow(hWnd);
         break;
         default:
         return DefWindowProc(hWnd, message, wParam, lParam);
         }
         break;
         */
        case WM_SIZE:
            adjustGameScreen(hWnd);
            break;
            //    case WM_KEYDOWN:
            //        //エスケープキーを押したら終了させる
            //        case VK_ESCAPE:
            //            PostMessage(hWnd,WM_CLOSE,0,0);
            //            return 0;
            //
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラです。
/*
 INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
 {
 UNREFERENCED_PARAMETER(lParam);
 switch (message)
 {
 case WM_INITDIALOG:
 return (INT_PTR)TRUE;

 case WM_COMMAND:
 if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
 {
 EndDialog(hDlg, LOWORD(wParam));
 return (INT_PTR)TRUE;
 }
 break;
 }
 return (INT_PTR)FALSE;
 }
 */

void adjustGameScreen(HWND hWnd) {
    if (GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)) {
        RECT rect;
        GetClientRect(hWnd, &rect); //あるいは？
        if (1.0f * rect.right / rect.bottom > 1.0f * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) {
            //より横長になってしまっている
            float rate = 1.0f * rect.bottom / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT); //縮小率=縦幅の比率
            GgafDx9Core::GgafDx9God::_rectPresentDest.left = (rect.right / 2.0f) - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)
                    * rate / 2.0f);
            GgafDx9Core::GgafDx9God::_rectPresentDest.top = 0;
            GgafDx9Core::GgafDx9God::_rectPresentDest.right = (rect.right / 2.0f)
                    + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * rate / 2.0f);
            GgafDx9Core::GgafDx9God::_rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * rate;
        } else {
            //より縦長になってしまっている
            float rate = 1.0f * rect.right / GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH); //縮小率=横幅の比率
            GgafDx9Core::GgafDx9God::_rectPresentDest.left = 0;
            GgafDx9Core::GgafDx9God::_rectPresentDest.top = (rect.bottom / 2.0f)
                    - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * rate / 2.0f);
            GgafDx9Core::GgafDx9God::_rectPresentDest.right = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * rate;
            GgafDx9Core::GgafDx9God::_rectPresentDest.bottom = (rect.bottom / 2.0f)
                    + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * rate / 2.0f);
        }
    } else {
        GetClientRect(hWnd, &(GgafDx9Core::GgafDx9God::_rectPresentDest));
    }
}
