#include "stdafx.h"

const int GgafDx9Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDx9Input::_pIDirectInput8 = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_pIDirectInputDevice8_Keyboard = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_pIDirectInputDevice8_Joystick = NULL;
char GgafDx9Input::_caKeyboardState[256];
DIDEVCAPS GgafDx9Input::_didevcap;
DIJOYSTATE GgafDx9Input::_dijoystate;

bool GgafDx9Input::_isReleasedKey[256];
bool GgafDx9Input::_isReleasedJoyRgbButton[32];
bool GgafDx9Input::_isReleasedJoyDirection[10];
bool GgafDx9Input::_isReleasedJoyUp = true;
bool GgafDx9Input::_isReleasedJoyDown = true;
bool GgafDx9Input::_isReleasedJoyLeft = true;
bool GgafDx9Input::_isReleasedJoyRight = true;



BOOL CALLBACK EnumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
	_TRACE_("EnumGameCtrlCallback ���[��΂����I");

	HRESULT hr;

	// �Q�[���X�e�B�b�N�f�o�C�X��T������

	hr = GgafDx9Input::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDx9Input::_pIDirectInputDevice8_Joystick, NULL);
	if(FAILED(hr)){
		_TRACE_("EnumGameCtrlCallback �W���C�X�e�B�b�NCreateDevice�Ɏ��s���܂���");
		// �f�o�C�X�̍쐬�Ɏ��s������񋓂𑱂���i����ɒT���j
		return DIENUM_CONTINUE;
	}

	// �W���C�X�e�B�b�N�̔\�͂��擾
	GgafDx9Input::_didevcap.dwSize = sizeof(DIDEVCAPS);
	hr = GgafDx9Input::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDx9Input::_didevcap );
	if( FAILED(hr) ) {
		_TRACE_("EnumGameCtrlCallback �W���C�X�e�B�b�NGetCapabilities�Ɏ��s���܂���");
		// �W���C�X�e�B�b�N�̔\�͂��擾�o���Ȃ��悤�Ȃ�A���ي肤
		GgafDx9Input::_pIDirectInputDevice8_Joystick->Release();
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
	DIPROPRANGE	diproprange;
	ZeroMemory( &diproprange, sizeof(diproprange) ); 
	diproprange.diph.dwSize = sizeof(diproprange); 
	diproprange.diph.dwHeaderSize = sizeof(diproprange.diph); 
	diproprange.diph.dwHow = DIPH_BYID; 
	diproprange.diph.dwObj = lpddoi->dwType; 
	diproprange.lMin = -255; 
	diproprange.lMax = +255; 

	HRESULT	hr = GgafDx9Input::_pIDirectInputDevice8_Joystick->SetProperty(DIPROP_RANGE, &diproprange.diph);
	if(FAILED(hr)){
		_TRACE_("EnumPadAxisCallback �W���C�X�e�B�b�NSetProperty�Ɏ��s���܂���");
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

GgafDx9Input::GgafDx9Input() {
	TRACE("GgafDx9Input::GgafDx9Input(HWND prm_hWnd) ");
}

HRESULT GgafDx9Input::init() {

	HRESULT hr;
	// DirectInput �̍쐬
	hr = DirectInput8Create(
			 GgafDx9God::_hInstance, 
			 DIRECTINPUT_VERSION,
			 IID_IDirectInput8, 
			 (LPVOID*)&_pIDirectInput8,
			 NULL
		 );
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() �����Ȃ�DirectInput8�̍쐬�Ɏ��s���܂����B���`���C���Ȃ��Ȃ�܂���G"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	//==============================
	//	�L�[�{�[�h
	//==============================
	// �L�[�{�[�h�f�o�C�X�̍쐬
	hr = _pIDirectInput8->CreateDevice(
							  GUID_SysKeyboard,
							  &_pIDirectInputDevice8_Keyboard,
							  NULL
						  ); 
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() �L�[�{�[�h�f�o�C�X�쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �擾�f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = _pIDirectInputDevice8_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() �L�[�{�[�h��SetDataFormat �Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �������x���ݒ�
	hr = _pIDirectInputDevice8_Keyboard->SetCooperativeLevel(
											 GgafDx9God::_hWnd, 
											 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
										 );
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() �L�[�{�[�h��SetCooperativeLevel�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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
	dipropdword.dwData				= GgafDx9Input::BUFFER_SIZE;

	hr = _pIDirectInputDevice8_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() �L�[�{�[�h��SetProperty�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}
*/
	// �A�N�Z�X���擾
	if(_pIDirectInputDevice8_Keyboard) {
		_pIDirectInputDevice8_Keyboard->Acquire(); 
	}

	//=================================
	//�W���C�X�e�B�b�N
	//=================================
// �f�o�C�X��񋓂���
	// �Q�[���X�e�B�b�N��񋓂��� ���ăf�o�C�X�𓾂�
	hr = _pIDirectInput8->EnumDevices(
							  DI8DEVCLASS_GAMECTRL, 
							  EnumGameCtrlCallback, 
							  NULL, 
							  DIEDFL_ATTACHEDONLY
						  );
	if(FAILED(hr) || _pIDirectInputDevice8_Joystick == NULL){
        _TRACE_("GgafDx9Input::initDx9Input() EnumDevices�񋓂��܂������A�ŃW���C�X�e�B�b�N��������܂���ł���");
		_pIDirectInputDevice8_Joystick = NULL;
	} else {
		_TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�N�f�o�C�X�擾");


		// �Q�[���X�e�B�b�N�̃f�[�^�`����ݒ肷��
		hr = _pIDirectInputDevice8_Joystick->SetDataFormat(&c_dfDIJoystick);
		if(FAILED(hr)){
	        _TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�NSetDataFormat�Ɏ��s���܂���");
			return FALSE;
		}

		// �������x����ݒ肷��
		hr = _pIDirectInputDevice8_Joystick->SetCooperativeLevel(GgafDx9God::_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�NSetCooperativeLevel�Ɏ��s���܂���");
			return FALSE;
		}

		// �Q�[���X�e�B�b�N�̎��f�[�^�͈̔͂�ݒ肷��
		hr = _pIDirectInputDevice8_Joystick->EnumObjects(EnumPadAxisCallback, NULL, DIDFT_AXIS);
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�NEnumObjects�Ɏ��s���܂���");
			return FALSE;
		}

	    // �����[�h��ݒ�
	    DIPROPDWORD dipropword;
	    dipropword.diph.dwSize  = sizeof(dipropword); 
	    dipropword.diph.dwHeaderSize    = sizeof(dipropword.diph); 
	    dipropword.diph.dwObj   = 0;
	    dipropword.diph.dwHow   = DIPH_DEVICE;
	    dipropword.dwData       = DIPROPAXISMODE_ABS;   // ��Βl���[�h
	//  dipropword.dwData       = DIPROPAXISMODE_REL;   // ���Βl���[�h
	    hr = _pIDirectInputDevice8_Joystick->SetProperty( DIPROP_AXISMODE, &dipropword.diph );
	    if( FAILED(hr) ) {
	        _TRACE_( "�����[�h�̐ݒ�Ɏ��s");
	        return FALSE;
	    }


		// �Q�[���X�e�B�b�N�̃A�N�Z�X�����擾����
		hr = _pIDirectInputDevice8_Joystick->Poll(); 
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() �W���C�X�e�B�b�NPoll�Ɏ��s���܂���");
			do{
				hr = _pIDirectInputDevice8_Joystick->Acquire();
			} while(hr == DIERR_INPUTLOST);
		}
	}
    return S_OK;
}


void GgafDx9Input::updateKeyboardState() {
	if (_pIDirectInputDevice8_Keyboard == NULL) {
		_TRACE_("GgafDx9Input::updateKeyboardState() NULL����");
		
		return;	
	}
	
	HRESULT hr;
	
	again:

	hr = _pIDirectInputDevice8_Keyboard->GetDeviceState(sizeof(_caKeyboardState), (void*)&_caKeyboardState);
	if(hr != DI_OK){
		//�P�񂾂�Acquire()�����݂�B
		hr = _pIDirectInputDevice8_Keyboard->Acquire();
        if(hr == DI_OK) {
			goto again;
        } else {
			//�_���Ȃ�܂������
        }
	}
	return;
}

bool GgafDx9Input::isBeingPressedKey(int prm_DIK) {
	if (prm_DIK < 0 || 255 < prm_DIK) {
		return false;
	} else {
		if (_caKeyboardState[prm_DIK] & 0x80) {
			return true;
		} else {
			_isReleasedKey[prm_DIK] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isPressedKey(int prm_iKeyNo) {
	bool ret = isBeingPressedKey(prm_iKeyNo);
	if (_isReleasedKey[prm_iKeyNo]) {
		if (ret) {
			_isReleasedKey[prm_iKeyNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}



void GgafDx9Input::updateJoystickState() {
	if (_pIDirectInputDevice8_Joystick == NULL) {
		return;	
	}
	
	// �W���C�X�e�B�b�N�̏�Ԃ��擾
	HRESULT hr;
		
	again1:
	
	hr = _pIDirectInputDevice8_Joystick->Poll();
	if(hr != DI_OK){
		hr = _pIDirectInputDevice8_Joystick->Acquire();
        if(hr == DI_OK) {
			goto again1;
        } else {
        }
	}
	
	again2:
	
	hr = _pIDirectInputDevice8_Joystick->GetDeviceState( sizeof(DIJOYSTATE), &_dijoystate );
	if(hr != DI_OK){
		hr = _pIDirectInputDevice8_Joystick->Acquire();
        if(hr == DI_OK) {
			goto again2;
        } else {
        }        	
	}	
}

bool GgafDx9Input::isBeingPressedJoyRgbButton(int prm_iRgbButtonNo) {
	if (prm_iRgbButtonNo < 0 || 31 < prm_iRgbButtonNo) {
		return false;
	} else {
		if (_dijoystate.rgbButtons[prm_iRgbButtonNo] & 0x80 ) {
			return true;
		} else {
			_isReleasedJoyRgbButton[prm_iRgbButtonNo] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isBeingPressedJoyUp() {
	if (_dijoystate.lY < -127) {
		return true;
	} else {
		_isReleasedJoyUp = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyDown() {
	if (_dijoystate.lY > 127) {
		return true;
	} else {
		_isReleasedJoyDown = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyLeft() {
	if (_dijoystate.lX < -127) {
		return true;
	} else {
		_isReleasedJoyLeft = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyRight() {
	if (_dijoystate.lX > 127) {
		return true;
	} else {
		_isReleasedJoyRight = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyDirection(int prm_iDirectionNo) {
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
				_isReleasedJoyDirection[prm_iDirectionNo] = true;
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
				_isReleasedJoyDirection[prm_iDirectionNo] = true;
				return false;
			}
		} else if (_dijoystate.lX > 127 && prm_iDirectionNo == 6) {
			return true;
		} else if (_dijoystate.lX < -127 && prm_iDirectionNo == 4) {
			return true;
		} else {
			_isReleasedJoyDirection[prm_iDirectionNo] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isPressedJoyRgbButton(int prm_iRgbButtonNo) {
	bool ret = isBeingPressedJoyRgbButton(prm_iRgbButtonNo);
	if (_isReleasedJoyRgbButton[prm_iRgbButtonNo]) {
		if (ret) {
			_isReleasedJoyRgbButton[prm_iRgbButtonNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyUp() {
	bool ret = isBeingPressedJoyUp();
	if (_isReleasedJoyUp) {
		if (ret) {
			_isReleasedJoyUp = false;
		}
		return ret;
	} else {
		return false;
	}
}


bool GgafDx9Input::isPressedJoyDown() {
	bool ret = isBeingPressedJoyDown();
	if (_isReleasedJoyDown) {
		if (ret) {
			_isReleasedJoyDown = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyLeft() {
	bool ret = isBeingPressedJoyLeft();
	if (_isReleasedJoyLeft) {
		if (ret) {
			_isReleasedJoyLeft = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyRight() {
	bool ret = isBeingPressedJoyRight();
	if (_isReleasedJoyRight) {
		if (ret) {
			_isReleasedJoyRight = false;
		}
		return ret;
	} else {
		return false;
	}
}



bool GgafDx9Input::isPressedJoyDirection(int prm_iDirectionNo) { //�e���L�[�̕����i���o�[�i�P�`�X�B�A���T�������j
	bool ret = isBeingPressedJoyDirection(prm_iDirectionNo);
	if (_isReleasedJoyDirection[prm_iDirectionNo]) {
		if (ret) {
			_isReleasedJoyDirection[prm_iDirectionNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}

void GgafDx9Input::release() {
	TRACE("GgafDx9Input::~GgafDx9Input() start -->");
	//�f�o�C�X���
	_pIDirectInputDevice8_Keyboard->Unacquire();
	_pIDirectInputDevice8_Keyboard->Release();
	_pIDirectInputDevice8_Keyboard = NULL;
	if (_pIDirectInputDevice8_Joystick != NULL) {
		_pIDirectInputDevice8_Joystick->Unacquire();
		_pIDirectInputDevice8_Joystick->Release();
		_pIDirectInputDevice8_Joystick = NULL;
    }
	_pIDirectInput8->Release();
	TRACE("GgafDx9Input::~GgafDx9Input() end <--");

}
