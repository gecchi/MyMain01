// MySTG2nd.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#include "stdafx.h"
#include "MySTG2nd.h"
#include "resource.h"

using namespace std;

#define MAX_LOADSTRING 100


// �O���[�o���ϐ�:
HINSTANCE hInst; // ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING]; // �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING]; // ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM MyRegisterClass_Primary(HINSTANCE hInstance);
ATOM MyRegisterClass_Secondary(HINSTANCE hInstance);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

void myUnexpectedHandler();
void myTerminateHandler();

/**
 * GNU GCC �Ȃ�΃G���g���|�C���g
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
    /* GetCommandLine����v���O�������𔲂��܂��B */
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0')
        lpCmdLine++;
    while (*lpCmdLine == ' ')
        lpCmdLine++;
    cout << lpCmdLine << endl;
    //�{����WinMain��
    WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
    return 0;
}

static MyStg2nd::God* pGod = NULL;

/**
 * VC�Ȃ�΃G���g���|�C���g
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;

    // �O���[�o������������������Ă��܂��B
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    _TRACE_("szTitle = "<<szTitle);
    LoadString(hInstance, IDC_MYSTG2ND, szWindowClass, MAX_LOADSTRING);
    _TRACE_("szWindowClass = "<<szWindowClass);

    //�v���p�e�B�t�@�C���Ǎ���
    try {
        MyStg2nd::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
        MessageBox(NULL, (string("config.properties �̃��[�h�̎��s�B\n���R�F")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP);
        MyStg2nd::Properties::clean();
        _TRACE_("[GgafCriticalException]:" << e.getMsg());
        return EXIT_FAILURE;
    }
    HWND hWnd1 = NULL;
    HWND hWnd2 = NULL;
    hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

    // �E�C���h�E�̐���
    if (CFG_PROPERTY(FULL_SCREEN)) {
        if (CFG_PROPERTY(DUAL_VIEW)) {
            //�t���X�N���[�����[�h�E�Q��ʎg�p
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
            //�t���X�N���[�����[�h�E�P��ʎg�p
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
                    szWindowClass, //WINDOW_CLASS,          // �E�C���h�E�N���X��
                    szTitle,//WINDOW_TITLE,             // �E�C���h�E�̃^�C�g����
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // �E�C���h�E�X�^�C��
                    WS_OVERLAPPEDWINDOW, // �E�C���h�E�X�^�C��
                    CW_USEDEFAULT, // �E�B���h�E�̕\���w���W
                    CW_USEDEFAULT, // �E�B���h�E�̕\���x���W
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), // �E�B���h�E�̕�
                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT), // �E�B���h�E�̕�
                    HWND_DESKTOP, // �e�E�C���h�E
                    NULL, // �E�C���h�E���j���[
                    hInstance, // �C���X�^���X�n���h��
                    NULL // WM_CREATE���
            );

            MyRegisterClass_Secondary(hInstance);
            hWnd2 = CreateWindow(
                    "secondary", //WINDOW_CLASS,
                    "secondary",//WINDOW_TITLE,
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // �E�C���h�E�X�^�C��
                    WS_OVERLAPPEDWINDOW, // �E�C���h�E�X�^�C��
                    CW_USEDEFAULT, // �E�B���h�E�̕\���w���W
                    CW_USEDEFAULT, // �E�B���h�E�̕\���x���W
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), // �E�B���h�E�̕�
                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT), // �E�B���h�E�̕�
                    HWND_DESKTOP, // �e�E�C���h�E
                    NULL, // �E�C���h�E���j���[
                    hInstance, // �C���X�^���X�n���h��
                    NULL // WM_CREATE���
            );
        } else {
            MyRegisterClass_Primary(hInstance);
            hWnd1 = CreateWindow(
                    szWindowClass, //WINDOW_CLASS,          // �E�C���h�E�N���X��
                    szTitle,//WINDOW_TITLE,             // �E�C���h�E�̃^�C�g����
                    //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // �E�C���h�E�X�^�C��
                    WS_OVERLAPPEDWINDOW, // �E�C���h�E�X�^�C��
                    CW_USEDEFAULT, // �E�B���h�E�̕\���w���W
                    CW_USEDEFAULT, // �E�B���h�E�̕\���x���W
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), // �E�B���h�E�̕�
                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT), // �E�B���h�E�̕�
                    HWND_DESKTOP, // �e�E�C���h�E
                    NULL, // �E�C���h�E���j���[
                    hInstance, // �C���X�^���X�n���h��
                    NULL // WM_CREATE���
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
            RECT wRect1, cRect1; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
            int ww1, wh1; // �E�B���h�E�S�̂̕��A����
            int cw1, ch1; // �N���C�A���g�̈�̕��A����
            int fw1, fh1; // �t���[���̕��A����
            // �E�B���h�E�S�̂̕��E�������v�Z
            GetWindowRect(hWnd1, &wRect1);
            ww1 = wRect1.right - wRect1.left;
            wh1 = wRect1.bottom - wRect1.top;
            // �N���C�A���g�̈�̕��E�������v�Z
            GetClientRect(hWnd1, &cRect1);
            cw1 = cRect1.right - cRect1.left;
            ch1 = cRect1.bottom - cRect1.top;
            // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
            fw1 = ww1 - cw1;
            fh1 = wh1 - ch1;
            // �v�Z�������ƍ������E�B���h�E�ɐݒ�
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

            RECT wRect2, cRect2; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
            int ww2, wh2; // �E�B���h�E�S�̂̕��A����
            int cw2, ch2; // �N���C�A���g�̈�̕��A����
            int fw2, fh2; // �t���[���̕��A����
            // �E�B���h�E�S�̂̕��E�������v�Z
            GetWindowRect(hWnd2, &wRect2);
            ww2 = wRect2.right - wRect2.left;
            wh2 = wRect2.bottom - wRect2.top;
            // �N���C�A���g�̈�̕��E�������v�Z
            GetClientRect(hWnd2, &cRect2);
            cw2 = cRect2.right - cRect2.left;
            ch2 = cRect2.bottom - cRect2.top;
            // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
            fw2 = ww2 - cw2;
            fh2 = wh2 - ch2;
            // �v�Z�������ƍ������E�B���h�E�ɐݒ�
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
            RECT wRect, cRect; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
            int ww, wh; // �E�B���h�E�S�̂̕��A����
            int cw, ch; // �N���C�A���g�̈�̕��A����
            int fw, fh; // �t���[���̕��A����
            // �E�B���h�E�S�̂̕��E�������v�Z
            GetWindowRect(hWnd1, &wRect);
            ww = wRect.right - wRect.left;
            wh = wRect.bottom - wRect.top;
            // �N���C�A���g�̈�̕��E�������v�Z
            GetClientRect(hWnd1, &cRect);
            cw = cRect.right - cRect.left;
            ch = cRect.bottom - cRect.top;
            // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
            fw = ww - cw;
            fh = wh - ch;
            // �v�Z�������ƍ������E�B���h�E�ɐݒ�
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
        //hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTSTG17_031));//�V���[�g�J�b�g���[�h
    }

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
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
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
        #else
            //���ɉ�������
        #endif
    #else
        //���ɉ�������
    #endif
#endif

    try {
        //�_�̒a���I
        pGod = NEW MyStg2nd::God(hInstance, hWnd1, hWnd2);
        if (SUCCEEDED(pGod->init())) {

            // ���[�v�E�U�E���[�v
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        if (MyStg2nd::God::_can_be) {
                            MyStg2nd::God::_can_be = false;
//                            pGod->_can_be = false;
                            while (pGod->_is_being) {
                                Sleep(2);
                                _TRACE_("Wait! �_ is being yet..");
                            }
                            delete pGod; //�_���悤�Ȃ�

                            //RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
                            pGod = NULL;
                            MyStg2nd::Properties::clean();
                        }

                        ::timeEndPeriod(1);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
                        //�_���v
                        //_CrtDumpMemoryLeaks();
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
                    if (MyStg2nd::God::_can_be && pGod->_is_being == false) {
                        pGod->be(); //�_�����݂����炵�߂�i���̐��������j
                    }

                }
            }
        }
    } catch (GgafCore::GgafException& e) {
        //�ُ�I����
        _TRACE_("����O��"<<e.getMsg());
        string message = "\n�E"+e.getMsg()+"  \n\n�G���[�ɂ��S�����肪�����ꍇ�A�{�A�v���̃o�O�̉\���������ł��B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("���v���I�ȗ�O��"<<what);
        string message = "\n�E"+what+"  \n\n�������܂����A��҂ɂ͗\���ł��Ȃ������v���I�G���[�ł��B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȗ�O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
        _TRACE_("[exception]:"<<what);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }

#ifndef MY_DEBUG
    //�ȉ��̃L���b�`�̓������ᔽ���Ԃ��\�������邽�߁ADEBUG���͖����Ƃ���B
    catch( ... ) {
        _TRACE_("���v���I�ȓ��O��");
        string message = "�������܂����A�s���ȓ����G���[���������܂����B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȓ��O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
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
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B
    wcex.lpfnWndProc = WndProc; //�E�B���h�E�v���V�[�W���̃A�h���X���w�肷��B
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

ATOM MyRegisterClass_Secondary(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B
    wcex.lpfnWndProc = WndProc;
                       //(WNDPROC)GetWindowLong(_pHWndPrimary, GWL_WNDPROC ); //�P��ʖڂ̃E�B���h�E�v���V�[�W�������ʎw�肷��B
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSTG2ND));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
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
                    _TRACE_("GgafDx9Input::initDx9Input() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���");
                }
            }
                // �L�[�{�[�h�������x���ݒ�
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Keyboard) {
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    MessageBox(hWnd, TEXT("GgafDx9Input::initDx9Input() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���"),
                               TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                }
            }
            if (GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick) {
                // �Q�[���X�e�B�b�N�������x����ݒ肷��
                hr = GgafDx9Core::GgafDx9Input::_pIDirectInputDevice8_Joystick->SetCooperativeLevel(hWnd, DISCL_FOREGROUND
                        | DISCL_NONEXCLUSIVE );
                if (hr != D3D_OK) {
                    _TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
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
