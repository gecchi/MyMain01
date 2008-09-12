// MySTG2nd.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "MySTG2nd.h"

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/**
 * GNU GCC �Ȃ�΃G���g���|�C���g
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
	/* GetCommandLine����v���O�������𔲂��܂��B */
	while(*lpCmdLine != ' ' && *lpCmdLine != '\0') lpCmdLine++;
	while(*lpCmdLine == ' ') lpCmdLine++;
cout << lpCmdLine << endl;
	/* �������炪�A�{���̏��� */
	wc.lpszClassName = "HOGEHOGE";
	/* ��d�N���h�~ (�o�O����...)*/
	if((hWnd=FindWindow(wc.lpszClassName, NULL))!=0) {
		if (IsIconic(hWnd)) {
			ShowWindow(hWnd, SW_RESTORE);
		}
		SetForegroundWindow(hWnd);
		return 0;
	}

	//�{����WinMain��
	WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

/**
 * VC�Ȃ�΃G���g���|�C���g
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

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);

	strcpy(szTitle,"MySTG2nd");        //�������
	strcpy(szWindowClass,"MYSTG2ND");  //�ł���I


	//�v���p�e�B�t�@�C���Ǎ���
	try {
		GgafDx9Properties::load(".\\config.properties");
	} catch (GgafCriticalException& e) {
		GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
		GgafDx9Properties::clean();
		return EXIT_FAILURE;
	}


	MyRegisterClass(hInstance);
	HWND hWnd;
	hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
	hWnd = CreateWindow(
		szWindowClass,			// �E�C���h�E�N���X��
		szTitle,				// �E�C���h�E�̃^�C�g����
		WS_OVERLAPPEDWINDOW,	// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̕\���w���W
		CW_USEDEFAULT,			// �E�B���h�E�̕\���x���W
		GGAFDX9_PROPERTY(SCREEN_WIDTH),		// �E�B���h�E�̕�
		GGAFDX9_PROPERTY(SCREEN_HEIGHT),	// �E�B���h�E�̍���
		NULL,					// �e�E�C���h�E
		NULL,					// �E�C���h�E���j���[
		hInstance,				// �C���X�^���X�n���h��
		NULL					// WM_CREATE���
	);

	if (!hWnd) {
		cout << "CreateWindow" << endl;
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//�V���[�g�J�b�g���[�h

#ifdef OREDEBUG
	//�������[���|�N�`�F�b�NBEGIN
	::detectMemoryLeaksStart(std::cout);
#endif

	//�_�̒a���I
	God* god = NEW God(hInstance, hWnd);
	if (SUCCEEDED(god->init())) {

		// ���[�v�E�U�E���[�v
		::timeBeginPeriod(1);
		while (true) {
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				if (msg.message == WM_QUIT) {
					delete god; //�_�l���悤�Ȃ�
					GgafDx9Properties::clean();
					::timeEndPeriod(1);
#ifdef OREDEBUG
					//�������[���|�N�`�F�b�NEND
					::detectMemoryLeaksEnd(std::cout);
#endif
					return EXIT_SUCCESS;
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			} else {
				try {
					god->be(); //�_�����݂����炵�߂�i���E�������j
				} catch (GgafCriticalException& e) {
					//�ُ�I����
					string message = "�ȉ��̃G���[���������Ă��܂��܂����B\n�u"+e.getMsg()+"�v\n���ɐ\\���󂲂����܂���B"; //"�\"�̓_����(0x905C)
					MessageBox(NULL, message.c_str(),"Error", MB_OK|MB_ICONSTOP);
					GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
					god->_pWorld->dump();
					delete god; //�_���ڂ�
					GgafDx9Properties::clean();
					::timeEndPeriod(1);//�^�C�}�[���x�I������
#ifdef OREDEBUG
					//�������[���|�N�`�F�b�NEND
					::detectMemoryLeaksEnd(std::cout);
#endif
					return EXIT_FAILURE;
				}
			}
		}
	}

	//_CrtDumpMemoryLeaks();	// ���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
	return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
//  �R�����g:
//
//    ���̊֐�����юg�����́A'RegisterClassEx' �֐����ǉ����ꂽ
//    Windows 95 ���O�� Win32 �V�X�e���ƌ݊�������ꍇ�ɂ̂ݕK�v�ł��B
//    �A�v���P�[�V�������A�֘A�t����ꂽ
//    �������`���̏������A�C�R�����擾�ł���悤�ɂ���ɂ́A
//    ���̊֐����Ăяo���Ă��������B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B
	wcex.lpfnWndProc	= WndProc;                 //�E�B���h�E�v���V�[�W���̃A�h���X���w�肷��B
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
/*
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	 HWND hWnd;

	 hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

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
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
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
		// �I�����ꂽ���j���[�̉��:
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

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���ł��B
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
