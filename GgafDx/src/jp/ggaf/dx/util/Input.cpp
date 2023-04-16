#include "jp/ggaf/dx/util/Input.h"

#include "jp/ggaf/dx/Caretaker.h"

#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

//const int Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 Input::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_apJoystickInputDevice[MAX_JOY_STICK_NUM];
LPDIRECTINPUTDEVICE8 Input::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 Input::_di_mouse_state[2];
int  Input::_flip_ms = 0;

BYTE Input::_keyboard_state[2][256];
int Input::_flip_ks = 0;
DIDEVCAPS Input::_devcap;
DIJOYSTATE Input::_joy_state[MAX_JOY_STICK_NUM][2];
int Input::_max_acquire_joy_stick_num = 0;
int Input::_flip_js = 0;

Input::MouseState Input::_win_mouse_state[2];

int Input::count_joy_stick_device_no = 0;

HRESULT Input::init() {
    if (Input::_pIDirectInput8) {
        //�����ς�
    } else {
        HRESULT hr;
        // DirectInput �̍쐬
        hr = DirectInput8Create(
                 pCARETAKER->_hInstance,
                 DIRECTINPUT_VERSION,
                 IID_IDirectInput8,
                 (LPVOID*)&Input::_pIDirectInput8,
                 nullptr
             );
        if (hr != D3D_OK) {
            MessageBox(pCARETAKER->_pHWndPrimary, "�����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }

        hr = Input::initKeybord();
        if (hr == D3D_OK) {
            hr = Input::initMouse();
            hr = Input::initJoyStick();
        } else {
            MessageBox(pCARETAKER->_pHWndPrimary, "�L�[�{�[�h�f�o�C�X�̏������Ɏ��s���܂����B",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }
    }
    return D3D_OK;
}

HRESULT Input::initMouse() {
    if (!Input::_pIDirectInput8) {
        Input::init();
    }
    if (Input::_pMouseInputDevice) {
        //�擾�ς�
        Input::_pMouseInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pMouseInputDevice);
        return FALSE;
    }
    HRESULT hr;
    // �}�E�X�f�o�C�X�̍쐬
    hr = Input::_pIDirectInput8->CreateDevice(
                                           GUID_SysMouse,
                                           &Input::_pMouseInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�}�E�X�f�o�C�X�쐬�Ɏ��s���܂���",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = Input::_pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�}�E�X��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�������x���ݒ�
    hr = Input::_pMouseInputDevice->SetCooperativeLevel(
                                              pCARETAKER->_pHWndPrimary,
                                              DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                          );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�}�E�X��SetCooperativeLevel�Ɏ��s���܂���",
                 "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �}�E�X�����[�h��ݒ�
    DIPROPDWORD dipropword_m;
    dipropword_m.diph.dwSize = sizeof(dipropword_m);
    dipropword_m.diph.dwHeaderSize = sizeof(dipropword_m.diph);
    dipropword_m.diph.dwObj = 0;
    dipropword_m.diph.dwHow = DIPH_DEVICE;
    dipropword_m.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
    hr = Input::_pMouseInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_("�y�x���z�����[�h�̐ݒ�Ɏ��s");
        return FALSE;
    }

    // �}�E�X�A�N�Z�X���擾
    if (Input::_pMouseInputDevice) {
        Input::_pMouseInputDevice->Acquire();
    }
    _TRACE_("�}�E�X�f�o�C�X�擾OK");
    return D3D_OK;
}


HRESULT Input::initKeybord() {
    if (!Input::_pIDirectInput8) {
        Input::init();
    }
    if (Input::_pKeyboardInputDevice) {
        //�擾�ς�
        Input::_pKeyboardInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pKeyboardInputDevice);
    }
    HRESULT hr;
    // �L�[�{�[�h�f�o�C�X�̍쐬
    hr = Input::_pIDirectInput8->CreateDevice(
                                           GUID_SysKeyboard,
                                           &Input::_pKeyboardInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�L�[�{�[�h�f�o�C�X�쐬�Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = Input::_pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�L�[�{�[�h��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�������x���ݒ�
    hr = Input::_pKeyboardInputDevice->SetCooperativeLevel(
                                                 pCARETAKER->_pHWndPrimary,
                                                 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                             );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "�L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    /*
     //�}�E�X�o�b�t�@�T�C�Y�̎w��
     DIPROPDWORD dipropdword;
     dipropdword.diph.dwSize			= sizeof(DIPROPDWORD);
     dipropdword.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
     dipropdword.diph.dwObj			= 0;
     dipropdword.diph.dwHow			= DIPH_DEVICE;
     dipropdword.dwData				= Input::BUFFER_SIZE;

     hr = Input::_pKeyboardInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(pCARETAKER->_pHWndPrimary,"�L�[�{�[�h��SetProperty�Ɏ��s���܂���", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
     return hr;
     }
     */
    // �L�[�{�[�h�A�N�Z�X���擾
    if (Input::_pKeyboardInputDevice) {
        Input::_pKeyboardInputDevice->Acquire();
    }
    _TRACE_("�L�[�{�[�h�f�o�C�X�擾OK");
    return D3D_OK;
}
HRESULT Input::initJoyStick() {
    if (!Input::_pIDirectInput8) {
        Input::init();
    }

    if (Input::_apJoystickInputDevice[P1_JOY_STICK]) {
        //�擾�ς�
        Input::_apJoystickInputDevice[P1_JOY_STICK]->Unacquire();
        GGAF_RELEASE(Input::_apJoystickInputDevice[P1_JOY_STICK]);
    }
    if (Input::_apJoystickInputDevice[P2_JOY_STICK]) {
        //�擾�ς�
        Input::_apJoystickInputDevice[P2_JOY_STICK]->Unacquire();
        GGAF_RELEASE(Input::_apJoystickInputDevice[P2_JOY_STICK]);
    }
    Input::_apJoystickInputDevice[P1_JOY_STICK] = nullptr;
    Input::_apJoystickInputDevice[P2_JOY_STICK] = nullptr;
    Input::count_joy_stick_device_no = 0;
    Input::_max_acquire_joy_stick_num = 0;

    HRESULT hr;
    // �Q�[���X�e�B�b�N��񋓂��ăf�o�C�X�𓾂�
    hr = Input::_pIDirectInput8->EnumDevices(
                                           DI8DEVCLASS_GAMECTRL,
                                           Input::enumGameCtrlCallback,
                                           nullptr,
                                           DIEDFL_ATTACHEDONLY
                                       );
    for (int n = 0; n < MAX_JOY_STICK_NUM; n++) {
        if (hr != D3D_OK || Input::_apJoystickInputDevice[n] == nullptr) {
            _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N��������܂���ł����B");
            Input::_apJoystickInputDevice[n] = nullptr;
            continue;
        } else {
            _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N�͌�����܂���");
            // �Q�[���X�e�B�b�N�̃f�[�^�`����ݒ肷��
            hr = Input::_apJoystickInputDevice[n]->SetDataFormat(&c_dfDIJoystick);
            if (hr != D3D_OK) {
                _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N SetDataFormat�Ɏ��s���܂���");
                GGAF_RELEASE(Input::_apJoystickInputDevice[n]);
                Input::_apJoystickInputDevice[n] = nullptr;
                continue;
            }
            // �Q�[���X�e�B�b�N�������x����ݒ肷��
            hr = Input::_apJoystickInputDevice[n]->SetCooperativeLevel(
                                                         pCARETAKER->_pHWndPrimary,
                                                         DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
                                                     );
            if (hr != D3D_OK) {
                _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N SetCooperativeLevel�Ɏ��s���܂���");
                GGAF_RELEASE(Input::_apJoystickInputDevice[n]);
                Input::_apJoystickInputDevice[n] = nullptr;
                continue;
            }

            // �Q�[���X�e�B�b�N�̎��f�[�^�͈̔͂�ݒ肷��
            hr = Input::_apJoystickInputDevice[n]->EnumObjects(
                                                         Input::enumPadAxisCallback,
                                                         Input::_apJoystickInputDevice[n],
                                                         DIDFT_AXIS
                                                     );
            if (hr == D3D_OK) {
                // �����[�h��ݒ�
                DIPROPDWORD dipropword_j;
                dipropword_j.diph.dwSize = sizeof(dipropword_j);
                dipropword_j.diph.dwHeaderSize = sizeof(dipropword_j.diph);
                dipropword_j.diph.dwObj = 0;
                dipropword_j.diph.dwHow = DIPH_DEVICE;
                dipropword_j.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
                //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
                hr = Input::_apJoystickInputDevice[n]->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
                if (hr != D3D_OK) {
                    _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N �����[�h�̐ݒ�Ɏ��s SetProperty(DIPROP_AXISMODE)");
                }
            } else {
                _TRACE_("P"<<n+1<<" �W���C�X�e�B�b�N DIDFT_AXIS EnumObjects�Ɏ��s���܂���");
            }

            // �Q�[���X�e�B�b�N�̃A�N�Z�X�����擾����
            hr = Input::_apJoystickInputDevice[n]->Poll();
            if (hr != D3D_OK) {
                do {
                    hr = Input::_apJoystickInputDevice[n]->Acquire();
                } while (hr == DIERR_INPUTLOST);
            }
            Input::_max_acquire_joy_stick_num ++;
        }
    }
    return D3D_OK;
}

BOOL CALLBACK Input::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    HRESULT hr;
    // �Q�[���X�e�B�b�N�f�o�C�X��T��
    LPDIRECTINPUTDEVICE8 pJoystickInputDevice;
    hr = Input::_pIDirectInput8->CreateDevice(
                                           pDIDeviceInstance->guidInstance,
                                           &pJoystickInputDevice,
                                           nullptr
                                       );
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
        // �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
        return DIENUM_CONTINUE;
    }

    // �W���C�X�e�B�b�N�̔\�͂��擾
    Input::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = pJoystickInputDevice->GetCapabilities( &Input::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback �\�͎擾�ł��Ȃ��B�W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
        // �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
        pJoystickInputDevice->Release();
        return DIENUM_CONTINUE;
    }

    //�����c��΃f�o�C�X�̗p
    _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�N�̃f�o�C�X�ԍ�["<<count_joy_stick_device_no<<"] "<< pDIDeviceInstance->tszInstanceName<<"/"<<pDIDeviceInstance->tszProductName<<" �𔭌�");
    if (Input::count_joy_stick_device_no == Config::P1_JOY_STICK_DEVICE_NO) {
        Input::_apJoystickInputDevice[P1_JOY_STICK] = pJoystickInputDevice;
        _TRACE_("enumGameCtrlCallback �f�o�C�X�ԍ�["<<count_joy_stick_device_no<<"] �� 1P �W���C�X�e�B�b�N�Ƃ��Ďg�p����܂��B���R�AConfig::P1_JOY_STICK_DEVICE_NO="<<Config::P1_JOY_STICK_DEVICE_NO);
    } else if (Input::count_joy_stick_device_no == Config::P2_JOY_STICK_DEVICE_NO) {
        Input::_apJoystickInputDevice[P2_JOY_STICK] = pJoystickInputDevice;
        _TRACE_("enumGameCtrlCallback �f�o�C�X�ԍ�["<<count_joy_stick_device_no<<"] �� 2P �W���C�X�e�B�b�N�Ƃ��Ďg�p����܂��B���R�AConfig::P2_JOY_STICK_DEVICE_NO="<<Config::P2_JOY_STICK_DEVICE_NO);
    } else {
        pJoystickInputDevice->Release();
        _TRACE_("enumGameCtrlCallback �f�o�C�X�ԍ�["<<count_joy_stick_device_no<<"] �͎g�p����܂���B���R�AP1_JOY_STICK_DEVICE_NO="<<Config::P1_JOY_STICK_DEVICE_NO<<"/P2_JOY_STICK_DEVICE_NO="<<Config::P2_JOY_STICK_DEVICE_NO);

    }
    Input::count_joy_stick_device_no++;
    return DIENUM_CONTINUE;
}

BOOL CALLBACK Input::enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    LPDIRECTINPUTDEVICE8 pJoystickInputDevice = (LPDIRECTINPUTDEVICE8)pvRef;
    DIPROPRANGE diproprange;
    ZeroMemory( &diproprange, sizeof(diproprange) );
    diproprange.diph.dwSize = sizeof(diproprange);
    diproprange.diph.dwHeaderSize = sizeof(diproprange.diph);
    diproprange.diph.dwHow = DIPH_BYID;
    diproprange.diph.dwObj = lpddoi->dwType;
    diproprange.lMin = -255;
    diproprange.lMax = +255;
    HRESULT hr = pJoystickInputDevice->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
        _TRACE_("enumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void Input::updateMouseState() {
#ifdef MY_DEBUG
    if (Input::_pMouseInputDevice == nullptr) {
        _TRACE_("�y�x���z Input::updateKeyboardState() Input::_pMouseInputDevice == nullptr !!!!");
        return;
    }
#endif
    Input::_flip_ms ^= 1; //�X�e�[�g�Z�b�g�t���b�v
    HRESULT hr;
again:
    hr = Input::_pMouseInputDevice->Poll(); //�}�E�X�͒ʏ�Poll�s�p�Ǝv�����Ăяo���Ă����Q�Ə����Ă���̂ŌĂԁB
    hr = Input::_pMouseInputDevice->GetDeviceState(
                                              sizeof(DIMOUSESTATE2),
                                              (void*)&Input::_di_mouse_state[Input::_flip_ms]
                                          );
    if (FAILED(hr)) {
        hr = Input::_pMouseInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //�_���Ȃ�܂������
        }
    }
    Input::MouseState& s = Input::_win_mouse_state[Input::_flip_ms];
    s.buttons[0] = GetAsyncKeyState(VK_LBUTTON);
    s.buttons[1] = GetAsyncKeyState(VK_RBUTTON);
    s.buttons[2] = GetAsyncKeyState(VK_MBUTTON);
    return;
}


//bool Input::isPressedMouseButton_old(int prm_button_no) {
//    if (prm_button_no < 0 || 8 < prm_button_no) {
//        _TRACE_("isPressedMouseButton:�͈͊O");
//        return false;
//    } else {
//        if (Input::_di_mouse_state[Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

bool Input::isPressedMouseButton(int prm_button_no) {
#ifdef MY_DEBUG
    if (prm_button_no < 0 || 8 < prm_button_no) {
        throwCriticalException("Input::isPressedMouseButton() �͈͊O�ł� prm_button_no="<<prm_button_no);
    }
#endif
    return Input::_win_mouse_state[Input::_flip_ms].buttons[prm_button_no];
}


//bool Input::isPushedDownMouseButton_old(int prm_button_no) {
//    if (Input::isPressedMouseButton(prm_button_no)) { //���͉����Ă���
//        if (Input::_di_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            //�O��Z�b�g[!Input::_flip_ms]��������Ă���B�������ςȂ�
//            return false;
//        } else {
//            //�O��Z�b�g[!Input::_flip_ms]�͉�����Ă��Ȃ��̂�OK
//            return true;
//        }
//    } else {
//        return false;
//    }
//}

bool Input::isPushedDownMouseButton(int prm_button_no) {
    if (Input::isPressedMouseButton(prm_button_no)) { //���͉����Ă���
        if (Input::_win_mouse_state[!Input::_flip_ms].buttons[prm_button_no]) {
            //�O��Z�b�g[!Input::_flip_ms]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!Input::_flip_ms]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}


//
//bool Input::isReleasedUpMouseButton_old(int prm_button_no) {
//    if (!Input::isPressedMouseButton(prm_button_no)) { //���͗����Ă���
//        if (Input::_di_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            //�O��Z�b�g[!Input::_flip_ms]��������Ă����B�����B
//            return true;
//        } else {
//            //�O��Z�b�g[!Input::_flip_ms]�͉�����Ă��Ȃ��B�������ςȂ��B
//            return false;
//        }
//    } else {
//        return false;
//    }
//}

bool Input::isReleasedUpMouseButton(int prm_button_no) {
    if (!Input::isPressedMouseButton(prm_button_no)) { //���͗����Ă���
        if (Input::_win_mouse_state[!Input::_flip_ms].buttons[prm_button_no]) {
            //�O��Z�b�g[!Input::_flip_ms]��������Ă����B�����B
            return true;
        } else {
            //�O��Z�b�g[!Input::_flip_ms]�͉�����Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}


void Input::getMousePointer(long* x, long* y, long* z) {
    //�}�E�X�̈ړ�
    *x = Input::_di_mouse_state[Input::_flip_ms].lX;
    *y = Input::_di_mouse_state[Input::_flip_ms].lY;
    //�z�C�[���̏��
    *z = Input::_di_mouse_state[Input::_flip_ms].lZ;
}

void Input::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //�}�E�X�̈ړ�
    *dx = Input::_di_mouse_state[Input::_flip_ms].lX - Input::_di_mouse_state[!Input::_flip_ms].lX;
    *dy = Input::_di_mouse_state[Input::_flip_ms].lY - Input::_di_mouse_state[!Input::_flip_ms].lY;
    //�z�C�[���̏��
    *dz = Input::_di_mouse_state[Input::_flip_ms].lZ - Input::_di_mouse_state[!Input::_flip_ms].lZ;
}

void Input::updateKeyboardState() {
#ifdef MY_DEBUG
    if (Input::_pKeyboardInputDevice == nullptr) {
        throwCriticalException("Input::_pKeyboardInputDevice==nullptr");
    }
#endif
    Input::_flip_ks ^= 1;
    HRESULT hr;
again:
    hr = Input::_pKeyboardInputDevice->Poll(); //�L�[�{�[�h�͒ʏ�Poll�s�p�Ǝv�����A�K�v�ȃL�[�{�[�h�����邩������Ȃ��B
    hr = Input::_pKeyboardInputDevice->GetDeviceState(
                                                 256,
                                                 (void*)&Input::_keyboard_state[Input::_flip_ks]
                                             );
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()�����݂�B
        hr = Input::_pKeyboardInputDevice->Acquire();
        if (hr == DI_OK) {
            //_TRACE_("Acquire is DI_OK");
            goto again;
        } else {
            //_TRACE_("Acquire is not DI_OK");
            //�_���Ȃ�܂������
        }
    }
    return;
}

bool Input::isPushedDownKey(int prm_DIK) {
    if (Input::isPressedKey(prm_DIK)) { //���͉����Ă���
        if (Input::_keyboard_state[!Input::_flip_ks][prm_DIK] & 0x80) {
            //�O��Z�b�g[!Input::_flip_ks]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!Input::_flip_ks]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}
int Input::getFirstPushedDownKey() {
    int DIK_pressed = Input::getFirstPressedKey();
    if (DIK_pressed >= 0 ) { //���͉����Ă���
        if (Input::_keyboard_state[!Input::_flip_ks][DIK_pressed] & 0x80) {
            //�O��Z�b�g[!Input::_flip_ks]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!Input::_flip_ks]�͉�����Ă��Ȃ��̂�OK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool Input::isReleasedUpKey(int prm_DIK) {
    if (!Input::isPressedKey(prm_DIK)) { //���͗����Ă���
        if (Input::_keyboard_state[!Input::_flip_ks][prm_DIK] & 0x80) {
            //�O��Z�b�g[!Input::_flip_ks]�͉�����Ă����B����
            return true;
        } else {
            //�O��Z�b�g[!Input::_flip_ks]��������Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}
void Input::updateAllJoystickState() {
    Input::_flip_js ^= 1;
    for (int joy_stick_no = 0; joy_stick_no < MAX_JOY_STICK_NUM; joy_stick_no++) {
        GgafDx::Input::updateJoystickState(joy_stick_no);
    }
}
void Input::updateJoystickState(int prm_joystic_no) {

    if (Input::_apJoystickInputDevice[prm_joystic_no] == nullptr) {
        //Input::_joy_state[prm_joystic_no][Input::_flip_js] = {0};
        return;
    }
    if (prm_joystic_no+1 > Input::_max_acquire_joy_stick_num) {
        //Input::_joy_state[prm_joystic_no][Input::_flip_js] = {0};
        return;
    }

    HRESULT hr;

again1:
    hr = Input::_apJoystickInputDevice[prm_joystic_no]->Poll();
    if (hr != DI_OK) {
        hr = Input::_apJoystickInputDevice[prm_joystic_no]->Acquire();
        if (hr == DI_OK) {
            //�P�񂾂��撣��
            goto again1;
        }
    }

again2:
    hr = Input::_apJoystickInputDevice[prm_joystic_no]->GetDeviceState(
                                                 sizeof(DIJOYSTATE),
                                                 &Input::_joy_state[prm_joystic_no][Input::_flip_js]
                                             );
    if (hr != DI_OK) {
        hr = Input::_apJoystickInputDevice[prm_joystic_no]->Acquire();
        if (hr == DI_OK) {
            //�P�񂾂��撣��
            goto again2;
        }
    }
    //DEBUG
//    DIJOYSTATE& sta_dbg =  Input::_joy_state[prm_joystic_no][Input::_flip_js];
//    _TRACE_("Input::_joy_state prm_joystic_no="<<prm_joystic_no<<"/Input::_flip_js="<<Input::_flip_js);
//    _TRACE_("sta_dbg="<<sta_dbg.lX<<","<<sta_dbg.lY<<","<<sta_dbg.lZ<<"/"<<sta_dbg.lRx<<","<<sta_dbg.lRy<<","<<sta_dbg.lRz);
//    _TRACE_("sta_dbg.rglSlider="<<sta_dbg.rglSlider<<",[0]="<<sta_dbg.rglSlider[0]<<",[1]="<<sta_dbg.rglSlider[1]);
//    _TRACE_("sta_dbg.rgdwPOV="<<sta_dbg.rgdwPOV<<",[0]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[0])<<",[1]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[1])<<",[2]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[2])<<",[3]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[3]));
//    _TRACE_("sta_dbg.rgbButtons="<<sta_dbg.rgbButtons<<
//            ",[0]=" << (int)(sta_dbg.rgbButtons[0]  & 0x80) <<
//            ",[1]=" << (int)(sta_dbg.rgbButtons[1]  & 0x80) <<
//            ",[2]=" << (int)(sta_dbg.rgbButtons[2]  & 0x80) <<
//            ",[3]=" << (int)(sta_dbg.rgbButtons[3]  & 0x80) <<
//            ",[4]=" << (int)(sta_dbg.rgbButtons[4]  & 0x80) <<
//            ",[5]=" << (int)(sta_dbg.rgbButtons[5]  & 0x80) <<
//            ",[6]=" << (int)(sta_dbg.rgbButtons[6]  & 0x80) <<
//            ",[7]=" << (int)(sta_dbg.rgbButtons[7]  & 0x80) <<
//            ",[8]=" << (int)(sta_dbg.rgbButtons[8]  & 0x80) <<
//            ",[9]=" << (int)(sta_dbg.rgbButtons[9]  & 0x80) <<
//            ",[10]="<< (int)(sta_dbg.rgbButtons[10] & 0x80) <<
//            ",[11]="<< (int)(sta_dbg.rgbButtons[11] & 0x80) <<
//            ",[12]="<< (int)(sta_dbg.rgbButtons[12] & 0x80) <<
//            ",[13]="<< (int)(sta_dbg.rgbButtons[13] & 0x80) <<
//            ",[14]="<< (int)(sta_dbg.rgbButtons[14] & 0x80) <<
//            ",[15]="<< (int)(sta_dbg.rgbButtons[15] & 0x80) <<
//            ",[16]="<< (int)(sta_dbg.rgbButtons[16] & 0x80) <<
//            ",[17]="<< (int)(sta_dbg.rgbButtons[17] & 0x80) <<
//            ",[18]="<< (int)(sta_dbg.rgbButtons[18] & 0x80) <<
//            ",[19]="<< (int)(sta_dbg.rgbButtons[19] & 0x80) <<
//            ",[20]="<< (int)(sta_dbg.rgbButtons[20] & 0x80) <<
//            ",[21]="<< (int)(sta_dbg.rgbButtons[21] & 0x80) <<
//            ",[22]="<< (int)(sta_dbg.rgbButtons[22] & 0x80) <<
//            ",[23]="<< (int)(sta_dbg.rgbButtons[23] & 0x80) <<
//            ",[24]="<< (int)(sta_dbg.rgbButtons[24] & 0x80) <<
//            ",[25]="<< (int)(sta_dbg.rgbButtons[25] & 0x80) <<
//            ",[26]="<< (int)(sta_dbg.rgbButtons[26] & 0x80) <<
//            ",[27]="<< (int)(sta_dbg.rgbButtons[27] & 0x80) <<
//            ",[28]="<< (int)(sta_dbg.rgbButtons[28] & 0x80) <<
//            ",[29]="<< (int)(sta_dbg.rgbButtons[29] & 0x80) <<
//            ",[30]="<< (int)(sta_dbg.rgbButtons[30] & 0x80) <<
//            ",[31]="<< (int)(sta_dbg.rgbButtons[31] & 0x80)  );
}

bool Input::isPushedDownJoyRgbButton(int prm_joystic_no, int prm_joy_button_no) {
    if (Input::isPressedJoyButton(prm_joystic_no, prm_joy_button_no)) { //���͉����Ă���
        if (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) {
            //�O��Z�b�g[!Input::_flip_js]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!Input::_flip_js]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}

int Input::getFirstPushedDownJoyRgbButton(int prm_joystic_no) {
    int JOY_pressed = Input::getFirstPressedJoyRgbButton(prm_joystic_no);
    if (JOY_pressed >= 0 ) { //���͉����Ă���
        if (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[JOY_pressed] & 0x80) {
            //�O��Z�b�g[!Input::_flip_js]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!Input::_flip_js]�͉�����Ă��Ȃ��̂�OK
            return JOY_pressed;
        }
    } else {
        return -1;
    }
}


int Input::getPressedJoyDirection(int prm_joystic_no) {
    DIJOYSTATE& sta = Input::_joy_state[prm_joystic_no][Input::_flip_js];
    if (sta.lY < -127) {
        if (sta.lX > 127) {
            return 9;
        } else if (sta.lX < -127) {
            return 7;
        } else {
            return 8;
        }
    } else if (sta.lY > 127) {
        if (sta.lX > 127) {
            return 3;
        } else if (sta.lX < -127) {
            return 1;
        } else {
            return 2;
        }
    } else if (sta.lX > 127) {
        return 6;
    } else if (sta.lX < -127) {
        return 4;
    } else {
        return 5;
    }
}

int Input::getPressedPovDirection(int prm_joystic_no) {
    if (Input::_apJoystickInputDevice[prm_joystic_no]) { //JoyStick�������ꍇ�ArgdwPOV[0]=0�̂��߁A��Ɣ��肳��邱�Ƃ�h��
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        if (LOWORD(n) != 0xFFFF) {
            if (n == 0 ) {
                return 8; //UP
            } else if (n == 4500) {
                return 9; //RIGHT+UP
            } else if (n == 9000) {
                return 6; //RIGHT
            } else if (n == 13500) {
                return 3; //RIGHT+DOWN
            } else if (n == 18000) {
                return 2; //DOWN
            } else if (n == 22500) {
                return 1; //LEFT+DOWN
            } else if (n == 27000) {
                return 4; //LEFT
            } else if (n == 31500) {
                return 7; //LEFT+UP
            } else {
                _TRACE_("�y�x���z���肦�Ȃ� getPressedPovDirection n="<<n);
                return 5;
            }
        } else {
            return 5;
        }
    } else {
        return 5;
    }
}


void Input::release() {
    //�f�o�C�X���
    if (Input::_pIDirectInput8) {
        if (Input::_pKeyboardInputDevice) {
            Input::_pKeyboardInputDevice->Unacquire();
            GGAF_RELEASE(Input::_pKeyboardInputDevice);
        }
        if (Input::_apJoystickInputDevice[P1_JOY_STICK]) {
            Input::_apJoystickInputDevice[P1_JOY_STICK]->Unacquire();
            GGAF_RELEASE(Input::_apJoystickInputDevice[P1_JOY_STICK]);
        }
        if (Input::_apJoystickInputDevice[P2_JOY_STICK]) {
            Input::_apJoystickInputDevice[P2_JOY_STICK]->Unacquire();
            GGAF_RELEASE(Input::_apJoystickInputDevice[P2_JOY_STICK]);
        }
        if (Input::_pMouseInputDevice) {
            Input::_pMouseInputDevice->Unacquire();
            GGAF_RELEASE(Input::_pMouseInputDevice);
        }
        GGAF_RELEASE(Input::_pIDirectInput8);
    }
}
