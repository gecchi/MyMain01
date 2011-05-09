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
int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
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

    MyRegisterClass_Primary(hInstance);
    HWND hWnd;
    hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
    if (PROPERTY(FULL_SCREEN)) {
        // �E�C���h�E�̐���
        if (PROPERTY(DUAL_DISPLAY)) {
            hWnd = CreateWindowEx(
                WS_EX_APPWINDOW,
                szWindowClass, //WINDOW_CLASS,
                szTitle,//WINDOW_TITLE,
                WS_POPUP | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                PROPERTY(GAME_BUFFER_WIDTH)/2, //�E�B���h�E�̕��A�Ⴄ�̂̓R�R�̂�
                PROPERTY(GAME_BUFFER_HEIGHT),
                HWND_DESKTOP,
                NULL,
                hInstance,
                NULL);
        } else {
            hWnd = CreateWindowEx(
                WS_EX_APPWINDOW,
                szWindowClass, //WINDOW_CLASS,
                szTitle,//WINDOW_TITLE,
                WS_POPUP | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                PROPERTY(GAME_BUFFER_WIDTH)/2, // �E�B���h�E�̕�
                PROPERTY(GAME_BUFFER_HEIGHT),
                HWND_DESKTOP,
                NULL,
                hInstance,
                NULL);
        }

    } else {
        hWnd = CreateWindow(
                szWindowClass, //WINDOW_CLASS,			// �E�C���h�E�N���X��
                szTitle,//WINDOW_TITLE,				// �E�C���h�E�̃^�C�g����
                //WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // �E�C���h�E�X�^�C��
                WS_OVERLAPPEDWINDOW, // �E�C���h�E�X�^�C��
                CW_USEDEFAULT, // �E�B���h�E�̕\���w���W
                CW_USEDEFAULT, // �E�B���h�E�̕\���x���W
                PROPERTY(GAME_BUFFER_WIDTH), // �E�B���h�E�̕�
                PROPERTY(GAME_BUFFER_HEIGHT), // �E�B���h�E�̕�
                HWND_DESKTOP, // �e�E�C���h�E
                NULL, // �E�C���h�E���j���[
                hInstance, // �C���X�^���X�n���h��
                NULL // WM_CREATE���
        );
    }

    if (!hWnd) {
        cout << "can't CreateWindow " << endl;
        cout << "szWindowClass=" << szWindowClass << endl;
        cout << "szTitle=" << szTitle << endl;
        return FALSE;
    }

    if (PROPERTY(FULL_SCREEN)) {

    } else {
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
                PROPERTY(GAME_BUFFER_WIDTH) + fw,
                PROPERTY(GAME_BUFFER_HEIGHT) + fh,
                SWP_NOMOVE
        );

        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);
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
        pGod = NEW MyStg2nd::God(hInstance, hWnd);
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
    catch( ... ) {
        _TRACE_("���v���I�ȓ��O��");
        string message = "�������܂����A�s���ȓ����G���[���������܂����B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȓ��O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }


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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //  int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {

        case WM_SIZE:
			if (GgafDx9Core::GgafDx9God::_can_be) {
                if (!PROPERTY(FULL_SCREEN)) {
                    GgafDx9Core::GgafDx9God::_adjustGameScreen = true;
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
