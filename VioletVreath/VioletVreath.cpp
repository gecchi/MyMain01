#include "stdafx.h"
#include "GgafLibEntory.h"
#include "resource.h"

using namespace std;

#define MY_IDM_RESET_WINDOW_SIZE 10
#define MY_IDM_ABOUT             11
#define MAX_LOADSTRING 100
// �O���[�o���ϐ�:
HINSTANCE hInst; // ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING]; // �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING]; // ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

void myUnexpectedHandler();
void myTerminateHandler();


/**
 * GNU GCC �Ȃ�΃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv);
}

static VioletVreath::God* pGod = NULL;

/**
 * VC�Ȃ�΃G���g���|�C���g
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);


    // �O���[�o������������������Ă��܂��B
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_VIOLETVREATH, szWindowClass, MAX_LOADSTRING);

    //�v���p�e�B�t�@�C���Ǎ���
    try {
        VioletVreath::Properties::load(".\\config.properties");
    } catch (GgafCore::GgafCriticalException& e) {
        MessageBox(NULL, (string("config.properties �̃��[�h�̎��s�B\n���R�F")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VioletVreath::Properties::clean();
        _TRACE_("[GgafCriticalException]:" << e.getMsg());
        return EXIT_FAILURE;
    }
    hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B





    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    WNDCLASSEX wcex1;
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B
    wcex1.lpfnWndProc =  (WNDPROC)WndProc; //�E�B���h�E�v���V�[�W���̃A�h���X���w�肷��B
    wcex1.cbClsExtra = 0;
    wcex1.cbWndExtra = 0;
    wcex1.hInstance = hInstance;
    wcex1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIOLETVREATH));
    wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    wcex1.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_VIOLETVREATH);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
    wcex1.lpszClassName = szWindowClass;
    wcex1.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));


    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";

    HWND hWnd1, hWnd2;
    GgafLibCreateWindow(wcex1, wcex2, szTitle, "secondary", hWnd1, hWnd2);

    //_CrtSetBreakAlloc(203659);

#ifdef MY_DEBUG
    #ifdef _MSC_VER
        #ifdef _DEBUG
            ::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
        #else
            //���ɉ�������
        #endif
    #else
        //�������[���|�N�`�F�b�NBEGIN
       // ::detectMemoryLeaksStart(std::cout);
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

    MSG msg;
    try {
        //�_�̒a��
        pGod = NEW VioletVreath::God(hInstance, hWnd1, hWnd2);
        if (SUCCEEDED(pGod->init())) {
            // ���[�v�E�U�E���[�v
            ::timeBeginPeriod(1);
            while (true) {
                if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        if (VioletVreath::God::_can_be) {
                            VioletVreath::God::_can_be = false;
                            while (pGod->_is_being) {
                                Sleep(2);
                                _TRACE_("Wait! �_ is being yet..");
                            }
                            delete pGod; //�_�̍Ŋ�
                            pGod = NULL;
                            VioletVreath::Properties::clean();
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
                      //  ::detectMemoryLeaksEnd(std::cout);
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
                    if (VioletVreath::God::_can_be && pGod->_is_being == false) {
                        pGod->be(); //be() �ŁA���̐�������
                    }

                }
            }
        }
    } catch (GgafCore::GgafException& e) {
        //�ُ�I����
        _TRACE_("����O��"<<e.getMsg());
        string message = "\n�E"+e.getMsg()+"  \n\n�G���[�ɂ��S�����肪�����ꍇ�A�{�A�v���̃o�O�̉\���������ł��B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_GgafException.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_GgafException.rep");
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (exception& e2) {
        string what(e2.what());
        _TRACE_("���v���I�ȗ�O��"<<what);
        string message = "\n�E"+what+"  \n\n�������܂����A��҂ɂ͗\���ł��Ȃ������v���I�G���[�ł��B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȗ�O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        _TRACE_("[exception]:"<<what);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_exception.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_exception.rep");
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }

#ifndef MY_DEBUG
    //�ȉ��̃L���b�`��DEBUG���ł����Ă��A�������ᔽ���Ԃ��\�������邽�߁ADEBUG���͖����Ƃ���B
    catch( ... ) {
        _TRACE_("���v���I�ȓ��O��");
        string message = "�������܂����A�s���ȓ����G���[���������܂����B\n���ɐ\���󂲂����܂���B\n";
        string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(NULL, message_dialog.c_str(),"���L�̒v���I�ȓ��O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam);

    switch (message) {

        case WM_CREATE:
            // �V�X�e�����j���[�J�X�^���֐����Ă�
            CustmizeSysMenu(hWnd);
            break;
        case WM_SYSCOMMAND:
            if ( (wParam & 0xFFF0) == SC_SCREENSAVE ) {
                return 1;
            }
            if(wParam == MY_IDM_ABOUT) {
                //�o�[�W�����_�C�A���O
//                dhwnd  = CreateDialog(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
                DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            } else if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //�E�B���h�E���T�C�Y
                resetWindowsize(hWnd);
            }
            break;
        default:
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// �V�X�e�����j���[���J�X�^�}�C�Y���܂��B
BOOL CustmizeSysMenu(HWND hWnd)
{
    HMENU hMenu;
    // �V�X�e�����j���[�̃n���h�����擾
    hMenu = GetSystemMenu(hWnd, FALSE);
//    for (i = 0; i <= 5; i++)
//        //�V�X�e�����j���[�̍��ڂ�����
//        DeleteMenu(hMenu, 0, MF_BYPOSITION);
//    //�V�X�e�����j���[�̍��ڂ�ǉ�
    InsertMenu(hMenu, 5, MF_BYPOSITION | MF_SEPARATOR, NULL, "");
    InsertMenu(hMenu, 6, MF_BYPOSITION | MF_STRING, MY_IDM_RESET_WINDOW_SIZE, "Reset window size.");
    InsertMenu(hMenu, 7, MF_BYPOSITION | MF_STRING, MY_IDM_ABOUT, "about");

//    AppendMenu(hMenu, MF_STRING, IDM_ABOUT, "�A�o�E�g");
    //�V�X�e�����j���[���쐬
    DrawMenuBar(hWnd);

    return TRUE;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���ł��B
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


//// �V�X�e�����j���[�̋������L�q
//LRESULT SysMenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//switch (wParam) {
//    case IDM_TEST:
//        MessageBox(hWnd, (LPCSTR)"�e�X�g���ڂ��I�΂�܂����B",
//            (LPCSTR)"�e�X�g", MB_OK);
//        return 0L;
//        break;
//    default:
//        return(DefWindowProc(hWnd, msg, wParam, lParam));
//        break;
//}
//}


