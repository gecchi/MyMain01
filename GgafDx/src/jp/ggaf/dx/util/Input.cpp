#include "jp/ggaf/dx/util/Input.h"

#include "jp/ggaf/dx/God.h"

#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

//const int Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 Input::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pJoystickInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 Input::_mouse_state[2];
int  Input::_flip_ms = 0;

BYTE Input::_keyboard_state[2][256];
int Input::_flip_ks = 0;
DIDEVCAPS Input::_devcap;
DIJOYSTATE Input::_joy_state[2];
int Input::_flip_js = 0;


HRESULT Input::init() {
    if (Input::_pIDirectInput8) {
        //�����ς�
    } else {
        HRESULT hr;
        // DirectInput �̍쐬
        hr = DirectInput8Create(
                 God::_hInstance,
                 DIRECTINPUT_VERSION,
                 IID_IDirectInput8,
                 (LPVOID*)&Input::_pIDirectInput8,
                 nullptr
             );
        if (hr != D3D_OK) {
            MessageBox(God::_pHWndPrimary, "�����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }

        hr = Input::initKeybord();
        if (hr == D3D_OK) {
            hr = Input::initMouse();
            hr = Input::initJoyStick();
        } else {
            MessageBox(God::_pHWndPrimary, "�L�[�{�[�h�f�o�C�X�̏������Ɏ��s���܂����B",
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
        MessageBox(God::_pHWndPrimary, "�}�E�X�f�o�C�X�쐬�Ɏ��s���܂���",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = Input::_pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(God::_pHWndPrimary, "�}�E�X��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�������x���ݒ�
    hr = Input::_pMouseInputDevice->SetCooperativeLevel(
                                              God::_pHWndPrimary,
                                              DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                          );
    if (hr != D3D_OK) {
        MessageBox(God::_pHWndPrimary, "�}�E�X��SetCooperativeLevel�Ɏ��s���܂���",
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
        _TRACE_("���x���������[�h�̐ݒ�Ɏ��s");
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
        MessageBox(God::_pHWndPrimary, "�L�[�{�[�h�f�o�C�X�쐬�Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = Input::_pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(God::_pHWndPrimary, "�L�[�{�[�h��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�������x���ݒ�
    hr = Input::_pKeyboardInputDevice->SetCooperativeLevel(
                                                 God::_pHWndPrimary,
                                                 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                             );
    if (hr != D3D_OK) {
        MessageBox(God::_pHWndPrimary, "�L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���",
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
     MessageBox(God::_pHWndPrimary,"�L�[�{�[�h��SetProperty�Ɏ��s���܂���", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
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
    if (Input::_pJoystickInputDevice) {
        //�擾�ς�
        Input::_pJoystickInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pJoystickInputDevice);
    }
    HRESULT hr;
    // �Q�[���X�e�B�b�N��񋓂��ăf�o�C�X�𓾂�
    hr = Input::_pIDirectInput8->EnumDevices(
                                           DI8DEVCLASS_GAMECTRL,
                                           Input::enumGameCtrlCallback,
                                           nullptr,
                                           DIEDFL_ATTACHEDONLY
                                       );
    if (hr != D3D_OK || Input::_pJoystickInputDevice == nullptr) {
        _TRACE_("�W���C�X�e�B�b�N��������܂���");
        Input::_pJoystickInputDevice = nullptr;
        return FALSE;
    } else {
        _TRACE_("�W���C�X�e�B�b�N�f�o�C�X�擾");

        // �Q�[���X�e�B�b�N�̃f�[�^�`����ݒ肷��
        hr = Input::_pJoystickInputDevice->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("�W���C�X�e�B�b�NSetDataFormat�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�������x����ݒ肷��
        hr = Input::_pJoystickInputDevice->SetCooperativeLevel(
                                                     God::_pHWndPrimary,
                                                     DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
                                                 );
        if (hr != D3D_OK) {
            _TRACE_("�W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̎��f�[�^�͈̔͂�ݒ肷��
        hr = Input::_pJoystickInputDevice->EnumObjects(
                                                     Input::enumPadAxisCallback,
                                                     nullptr,
                                                     DIDFT_AXIS
                                                 );
        if (hr != D3D_OK) {
            _TRACE_("�W���C�X�e�B�b�NEnumObjects�Ɏ��s���܂���");
            return FALSE;
        }

        // �����[�h��ݒ�
        DIPROPDWORD dipropword_j;
        dipropword_j.diph.dwSize = sizeof(dipropword_j);
        dipropword_j.diph.dwHeaderSize = sizeof(dipropword_j.diph);
        dipropword_j.diph.dwObj = 0;
        dipropword_j.diph.dwHow = DIPH_DEVICE;
        dipropword_j.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
        //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
        hr = Input::_pJoystickInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̃A�N�Z�X�����擾����
        hr = Input::_pJoystickInputDevice->Poll();
        if (hr != D3D_OK) {
            do {
                hr = Input::_pJoystickInputDevice->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return D3D_OK;
}

BOOL CALLBACK Input::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("call back");
    HRESULT hr;
    // �Q�[���X�e�B�b�N�f�o�C�X��T��
    hr = Input::_pIDirectInput8->CreateDevice(
                                           pDIDeviceInstance->guidInstance,
                                           &Input::_pJoystickInputDevice,
                                           nullptr
                                       );
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
        // �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
        return DIENUM_CONTINUE;
    }

    // �W���C�X�e�B�b�N�̔\�͂��擾
    Input::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = Input::_pJoystickInputDevice->GetCapabilities( &Input::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
        // �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
        Input::_pJoystickInputDevice->Release();
        return DIENUM_CONTINUE;
    }

    //�����c��΃f�o�C�X�̗p
    return DIENUM_STOP;
}

BOOL CALLBACK Input::enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    _TRACE_("call back");
    DIPROPRANGE diproprange;
    ZeroMemory( &diproprange, sizeof(diproprange) );
    diproprange.diph.dwSize = sizeof(diproprange);
    diproprange.diph.dwHeaderSize = sizeof(diproprange.diph);
    diproprange.diph.dwHow = DIPH_BYID;
    diproprange.diph.dwObj = lpddoi->dwType;
    diproprange.lMin = -255;
    diproprange.lMax = +255;

    HRESULT hr = Input::_pJoystickInputDevice->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
        _TRACE_("enumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void Input::updateMouseState() {
#ifdef MY_DEBUG
    if (Input::_pMouseInputDevice == nullptr) {
        _TRACE_("���x���� Input::updateKeyboardState() Input::_pMouseInputDevice == nullptr !!!!");
        return;
    }
#endif
    Input::_flip_ms ^= 1; //�X�e�[�g�Z�b�g�t���b�v
    HRESULT hr;
again:
    hr = Input::_pMouseInputDevice->Poll(); //�}�E�X�͒ʏ�Poll�s�p�Ǝv�����Ăяo���Ă����Q�Ə����Ă���̂ŌĂԁB
    hr = Input::_pMouseInputDevice->GetDeviceState(
                                              sizeof(DIMOUSESTATE2),
                                              (void*)&Input::_mouse_state[Input::_flip_ms]
                                          );
    if (FAILED(hr)) {
        hr = Input::_pMouseInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //�_���Ȃ�܂������
        }
    }
    return;
}


bool Input::isPressedMouseButton(int prm_button_no) {
    if (prm_button_no < 0 || 8 < prm_button_no) {
        _TRACE_("isPressedMouseButton:�͈͊O");
        return false;
    } else {
        if (Input::_mouse_state[Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool Input::isPushedDownMouseButton(int prm_button_no) {
    if (Input::isPressedMouseButton(prm_button_no)) { //���͉����Ă���
        if (Input::_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
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

bool Input::isReleasedUpMouseButton(int prm_button_no) {
    if (!Input::isPressedMouseButton(prm_button_no)) { //���͗����Ă���
        if (Input::_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
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
    *x = Input::_mouse_state[Input::_flip_ms].lX;
    *y = Input::_mouse_state[Input::_flip_ms].lY;
    //�z�C�[���̏��
    *z = Input::_mouse_state[Input::_flip_ms].lZ;
}

void Input::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //�}�E�X�̈ړ�
    *dx = Input::_mouse_state[Input::_flip_ms].lX - Input::_mouse_state[!Input::_flip_ms].lX;
    *dy = Input::_mouse_state[Input::_flip_ms].lY - Input::_mouse_state[!Input::_flip_ms].lY;
    //�z�C�[���̏��
    *dz = Input::_mouse_state[Input::_flip_ms].lZ - Input::_mouse_state[!Input::_flip_ms].lZ;
}

void Input::updateKeyboardState() {
#ifdef MY_DEBUG
    if (Input::_pKeyboardInputDevice == nullptr) {
        _TRACE_("Input::_pKeyboardInputDevice==nullptr !!!!");
        return;
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
int Input::getPushedDownKey() {
    int DIK_pressed = Input::getPressedKey();
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

void Input::updateJoystickState() {
    if (Input::_pJoystickInputDevice == nullptr) {
        return;
    }
    Input::_flip_js ^= 1;
    // �W���C�X�e�B�b�N�̏�Ԃ��擾
    HRESULT hr;

again1:
    hr = Input::_pJoystickInputDevice->Poll();
    if (hr != DI_OK) {
        hr = Input::_pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again1;
        } else {
        }
    }

again2:
    hr = Input::_pJoystickInputDevice->GetDeviceState(
                                                 sizeof(DIJOYSTATE),
                                                 &Input::_joy_state[Input::_flip_js]
                                             );
    if (hr != DI_OK) {
        hr = Input::_pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again2;
        } else {
        }
    }

//    _TRACE_("lX="<<Input::_joy_state[Input::_flip_js].lX);
//    _TRACE_("lY="<<Input::_joy_state[Input::_flip_js].lY);
//    _TRACE_("lZ="<<Input::_joy_state[Input::_flip_js].lZ);
//    _TRACE_("lRx="<<Input::_joy_state[Input::_flip_js].lRx);
//    _TRACE_("lRy="<<Input::_joy_state[Input::_flip_js].lRy);
//    _TRACE_("lRz="<<Input::_joy_state[Input::_flip_js].lRz);
}

bool Input::isPushedDownJoyRgbButton(int prm_joy_button_no) {
    if (Input::isPressedJoyButton(prm_joy_button_no)) { //���͉����Ă���
        if (Input::_joy_state[!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) {
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

int Input::getPushedDownJoyRgbButton() {
    int JOY_pressed = Input::getPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //���͉����Ă���
        if (Input::_joy_state[!Input::_flip_js].rgbButtons[JOY_pressed] & 0x80) {
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


int Input::getPressedJoyDirection() {
    if (Input::_joy_state[Input::_flip_js].lY < -127) {
        if (Input::_joy_state[Input::_flip_js].lX > 127) {
            return 9;
        } else if (Input::_joy_state[Input::_flip_js].lX < -127) {
            return 7;
        } else {
            return 8;
        }
    } else if (Input::_joy_state[Input::_flip_js].lY > 127) {
        if (Input::_joy_state[Input::_flip_js].lX > 127) {
            return 3;
        } else if (Input::_joy_state[Input::_flip_js].lX < -127) {
            return 1;
        } else {
            return 2;
        }
    } else if (Input::_joy_state[Input::_flip_js].lX > 127) {
        return 6;
    } else if (Input::_joy_state[Input::_flip_js].lX < -127) {
        return 4;
    } else {
        return 5;
    }
}


int Input::getPressedPovDirection() {
    if (Input::_pJoystickInputDevice) { //JoyStick�������ꍇ�ArgdwPOV[0]=0�̂��߁A��Ɣ��肳��邱�Ƃ�h��
        DWORD n = Input::_joy_state[Input::_flip_js].rgdwPOV[0];
        if (LOWORD(n) != 0xFFFF) {
            if (n < 20750) {
                if (n < 11750) {
                    if (n < 2750) {
                        return 8;         //UP
                    } else if (n < 7250) {
                        return 9;         //UP+RIGHT
                    } else { //n >= 7250
                        return 6;         //RIGHT
                    }
                } else { //n >= 11750
                    if (n < 15250) {
                        return 3;         //DOWN+RIGHT
                    } else { //n >= 15250
                        return 2;         //DOWN
                    }
                }
            } else { //n >= 20750
                if (n < 29750) {
                    if (n < 24250) {
                        return 1;         //DOWN+LEFT
                    } else { //n >= 24250
                        return 4;         //LEFT
                    }
                } else { //n >= 29750
                    if (n < 33250) {
                        return 7;         //UP+LEFT
                    } else { //n >= 33250
                        return 8;         //UP
                    }
                }
            }
        } else {
            return 5;                     //NEUTRAL
        }
    } else {
        //�W���C�X�e�B�b�N���h�����ĂȂ�
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
        if (Input::_pJoystickInputDevice) {
            Input::_pJoystickInputDevice->Unacquire();
            GGAF_RELEASE(Input::_pJoystickInputDevice);
        }
        if (Input::_pMouseInputDevice) {
            Input::_pMouseInputDevice->Unacquire();
            GGAF_RELEASE(Input::_pMouseInputDevice);
        }
        GGAF_RELEASE(Input::_pIDirectInput8);
    }
}
