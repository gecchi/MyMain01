#include "stdafx.h"

const int GgafDx9Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDx9Input::_s_pIDirectInput8 = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_s_pIDirectInputDevice8_Keyboard = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_s_pIDirectInputDevice8_Joystick = NULL;
char GgafDx9Input::_s_caKeyboardState[256];
DIDEVCAPS GgafDx9Input::_s_didevcap;
DIJOYSTATE GgafDx9Input::_s_dijoystate;

bool GgafDx9Input::_s_isReleasedKey[256];
bool GgafDx9Input::_s_isReleasedJoyRgbButton[32];
bool GgafDx9Input::_s_isReleasedJoyDirection[10];
bool GgafDx9Input::_s_isReleasedJoyUp = true;
bool GgafDx9Input::_s_isReleasedJoyDown = true;
bool GgafDx9Input::_s_isReleasedJoyLeft = true;
bool GgafDx9Input::_s_isReleasedJoyRight = true;



BOOL CALLBACK EnumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
	_TRACE_("EnumGameCtrlCallback こーるばっく！");

	HRESULT hr;

	// ゲームスティックデバイスを探すする

	hr = GgafDx9Input::_s_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDx9Input::_s_pIDirectInputDevice8_Joystick, NULL);
	if(FAILED(hr)){
		_TRACE_("EnumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
		// デバイスの作成に失敗したら列挙を続ける（さらに探す）
		return DIENUM_CONTINUE;
	}

	// ジョイスティックの能力を取得
	GgafDx9Input::_s_didevcap.dwSize = sizeof(DIDEVCAPS);
	hr = GgafDx9Input::_s_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDx9Input::_s_didevcap );
	if( FAILED(hr) ) {
		_TRACE_("EnumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
		// ジョイスティックの能力を取得出来ないようなら、勘弁願う
		GgafDx9Input::_s_pIDirectInputDevice8_Joystick->Release();
		return DIENUM_CONTINUE;
	}
	
	//生き残ればデバイス採用
	return DIENUM_STOP;
}

/**
 * 軸ボタン列挙コールバック関数
 * 各軸の最低値を -255、最高値を 255 に設定
 */
BOOL CALLBACK EnumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
	_TRACE_("EnumPadAxisCallback こーるばっく！"); 
	DIPROPRANGE	diproprange;
	ZeroMemory( &diproprange, sizeof(diproprange) ); 
	diproprange.diph.dwSize = sizeof(diproprange); 
	diproprange.diph.dwHeaderSize = sizeof(diproprange.diph); 
	diproprange.diph.dwHow = DIPH_BYID; 
	diproprange.diph.dwObj = lpddoi->dwType; 
	diproprange.lMin = -255; 
	diproprange.lMax = +255; 

	HRESULT	hr = GgafDx9Input::_s_pIDirectInputDevice8_Joystick->SetProperty(DIPROP_RANGE, &diproprange.diph);
	if(FAILED(hr)){
		_TRACE_("EnumPadAxisCallback ジョイスティックSetPropertyに失敗しました");
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

GgafDx9Input::GgafDx9Input() {
	TRACE("GgafDx9Input::GgafDx9Input(HWND prm_hWnd) ");
}

HRESULT GgafDx9Input::init() {

	HRESULT hr;
	// DirectInput の作成
	hr = DirectInput8Create(
			 GgafDx9God::_hInstance, 
			 DIRECTINPUT_VERSION,
			 IID_IDirectInput8, 
			 (LPVOID*)&_s_pIDirectInput8,
			 NULL
		 );
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() いきなりDirectInput8の作成に失敗しました。も〜やる気もなくなりますわ；"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	//==============================
	//	キーボード
	//==============================
	// キーボードデバイスの作成
	hr = _s_pIDirectInput8->CreateDevice(
							  GUID_SysKeyboard,
							  &_s_pIDirectInputDevice8_Keyboard,
							  NULL
						  ); 
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() キーボードデバイス作成に失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 取得データフォーマットの設定
	hr = _s_pIDirectInputDevice8_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() キーボードのSetDataFormat に失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 強調レベル設定
	hr = _s_pIDirectInputDevice8_Keyboard->SetCooperativeLevel(
											 GgafDx9God::_hWnd, 
											 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
										 );
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() キーボードのSetCooperativeLevelに失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}

/*
//ばふぁなぞいらんｗ
  	// バッファサイズの指定
	DIPROPDWORD dipropdword;
	dipropdword.diph.dwSize			= sizeof(DIPROPDWORD);
	dipropdword.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	dipropdword.diph.dwObj			= 0;
	dipropdword.diph.dwHow			= DIPH_DEVICE;
	dipropdword.dwData				= GgafDx9Input::BUFFER_SIZE;

	hr = _s_pIDirectInputDevice8_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
	if(FAILED(hr)) {
        MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() キーボードのSetPropertyに失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return hr;
	}
*/
	// アクセス権取得
	if(_s_pIDirectInputDevice8_Keyboard) {
		_s_pIDirectInputDevice8_Keyboard->Acquire(); 
	}

	//=================================
	//ジョイスティック
	//=================================
// デバイスを列挙する
	// ゲームスティックを列挙する してデバイスを得る
	hr = _s_pIDirectInput8->EnumDevices(
							  DI8DEVCLASS_GAMECTRL, 
							  EnumGameCtrlCallback, 
							  NULL, 
							  DIEDFL_ATTACHEDONLY
						  );
	if(FAILED(hr) || _s_pIDirectInputDevice8_Joystick == NULL){
        _TRACE_("GgafDx9Input::initDx9Input() EnumDevices列挙しましたが、でジョイスティックが見つかりませんでした");
		_s_pIDirectInputDevice8_Joystick = NULL;
	} else {
		_TRACE_("GgafDx9Input::initDx9Input() ジョイスティックデバイス取得");


		// ゲームスティックのデータ形式を設定する
		hr = _s_pIDirectInputDevice8_Joystick->SetDataFormat(&c_dfDIJoystick);
		if(FAILED(hr)){
	        _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックSetDataFormatに失敗しました");
			return FALSE;
		}

		// 協調レベルを設定する
		hr = _s_pIDirectInputDevice8_Joystick->SetCooperativeLevel(GgafDx9God::_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
			return FALSE;
		}

		// ゲームスティックの軸データの範囲を設定する
		hr = _s_pIDirectInputDevice8_Joystick->EnumObjects(EnumPadAxisCallback, NULL, DIDFT_AXIS);
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() ジョイスティックEnumObjectsに失敗しました");
			return FALSE;
		}

	    // 軸モードを設定
	    DIPROPDWORD dipropword;
	    dipropword.diph.dwSize  = sizeof(dipropword); 
	    dipropword.diph.dwHeaderSize    = sizeof(dipropword.diph); 
	    dipropword.diph.dwObj   = 0;
	    dipropword.diph.dwHow   = DIPH_DEVICE;
	    dipropword.dwData       = DIPROPAXISMODE_ABS;   // 絶対値モード
	//  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
	    hr = _s_pIDirectInputDevice8_Joystick->SetProperty( DIPROP_AXISMODE, &dipropword.diph );
	    if( FAILED(hr) ) {
	        _TRACE_( "軸モードの設定に失敗");
	        return FALSE;
	    }


		// ゲームスティックのアクセス権を取得する
		hr = _s_pIDirectInputDevice8_Joystick->Poll(); 
		if(FAILED(hr)){
			_TRACE_("GgafDx9Input::initDx9Input() ジョイスティックPollに失敗しました");
			do{
				hr = _s_pIDirectInputDevice8_Joystick->Acquire();
			} while(hr == DIERR_INPUTLOST);
		}
	}
    return S_OK;
}


void GgafDx9Input::updateKeyboardState() {
	if (_s_pIDirectInputDevice8_Keyboard == NULL) {
		_TRACE_("GgafDx9Input::updateKeyboardState() NULLっす");
		
		return;	
	}
	
	HRESULT hr;
	
	again:

	hr = _s_pIDirectInputDevice8_Keyboard->GetDeviceState(sizeof(_s_caKeyboardState), (void*)&_s_caKeyboardState);
	if(hr != DI_OK){
		//１回だけAcquire()を試みる。
		hr = _s_pIDirectInputDevice8_Keyboard->Acquire();
        if(hr == DI_OK) {
			goto again;
        } else {
			//ダメならまた次回へ
        }
	}
	return;
}

bool GgafDx9Input::isBeingPressedKey(int prm_DIK) {
	if (prm_DIK < 0 || 255 < prm_DIK) {
		return false;
	} else {
		if (_s_caKeyboardState[prm_DIK] & 0x80) {
			return true;
		} else {
			_s_isReleasedKey[prm_DIK] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isPressedKey(int prm_iKeyNo) {
	bool ret = isBeingPressedKey(prm_iKeyNo);
	if (_s_isReleasedKey[prm_iKeyNo]) {
		if (ret) {
			_s_isReleasedKey[prm_iKeyNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}



void GgafDx9Input::updateJoystickState() {
	if (_s_pIDirectInputDevice8_Joystick == NULL) {
		return;	
	}
	
	// ジョイスティックの状態を取得
	HRESULT hr;
		
	again1:
	
	hr = _s_pIDirectInputDevice8_Joystick->Poll();
	if(hr != DI_OK){
		hr = _s_pIDirectInputDevice8_Joystick->Acquire();
        if(hr == DI_OK) {
			goto again1;
        } else {
        }
	}
	
	again2:
	
	hr = _s_pIDirectInputDevice8_Joystick->GetDeviceState( sizeof(DIJOYSTATE), &_s_dijoystate );
	if(hr != DI_OK){
		hr = _s_pIDirectInputDevice8_Joystick->Acquire();
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
		if (_s_dijoystate.rgbButtons[prm_iRgbButtonNo] & 0x80 ) {
			return true;
		} else {
			_s_isReleasedJoyRgbButton[prm_iRgbButtonNo] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isBeingPressedJoyUp() {
	if (_s_dijoystate.lY < -127) {
		return true;
	} else {
		_s_isReleasedJoyUp = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyDown() {
	if (_s_dijoystate.lY > 127) {
		return true;
	} else {
		_s_isReleasedJoyDown = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyLeft() {
	if (_s_dijoystate.lX < -127) {
		return true;
	} else {
		_s_isReleasedJoyLeft = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyRight() {
	if (_s_dijoystate.lX > 127) {
		return true;
	} else {
		_s_isReleasedJoyRight = true;
		return false;
	}
}

bool GgafDx9Input::isBeingPressedJoyDirection(int prm_iDirectionNo) {
	if (prm_iDirectionNo < 1 || 9 < prm_iDirectionNo) {
		return false;
	} else {
		if (_s_dijoystate.lY < -127) {
			if (_s_dijoystate.lX > 127 && prm_iDirectionNo == 9) {
				return true;
			} else if (_s_dijoystate.lX < -127 && prm_iDirectionNo == 7) {
				return true;
			} else if (prm_iDirectionNo == 8) {
				return true;
			} else {
				_s_isReleasedJoyDirection[prm_iDirectionNo] = true;
				return false;
			}
		} else if (_s_dijoystate.lY > 127) {
			if (_s_dijoystate.lX > 127 && prm_iDirectionNo == 3) {
				return true;
			} else if (_s_dijoystate.lX < -127 && prm_iDirectionNo == 1) {
				return true;
			} else if (prm_iDirectionNo == 2) {
				return true;
			} else {
				_s_isReleasedJoyDirection[prm_iDirectionNo] = true;
				return false;
			}
		} else if (_s_dijoystate.lX > 127 && prm_iDirectionNo == 6) {
			return true;
		} else if (_s_dijoystate.lX < -127 && prm_iDirectionNo == 4) {
			return true;
		} else {
			_s_isReleasedJoyDirection[prm_iDirectionNo] = true;
			return false;
		}
	}
}

bool GgafDx9Input::isPressedJoyRgbButton(int prm_iRgbButtonNo) {
	bool ret = isBeingPressedJoyRgbButton(prm_iRgbButtonNo);
	if (_s_isReleasedJoyRgbButton[prm_iRgbButtonNo]) {
		if (ret) {
			_s_isReleasedJoyRgbButton[prm_iRgbButtonNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyUp() {
	bool ret = isBeingPressedJoyUp();
	if (_s_isReleasedJoyUp) {
		if (ret) {
			_s_isReleasedJoyUp = false;
		}
		return ret;
	} else {
		return false;
	}
}


bool GgafDx9Input::isPressedJoyDown() {
	bool ret = isBeingPressedJoyDown();
	if (_s_isReleasedJoyDown) {
		if (ret) {
			_s_isReleasedJoyDown = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyLeft() {
	bool ret = isBeingPressedJoyLeft();
	if (_s_isReleasedJoyLeft) {
		if (ret) {
			_s_isReleasedJoyLeft = false;
		}
		return ret;
	} else {
		return false;
	}
}

bool GgafDx9Input::isPressedJoyRight() {
	bool ret = isBeingPressedJoyRight();
	if (_s_isReleasedJoyRight) {
		if (ret) {
			_s_isReleasedJoyRight = false;
		}
		return ret;
	} else {
		return false;
	}
}



bool GgafDx9Input::isPressedJoyDirection(int prm_iDirectionNo) { //テンキーの方向ナンバー（１〜９。但し５を除く）
	bool ret = isBeingPressedJoyDirection(prm_iDirectionNo);
	if (_s_isReleasedJoyDirection[prm_iDirectionNo]) {
		if (ret) {
			_s_isReleasedJoyDirection[prm_iDirectionNo] = false;
		}
		return ret;
	} else {
		return false;
	}
}

void GgafDx9Input::release() {
	TRACE("GgafDx9Input::~GgafDx9Input() start -->");
	//デバイス解放
	_s_pIDirectInputDevice8_Keyboard->Unacquire();
	_s_pIDirectInputDevice8_Keyboard->Release();
	_s_pIDirectInputDevice8_Keyboard = NULL;
	if (_s_pIDirectInputDevice8_Joystick != NULL) {
		_s_pIDirectInputDevice8_Joystick->Unacquire();
		_s_pIDirectInputDevice8_Joystick->Release();
		_s_pIDirectInputDevice8_Joystick = NULL;
    }
	_s_pIDirectInput8->Release();
	TRACE("GgafDx9Input::~GgafDx9Input() end <--");

}
