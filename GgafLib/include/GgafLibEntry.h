#ifndef GGAFLIBENTRY_H_
#define GGAFLIBENTRY_H_
#include "GgafDxCommonHeader.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //������胊���N�G���[��� for GCC
    //VC �ł͕s�v�B����ŗǂ����낤���E�E�E
//    uintptr_t __security_cookie;
//    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif

#ifdef  __cplusplus
};
#endif


HWND _hWnd1_ = nullptr;
HWND _hWnd2_ = nullptr;
HINSTANCE WinMain_hInstance;
HINSTANCE WinMain_hPrevInstance;
LPTSTR WinMain_lpCmdLine;
int WinMain_nCmdShow;

/**
 * �E�B���h�E�̃T�C�Y���Đݒ� .
 * @param hWnd �Đݒ肷��E�B���h�E��HWND
 * @param client_width �N���C�A���g�̈扡���i�s�N�Z���j
 * @param client_height �N���C�A���g�̈�c���i�s�N�Z���j
 */
void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height) {
    RECT wRect1, cRect1; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
    pixcoord ww1, wh1; // �E�B���h�E�S�̂̕��A����
    pixcoord cw1, ch1; // �N���C�A���g�̈�̕��A����
    pixcoord fw1, fh1; // �t���[���̕��A����
    // �E�B���h�E�S�̂̕��E�������v�Z
    GetWindowRect(hWnd, &wRect1);
    ww1 = wRect1.right - wRect1.left;
    wh1 = wRect1.bottom - wRect1.top;
    // �N���C�A���g�̈�̕��E�������v�Z
    GetClientRect(hWnd, &cRect1);
    cw1 = cRect1.right - cRect1.left;
    ch1 = cRect1.bottom - cRect1.top;
    // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
    fw1 = ww1 - cw1;
    fh1 = wh1 - ch1;
    // �v�Z�������ƍ������E�B���h�E�ɐݒ�
    SetWindowPos(
            hWnd,
            HWND_TOP,
            0,
            0,
            client_width + fw1,
            client_height + fh1,
            SWP_NOMOVE
    );
}


/**
 * �E�B���h�E�̃T�C�Y�����̑傫���Ƀ��Z�b�g .
 * @param hWnd ���Z�b�g����E�B���h�E��HWND
 */
void resetWindowsize(HWND hWnd) {
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            if (hWnd == _hWnd2_) {
                resetWindowsize(hWnd, GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else if (hWnd == _hWnd1_) {
                resetWindowsize(hWnd, GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
            }
        } else {
            resetWindowsize(hWnd, GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
        }
    }
}

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
    while (*lpCmdLine != ' ' && *lpCmdLine != '\0') { lpCmdLine++; }
    while (*lpCmdLine == ' ') { lpCmdLine++; }

    //�{����WinMain��
    return WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
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
        case WM_SIZE:
            if (GgafDxCore::GgafDxGod::_can_be) {
                if (!GGAF_PROPERTY(FULL_SCREEN)) {
                    GgafDxCore::GgafDxGod::_adjustGameScreen = true;
                    GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = hWnd;
                }
            }
            break;
        case WM_SETFOCUS:
            HRESULT hr;
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Mouse) {
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    _TRACE_("GgafDxInput::initDx9Input() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���");
                }
            }
                // �L�[�{�[�h�������x���ݒ�
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Keyboard) {
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
                if (hr != D3D_OK) {
                    MessageBox(hWnd, TEXT("GgafDxInput::initDx9Input() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���"),
                               TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                }
            }
            if (GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Joystick) {
                // �Q�[���X�e�B�b�N�������x����ݒ肷��
                hr = GgafDxCore::GgafDxInput::_pIDirectInputDevice8_Joystick->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
                if (hr != D3D_OK) {
                    _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
                }
            }

            break;
        case WM_SYSCOMMAND:
            if(wParam == SC_CLOSE){
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

/**
 * �E�B���h�E��������
 * @param prm_wndclass1 �P��ʖڂ�WNDCLASSEX�p�����[�^
 * @param prm_wndclass2 �Q��ʖڂ�WNDCLASSEX�p�����[�^
 * @param prm_title1 �P��ʖڂ̃^�C�g��
 * @param prm_title2 �Q��ʖڂ̃^�C�g��
 * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
 * @param out_hWnd2 �i�߂�l�j�Q��ʖڂ̃E�B���h�E�n���h��
 */
void GgafLibCreateWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                         const char* prm_title1   , const char* prm_title2,
                         HWND&       out_hWnd1    , HWND&       out_hWnd2) {

    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    prm_wndclass1.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));
    prm_wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._R, rgb._G, rgb._B));

    // �E�C���h�E�̐���
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            //�t���X�N���[�����[�h�E�Q��ʎg�p
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

            RegisterClassEx(&prm_wndclass2);
            _hWnd2_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                      );

        } else {
            //�t���X�N���[�����[�h�E�P��ʎg�p
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH),
                        GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

        }
    } else {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            //�E�C���h���[�h�E�Q���g�p
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );

            RegisterClassEx(&prm_wndclass2);
            _hWnd2_ = CreateWindow(
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH),
                        GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                      );
        } else {
            //�E�C���h���[�h�E�P���g�p
            RegisterClassEx(&prm_wndclass1);
            _hWnd1_ = CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH),
                        GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT),
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                      );
        }
    }

    out_hWnd1 = _hWnd1_;
    out_hWnd2 = _hWnd2_;

    if (!_hWnd1_) {
        std::cout << "can't CreateWindow " << std::endl;
    }

    //�E�B���h�E���[�h���A�N���C�A���g�̈�����]�̑傫���ɂ��邽�߁A
    //�^�C�g���o�[�A���T�C�Y�{�[�_�[�̌������l�����Đݒ�B
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            resetWindowsize(_hWnd1_, GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
            resetWindowsize(_hWnd2_, GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
        } else {
            resetWindowsize(_hWnd1_, GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
        }
    }

    //�A�N�e�B�u��
    ShowWindow(_hWnd1_, WinMain_nCmdShow);
    UpdateWindow(_hWnd1_);
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        ShowWindow(_hWnd2_, WinMain_nCmdShow);
        UpdateWindow(_hWnd2_);
    }
}





//
//#include <windows.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//
//

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





























#endif /*GGAFLIBENTRY_H_*/

