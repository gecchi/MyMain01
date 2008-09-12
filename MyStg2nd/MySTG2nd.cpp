// MySTG2nd.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "MySTG2nd.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/**
 * GNU GCC ならばエントリポイント
 */
int main(int argc,char *argv[]) {
	STARTUPINFO	StatUpInfo;
	HINSTANCE		hInstance;
	HANDLE		hPrevInstance;
	LPSTR		lpCmdLine;
	int			nCmdShow;
	WNDCLASS	wc;
	HWND		hWnd;
//	MSG			msg;

	GetStartupInfo(&StatUpInfo);
	hInstance = GetModuleHandle(0);
	hPrevInstance = 0;
	lpCmdLine = GetCommandLine();
	nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW)?
				StatUpInfo.wShowWindow:SW_SHOWNORMAL;
	/* GetCommandLineからプログラム名を抜きます。 */
	while(*lpCmdLine != ' ' && *lpCmdLine != '\0') lpCmdLine++;
	while(*lpCmdLine == ' ') lpCmdLine++;
cout << lpCmdLine << endl;
	/* ここからが、本来の処理 */
	wc.lpszClassName = "HOGEHOGE";
	/* 二重起動防止 (バグあり...)*/
	if((hWnd=FindWindow(wc.lpszClassName, NULL))!=0) {
		if (IsIconic(hWnd)) {
			ShowWindow(hWnd, SW_RESTORE);
		}
		SetForegroundWindow(hWnd);
		return 0;
	}

	//本来のWinMainへ
	WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

/**
 * VCならばエントリポイント
 */
int APIENTRY _tWinMain(HINSTANCE hInstance,
										 HINSTANCE hPrevInstance,
										 LPTSTR    lpCmdLine,
										 int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
//	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);

	strcpy(szTitle,"MySTG2nd");        //無理やり
	strcpy(szWindowClass,"MYSTG2ND");  //ですよ！


	//プロパティファイル読込み
	try {
		GgafDx9Properties::load(".\\config.properties");
	} catch (GgafCriticalException& e) {
		GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
		GgafDx9Properties::clean();
		return EXIT_FAILURE;
	}


	MyRegisterClass(hInstance);
	HWND hWnd;
	hInst = hInstance; // グローバル変数にインスタンス処理を格納します。
	hWnd = CreateWindow(
		szWindowClass,			// ウインドウクラス名
		szTitle,				// ウインドウのタイトル名
		WS_OVERLAPPEDWINDOW,	// ウインドウスタイル
		CW_USEDEFAULT,			// ウィンドウの表示Ｘ座標
		CW_USEDEFAULT,			// ウィンドウの表示Ｙ座標
		GGAFDX9_PROPERTY(SCREEN_WIDTH),		// ウィンドウの幅
		GGAFDX9_PROPERTY(SCREEN_HEIGHT),	// ウィンドウの高さ
		NULL,					// 親ウインドウ
		NULL,					// ウインドウメニュー
		hInstance,				// インスタンスハンドル
		NULL					// WM_CREATE情報
	);

	if (!hWnd) {
		cout << "CreateWindow" << endl;
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//ショートカットロード

#ifdef OREDEBUG
	//メモリーリ－クチェックBEGIN
	::detectMemoryLeaksStart(std::cout);
#endif

	//神の誕生！
	God* god = NEW God(hInstance, hWnd);
	if (SUCCEEDED(god->init())) {

		// ループ・ザ・ループ
		::timeBeginPeriod(1);
		while (true) {
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				if (msg.message == WM_QUIT) {
					delete god; //神様さようなら
					GgafDx9Properties::clean();
					::timeEndPeriod(1);
#ifdef OREDEBUG
					//メモリーリ－クチェックEND
					::detectMemoryLeaksEnd(std::cout);
#endif
					return EXIT_SUCCESS;
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			} else {
				try {
					god->be(); //神が存在したらしめる（世界が動く）
				} catch (GgafCriticalException& e) {
					//異常終了時
					string message = "以下のエラーが発生してしまいました。\n「"+e.getMsg()+"」\n誠に申\し訳ございません。"; //"申"はダメ字(0x905C)
					MessageBox(NULL, message.c_str(),"Error", MB_OK|MB_ICONSTOP);
					GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
					god->_pWorld->dump();
					delete god; //神あぼん
					GgafDx9Properties::clean();
					::timeEndPeriod(1);//タイマー精度終了処理
#ifdef OREDEBUG
					//メモリーリ－クチェックEND
					::detectMemoryLeaksEnd(std::cout);
#endif
					return EXIT_FAILURE;
				}
			}
		}
	}

	//_CrtDumpMemoryLeaks();	// この時点で開放されていないメモリの情報の表示
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
	wcex.lpfnWndProc	= WndProc;                 //ウィンドウプロシージャのアドレスを指定する。
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
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
