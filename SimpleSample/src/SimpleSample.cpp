/**
 * �uGecchi Game App Framework ���C�u�����v�g�p�T���v��
 */
#include "GgafLibEntry.h" //"GgafLibEntry.h" ���C���N���[�h���A
                          //main�֐� WinMain�֐� �E�B���h�E�v���V�[�W����
                          //�P�̃t�@�C���ɋL�q���܂��B
#include "SimpleSample.h"
#include "SmpGod.h"

using namespace SimpleSample;

/**
 * �E�B���h�E�v���V�[�W�������� .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //����ɁA���̗l�ɌĂяo���ĉ������B
    //�K�v������΁A���b�Z�[�W�������R�R�ɒǉ��L�q
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //����ɁA���̗l�ɌĂяo���ĉ������B
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //����ɁA���̗l�ɌĂяo���ĉ������B

    //�v���p�e�B�t�@�C���Ǎ���
    GgafLib::GgafLibProperties::load(".\\config.properties");
    //�_�̒a��
    SmpGod* pGod = new SmpGod();
    //���C������
    MSG msg;
    HWND hWnd1, hWnd2; //HWND�͂Q�p�ӂ��܂��B
    try {
        //�E�B���h�E�쐬
        pGod->createWindow(WndProc,
                           "SimpleSample[1]", "SimpleSample[2]",
                           hWnd1, hWnd2); //HWND���������܂�(�߂�l)
        //���[�v�{��
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //�I�����b�Z�[�W�̏ꍇ�A�v�����I��
                    if (SmpGod::_can_be) {
                        SmpGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        GGAF_DELETE(pGod);
                        GgafLib::GgafLibProperties::clean(); //�v���p�e�B���
                    }
                    return EXIT_SUCCESS; //�A�v���I��
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //���̂悤�ɂЂ�����_�� be() ���\�b�h���R�[�����Ă��������B
                if (SmpGod::_can_be) {
                    pGod->be();
                }
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "SimpleSample Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[�G���[]:"<<what); //_TRACE_() �̓f�o�b�O���[�h���̂ݕW���o�͂ɏo�͂���܂��B
        return EXIT_FAILURE; //�ُ�I��
    }
    return (int)msg.wParam;
}

