#include "jp/ggaf/GgafLib.h"
#include "VioletVreath_launcher.h"

#include <Shlwapi.h>
#include "resource.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"

#define MY_IDM_RESET_WINDOW_SIZE  10
#define MY_IDM_CHANGE_TO_BORDERLESS_WINDOW 11
#define MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE  12
#define MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE  13
#define MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE  14
#define MY_IDM_SAVE               15
#define MY_IDM_REBOOT             16
#define MY_IDM_ABOUT              17
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);

void myUnexpectedHandler();
void myTerminateHandler();

/**
 * VC�Ȃ�΃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
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

    TCHAR current_dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_dir);
    LPTSTR command_line = GetCommandLine();
    _TRACE_("current_dir="<<current_dir);
    _TRACE_("command_line="<<command_line);
    _TRACE_("lpCmdLine="<<lpCmdLine);
    _TRACE_("nCmdShow="<<nCmdShow);

    for(int i = 0; i < __argc; i++){
        std::string arg = std::string(__argv[i]);
        _TRACE_("__argv["<<i<<"]=" << arg);
    }

    std::set_unexpected(myUnexpectedHandler);
    std::set_terminate(myTerminateHandler);

    // �O���[�o������������������Ă��܂��B
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_VIOLETVREATH, szWindowClass, MAX_LOADSTRING);

    std::string config_file = "";
    if (__argc >= 2) {
        config_file = std::string(__argv[1]);
    } else {
        _TRACE_("�y�x���z�����ɐݒ�t�@�C�������݂��Ȃ��̂ŁA����� '" <<VV_DEFAULT_CONFIG_FILE << "' �� load ���܂��B");
        config_file = std::string(VV_DEFAULT_CONFIG_FILE);
    }
    //�v���p�e�B�t�@�C���Ǎ���
    if (PathFileExists(config_file.c_str())) {
        _TRACE_("�E�E�E"<<config_file<< " �� load ���܂�");
        CONFIG::loadProperties(config_file);
        _TRACE_("�E�E�E"<<config_file<< " �� load ���܂���");
    } else {
        std::string msg = "�ݒ�t�@�C��("+config_file+")��������܂���B";
        MessageBox(nullptr, msg.c_str(), "Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return EXIT_FAILURE;
    }


//    _TRACE_(""<<config_file<< " �� load ���܂���");
//    //�v���p�e�B�t�@�C���Ǎ���
//    if (PathFileExists(VV_DEFAULT_CONFIG_FILE)) {
//        if (PathFileExists(VV_CONFIG_FILE)) {
//            CONFIG::loadProperties(VV_CONFIG_FILE);
//            _TRACE_("config.properties �� load ���܂���");
//        } else {
//            CONFIG::loadProperties(VV_DEFAULT_CONFIG_FILE);
//            CONFIG::_properties.write(VV_CONFIG_FILE);
//            _TRACE_("�y�x���zconfig.properties �����݂��Ȃ��̂ŁA����� '" <<VV_DEFAULT_CONFIG_FILE << "' �� load ���܂����B");
//        }
//    } else {
//        MessageBox(nullptr, "����ݒ�t�@�C��(.default_config.properties)��������܂���B",
//                                 "Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
//        return EXIT_FAILURE;
//    }

    hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
    GgafCore::Rgb rgb = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    WNDCLASSEX wcex1;
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS ;
    //�����E���������ɃE�C���h�E�T�C�Y���ύX���ꂽ�Ƃ��E�C���h�E���č�悷��B�_�u���N���b�N����
    wcex1.lpfnWndProc =  (WNDPROC)WndProc; //�E�B���h�E�v���V�[�W���̃A�h���X���w�肷��B
    wcex1.cbClsExtra = 0;
    wcex1.cbWndExtra = 0;
    wcex1.hInstance = hInstance;
    wcex1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIOLETVREATH));
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    wcex1.lpszMenuName = nullptr;//MAKEINTRESOURCE(IDC_VIOLETVREATH);//nullptr; //MAKEINTRESOURCE(IDC_MTSTG17_031);//���j���[�o�[�͂Ȃ�
    wcex1.lpszClassName = szWindowClass;
    wcex1.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    MSG msg;
#ifdef MY_DEBUG
    try {
#endif
        //�Ǘ��҂̒a��
        VioletVreath::Caretaker crtkr;
        crtkr.createWindow(wcex1, wcex2, szTitle, "secondary", dwStyle, dwStyle, hWnd1, hWnd2);
        // ���[�v�E�U�E���[�v
        while (true) {
            if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    _TRACE_("�����܂� WM_QUIT!!!");
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
                        //::detectMemoryLeaksEnd(std::cout);
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
                    if (VioletVreath::Caretaker::g_should_reboot_) {
                        //�ċN��
                        Sleep(2000);
                        PROCESS_INFORMATION pi;
                        STARTUPINFO si;
                        ZeroMemory(&si, sizeof(si));
                        si.cb = sizeof(si);
                        BOOL r = CreateProcess(
                                    NULL,         //LPCTSTR lpApplicationName,                 // ���s�\���W���[���̖��O
                                    command_line, //LPTSTR lpCommandLine,                      // �R�}���h���C���̕�����
                                    NULL,         //LPSECURITY_ATTRIBUTES lpProcessAttributes, // �Z�L�����e�B�L�q�q
                                    NULL,         //LPSECURITY_ATTRIBUTES lpThreadAttributes,  // �Z�L�����e�B�L�q�q
                                    FALSE,        //BOOL bInheritHandles,                      // �n���h���̌p���I�v�V����
                                    0,            //DWORD dwCreationFlags,                     // �쐬�̃t���O
                                    NULL,         //LPVOID lpEnvironment,                      // �V�������u���b�N
                                    current_dir,  //LPCTSTR lpCurrentDirectory,                // �J�����g�f�B���N�g���̖��O
                                    &si,          //LPSTARTUPINFO lpStartupInfo,               // �X�^�[�g�A�b�v���
                                    &pi           //LPPROCESS_INFORMATION lpProcessInformation // �v���Z�X���
                        );
                        if (r == 0) {
                            MessageBox(nullptr, "Cannot Reboot! \n ���݂܂���A�蓮�ōċN�����Ă��������B","orz", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
                        }
                    }
                    return EXIT_SUCCESS;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                crtkr.present(); //be() �ŁA���̐�������
            }
        }
#ifdef MY_DEBUG
    } catch (GgafCore::Exception& e) {
        //�ُ�I����
        _TRACE_("����O��"<<e.getMsg());
        std::string message = "\n�E"+e.getMsg()+"  \n\n�G���[�ɂ��S�����肪�����ꍇ�A�{�A�v���̃o�O�̉\���������ł��B\n���ɐ\���󂲂����܂���B\n";
        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(nullptr, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        if (VVB_PLAY) {
            VVB_PLAY->_pRpy->outputFile("VVB_PLAY_LAST_ggaf_Exception.rep");
        }
        if (VVB_UI) {
            VVB_UI->_pRpy->outputFile("VVB_UI_LAST_ggaf_Exception.rep");
        }
        _TRACE_("[GgafCore::CriticalException]:"<<e.getMsg());
        return EXIT_FAILURE;
    } catch (std::exception& e2) {
        std::string what(e2.what());
        _TRACE_("���v���I�ȗ�O��"<<what);
        std::string message = "\n�E"+what+"  \n\n�������܂����A��҂ɂ͗\���ł��Ȃ������v���I�G���[�ł��B\n���ɐ\���󂲂����܂���B\n";
        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
        MessageBox(nullptr, message_dialog.c_str(),"���L�̒v���I�ȗ�O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        _TRACE_("[exception]:"<<what);
        VVB_PLAY->_pRpy->outputFile("VVB_PLAY_LAST_exception.rep");
        VVB_UI->_pRpy->outputFile("VVB_UI_LAST_exception.rep");
        return EXIT_FAILURE;
    }
#endif
//#ifndef MY_DEBUG
//    //�ȉ��̃L���b�`��DEBUG���ł����Ă��A�������ᔽ���Ԃ��\�������邽�߁ADEBUG���͖����Ƃ���B
//    catch( ... ) {
//        _TRACE_("���v���I�ȓ��O��");
//        std::string message = "�������܂����A�s���ȓ����G���[���������܂����B\n���ɐ\���󂲂����܂���B\n";
//        std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
//        MessageBox(nullptr, message_dialog.c_str(),"���L�̒v���I�ȓ��O���������Ă��܂��܂���", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
//        VVB_PLAY->_pRpy->outputFile("VVB_PLAY_LAST_UNKNOWN_ERROR.rep");
//        VVB_UI->_pRpy->outputFile("VVB_UI_LAST_UNKNOWN_ERROR.rep");
//        return EXIT_FAILURE;
//    }
//#endif
    return (int) msg.wParam;
}
/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return CALL_WinMain();
}

void myUnexpectedHandler() {
    //MessageBox(nullptr, "UnexpectedHandler was called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    _TRACE_("ERROR. UnexpectedHandler was called.");
    VVB_PLAY->_pRpy->outputFile("VVB_PLAY_LAST_Unexpected.rep");
    VVB_UI->_pRpy->outputFile("VVB_UI_LAST_Unexpected.rep");
    std::unexpected();
}

void myTerminateHandler() {
    //MessageBox(nullptr, "TerminateHandler was called.","ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
    _TRACE_("ERROR. TerminateHandler was called.");
    VVB_PLAY->_pRpy->outputFile("VVB_PLAY_LAST_Terminate.rep");
    VVB_UI->_pRpy->outputFile("VVB_UI_LAST_Terminate.rep");
    std::terminate();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam);
    VioletVreath::Caretaker* pCaretaker = pCARETAKER;
    switch (message) {
        case WM_CREATE: {
            // �V�X�e�����j���[�J�X�^���֐����Ă�
            CustmizeSysMenu(hWnd);
            break;
        }
        case WM_SYSKEYDOWN: {
            //�V�X�e���̃��j���[�t�H�[�J�X�L�[�𖳌��ɂ���B
            //������s���Ă����Ȃ��ƁAF10�������Ă��܂����ۂɁA
            //�t�H�[�J�X�������Ȃ����j���[�ֈڂ��Ă��܂��A
            //�L�[��}�E�X���͂��󂯕t���Ȃ��Ȃ��Ă��܂��B
            //�Q�[���ł͒v���I�B
            if (LOWORD(wParam) == VK_F10) {
                return TRUE;
            }
            if (LOWORD(wParam) == VK_MENU) {
                return TRUE;
            }
            break;
        }
        /*
        case WM_LBUTTONDBLCLK: {
            //�[���t���X�N���[���̐؂�ւ�
            LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
            if (lStyle & WS_POPUP) {
                //���݃{�[�_���X�t���X�N���[���E�B���h�E�ł���̂Ŗ߂��B
                pCaretaker->backToNomalWindow(hWnd);
            } else {
                //���ݒʏ�E�B���h�E�ł���̂ŁA�{�[�_���X�t���X�N���[���E�B���h�E�ɐ؂�ւ���B
                pCaretaker->chengeToBorderlessFullWindow(hWnd);
            }
            break;
        }
        */
        case WM_KEYDOWN: {
            if (wParam == VK_F11) {
                //�[���t���X�N���[���̐؂�ւ�
                LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
                if (lStyle & WS_POPUP) {
                    //���݃{�[�_���X�t���X�N���[���E�B���h�E�ł���̂Ŗ߂��B
                    pCaretaker->backToNomalWindow(hWnd);
                } else {
                    //���ݒʏ�E�B���h�E�ł���̂ŁA�{�[�_���X�t���X�N���[���E�B���h�E�ɐ؂�ւ���B
                    pCaretaker->chengeToBorderlessFullWindow(hWnd);
                }
            }
            break;
        }
        case WM_SYSCOMMAND: {
            pCaretaker->syncTimeFrame();
            if ( (wParam & 0xFFF0) == SC_SCREENSAVE ) {
                return 1;
            }
            if(wParam == MY_IDM_ABOUT) {
                //�o�[�W�����_�C�A���O
//                dhwnd  = CreateDialog(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
                DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            } else if(wParam == MY_IDM_CHANGE_TO_BORDERLESS_WINDOW) {
                LONG lStyle  = GetWindowLong( hWnd, GWL_STYLE );
                if (lStyle & WS_POPUP) {
                    //���݃{�[�_���X�t���X�N���[���E�B���h�E�ł���̂Ŗ߂��B
                    pCaretaker->backToNomalWindow(hWnd);
                } else {
                    //���ݒʏ�E�B���h�E�ł���̂ŁA�{�[�_���X�t���X�N���[���E�B���h�E�ɐ؂�ւ���B
                    pCaretaker->chengeToBorderlessFullWindow(hWnd);
                }
            } else if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //�����E�B���h�E�T�C�Y�Ƀ��Z�b�g
                pCaretaker->resetInitWindowsize();
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE) {
                //pixel by dot �E�B���h�E�T�C�Y�Ƀ��Z�b�g
                pCaretaker->resetDotByDotWindowsize(1);
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE) {
                //pixel by 2*2dot �E�B���h�E�T�C�Y�Ƀ��Z�b�g
                pCaretaker->resetDotByDotWindowsize(2);
            } else if(wParam == MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE) {
                //pixel by 3*3dot �E�B���h�E�T�C�Y�Ƀ��Z�b�g
                pCaretaker->resetDotByDotWindowsize(3);
            } else if(wParam == MY_IDM_SAVE) {
                if (!CONFIG::FULL_SCREEN) {
                    if (CONFIG::DUAL_VIEW) {
                        RECT cRect1, cRect2;
                        GetClientRect(hWnd1, &cRect1);
                        GetClientRect(hWnd2, &cRect2);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        pixcoord cw2 = cRect2.right - cRect2.left;
                        pixcoord ch2 = cRect2.bottom - cRect2.top;
                        CONFIG::PRIMARY_VIEW_WINDOW_WIDTH  = cw1;
                        CONFIG::PRIMARY_VIEW_WINDOW_HEIGHT = ch1;
                        CONFIG::SECONDARY_VIEW_WINDOW_WIDTH  = cw2;
                        CONFIG::SECONDARY_VIEW_WINDOW_HEIGHT = ch2;
                        CONFIG::_properties.setValue("PRIMARY_VIEW_WINDOW_WIDTH" , CONFIG::PRIMARY_VIEW_WINDOW_WIDTH);
                        CONFIG::_properties.setValue("PRIMARY_VIEW_WINDOW_HEIGHT", CONFIG::PRIMARY_VIEW_WINDOW_HEIGHT);
                        CONFIG::_properties.setValue("SECONDARY_VIEW_WINDOW_WIDTH" , CONFIG::SECONDARY_VIEW_WINDOW_WIDTH);
                        CONFIG::_properties.setValue("SECONDARY_VIEW_WINDOW_HEIGHT", CONFIG::SECONDARY_VIEW_WINDOW_HEIGHT);

                        CONFIG::_properties.setValue("PRIMARY_VIEW_PRESENT_POSITION", CONFIG::PRIMARY_VIEW_PRESENT_POSITION);
                        CONFIG::_properties.setValue("SECONDARY_VIEW_PRESENT_POSITION", CONFIG::SECONDARY_VIEW_PRESENT_POSITION);

                    } else {
                        RECT cRect1;
                        GetClientRect(hWnd1, &cRect1);
                        pixcoord cw1 = cRect1.right - cRect1.left;
                        pixcoord ch1 = cRect1.bottom - cRect1.top;
                        CONFIG::PRIMARY_VIEW_WINDOW_WIDTH  = cw1;
                        CONFIG::PRIMARY_VIEW_WINDOW_HEIGHT = ch1;
                        CONFIG::_properties.setValue("PRIMARY_VIEW_WINDOW_WIDTH" , CONFIG::PRIMARY_VIEW_WINDOW_WIDTH);
                        CONFIG::_properties.setValue("PRIMARY_VIEW_WINDOW_HEIGHT", CONFIG::PRIMARY_VIEW_WINDOW_HEIGHT);

                        CONFIG::_properties.setValue("PRIMARY_VIEW_PRESENT_POSITION", CONFIG::PRIMARY_VIEW_PRESENT_POSITION);
                    }
                    CONFIG::_properties.setValue("FIXED_VIEW_ASPECT", CONFIG::FIXED_VIEW_ASPECT);

                    CONFIG::_properties.write(CONFIG::_load_properties_filename); //�v���p�e�B�ۑ�
                    CONFIG::loadProperties(CONFIG::_load_properties_filename); //�v���p�e�B�Ĕ��f
                }
            } else if(wParam == MY_IDM_REBOOT) {
                //�ċN�����s
                int ret = MessageBox(nullptr, "Quit and Reboot. Are You Sure ?", "VioletVreath_launcher", MB_OKCANCEL|MB_SETFOREGROUND);
                if (ret == IDOK) {
                    VioletVreath::Caretaker::g_should_reboot_ = true;
                    PostQuitMessage(0);
                }
            } else if(wParam == MY_IDM_VPOS_1) {
                pCaretaker->chengeViewPos(hWnd, 1);
            } else if(wParam == MY_IDM_VPOS_2) {
                pCaretaker->chengeViewPos(hWnd, 2);
            } else if(wParam == MY_IDM_VPOS_3) {
                pCaretaker->chengeViewPos(hWnd, 3);
            } else if(wParam == MY_IDM_VPOS_4) {
                pCaretaker->chengeViewPos(hWnd, 4);
            } else if(wParam == MY_IDM_VPOS_5) {
                pCaretaker->chengeViewPos(hWnd, 5);
            } else if(wParam == MY_IDM_VPOS_6) {
                pCaretaker->chengeViewPos(hWnd, 6);
            } else if(wParam == MY_IDM_VPOS_7) {
                pCaretaker->chengeViewPos(hWnd, 7);
            } else if(wParam == MY_IDM_VPOS_8) {
                pCaretaker->chengeViewPos(hWnd, 8);
            } else if(wParam == MY_IDM_VPOS_9) {
                pCaretaker->chengeViewPos(hWnd, 9);
            } else if(wParam == MY_IDM_ASPECT_FIXED) {
                pCaretaker->chengeViewAspect(true);
            } else if(wParam == MY_IDM_ASPECT_STRETCH) {
                pCaretaker->chengeViewAspect(false);
            }
            break;
        }
        default: {
            break;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}


// �V�X�e�����j���[���J�X�^�}�C�Y���܂��B
BOOL CustmizeSysMenu(HWND hWnd)
{
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

    HMENU reset_window_size = CreateMenu();
    InsertMenu(reset_window_size, 0, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_WINDOW_SIZE, "size of default.");
    InsertMenu(reset_window_size, 1, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_DOT_WINDOW_SIZE,  "size of pixel = 1*1dot.");
    InsertMenu(reset_window_size, 2, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_2DOT_WINDOW_SIZE, "size of pixel = 2*2dot.");
    InsertMenu(reset_window_size, 3, MF_STRING | MF_BYPOSITION, MY_IDM_RESET_PIXEL_BY_3DOT_WINDOW_SIZE, "size of pixel = 3*3dot.");

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    int i;
    i=5; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_CHANGE_TO_BORDERLESS_WINDOW ,"Change to borderless windowed.(Double Click)");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)reset_window_size, "Reset window size. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_aspect, "Game view aspect. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)menu_vp    , "Game view position. >>");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_SAVE ,"Save window size and view.");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_REBOOT ,"Reboot...");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING, MY_IDM_ABOUT, "About");

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


