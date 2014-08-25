#include "jp/ggaf/dxcore/util/GgafDxInput.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"

using namespace GgafCore;
using namespace GgafDxCore;

//const int GgafDxInput::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDxInput::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pJoystickInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 GgafDxInput::_mouse_state[2];
int  GgafDxInput::_flip_ms = 0;

char GgafDxInput::_keyboard_state[2][256];
int GgafDxInput::_flip_ks = 0;
DIDEVCAPS GgafDxInput::_devcap;
DIJOYSTATE GgafDxInput::_joy_state[2];
int GgafDxInput::_flip_js = 0;


HRESULT GgafDxInput::init() {
    HRESULT hr;
    // DirectInput �̍쐬
    hr = DirectInput8Create(GgafDxGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �}�E�X�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pMouseInputDevice, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �}�E�X�f�o�C�X�쐬�Ɏ��s���܂���",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = _pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �}�E�X��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // �}�E�X�������x���ݒ�
    hr = _pMouseInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �}�E�X��SetCooperativeLevel�Ɏ��s���܂���",
                 "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

//    if (GgafDxGod::_pHWndSecondary) {
//        // �}�E�X�������x���ݒ�
//        hr = _pMouseInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndSecondary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//        if (hr != D3D_OK) {
//            MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���"),
//                       "ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
//            return hr;
//        }
//    }
    // �}�E�X�����[�h��ݒ�
    DIPROPDWORD dipropword_m;
    dipropword_m.diph.dwSize = sizeof(dipropword_m);
    dipropword_m.diph.dwHeaderSize = sizeof(dipropword_m.diph);
    dipropword_m.diph.dwObj = 0;
    dipropword_m.diph.dwHow = DIPH_DEVICE;
    dipropword_m.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
    hr = _pMouseInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
        return FALSE;
    }

    // �}�E�X�A�N�Z�X���擾
    if (_pMouseInputDevice) {
        _pMouseInputDevice->Acquire();
    }

    // �L�[�{�[�h�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pKeyboardInputDevice, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �L�[�{�[�h�f�o�C�X�쐬�Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = _pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �L�[�{�[�h��SetDataFormat �Ɏ��s���܂���",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // �L�[�{�[�h�������x���ݒ�
    hr = _pKeyboardInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���",
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
     dipropdword.dwData				= GgafDxInput::BUFFER_SIZE;

     hr = _pKeyboardInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDxGod::_pHWndPrimary,"GgafDxInput::initDx9Input() �L�[�{�[�h��SetProperty�Ɏ��s���܂���", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
     return hr;
     }
     */
    // �L�[�{�[�h�A�N�Z�X���擾
    if (_pKeyboardInputDevice) {
        _pKeyboardInputDevice->Acquire();
    }


    // �Q�[���X�e�B�b�N��񋓂��ăf�o�C�X�𓾂�
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, GgafDxInput::enumGameCtrlCallback, nullptr, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pJoystickInputDevice == nullptr) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices�񋓂��܂������A�W���C�X�e�B�b�N��������܂���ł���");
        _pJoystickInputDevice = nullptr;
    } else {
        _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�N�f�o�C�X�擾");

        // �Q�[���X�e�B�b�N�̃f�[�^�`����ݒ肷��
        hr = _pJoystickInputDevice->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NSetDataFormat�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�������x����ݒ肷��
        hr = _pJoystickInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_FOREGROUND
                | DISCL_NONEXCLUSIVE );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̎��f�[�^�͈̔͂�ݒ肷��
        hr = _pJoystickInputDevice->EnumObjects(GgafDxInput::enumPadAxisCallback, nullptr, DIDFT_AXIS);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NEnumObjects�Ɏ��s���܂���");
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
        hr = _pJoystickInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̃A�N�Z�X�����擾����
        hr = _pJoystickInputDevice->Poll();
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NPoll�Ɏ��s���܂���");
            do {
                hr = _pJoystickInputDevice->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return S_OK;
}

BOOL CALLBACK GgafDxInput::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("enumGameCtrlCallback ���[��΂����I");

    HRESULT hr;

    // �Q�[���X�e�B�b�N�f�o�C�X��T������
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pJoystickInputDevice, nullptr);
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
        // �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
        return DIENUM_CONTINUE;
    }

    // �W���C�X�e�B�b�N�̔\�͂��擾
    GgafDxInput::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pJoystickInputDevice->GetCapabilities( &GgafDxInput::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
        // �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
        GgafDxInput::_pJoystickInputDevice->Release();
        return DIENUM_CONTINUE;
    }

    //�����c��΃f�o�C�X�̗p
    return DIENUM_STOP;
}

BOOL CALLBACK GgafDxInput::enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    _TRACE_("enumPadAxisCallback ���[��΂����I");
    DIPROPRANGE diproprange;
    ZeroMemory( &diproprange, sizeof(diproprange) );
    diproprange.diph.dwSize = sizeof(diproprange);
    diproprange.diph.dwHeaderSize = sizeof(diproprange.diph);
    diproprange.diph.dwHow = DIPH_BYID;
    diproprange.diph.dwObj = lpddoi->dwType;
    diproprange.lMin = -255;
    diproprange.lMax = +255;

    HRESULT hr = GgafDxInput::_pJoystickInputDevice->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
        _TRACE_("enumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void GgafDxInput::updateMouseState() {
#ifdef MY_DEBUG
    if (_pMouseInputDevice == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() _pMouseInputDevice == nullptr !!!!");
        return;
    }
#endif
    _flip_ms = !_flip_ms; //�X�e�[�g�Z�b�g�t���b�v
    HRESULT hr;
again:
    hr = _pMouseInputDevice->Poll(); //�}�E�X�͒ʏ�Poll�s�p�Ǝv�����Ăяo���Ă����Q�Ə����Ă���̂ŌĂԁB
    hr = _pMouseInputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_mouse_state[_flip_ms]);
    if (FAILED(hr)) {
        hr = _pMouseInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //�_���Ȃ�܂������
        }
    }
    return;
}


bool GgafDxInput::isBeingPressedMouseButton(int prm_button_no) {
    if (prm_button_no < 0 || 8 < prm_button_no) {
        _TRACE_("isBeingPressedMouseButton:�͈͊O");
        return false;
    } else {
        if (_mouse_state[_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isPushedDownMouseButton(int prm_button_no) {
    if (GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //���͉����Ă���
        if (_mouse_state[!_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //�O��Z�b�g[!_flip_ms]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_flip_ms]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}

bool GgafDxInput::isReleasedUpMouseButton(int prm_button_no) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //���͗����Ă���
        if (_mouse_state[!_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //�O��Z�b�g[!_flip_ms]��������Ă����B�����B
            return true;
        } else {
            //�O��Z�b�g[!_flip_ms]�͉�����Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::getMousePointer(long* x, long* y, long* z) {
    //�}�E�X�̈ړ�
    *x = _mouse_state[_flip_ms].lX;
    *y = _mouse_state[_flip_ms].lY;
    //�z�C�[���̏��
    *z = _mouse_state[_flip_ms].lZ;
}

void GgafDxInput::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //�}�E�X�̈ړ�
    *dx = _mouse_state[_flip_ms].lX - _mouse_state[!_flip_ms].lX;
    *dy = _mouse_state[_flip_ms].lY - _mouse_state[!_flip_ms].lY;
    //�z�C�[���̏��
    *dz = _mouse_state[_flip_ms].lZ - _mouse_state[!_flip_ms].lZ;
}

void GgafDxInput::updateKeyboardState() {
#ifdef MY_DEBUG
    if (_pKeyboardInputDevice == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() _pKeyboardInputDevice == nullptr !!!!");
        return;
    }
#endif
    _flip_ks = !_flip_ks; //�X�e�[�g�Z�b�g�t���b�v
    HRESULT hr;
again:
    hr = _pKeyboardInputDevice->Poll(); //�L�[�{�[�h�͒ʏ�Poll�s�p�Ǝv�����A�K�v�ȃL�[�{�[�h�����邩������Ȃ��B
    hr = _pKeyboardInputDevice->GetDeviceState(256, (void*)&_keyboard_state[_flip_ks]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()�����݂�B
        hr = _pKeyboardInputDevice->Acquire();
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

bool GgafDxInput::isPushedDownKey(int prm_DIK) {
    if (GgafDxInput::isBeingPressedKey(prm_DIK)) { //���͉����Ă���
        if (_keyboard_state[!_flip_ks][prm_DIK] & 0x80) {
            //�O��Z�b�g[!_flip_ks]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_flip_ks]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}
int GgafDxInput::getPushedDownKey() {
    int DIK_pressed = GgafDxInput::getBeingPressedKey();
    if (DIK_pressed >= 0 ) { //���͉����Ă���
        if (_keyboard_state[!_flip_ks][DIK_pressed] & 0x80) {
            //�O��Z�b�g[!_flip_ks]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!_flip_ks]�͉�����Ă��Ȃ��̂�OK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isReleasedUpDownKey(int prm_DIK) {
    if (!GgafDxInput::isBeingPressedKey(prm_DIK)) { //���͗����Ă���
        if (_keyboard_state[!_flip_ks][prm_DIK] & 0x80) {
            //�O��Z�b�g[!_flip_ks]�͉�����Ă����B����
            return true;
        } else {
            //�O��Z�b�g[!_flip_ks]��������Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::updateJoystickState() {
    if (_pJoystickInputDevice == nullptr) {
        return;
    }
    _flip_js = !_flip_js; //�X�e�[�g�Z�b�g�t���b�v
    // �W���C�X�e�B�b�N�̏�Ԃ��擾
    HRESULT hr;

again1:
    hr = _pJoystickInputDevice->Poll();
    if (hr != DI_OK) {
        hr = _pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again1;
        } else {
        }
    }

again2:
    hr = _pJoystickInputDevice->GetDeviceState(sizeof(DIJOYSTATE), &_joy_state[_flip_js]);
    if (hr != DI_OK) {
        hr = _pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again2;
        } else {
        }
    }
}

bool GgafDxInput::isPushedDownJoyRgbButton(int prm_rgb_button_no) {
    if (GgafDxInput::isBeingPressedJoyRgbButton(prm_rgb_button_no)) { //���͉����Ă���
        if (_joy_state[!_flip_js].rgbButtons[prm_rgb_button_no] & 0x80) {
            //�O��Z�b�g[!_flip_js]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_flip_js]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}

int GgafDxInput::getPushedDownJoyRgbButton() {
    int JOY_pressed = GgafDxInput::getBeingPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //���͉����Ă���
        if (_joy_state[!_flip_js].rgbButtons[JOY_pressed] & 0x80) {
            //�O��Z�b�g[!_flip_js]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!_flip_js]�͉�����Ă��Ȃ��̂�OK
            return JOY_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isBeingPressedJoyDirection(int prm_direction_no) {
    if (prm_direction_no < 1 || 9 < prm_direction_no) {
        return false;
    } else {
        if (_joy_state[_flip_js].lY < -127) {
            if (_joy_state[_flip_js].lX > 127 && prm_direction_no == 9) {
                return true;
            } else if (_joy_state[_flip_js].lX < -127 && prm_direction_no == 7) {
                return true;
            } else if (prm_direction_no == 8) {
                return true;
            } else {
                return false;
            }
        } else if (_joy_state[_flip_js].lY > 127) {
            if (_joy_state[_flip_js].lX > 127 && prm_direction_no == 3) {
                return true;
            } else if (_joy_state[_flip_js].lX < -127 && prm_direction_no == 1) {
                return true;
            } else if (prm_direction_no == 2) {
                return true;
            } else {
                return false;
            }
        } else if (_joy_state[_flip_js].lX > 127 && prm_direction_no == 6) {
            return true;
        } else if (_joy_state[_flip_js].lX < -127 && prm_direction_no == 4) {
            return true;
        } else if (prm_direction_no == 5) {
            return true;
        } else {
            return false;
        }
    }
}

void GgafDxInput::release() {
    //�f�o�C�X���
    if (_pIDirectInput8) {
        if (_pKeyboardInputDevice) {
            _pKeyboardInputDevice->Unacquire();
            GGAF_RELEASE(_pKeyboardInputDevice);
        }
        if (_pJoystickInputDevice) {
            _pJoystickInputDevice->Unacquire();
            GGAF_RELEASE(_pJoystickInputDevice);
        }
        GGAF_RELEASE(_pIDirectInput8);
    }
}
