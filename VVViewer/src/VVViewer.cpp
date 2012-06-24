#include "stdafx.h"
#include "GgafLibEntory.h"
using namespace VVViewer;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv);
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
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
    wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex1.lpszClassName = "primary";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    HWND hWnd1, hWnd2;
    GgafLibCreateWindow(wcex1, wcex2,
                        "VVViewer[1]", "VVViewer[2]", //�^�C�g��������
                        hWnd1, hWnd2); //HWND���������܂�(�߂�l)

    DragAcceptFiles(hWnd1,TRUE);

    //�Q�[�����[�v
    MSG msg;
    try {
        //�_�̒a��
        VvvGod* pGod = new VvvGod(hInstance, hWnd1, hWnd2);
        pGod->init();
        timeBeginPeriod(1);
        //���[�v�{��
        while (true) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //�I�����b�Z�[�W�̏ꍇ�A�v�����I��
                    if (VvvGod::_can_be) {
                        VvvGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        delete pGod;
                        GgafLib::GgafLibProperties::clean(); //�v���p�e�B���
                    }
                    timeEndPeriod(1);
                    return EXIT_SUCCESS; //�A�v���I��
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                if (VvvGod::_can_be) {
                    pGod->be();
                }
            }
        }
    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(NULL, what.c_str(), "VVViewer Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[�G���[]:"<<what); //_TRACE_() �̓f�o�b�O���[�h���̂ݕW���o�͂ɏo�͂���܂��B
        timeEndPeriod(1);
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
        case WM_DROPFILES: {/* �t�@�C�����h���b�v���ꂽ���̏��� */
            HDROP  hDrop = (HDROP)wParam;
            UINT  uFileNo = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, NULL, 0);
            for(int i = 0; i < (int)uFileNo; i++) {
                DragQueryFile(hDrop, i, VvvGod::dropfiles_, sizeof(VvvGod::dropfiles_));
                _TRACE_("VvvGod::dropfiles_="<<VvvGod::dropfiles_);
            }
            DragFinish(hDrop);
            VvvGod::is_wm_dropfiles_ = true;
            break;
        }
        default: {
            break;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
