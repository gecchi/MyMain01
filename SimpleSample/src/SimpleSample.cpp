/**
 * �uGecchi Game App Framework ���C�u�����v�g�p�T���v��
 */
#include "SimpleSample.h"
#include "SmpCaretaker.h"
#include "jp/ggaf/GgafLib.h" //�C���N���[�h���Ă��������B

using namespace SimpleSample;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    //�v���p�e�B�t�@�C���Ǎ���
    CONFIG::loadProperties("config.properties");
    //�Ǘ��҂̒a��
    SmpCaretaker crtkr;
    //�E�B���h�E�쐬
    HWND hWnd1;
    crtkr.createWindow(WndProc, "SimpleSampleWindow", hWnd1);
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
            crtkr.present(); //���̂悤�ɊǗ��҂� present() ���\�b�h���Ђ�����R�[�����Ă��������B
        }
    }
    return (int)msg.wParam;
}

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return CALL_WinMain(); //���̃}�N�����L�q���� WinMain() �����s�Ăяo���Ă��������B
}

/**
 * �E�B���h�E�v���V�[�W�������� .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam); //FW �̃v���V�[�W���������s���܂��B
    //�K�v������΁A���b�Z�[�W�������R�R�ɒǉ��L�q
    return DefWindowProc(hWnd, message, wParam, lParam);
}
