#ifndef GGAFLIB_H_
#define GGAFLIB_H_
#include "GgafLibCommonHeader.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/GgafLibConfig.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/WMKeyInput.h"

HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

/**
 * ���C������ .
 * @param argc
 * @param argv
 * @return
 */
int GgafLibMain(int argc, char *argv[]) {
    STARTUPINFO StatUpInfo;
    HINSTANCE hInstance;
    HANDLE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;

    GetStartupInfo(&StatUpInfo);
    hInstance = GetModuleHandle(0);
    hPrevInstance = 0;
    lpCmdLine = GetCommandLine();
    nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW) ? StatUpInfo.wShowWindow : SW_SHOWNORMAL;

    //PG������
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0') { ++lpCmdLine; }
    while (*lpCmdLine == ' ') { ++lpCmdLine; }

    //�{����WinMain��
    return ::WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

/**
 * WinMain�̏������� .
 * @param hInstance
 * @param hPrevInstance
 * @param lpCmdLine
 * @param nCmdShow
 */
void GgafLibWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    WinMain_hInstance = hInstance;
    WinMain_hPrevInstance = hPrevInstance;
    WinMain_lpCmdLine = lpCmdLine;
    WinMain_nCmdShow = nCmdShow;
}

/**
 * Ggaf�t���[�����[�N�̃E�B���h�E�v���V�[�W������ .
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 */
void GgafLibWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CHAR:
            GgafLib::WMKeyInput::catchWmChar(wParam);
            break;
        case WM_SIZE:
            if (pGOD && GgafDxCore::GgafDxGod::_pHWndPrimary) {
                if (!CONFIG::FULL_SCREEN) {
                    _TRACE_("GgafLibWndProc WM_SIZE");
                    GgafDxCore::GgafDxGod::_adjustGameWindow = true;
                    GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = hWnd;
                }
            }
            break;
        case WM_SETFOCUS:
            if (GgafDxCore::GgafDxGod::_pHWndPrimary) {
                HRESULT hr;
                // �}�E�X�������x���ݒ�
                if (GgafDxCore::GgafDxInput::_pMouseInputDevice) {
                    hr = GgafDxCore::GgafDxInput::_pMouseInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        _TRACE_("GgafLibWndProc() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���");
                    }
                }
                    // �L�[�{�[�h�������x���ݒ�
                if (GgafDxCore::GgafDxInput::_pKeyboardInputDevice) {
                    hr = GgafDxCore::GgafDxInput::_pKeyboardInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                    if (hr != D3D_OK) {
                        MessageBox(hWnd, "GgafLibWndProc() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���",
                                   "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                    }
                }
                if (GgafDxCore::GgafDxInput::_pJoystickInputDevice) {
                    // �Q�[���X�e�B�b�N�������x����ݒ肷��
                    hr = GgafDxCore::GgafDxInput::_pJoystickInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
                    if (hr != D3D_OK) {
                        _TRACE_("GgafLibWndProc() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
                        // �Q�[���X�e�B�b�N�f�o�C�X�̏����������݂�
                        GgafDxCore::GgafDxInput::initJoyStick();
                    }
                } else {
                    // �Q�[���X�e�B�b�N�f�o�C�X�̏����������݂�
                    GgafDxCore::GgafDxInput::initJoyStick();
                }
            }
            break;
        case WM_SYSCOMMAND:
            if(wParam == SC_CLOSE) {
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
}




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


#endif /*GGAFLIB_H_*/

