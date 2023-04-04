#include "jp/ggaf/GgafLib.h"
#include <windows.h>

#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/util/WMKeyInput.h"

HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

HINSTANCE get_WinMain_hInstance() {
    WinMain_hInstance = GetModuleHandle(0);
    return WinMain_hInstance;
}

HINSTANCE get_WinMain_hPrevInstance() {
    WinMain_hPrevInstance = 0;
    return WinMain_hPrevInstance;
}

LPTSTR get_WinMain_lpCmdLine() {
    WinMain_lpCmdLine = GetCommandLine();
    //PG������
    while (*WinMain_lpCmdLine != ' ' && *WinMain_lpCmdLine != '\0') { ++WinMain_lpCmdLine; }
    while (*WinMain_lpCmdLine == ' ') { ++WinMain_lpCmdLine; }
    return WinMain_lpCmdLine;
}

int get_WinMain_nCmdShow() {
    STARTUPINFO StatUpInfo;
    GetStartupInfo(&StatUpInfo);
    WinMain_nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW) ? StatUpInfo.wShowWindow : SW_SHOWNORMAL;
    return WinMain_nCmdShow;
}

/**
 * �t���[�����[�N�̃E�B���h�E�v���V�[�W������ .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void LibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CHAR: {
            GgafLib::WMKeyInput::catchWmChar(wParam);
            break;
        }
        case WM_SIZE: {
            if (pCARETAKER && pCARETAKER->_pHWndPrimary) {
                if (!CONFIG::FULL_SCREEN) {
                    pCARETAKER->_adjustGameWindow = true;
                }
            }
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_SIZING: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_MOVING: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_CONTEXTMENU: {
            GgafCore::Caretaker::_pCaretaker->syncTimeFrame();
            break;
        }
        case WM_SETFOCUS: {
            if (pCARETAKER->_pHWndPrimary) {
                HRESULT hr;
                // �}�E�X�������x���ݒ�
                if (GgafDx::Input::_pMouseInputDevice) {
                    hr = GgafDx::Input::_pMouseInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        _TRACE_("LibWndProc() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���");
                    }
                }
                    // �L�[�{�[�h�������x���ݒ�
                if (GgafDx::Input::_pKeyboardInputDevice) {
                    hr = GgafDx::Input::_pKeyboardInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        MessageBox(hWnd, "LibWndProc() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���",
                                   "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                    }
                }
                if (GgafDx::Input::_apJoystickInputDevice[P1_JOY_STICK]) {
                    // �Q�[���X�e�B�b�N�������x����ݒ肷��
                    hr = GgafDx::Input::_apJoystickInputDevice[P1_JOY_STICK]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
                    if (hr != D3D_OK) {
                        _TRACE_("LibWndProc() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
                        // �Q�[���X�e�B�b�N�f�o�C�X�̏����������݂�
                        GgafDx::Input::initJoyStick();
                    }
                } else {
                    // �Q�[���X�e�B�b�N�f�o�C�X�̏����������݂�
                    GgafDx::Input::initJoyStick();
                }
            }
            break;
        }

        case WM_SYSCOMMAND: {
            if(wParam == SC_CLOSE) {
                PostQuitMessage(0);
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            break;
    }
}

//#define MOUSEEVENTF_FROMTOUCH 0xFF515700
//
//switch(uMsg){
//case WM_LBUTTONDOWN:
//    {
//        auto extra = GetMessageExtraInfo();
//        if((extra & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH){
//            if(extra & 0x80){
//                // ���͂̓^�b�`
//            }else{
//                // ���͂̓y��
//            }
//        }else{
//            // ���͂̓}�E�X
//        }
//        break;
//    }
//}


//int main(void) {
//    PIP_ADAPTER_INFO pAdapterInfo;
//    DWORD aiSize;
//    BYTE* paBuff;
//
//    GetAdaptersInfo(nullptr, &aiSize);//�K�v�o�b�t�@�T�C�Y�擾
//    paBuff = new BYTE[aiSize];
//    pAdapterInfo = (PIP_ADAPTER_INFO) paBuff;
//
//    if (GetAdaptersInfo(pAdapterInfo, &aiSize) != ERROR_SUCCESS) {
//        printf("GetAdapterInfo�Ăяo�����s\n");
//        return 1;
//    }
//    std::stringstream ss;
//
//
//    while (pAdapterInfo) {
//        //fprintf(stdout, "MAC�A�h���X = [");
//
//        for (UINT i = 0; i < pAdapterInfo->AddressLength; i++) {
//            ss.width(2);
//            ss.fill('0');
//            ss << std::hex << (int)pAdapterInfo->Address[i];
//            //fprintf(stdout, "%.2X", (int)pAdapterInfo->Address[i]);
//
//            if (i == (pAdapterInfo->AddressLength - 1)) {
//                //fputs("]\n", stdout);
//            } else {
//                ss.width(1);
//                ss << "-";
//                //fputs("-", stdout);
//            }
//        }
//        pAdapterInfo = pAdapterInfo->Next;
//    }
//    delete[] paBuff;
//    printf("%s", ss.str().c_str());
//    return 0;
//}

