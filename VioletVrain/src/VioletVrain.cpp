#include "GgafLib.h"
#include "VioletVrain.h"

#include "jp/gecchi/VioletVrain/VvGod.h"

using namespace VioletVrain;


/**
 * �E�B���h�E�v���V�[�W��
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LibWndProc(hWnd, message, wParam, lParam);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return LibMain(argc, argv); //����ɁA���̗l�ɌĂяo���ĉ������B
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    LibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //����ɁA���̗l�ɌĂяo���ĉ������B

    //�v���p�e�B�t�@�C���Ǎ���
    CONFIG::loadProperties(".\\config.properties");

    VvGod god;
    MSG msg;
    HWND hWnd1;
    try {
        god.createWindow(WndProc, "VioletVrain", hWnd1);
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
        MessageBox(nullptr, what.c_str(), "VioletVrain Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[�G���[]:"<<what);
        return EXIT_FAILURE; //�ُ�I��
    }
    return (int)msg.wParam;
}

