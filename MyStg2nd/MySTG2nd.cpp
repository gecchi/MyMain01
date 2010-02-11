// MySTG2nd.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#include "stdafx.h"
#include "MySTG2nd.h"
#include "resource.h"

using namespace std;

#define MAX_LOADSTRING 100
//#define WINDOW_TITLE "MyStg2nd"
//#define WINDOW_CLASS "mogera"

// �O���[�o���ϐ�:
HINSTANCE hInst; // ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING]; // �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING]; // ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

void adjustGameScreen(HWND);

/**
 * GNU GCC �Ȃ�΃G���g���|�C���g
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
    /* GetCommandLine����v���O�������𔲂��܂��B */
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0')
        lpCmdLine++;
    while (*lpCmdLine == ' ')
        lpCmdLine++;
    cout << lpCmdLine << endl;
    /* �������炪�A�{���̏��� */
    //wc.lpszClassName = "MySTG2nd";
    /* ��d�N���h�~ (�o�O����...)*/
    //	if((hWnd=FindWindow(WINDOW_CLASS, NULL))!=0) {
    //		if (IsIconic(hWnd)) {
    //			ShowWindow(hWnd, SW_RESTORE);
    //		}
    //		SetForegroundWindow(hWnd);
    //		return 0;
    //	}

    //�{����WinMain��
    WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
    return 0;
}

static MyStg2nd::God* pGod = NULL;
static bool can_be_god = true;

/**
 * VC�Ȃ�΃G���g���|�C���g
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

    // �O���[�o������������������Ă��܂��B
    //	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //	LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);
    //LoadString���ł���I
    strcpy(szTitle,"MyStg2nd"); //�������
    strcpy(szWindowClass,"MYSTG2ND"); //�ł���I


    //�v���p�e�B�t�@�C���Ǎ���
    try {
        MyStg2nd::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
		MessageBox(NULL, (string("config.properties �̃��[�h�̎��s�B\n���R�F")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP);
        MyStg2nd::Properties::clean();
        GgafCore::GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
        return EXIT_FAILURE;
    }

    MyRegisterClass(hInstance);
    HWND hWnd;
    hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
    hWnd = CreateWindow(
            szWindowClass, //WINDOW_CLASS,			// �E�C���h�E�N���X��
            szTitle,//WINDOW_TITLE,				// �E�C���h�E�̃^�C�g����
            WS_OVERLAPPEDWINDOW, // �E�C���h�E�X�^�C��
            CW_USEDEFAULT, // �E�B���h�E�̕\���w���W
            CW_USEDEFAULT, // �E�B���h�E�̕\���x���W
            GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH), // �E�B���h�E�̕�
            GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT), // �E�B���h�E�̕�
            NULL, // �e�E�C���h�E
            NULL, // �E�C���h�E���j���[
            hInstance, // �C���X�^���X�n���h��
            NULL // WM_CREATE���
    );

    if (!hWnd) {
        cout << "can't CreateWindow " << endl;
        cout << "szWindowClass=" << szWindowClass << endl;
        cout << "szTitle=" << szTitle << endl;
        return FALSE;
    }

    RECT wRect, cRect; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
    int ww, wh; // �E�B���h�E�S�̂̕��A����
    int cw, ch; // �N���C�A���g�̈�̕��A����
    int fw, fh; // �t���[���̕��A����
    // �E�B���h�E�S�̂̕��E�������v�Z
    GetWindowRect(hWnd, &wRect);
    ww = wRect.right - wRect.left;
    wh = wRect.bottom - wRect.top;
    // �N���C�A���g�̈�̕��E�������v�Z
    GetClientRect(hWnd, &cRect);
    cw = cRect.right - cRect.left;
    ch = cRect.bottom - cRect.top;
    // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
    fw = ww - cw;
    fh = wh - ch;
    // �v�Z�������ƍ������E�B���h�E�ɐݒ�
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
    //hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//�V���[�g�J�b�g���[�h

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            //���ɉ�������
        #else
            //���ɉ�������
        #endif
    #else
        //�������[���|�N�`�F�b�NBEGIN
        ::detectMemoryLeaksStart(std::cout);
    #endif
#else
    #ifdef _MSC_VER
        #ifdef _DEBUG
            //���ɉ�������
        #else
            //���ɉ�������
        #endif
    #else
        //���ɉ�������
    #endif
#endif

    try {
        //�_�̒a���I
        pGod = NEW MyStg2nd::God(hInstance, hWnd);
        if (SUCCEEDED(pGod->init())) {
            adjustGameScreen(hWnd);

            // ���[�v�E�U�E���[�v
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        can_be_god = false;
                        SetActiveWindow(hWnd);
                        SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS );
                        //�D��x�グ�闝�R�B
                        //��A�N�e�B�u�ɂȂ�Ɖ�����������x���Ȃ��Ă��܂��̂�������悤�Ƃ����B

                        delete pGod; //�_���悤�Ȃ�
                        MyStg2nd::Properties::clean();

                        ::timeEndPeriod(1);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //�_���v
                        _CrtDumpMemoryLeaks();
        #else
                        //���ɉ�������
        #endif
    #else
                        //�������[���|�N�`�F�b�NEND
                        ::detectMemoryLeaksEnd(std::cout);
    #endif
#else
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //�_���v
                        //_CrtDumpMemoryLeaks();
						_CrtMemDumpAllObjectsSince( NULL );

        #else
                        //���ɉ�������
        #endif
    #else
                        //���ɉ�������
    #endif
#endif

                        return EXIT_SUCCESS;
                    }
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                } else {
                    if (can_be_god) {
                        pGod->be(); //�_�����݂����炵�߂�i���̐��������j
                    }

                }
            }
        }
    } catch (GgafCore::GgafCriticalException& e) {
        //�ُ�I����
        _TRACE_("����O��"<<e.getMsg());
        string message = "\n�E"+e.getMsg()+"  \n\n���S�����肪�������b�Z�[�W�̏ꍇ�A�����̃o�O�̉\\��������܂��B\n���ɐ\\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
        GgafCore::GgafLogger::write("[GgafCriticalException]:"+e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("���v���I�ȗ�O��"<<what);
        string message = "\n�E"+what+"  \n\n�������܂����A��҂ɂ͗\\���ł��Ȃ������G���[�ł��B\n���ɐ\\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȗ�O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
        GgafCore::GgafLogger::write("[exception]:"+what);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }
    /*
     } catch (...) {
     _TRACE_("�������s����O�����Ԃ�A�N�Z�X�ᔽ");
     string message = "�����s����O���������܂����B�S�����肪�������b�Z�[�W�̏ꍇ�A�����̃o�O�Ǝv���܂��B\n�����f�����������܂������Ƃ����l�т������܂��B";
     MessageBox(NULL, message.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
     GgafCore::GgafLogger::write("�������s����O�����Ԃ�A�N�Z�X�ᔽ");
     ::timeEndPeriod(1);
     try { god->_pUniverse->dump();       } catch (...) { GgafCore::GgafLogger::write("god->_pUniverse->dump() �s��"); } //�G���[����
     try { delete god;                 } catch (...) { GgafCore::GgafLogger::write("delete god; �s��"); } //�G���[����
     try { GgafDx9Core::MyStg2nd::Properties::clean(); } catch (...) { GgafCore::GgafLogger::write("MyStg2nd::Properties::clean(); �s��"); } //�G���[����
     return EXIT_SUCCESS;
     }
     */
    //_CrtDumpMemoryLeaks();	// ���̎��_�ŉ������Ă��Ȃ��������̏��̕\��
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
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B
    wcex.lpfnWndProc = WndProc; //�E�B���h�E�v���V�[�W���̃A�h���X���w�肷��B
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //	int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
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
        case WM_SIZE:
            adjustGameScreen(hWnd);
            break;
            //    case WM_KEYDOWN:
            //        //�G�X�P�[�v�L�[����������I��������
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

void adjustGameScreen(HWND hWnd) {
    if (GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)) {
        RECT rect;
        GetClientRect(hWnd, &rect); //���邢�́H
        if (1.0f * rect.right / rect.bottom > 1.0f * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) {
            //��艡���ɂȂ��Ă��܂��Ă���
            float rate = 1.0f * rect.bottom / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT); //�k����=�c���̔䗦
            GgafDx9Core::GgafDx9God::_rectPresentDest.left = (rect.right / 2.0f) - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)
                    * rate / 2.0f);
            GgafDx9Core::GgafDx9God::_rectPresentDest.top = 0;
            GgafDx9Core::GgafDx9God::_rectPresentDest.right = (rect.right / 2.0f)
                    + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * rate / 2.0f);
            GgafDx9Core::GgafDx9God::_rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * rate;
        } else {
            //���c���ɂȂ��Ă��܂��Ă���
            float rate = 1.0f * rect.right / GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH); //�k����=�����̔䗦
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
