#include "GgafLibEntry.h"

#include "VvvGod.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
using namespace VVViewer;

#define MY_IDM_RESET_WINDOW_SIZE  10
HWND hWnd1, hWnd2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CustmizeSysMenu(HWND hWnd);
/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv);
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    //�v���p�e�B�t�@�C���Ǎ���
    GgafLib::GgafLibProperties::load(".\\config.properties");

    //�E�B���h�E��`���쐬
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)WndProc;
    wcex1.hInstance = hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "primary";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;



    //�_�̒a��
    VvvGod god = VvvGod();
    //�Q�[�����[�v
    MSG msg;
    try {
        god.createWindow(wcex1, wcex2,
                         "VVViewer[1]", "VVViewer[2]", //�^�C�g��������
                         dwStyle, dwStyle,
                         hWnd1, hWnd2);
        DragAcceptFiles(hWnd1, TRUE);
        //���[�v�{��
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return EXIT_SUCCESS; //�A�v���I��
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                god.be();
            }
        }
    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "VVViewer Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        _TRACE_("[�G���[]:"<<what); //_TRACE_() �̓f�o�b�O���[�h���̂ݕW���o�͂ɏo�͂���܂��B
        return EXIT_FAILURE; //�ُ�I��
    }
    return (int)msg.wParam;
}

/**
 * �E�B���h�E�v���V�[�W�������� .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //����ɁA���̗l�ɌĂяo���ĉ������B
    //�K�v������΁A���b�Z�[�W�������R�R�ɒǉ��L�q
    switch (message) {

        case WM_CREATE: {
            // �V�X�e�����j���[�J�X�^���֐����Ă�
            CustmizeSysMenu(hWnd);
            break;
        }
        case WM_DROPFILES: {/* �t�@�C�����h���b�v���ꂽ���̏��� */
            HDROP hDrop = (HDROP)wParam;
            UINT uFileNo = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, nullptr, 0);
            for (int i = 0; i < (int)uFileNo; i++) {
                DragQueryFile(hDrop, i, VvvGod::dropfiles_, sizeof(VvvGod::dropfiles_));
                _TRACE_("VvvGod::dropfiles_="<<VvvGod::dropfiles_);
            }
            DragFinish(hDrop);
            VvvGod::is_wm_dropfiles_ = true;
            break;
        }
        case WM_SYSCOMMAND: {
            if(wParam == MY_IDM_RESET_WINDOW_SIZE) {
                //�����E�B���h�E�T�C�Y�Ƀ��Z�b�g
                if (!PROPERTY::FULL_SCREEN) {
                    if (PROPERTY::DUAL_VIEW) {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::DUAL_VIEW_WINDOW1_WIDTH, PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT);
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd2, PROPERTY::DUAL_VIEW_WINDOW2_WIDTH, PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT);
                    } else {
                        GgafDxCore::GgafDxGod::resetWindowsize(hWnd1, PROPERTY::SINGLE_VIEW_WINDOW_WIDTH, PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT);
                    }
                }
            }
            break;
        }
        case WM_SYSKEYDOWN: {
            if (LOWORD(wParam) == VK_F10) {
                return TRUE;
            }
            if (LOWORD(wParam) == VK_MENU) {
                return TRUE;
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

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    int i;
    i=5; InsertMenu(hMenu, i, MF_BYPOSITION | MF_SEPARATOR, (UINT_PTR)0, "");
    i++; InsertMenu(hMenu, i, MF_BYPOSITION | MF_STRING , MY_IDM_RESET_WINDOW_SIZE, "Reset window size.(&R)");

    //�V�X�e�����j���[���쐬
    DrawMenuBar(hWnd);

    return TRUE;
}

