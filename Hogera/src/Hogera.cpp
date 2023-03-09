/**
 * �uGecchi Game App Framework ���C�u�����v�g�p�T���v��
 */
#include "GgafLib.h" //"GgafLib::Lib.h" ���C���N���[�h���A
#include "Hogera.h"

#include "HgrCaretaker.h"
#include <scrnsave.h>
using namespace Hogera;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    //�v���p�e�B�t�@�C���Ǎ���
    GgafLib::LibConfig::loadProperties(".\\config.properties");

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
    HWND hWnd1, hWnd2;

    HgrCaretaker crtkr;
    //�Q�[�����[�v
    MSG msg;
    try {
        //�Ǘ��҂̒a��
        crtkr.createWindow(wcex1, wcex2,
                         "Hogera[1]", "Hogera[2]", //�^�C�g��������
                         dwStyle, dwStyle,
                         hWnd1, hWnd2); //HWND���������܂�(�߂�l)
        //���[�v�{��
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    return EXIT_SUCCESS; //�A�v���I��
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //���̂悤�ɂЂ�����Ǘ��҂� present() ���\�b�h���R�[�����Ă��������B
                crtkr.present();
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "Hogera Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[�G���[]:"<<what); //_TRACE_() �̓f�o�b�O���[�h���̂ݕW���o�͂ɏo�͂���܂��B
        return EXIT_FAILURE; //�ُ�I��
    }
    return (int)msg.wParam;
}

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    LibMain(argc, argv); //����ɁA���̗l�ɌĂяo���ĉ������B
    return WinMain(WinMain_hInstance, WinMain_hPrevInstance, WinMain_lpCmdLine, WinMain_nCmdShow);
}


/**
 * �E�B���h�E�v���V�[�W��
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //����ɁA���̗l�ɌĂяo���ĉ������B
    static HRGN hRgn1,hRgn2;
    switch (message) {
        case WM_CREATE: {
            SetWindowRgn(hWnd, hRgn1, 1 );
            break;
        }
        case WM_DESTROY: {
            DeleteObject(hRgn1);
            DeleteObject(hRgn2);
            break;
        }
        // �N���C�A���g�̈���N���b�N���ꂽ�ꍇ�AHTCAPTION��Ԃ�
        case WM_NCHITTEST: {
            // �N���C�A���g�̈���}�E�X�Ńh���b�O���ăE�B���h�E���ړ��ł���悤��
            // �L���v�V�����o�[�̐U���������
            RECT rcClient;
            POINT poClient;
            poClient.x = LOWORD ( lParam );
            poClient.y = HIWORD ( lParam );
            GetClientRect ( hWnd, &rcClient );
            ScreenToClient ( hWnd, &poClient );
            if ( PtInRect ( &rcClient, poClient )
                && GetAsyncKeyState ( VK_LBUTTON ) < 0 ) {
                return HTCAPTION;
            }
            break;
        }
        // �t�H�[�����_�u���N���b�N���ꂽ�ꍇ�ő剻���Ȃ�
        case WM_NCLBUTTONDBLCLK: {
            break;
        }
    }
    //�K�v������΁A���b�Z�[�W�������R�R�ɒǉ��L�q
    return DefWindowProc(hWnd, message, wParam, lParam);
}


