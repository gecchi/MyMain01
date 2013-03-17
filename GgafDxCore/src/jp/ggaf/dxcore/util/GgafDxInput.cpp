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
    // DirectInput の作成
    hr = DirectInput8Create(GgafGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() いきなりDirectInput8の作成に失敗しました。も～やる気もなくなりますわ；"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // マウスデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pIDirectInputDevice8_Mouse, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() マウスデバイス作成に失敗しました"), TEXT("ERROR"), MB_OK
                | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }
    // マウス取得データフォーマットの設定
    hr = _pIDirectInputDevice8_Mouse->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() マウスのSetDataFormat に失敗しました"), TEXT("ERROR"),
                   MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }
    // マウス強調レベル設定
    hr = _pIDirectInputDevice8_Mouse->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() マウスのSetCooperativeLevelに失敗しました"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

//    if (GgafDxGod::_pHWndSecondary) {
//        // マウス強調レベル設定
//        hr = _pIDirectInputDevice8_Mouse->SetCooperativeLevel(GgafDxGod::_pHWndSecondary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//        if (hr != D3D_OK) {
//            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました"),
//                       TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
//            return hr;
//        }
//    }
    // マウス軸モードを設定
    DIPROPDWORD dipropword_m;
    dipropword_m.diph.dwSize = sizeof(dipropword_m);
    dipropword_m.diph.dwHeaderSize = sizeof(dipropword_m.diph);
    dipropword_m.diph.dwObj = 0;
    dipropword_m.diph.dwHow = DIPH_DEVICE;
    dipropword_m.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
    hr = _pIDirectInputDevice8_Mouse->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_( "軸モードの設定に失敗");
        return FALSE;
    }

    // マウスアクセス権取得
    if (_pIDirectInputDevice8_Mouse) {
        _pIDirectInputDevice8_Mouse->Acquire();
    }

    // キーボードデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pIDirectInputDevice8_Keyboard, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() キーボードデバイス作成に失敗しました"), TEXT("ERROR"), MB_OK
                | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // キーボード取得データフォーマットの設定
    hr = _pIDirectInputDevice8_Keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() キーボードのSetDataFormat に失敗しました"), TEXT("ERROR"),
                   MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // キーボード強調レベル設定
    hr = _pIDirectInputDevice8_Keyboard->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() キーボードのSetCooperativeLevelに失敗しました"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    /*
     //マウスバッファサイズの指定
     DIPROPDWORD dipropdword;
     dipropdword.diph.dwSize			= sizeof(DIPROPDWORD);
     dipropdword.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
     dipropdword.diph.dwObj			= 0;
     dipropdword.diph.dwHow			= DIPH_DEVICE;
     dipropdword.dwData				= GgafDxInput::BUFFER_SIZE;

     hr = _pIDirectInputDevice8_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDxGod::_pHWndPrimary,TEXT("GgafDxInput::initDx9Input() キーボードのSetPropertyに失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
     return hr;
     }
     */
    // キーボードアクセス権取得
    if (_pIDirectInputDevice8_Keyboard) {
        _pIDirectInputDevice8_Keyboard->Acquire();
    }


    // ゲームスティックを列挙してデバイスを得る
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, GgafDxInput::enumGameCtrlCallback, nullptr, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pIDirectInputDevice8_Joystick == nullptr) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices列挙しましたが、ジョイスティックが見つかりませんでした");
        _pIDirectInputDevice8_Joystick = nullptr;
    } else {
        _TRACE_("GgafDxInput::initDx9Input() ジョイスティックデバイス取得");

        // ゲームスティックのデータ形式を設定する
        hr = _pIDirectInputDevice8_Joystick->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックSetDataFormatに失敗しました");
            return FALSE;
        }

        // ゲームスティック協調レベルを設定する
        hr = _pIDirectInputDevice8_Joystick->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_FOREGROUND
                | DISCL_NONEXCLUSIVE );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
            return FALSE;
        }

        // ゲームスティックの軸データの範囲を設定する
        hr = _pIDirectInputDevice8_Joystick->EnumObjects(GgafDxInput::enumPadAxisCallback, nullptr, DIDFT_AXIS);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックEnumObjectsに失敗しました");
            return FALSE;
        }

        // 軸モードを設定
        DIPROPDWORD dipropword_j;
        dipropword_j.diph.dwSize = sizeof(dipropword_j);
        dipropword_j.diph.dwHeaderSize = sizeof(dipropword_j.diph);
        dipropword_j.diph.dwObj = 0;
        dipropword_j.diph.dwHow = DIPH_DEVICE;
        dipropword_j.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
        //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
        hr = _pIDirectInputDevice8_Joystick->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "軸モードの設定に失敗");
            return FALSE;
        }

        // ゲームスティックのアクセス権を取得する
        hr = _pIDirectInputDevice8_Joystick->Poll();
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックPollに失敗しました");
            do {
                hr = _pIDirectInputDevice8_Joystick->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return S_OK;
}

BOOL CALLBACK GgafDxInput::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("enumGameCtrlCallback こーるばっく！");

    HRESULT hr;

    // ゲームスティックデバイスを探すする
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pIDirectInputDevice8_Joystick, nullptr);
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    GgafDxInput::_didevcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDxInput::_didevcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        GgafDxInput::_pIDirectInputDevice8_Joystick->Release();
        return DIENUM_CONTINUE;
    }

    //生き残ればデバイス採用
    return DIENUM_STOP;
}

BOOL CALLBACK GgafDxInput::enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    _TRACE_("enumPadAxisCallback こーるばっく！");
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
        _TRACE_("enumPadAxisCallback ジョイスティックSetPropertyに失敗しました");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void GgafDxInput::updateMouseState() {
    if (_pIDirectInputDevice8_Mouse == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() nullptrっす");
        return;
    }

    _active_MouseState = !_active_MouseState; //ステートセットフリップ

    HRESULT hr;

again:
    hr = _pIDirectInputDevice8_Mouse->Poll(); //マウスは通常Poll不用と思うが呼び出しても無害と書いてあるので呼ぶ。
    hr = _pIDirectInputDevice8_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_dimousestate[_active_MouseState]);
    if (FAILED(hr)) {
        hr = _pIDirectInputDevice8_Mouse->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //ダメならまた次回へ
        }
    }
    return;
}



bool GgafDxInput::isBeingPressedMouseButton(int prm_button_no) {
    if (prm_button_no < 0 || 8 < prm_button_no) {
        _TRACE_("isBeingPressedMouseButton:範囲外");
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
    if (GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //今は押している
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!_active_MouseState]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_active_MouseState]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

bool GgafDxInput::isReleasedUpMouseButton(int prm_button_no) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //今は離している
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!_active_MouseState]も押されていた。成立。
            return true;
        } else {
            //前回セット[!_active_MouseState]は押されていない。離しっぱなし。
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::getMousePointer(long* x, long* y, long* z) {
    //マウスの移動
    *x = _dimousestate[_active_MouseState].lX;
    *y = _dimousestate[_active_MouseState].lY;
    //ホイールの状態
    *z = _dimousestate[_active_MouseState].lZ;
}
void GgafDxInput::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //マウスの移動
    *dx = _dimousestate[_active_MouseState].lX - _dimousestate[!_active_MouseState].lX;
    *dy = _dimousestate[_active_MouseState].lY - _dimousestate[!_active_MouseState].lY;
    //ホイールの状態
    *dz = _dimousestate[_active_MouseState].lZ - _dimousestate[!_active_MouseState].lZ;
}

void GgafDxInput::updateKeyboardState() {
    if (_pIDirectInputDevice8_Mouse == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() nullptrっす");
        return;
    }

    _active_KeyboardState = !_active_KeyboardState; //ステートセットフリップ

    HRESULT hr;
again:
    hr = _pIDirectInputDevice8_Keyboard->Poll(); //キーボードは通常Poll不用と思うが、必要なキーボードもあるかもしれない。
    hr = _pIDirectInputDevice8_Keyboard->GetDeviceState(256, (void*)&_caKeyboardState[_active_KeyboardState]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()を試みる。
        hr = _pIDirectInputDevice8_Keyboard->Acquire();
        if (hr == DI_OK) {
            //_TRACE_("Acquire is DI_OK");
            goto again;
        } else {
            //_TRACE_("Acquire is not DI_OK");
            //ダメならまた次回へ
        }
    }
    return;
}

bool GgafDxInput::isPushedDownKey(int prm_DIK) {
    if (GgafDxInput::isBeingPressedKey(prm_DIK)) { //今は押している
        if (_caKeyboardState[!_active_KeyboardState][prm_DIK] & 0x80) {
            //前回セット[!_active_KeyboardState]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_active_KeyboardState]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}
int GgafDxInput::getPushedDownKey() {
    int DIK_pressed = GgafDxInput::getBeingPressedKey();
    if (DIK_pressed >= 0 ) { //今は押している
        if (_caKeyboardState[!_active_KeyboardState][DIK_pressed] & 0x80) {
            //前回セット[!_active_KeyboardState]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!_active_KeyboardState]は押されていないのでOK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isReleasedUpDownKey(int prm_DIK) {
    if (!GgafDxInput::isBeingPressedKey(prm_DIK)) { //今は離している
        if (_caKeyboardState[!_active_KeyboardState][prm_DIK] & 0x80) {
            //前回セット[!_active_KeyboardState]は押されていた。成立
            return true;
        } else {
            //前回セット[!_active_KeyboardState]も押されていない。離しっぱなし。
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


    _active_JoyState = !_active_JoyState; //ステートセットフリップ

    // ジョイスティックの状態を取得
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
    if (GgafDxInput::isBeingPressedJoyRgbButton(prm_rgb_button_no)) { //今は押している
        if (_dijoystate[!_active_JoyState].rgbButtons[prm_rgb_button_no] & 0x80) {
            //前回セット[!_active_JoyState]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_active_JoyState]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

int GgafDxInput::getPushedDownJoyRgbButton() {
    int JOY_pressed = GgafDxInput::getBeingPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //今は押している
        if (_dijoystate[!_active_JoyState].rgbButtons[JOY_pressed] & 0x80) {
            //前回セット[!_active_JoyState]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!_active_JoyState]は押されていないのでOK
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
    //デバイス解放
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
