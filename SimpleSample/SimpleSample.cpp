/**
 * �uGecchi Game App Freamework ���C�u�����v�g�p�T���v��
 */
#include "stdafx.h"
#include "GgafLibEntory.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    GgafLibMain(argc, argv); //����ɁA���̗l�ɌĂяo���ĉ������B
    return 0;
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //����ɁA���̗l�ɌĂяo���ĉ������B

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
    GgafLibCreateWindow(wcex1, wcex2, "SimpleSample[1]", "SimpleSample[2]", hWnd1, hWnd2);

    MSG msg;
    try {
        //�_�̒a��
        SimpleSample::God* pGod = NEW SimpleSample::God(hInstance, hWnd1, hWnd2);
        pGod->init();
        //�Q�[�����[�v
        timeBeginPeriod(1);
        while (true) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //�I�����b�Z�[�W�̏ꍇ���̗l�Ɏ������A
                    //�A�v�����I�������܂��B
                    if (SimpleSample::God::_can_be) {
                        SimpleSample::God::_can_be = false;
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
                //�ʏ펞�́A���̂悤�ɂЂ����� be() ���\�b�h���R�[�����Ă��������B
                if (SimpleSample::God::_can_be) {
                    pGod->be();
                }
            }
        }
    } catch (exception& e2) {
        string what(e2.what());
        MessageBox(NULL, what.c_str(), "SimpleSample Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
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
    return DefWindowProc(hWnd, message, wParam, lParam);
}
