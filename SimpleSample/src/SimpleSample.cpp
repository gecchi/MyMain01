/**
 * �uGecchi Game App Framework ���C�u�����v�g�p�T���v��
 */
#include "GgafLib.h" //"GgafLib.h" ���C���N���[�h���Ă��������B

#include "SimpleSample.h"
#include "SmpGod.h"

using namespace SimpleSample;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //����ɁA�����Ăяo���ĉ������B
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //����ɁA���̗l�ɌĂяo���ĉ������B

    //�v���p�e�B�t�@�C���Ǎ���
    CONFIG::loadProperties("config.properties");
    //�_�̒a��
    SmpGod god;
    //�E�B���h�E�쐬
    HWND hWnd1;
    god.createWindow(WndProc, "SimpleSampleWindow", hWnd1);
    //���C�����[�v����
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return EXIT_SUCCESS; //�I�����b�Z�[�W�̏ꍇ�A�A�v���I��
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            god.be(); //���̂悤�ɐ_�� be() ���\�b�h���Ђ�����R�[�����Ă��������B
        }
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


