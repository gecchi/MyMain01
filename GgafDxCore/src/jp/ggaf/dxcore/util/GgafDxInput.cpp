#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

const int GgafDxInput::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDxInput::_pIDirectInput8 = NULL;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Keyboard = NULL;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Joystick = NULL;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pIDirectInputDevice8_Mouse  = NULL;
DIMOUSESTATE2 GgafDxInput::_dimousestate[2];
int  GgafDxInput::_active_MouseState = 0;

char GgafDxInput::_caKeyboardState[2][256];
int GgafDxInput::_active_KeyboardState = 0;
DIDEVCAPS GgafDxInput::_didevcap;
DIJOYSTATE GgafDxInput::_dijoystate;

BOOL CALLBACK EnumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("EnumGameCtrlCallback ���[��΂����I");

    HRESULT hr;

    // �Q�[���X�e�B�b�N�f�o�C�X��T������
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pIDirectInputDevice8_Joystick, NULL);
    if(hr != D3D_OK) {
        _TRACE_("EnumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
        // �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
        return DIENUM_CONTINUE;
    }

    // �W���C�X�e�B�b�N�̔\�͂��擾
    GgafDxInput::_didevcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDxInput::_didevcap );
    if( hr != D3D_OK ) {
        _TRACE_("EnumGameCtrlCallback �W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
        // �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
        GgafDxInput::_pIDirectInputDevice8_Joystick->Release();
        return DIENUM_CONTINUE;
    }

    //�����c��΃f�o�C�X�̗p
    return DIENUM_STOP;
}

/**
 * ���{�^���񋓃R�[���o�b�N�֐�
 * �e���̍Œ�l�� -255�A�ō��l�� 255 �ɐݒ�
 */
BOOL CALLBACK EnumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    _TRACE_("EnumPadAxisCallback ���[��΂����I");
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
        _TRACE_("EnumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

GgafDxInput::GgafDxInput() {
    TRACE("GgafDxInput::GgafDxInput(HWND prm_pHWndPrimary) ");
}

HRESULT GgafDxInput::init() {

    HRESULT hr;
    // DirectInput �̍쐬
    hr = DirectInput8Create(GgafDxGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, NULL);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() �����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B���`���C���Ȃ��Ȃ�܂���G"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // �}�E�X�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pIDirectInputDevice8_Mouse, NULL);
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
    DIPROPDWORD dipropword;
    dipropword.diph.dwSize = sizeof(dipropword);
    dipropword.diph.dwHeaderSize = sizeof(dipropword.diph);
    dipropword.diph.dwObj = 0;
    dipropword.diph.dwHow = DIPH_DEVICE;
    dipropword.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
    hr = _pIDirectInputDevice8_Mouse->SetProperty(DIPROP_AXISMODE, &dipropword.diph);
    if (hr != D3D_OK) {
        _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
        return FALSE;
    }

    // �}�E�X�A�N�Z�X���擾
    if (_pIDirectInputDevice8_Mouse) {
        _pIDirectInputDevice8_Mouse->Acquire();
    }


    // �L�[�{�[�h�f�o�C�X�̍쐬
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pIDirectInputDevice8_Keyboard, NULL);
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
     //�΂ӂ��Ȃ������
     // �o�b�t�@�T�C�Y�̎w��
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
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGameCtrlCallback, NULL, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pIDirectInputDevice8_Joystick == NULL) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices�񋓂��܂������A�ŃW���C�X�e�B�b�N��������܂���ł���");
        _pIDirectInputDevice8_Joystick = NULL;
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
        hr = _pIDirectInputDevice8_Joystick->EnumObjects(EnumPadAxisCallback, NULL, DIDFT_AXIS);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() �W���C�X�e�B�b�NEnumObjects�Ɏ��s���܂���");
            return FALSE;
        }

        // �����[�h��ݒ�
        DIPROPDWORD dipropword;
        dipropword.diph.dwSize = sizeof(dipropword);
        dipropword.diph.dwHeaderSize = sizeof(dipropword.diph);
        dipropword.diph.dwObj = 0;
        dipropword.diph.dwHow = DIPH_DEVICE;
        dipropword.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h
        //  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
        hr = _pIDirectInputDevice8_Joystick->SetProperty(DIPROP_AXISMODE, &dipropword.diph);
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


void GgafDxInput::updateMouseState() {
    if (_pIDirectInputDevice8_Mouse == NULL) {
        _TRACE_("GgafDxInput::updateKeyboardState() NULL����");
        return;
    }

    _active_MouseState = !_active_MouseState; //�X�e�[�g�Z�b�g�t���b�v

    HRESULT hr;

again:
    hr = _pIDirectInputDevice8_Mouse->Poll(); //�}�E�X�͒ʏ�Poll�s�p�Ǝv�����Ăяo���Ă����Q�Ə����Ă���̂ŌĂԁB
    hr = _pIDirectInputDevice8_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_dimousestate[_active_MouseState]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()�����݂�B
        hr = _pIDirectInputDevice8_Mouse->Acquire();
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



bool GgafDxInput::isBeingPressedMouseButton(int prm_iButtonNo) {
    if (prm_iButtonNo < 0 || 8 < prm_iButtonNo) {
        _TRACE_("isBeingPressedMouseButton:�͈͊O");
        return false;
    } else {
        if (_dimousestate[_active_MouseState].rgbButtons[prm_iButtonNo] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isPushedDownMouseButton(int prm_iButtonNo) {
    if (GgafDxInput::isBeingPressedMouseButton(prm_iButtonNo)) { //���͉����Ă���
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_iButtonNo] & 0x80) {
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

bool GgafDxInput::isReleasedUpMouseButton(int prm_iButtonNo) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_iButtonNo)) { //���͗����Ă���
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_iButtonNo] & 0x80) {
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
    if (_pIDirectInputDevice8_Mouse == NULL) {
        _TRACE_("GgafDxInput::updateKeyboardState() NULL����");
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

bool GgafDxInput::isBeingPressedKey(int prm_DIK) {
    if (prm_DIK < 0 || 255 < prm_DIK) {
        _TRACE_("isBeingPressedKey:�͈͊O");
        return false;
    } else {
        if (_caKeyboardState[_active_KeyboardState][prm_DIK] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
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
    if (_pIDirectInputDevice8_Joystick == NULL) {
        return;
    }

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

    hr = _pIDirectInputDevice8_Joystick->GetDeviceState(sizeof(DIJOYSTATE), &_dijoystate);
    if (hr != DI_OK) {
        hr = _pIDirectInputDevice8_Joystick->Acquire();
        if (hr == DI_OK) {
            goto again2;
        } else {
        }
    }
}

bool GgafDxInput::isBeingPressedJoyRgbButton(int prm_iRgbButtonNo) {
    if (prm_iRgbButtonNo < 0 || 31 < prm_iRgbButtonNo) {
        _TRACE_("isBeingPressedJoyRgbButton:�͈͊O");
        return false;
    } else {
        if (_dijoystate.rgbButtons[prm_iRgbButtonNo] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isBeingPressedJoyUp() {
    if (_dijoystate.lY < -127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDxInput::isBeingPressedJoyDown() {
    if (_dijoystate.lY > 127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDxInput::isBeingPressedJoyLeft() {
    if (_dijoystate.lX < -127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDxInput::isBeingPressedJoyRight() {
    if (_dijoystate.lX > 127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDxInput::isBeingPressedJoyDirection(int prm_iDirectionNo) {
    if (prm_iDirectionNo < 1 || 9 < prm_iDirectionNo) {
        return false;
    } else {
        if (_dijoystate.lY < -127) {
            if (_dijoystate.lX > 127 && prm_iDirectionNo == 9) {
                return true;
            } else if (_dijoystate.lX < -127 && prm_iDirectionNo == 7) {
                return true;
            } else if (prm_iDirectionNo == 8) {
                return true;
            } else {
                return false;
            }
        } else if (_dijoystate.lY > 127) {
            if (_dijoystate.lX > 127 && prm_iDirectionNo == 3) {
                return true;
            } else if (_dijoystate.lX < -127 && prm_iDirectionNo == 1) {
                return true;
            } else if (prm_iDirectionNo == 2) {
                return true;
            } else {
                return false;
            }
        } else if (_dijoystate.lX > 127 && prm_iDirectionNo == 6) {
            return true;
        } else if (_dijoystate.lX < -127 && prm_iDirectionNo == 4) {
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
            RELEASE_IMPOSSIBLE_NULL(_pIDirectInputDevice8_Keyboard);
        }
        if (_pIDirectInputDevice8_Joystick) {
            _pIDirectInputDevice8_Joystick->Unacquire();
            RELEASE_IMPOSSIBLE_NULL(_pIDirectInputDevice8_Joystick);
        }
        RELEASE_IMPOSSIBLE_NULL(_pIDirectInput8);
    }
}
