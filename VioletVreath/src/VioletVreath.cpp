#include "stdafx.h"
#include "GgafLibEntry.h"
#include "resource.h"

#define MY_IDM_RESET_WINDOW_SIZE  10
#define MY_IDM_ABOUT              11
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
// �O���[�o���ϐ�:
HINSTANCE hInst; // ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING]; // �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING]; // ���C�� �E�B���h�E �N���X��
HWND hWnd1, hWnd2;
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

static VioletVreath::God* pGod = nullptr;

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
        MessageBox(nullptr, (std::string("config.properties �̃��[�h�̎��s�B\n���R�F")+e.getMsg()).c_str(),"Error", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
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
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    wcex1.lpszMenuName = nullptr;//MAKEINTRESOURCE(IDC_VIOLETVREATH);//nullptr; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
    wcex1.lpszClassName = szWindowClass;
    wcex1.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));


    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";


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
                if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        if (VioletVreath::God::_can_be) {
                            VioletVreath::God::_can_be = false;
                            while (pGod->_is_being) {
                                Sleep(2);
                                _TRACE_("Wait! �_ is being yet..");
                            }
                            delete pGod; //�_�̍Ŋ�
                            pGod = nullptr;
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
                        _CrtMemDumpAllObjectsSince( nullptr );

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
        std::string message = "\n�E"+e.getMsg()+"  \n\n�G���[�ɂ��S�����肪�����ꍇ�A�{�A�v���̃o�O�̉\���������ł��B\n���ɐ\���󂲂����܂���B\n";
        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(nullptr, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_GgafException.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_GgafException.rep");
        _TRACE_("[GgafCriticalException]:"<<e.getMsg());
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    } catch (std::exception& e2) {
        std::string what(e2.what());
        _TRACE_("���v���I�ȗ�O��"<<what);
        std::string message = "\n�E"+what+"  \n\n�������܂����A��҂ɂ͗\���ł��Ȃ������v���I�G���[�ł��B\n���ɐ\���󂲂����܂���B\n";
        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(nullptr, message_dialog.c_str(),"���L�̒v���I�ȗ�O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
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
        std::string message = "�������܂����A�s���ȓ����G���[���������܂����B\n���ɐ\���󂲂����܂���B\n";
        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(nullptr, message_dialog.c_str(),"���L�̒v���I�ȓ��O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
        VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_UNKNOWN_ERROR.rep");
        VB_UI->_pRpy->outputFile("VB_UI_LAST_UNKNOWN_ERROR.rep");
        ::timeEndPeriod(1);
        return EXIT_FAILURE;
    }
#endif

    return (int) msg.wParam;
}

void myUnexpectedHandler() {
    MessageBox(nullptr, "UnexpectedHandler called.","ERROR", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Unexpected.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Unexpected.rep");
    std::unexpected();
}

void myTerminateHandler() {
    MessageBox(nullptr, "TerminateHandler called.","ERROR", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Terminate.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Terminate.rep");
    std::terminate();
}


void chengeViewPos(HWND prm_pHWnd, int pos) {
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        if (prm_pHWnd == hWnd1) {
            GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1) = pos;
        } else if (prm_pHWnd == hWnd2) {
            GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2) = pos;
        }
    } else {
        GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION) = pos;
    }
    if (GgafDxCore::GgafDxGod::_can_be) {
        if (!GGAF_PROPERTY(FULL_SCREEN)) {
            GgafDxCore::GgafDxGod::_adjustGameScreen = true;
            GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = prm_pHWnd;
        }
    }
}
void chengeViewAspect(HWND prm_pHWnd, bool prm_b) {
    GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT) = prm_b;
    if (GgafDxCore::GgafDxGod::_can_be) {
        if (!GGAF_PROPERTY(FULL_SCREEN)) {
            GgafDxCore::GgafDxGod::_adjustGameScreen = true;
            GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = prm_pHWnd;
        }
    }
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
            } else if(wParam == MY_IDM_VPOS_1) {
                chengeViewPos(hWnd, 1);
            } else if(wParam == MY_IDM_VPOS_2) {
                chengeViewPos(hWnd, 2);
            } else if(wParam == MY_IDM_VPOS_3) {
                chengeViewPos(hWnd, 3);
            } else if(wParam == MY_IDM_VPOS_4) {
                chengeViewPos(hWnd, 4);
            } else if(wParam == MY_IDM_VPOS_5) {
                chengeViewPos(hWnd, 5);
            } else if(wParam == MY_IDM_VPOS_6) {
                chengeViewPos(hWnd, 6);
            } else if(wParam == MY_IDM_VPOS_7) {
                chengeViewPos(hWnd, 7);
            } else if(wParam == MY_IDM_VPOS_8) {
                chengeViewPos(hWnd, 8);
            } else if(wParam == MY_IDM_VPOS_9) {
                chengeViewPos(hWnd, 9);
            } else if(wParam == MY_IDM_ASPECT_FIXED) {
                chengeViewAspect(hWnd, true);
            } else if(wParam == MY_IDM_ASPECT_STRETCH) {
                chengeViewAspect(hWnd, false);
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
//    for (i = 0; i <= 5; i++)
//        //�V�X�e�����j���[�̍��ڂ�����
//        DeleteMenu(hMenu, 0, MF_BYPOSITION);
//    //�V�X�e�����j���[�̍��ڂ�ǉ�


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

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    InsertMenu(hMenu, 5, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    InsertMenu(hMenu, 6, MF_BYPOSITION | MF_STRING, MY_IDM_RESET_WINDOW_SIZE    , "Reset window size.");
    InsertMenu(hMenu, 7, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_aspect, "Game view aspect.");
    InsertMenu(hMenu, 8, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_vp    , "Game view position.");
    InsertMenu(hMenu, 9, MF_BYPOSITION | MF_STRING, MY_IDM_ABOUT, "About");

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


