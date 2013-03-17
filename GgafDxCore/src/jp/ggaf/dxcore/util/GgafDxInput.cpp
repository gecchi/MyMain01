#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

//const int GgafDxInput::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDxInput::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Keyboard = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Joystick = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Mouse  = nullptr;
DIMOUSESTATE2 GgafDxInput::_dimousestate[2];
int  GgafDxInput::_active_MouseState = 0;

char GgafDxInput::_caKeyboardState[2][256];
int GgafDxInput::_active_KeyboardState = 0;
DIDEVCAPS GgafDxInput::_didevcap;
DIJOYSTATE GgafDxInput::_dijoystate[2];
int GgafDxInput::_active_JoyState = 0;


HRESULT GgafDxInput::init() {
    HRESULT hr;
    // DirectInput �̍쐬
    hr = DirectInput8Create(GgafGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B���`���C���Ȃ��Ȃ�܂���G"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // �}�E�X�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pIDirectInputDevice8_Mouse, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �}�E�X�f�o�C�X�쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK
                | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }
    // �}�E�X�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = _pIDirectInputDevice8_Mouse->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �}�E�X��SetDataFormat �Ɏ��s���܂���"), TEXT("ERROR"),
                   MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }
    // �}�E�X�������x���ݒ�
    hr = _pIDirectInputDevice8_Mouse->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �}�E�X��SetCooperativeLevel�Ɏ��s���܂���"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

//    if (GgafDxGod::_pHWndSecondary) {
//        // �}�E�X�������x���ݒ�
//        hr = _pIDirectInputDevice8_Mouse->SetCooperativeLevel(GgafDxGod::_pHWndSecondary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//        if (hr != D3D_OK) {
//            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() _pHWndSecondary�}�E�X��SetCooperativeLevel�Ɏ��s���܂���"),
//                       TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
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
    hr = _pIDirectInputDevice8_Mouse->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
        return FALSE;
    }

    // �}�E�X�A�N�Z�X���擾
    if (_pIDirectInputDevice8_Mouse) {
        _pIDirectInputDevice8_Mouse->Acquire();
    }

    // �L�[�{�[�h�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pIDirectInputDevice8_Keyboard, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �L�[�{�[�h�f�o�C�X�쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK
                | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // �L�[�{�[�h�擾�f�[�^�t�H�[�}�b�g�̐ݒ�
    hr = _pIDirectInputDevice8_Keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �L�[�{�[�h��SetDataFormat �Ɏ��s���܂���"), TEXT("ERROR"),
                   MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // �L�[�{�[�h�������x���ݒ�
    hr = _pIDirectInputDevice8_Keyboard->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
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

     hr = _pIDirectInputDevice8_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDxGod::_pHWndPrimary,TEXT("GgafDxInput::initDx9Input() �L�[�{�[�h��SetProperty�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
     return hr;
     }
     */
    // �L�[�{�[�h�A�N�Z�X���擾
    if (_pIDirectInputDevice8_Keyboard) {
        _pIDirectInputDevice8_Keyboard->Acquire();
    }


    // �Q�[���X�e�B�b�N��񋓂��ăf�o�C�X�𓾂�
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, GgafDxInput::enumGameCtrlCallback, nullptr, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pIDirectInputDevice8_Joystick == nullptr) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices�񋓂��܂������A�W���C�X�e�B�b�N��������܂���ł���");
        _pIDirectInputDevice8_Joystick = nullptr;
    } else {
        _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�N�f�o�C�X�擾");

        // �Q�[���X�e�B�b�N�̃f�[�^�`����ݒ肷��
        hr = _pIDirectInputDevice8_Joystick->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NSetDataFormat�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�������x����ݒ肷��
        hr = _pIDirectInputDevice8_Joystick->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_FOREGROUND
                | DISCL_NONEXCLUSIVE );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̎��f�[�^�͈̔͂�ݒ肷��
        hr = _pIDirectInputDevice8_Joystick->EnumObjects(GgafDxInput::enumPadAxisCallback, nullptr, DIDFT_AXIS);
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
        hr = _pIDirectInputDevice8_Joystick->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
            return FALSE;
        }

        // �Q�[���X�e�B�b�N�̃A�N�Z�X�����擾����
        hr = _pIDirectInputDevice8_Joystick->Poll();
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NPoll�Ɏ��s���܂���");
            do {
                hr = _pIDirectInputDevice8_Joystick->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return S_OK;
}

BOOL CALLBACK GgafDxInput::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("enumGameCtrlCallback ���[��΂����I");

    HRESULT hr;

    // �Q�[���X�e�B�b�N�f�o�C�X��T������
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pIDirectInputDevice8_Joystick, nullptr);
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
        // �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
        return DIENUM_CONTINUE;
    }

    // �W���C�X�e�B�b�N�̔\�͂��擾
    GgafDxInput::_didevcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDxInput::_didevcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback �W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
        // �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
        GgafDxInput::_pIDirectInputDevice8_Joystick->Release();
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

    HRESULT hr = GgafDxInput::_pIDirectInputDevice8_Joystick->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
        _TRACE_("enumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void GgafDxInput::updateMouseState() {
    if (_pIDirectInputDevice8_Mouse == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() nullptr����");
        return;
    }

    _active_MouseState = !_active_MouseState; //�X�e�[�g�Z�b�g�t���b�v

    HRESULT hr;

again:
    hr = _pIDirectInputDevice8_Mouse->Poll(); //�}�E�X�͒ʏ�Poll�s�p�Ǝv�����Ăяo���Ă����Q�Ə����Ă���̂ŌĂԁB
    hr = _pIDirectInputDevice8_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_dimousestate[_active_MouseState]);
    if (FAILED(hr)) {
        hr = _pIDirectInputDevice8_Mouse->Acquire();
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
        if (_dimousestate[_active_MouseState].rgbButtons[prm_button_no] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isPushedDownMouseButton(int prm_button_no) {
    if (GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //���͉����Ă���
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_button_no] & 0x80) {
            //�O��Z�b�g[!_active_MouseState]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_active_MouseState]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}

bool GgafDxInput::isReleasedUpMouseButton(int prm_button_no) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //���͗����Ă���
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_button_no] & 0x80) {
            //�O��Z�b�g[!_active_MouseState]��������Ă����B�����B
            return true;
        } else {
            //�O��Z�b�g[!_active_MouseState]�͉�����Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::getMousePointer(long* x, long* y, long* z) {
    //�}�E�X�̈ړ�
    *x = _dimousestate[_active_MouseState].lX;
    *y = _dimousestate[_active_MouseState].lY;
    //�z�C�[���̏��
    *z = _dimousestate[_active_MouseState].lZ;
}
void GgafDxInput::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //�}�E�X�̈ړ�
    *dx = _dimousestate[_active_MouseState].lX - _dimousestate[!_active_MouseState].lX;
    *dy = _dimousestate[_active_MouseState].lY - _dimousestate[!_active_MouseState].lY;
    //�z�C�[���̏��
    *dz = _dimousestate[_active_MouseState].lZ - _dimousestate[!_active_MouseState].lZ;
}

void GgafDxInput::updateKeyboardState() {
    if (_pIDirectInputDevice8_Mouse == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() nullptr����");
        return;
    }

    _active_KeyboardState = !_active_KeyboardState; //�X�e�[�g�Z�b�g�t���b�v

    HRESULT hr;
again:
    hr = _pIDirectInputDevice8_Keyboard->Poll(); //�L�[�{�[�h�͒ʏ�Poll�s�p�Ǝv�����A�K�v�ȃL�[�{�[�h�����邩������Ȃ��B
    hr = _pIDirectInputDevice8_Keyboard->GetDeviceState(256, (void*)&_caKeyboardState[_active_KeyboardState]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()�����݂�B
        hr = _pIDirectInputDevice8_Keyboard->Acquire();
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
        if (_caKeyboardState[!_active_KeyboardState][prm_DIK] & 0x80) {
            //�O��Z�b�g[!_active_KeyboardState]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_active_KeyboardState]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}
int GgafDxInput::getPushedDownKey() {
    int DIK_pressed = GgafDxInput::getBeingPressedKey();
    if (DIK_pressed >= 0 ) { //���͉����Ă���
        if (_caKeyboardState[!_active_KeyboardState][DIK_pressed] & 0x80) {
            //�O��Z�b�g[!_active_KeyboardState]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!_active_KeyboardState]�͉�����Ă��Ȃ��̂�OK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isReleasedUpDownKey(int prm_DIK) {
    if (!GgafDxInput::isBeingPressedKey(prm_DIK)) { //���͗����Ă���
        if (_caKeyboardState[!_active_KeyboardState][prm_DIK] & 0x80) {
            //�O��Z�b�g[!_active_KeyboardState]�͉�����Ă����B����
            return true;
        } else {
            //�O��Z�b�g[!_active_KeyboardState]��������Ă��Ȃ��B�������ςȂ��B
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::updateJoystickState() {
    if (_pIDirectInputDevice8_Joystick == nullptr) {
        return;
    }


    _active_JoyState = !_active_JoyState; //�X�e�[�g�Z�b�g�t���b�v

    // �W���C�X�e�B�b�N�̏�Ԃ��擾
    HRESULT hr;

again1:

    hr = _pIDirectInputDevice8_Joystick->Poll();
    if (hr != DI_OK) {
        hr = _pIDirectInputDevice8_Joystick->Acquire();
        if (hr == DI_OK) {
            goto again1;
        } else {
        }
    }

again2:

    hr = _pIDirectInputDevice8_Joystick->GetDeviceState(sizeof(DIJOYSTATE), &_dijoystate[_active_JoyState]);
    if (hr != DI_OK) {
        hr = _pIDirectInputDevice8_Joystick->Acquire();
        if (hr == DI_OK) {
            goto again2;
        } else {
        }
    }
}

bool GgafDxInput::isPushedDownJoyRgbButton(int prm_rgb_button_no) {
    if (GgafDxInput::isBeingPressedJoyRgbButton(prm_rgb_button_no)) { //���͉����Ă���
        if (_dijoystate[!_active_JoyState].rgbButtons[prm_rgb_button_no] & 0x80) {
            //�O��Z�b�g[!_active_JoyState]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!_active_JoyState]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}

int GgafDxInput::getPushedDownJoyRgbButton() {
    int JOY_pressed = GgafDxInput::getBeingPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //���͉����Ă���
        if (_dijoystate[!_active_JoyState].rgbButtons[JOY_pressed] & 0x80) {
            //�O��Z�b�g[!_active_JoyState]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!_active_JoyState]�͉�����Ă��Ȃ��̂�OK
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
        if (_dijoystate[_active_JoyState].lY < -127) {
            if (_dijoystate[_active_JoyState].lX > 127 && prm_direction_no == 9) {
                return true;
            } else if (_dijoystate[_active_JoyState].lX < -127 && prm_direction_no == 7) {
                return true;
            } else if (prm_direction_no == 8) {
                return true;
            } else {
                return false;
            }
        } else if (_dijoystate[_active_JoyState].lY > 127) {
            if (_dijoystate[_active_JoyState].lX > 127 && prm_direction_no == 3) {
                return true;
            } else if (_dijoystate[_active_JoyState].lX < -127 && prm_direction_no == 1) {
                return true;
            } else if (prm_direction_no == 2) {
                return true;
            } else {
                return false;
            }
        } else if (_dijoystate[_active_JoyState].lX > 127 && prm_direction_no == 6) {
            return true;
        } else if (_dijoystate[_active_JoyState].lX < -127 && prm_direction_no == 4) {
            return true;
        } else if (prm_direction_no == 5) {
            return true;
        } else {
            return false;
        }
    }
}

void GgafDxInput::release() {
    TRACE("GgafDxInput::~GgafDxInput()");
    //�f�o�C�X���
    if (_pIDirectInput8) {
        if (_pIDirectInputDevice8_Keyboard) {
            _pIDirectInputDevice8_Keyboard->Unacquire();
            GGAF_RELEASE(_pIDirectInputDevice8_Keyboard);
        }
        if (_pIDirectInputDevice8_Joystick) {
            _pIDirectInputDevice8_Joystick->Unacquire();
            GGAF_RELEASE(_pIDirectInputDevice8_Joystick);
        }
        GGAF_RELEASE(_pIDirectInput8);
    }
}
