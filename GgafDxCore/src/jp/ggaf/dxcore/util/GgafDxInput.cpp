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
    // DirectInput の作成
    hr = DirectInput8Create(GgafDxGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() いきなりDirectInput8の作成に失敗しました。",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // マウスデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pMouseInputDevice, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() マウスデバイス作成に失敗しました",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス取得データフォーマットの設定
    hr = _pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() マウスのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス強調レベル設定
    hr = _pMouseInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() マウスのSetCooperativeLevelに失敗しました",
                 "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

//    if (GgafDxGod::_pHWndSecondary) {
//        // マウス強調レベル設定
//        hr = _pMouseInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndSecondary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//        if (hr != D3D_OK) {
//            MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() _pHWndSecondaryマウスのSetCooperativeLevelに失敗しました"),
//                       "ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
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
    hr = _pMouseInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_( "軸モードの設定に失敗");
        return FALSE;
    }

    // マウスアクセス権取得
    if (_pMouseInputDevice) {
        _pMouseInputDevice->Acquire();
    }

    // キーボードデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pKeyboardInputDevice, nullptr);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() キーボードデバイス作成に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード取得データフォーマットの設定
    hr = _pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() キーボードのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード強調レベル設定
    hr = _pKeyboardInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "GgafDxInput::initDx9Input() キーボードのSetCooperativeLevelに失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
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

     hr = _pKeyboardInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDxGod::_pHWndPrimary,"GgafDxInput::initDx9Input() キーボードのSetPropertyに失敗しました", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
     return hr;
     }
     */
    // キーボードアクセス権取得
    if (_pKeyboardInputDevice) {
        _pKeyboardInputDevice->Acquire();
    }


    // ゲームスティックを列挙してデバイスを得る
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, GgafDxInput::enumGameCtrlCallback, nullptr, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pJoystickInputDevice == nullptr) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices列挙しましたが、ジョイスティックが見つかりませんでした");
        _pJoystickInputDevice = nullptr;
    } else {
        _TRACE_("GgafDxInput::initDx9Input() ジョイスティックデバイス取得");

        // ゲームスティックのデータ形式を設定する
        hr = _pJoystickInputDevice->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックSetDataFormatに失敗しました");
            return FALSE;
        }

        // ゲームスティック協調レベルを設定する
        hr = _pJoystickInputDevice->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DISCL_FOREGROUND
                | DISCL_NONEXCLUSIVE );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
            return FALSE;
        }

        // ゲームスティックの軸データの範囲を設定する
        hr = _pJoystickInputDevice->EnumObjects(GgafDxInput::enumPadAxisCallback, nullptr, DIDFT_AXIS);
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
        hr = _pJoystickInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "軸モードの設定に失敗");
            return FALSE;
        }

        // ゲームスティックのアクセス権を取得する
        hr = _pJoystickInputDevice->Poll();
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックPollに失敗しました");
            do {
                hr = _pJoystickInputDevice->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return S_OK;
}

BOOL CALLBACK GgafDxInput::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("enumGameCtrlCallback こーるばっく！");

    HRESULT hr;

    // ゲームスティックデバイスを探すする
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pJoystickInputDevice, nullptr);
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    GgafDxInput::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pJoystickInputDevice->GetCapabilities( &GgafDxInput::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        GgafDxInput::_pJoystickInputDevice->Release();
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

    HRESULT hr = GgafDxInput::_pJoystickInputDevice->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
        _TRACE_("enumPadAxisCallback ジョイスティックSetPropertyに失敗しました");
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
    _flip_ms = !_flip_ms; //ステートセットフリップ
    HRESULT hr;
again:
    hr = _pMouseInputDevice->Poll(); //マウスは通常Poll不用と思うが呼び出しても無害と書いてあるので呼ぶ。
    hr = _pMouseInputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_mouse_state[_flip_ms]);
    if (FAILED(hr)) {
        hr = _pMouseInputDevice->Acquire();
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
        if (_mouse_state[_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isPushedDownMouseButton(int prm_button_no) {
    if (GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //今は押している
        if (_mouse_state[!_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!_flip_ms]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_flip_ms]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

bool GgafDxInput::isReleasedUpMouseButton(int prm_button_no) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_button_no)) { //今は離している
        if (_mouse_state[!_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!_flip_ms]も押されていた。成立。
            return true;
        } else {
            //前回セット[!_flip_ms]は押されていない。離しっぱなし。
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::getMousePointer(long* x, long* y, long* z) {
    //マウスの移動
    *x = _mouse_state[_flip_ms].lX;
    *y = _mouse_state[_flip_ms].lY;
    //ホイールの状態
    *z = _mouse_state[_flip_ms].lZ;
}

void GgafDxInput::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //マウスの移動
    *dx = _mouse_state[_flip_ms].lX - _mouse_state[!_flip_ms].lX;
    *dy = _mouse_state[_flip_ms].lY - _mouse_state[!_flip_ms].lY;
    //ホイールの状態
    *dz = _mouse_state[_flip_ms].lZ - _mouse_state[!_flip_ms].lZ;
}

void GgafDxInput::updateKeyboardState() {
#ifdef MY_DEBUG
    if (_pKeyboardInputDevice == nullptr) {
        _TRACE_("GgafDxInput::updateKeyboardState() _pKeyboardInputDevice == nullptr !!!!");
        return;
    }
#endif
    _flip_ks = !_flip_ks; //ステートセットフリップ
    HRESULT hr;
again:
    hr = _pKeyboardInputDevice->Poll(); //キーボードは通常Poll不用と思うが、必要なキーボードもあるかもしれない。
    hr = _pKeyboardInputDevice->GetDeviceState(256, (void*)&_keyboard_state[_flip_ks]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()を試みる。
        hr = _pKeyboardInputDevice->Acquire();
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
        if (_keyboard_state[!_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!_flip_ks]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_flip_ks]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}
int GgafDxInput::getPushedDownKey() {
    int DIK_pressed = GgafDxInput::getBeingPressedKey();
    if (DIK_pressed >= 0 ) { //今は押している
        if (_keyboard_state[!_flip_ks][DIK_pressed] & 0x80) {
            //前回セット[!_flip_ks]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!_flip_ks]は押されていないのでOK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isReleasedUpDownKey(int prm_DIK) {
    if (!GgafDxInput::isBeingPressedKey(prm_DIK)) { //今は離している
        if (_keyboard_state[!_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!_flip_ks]は押されていた。成立
            return true;
        } else {
            //前回セット[!_flip_ks]も押されていない。離しっぱなし。
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
    _flip_js = !_flip_js; //ステートセットフリップ
    // ジョイスティックの状態を取得
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
    if (GgafDxInput::isBeingPressedJoyRgbButton(prm_rgb_button_no)) { //今は押している
        if (_joy_state[!_flip_js].rgbButtons[prm_rgb_button_no] & 0x80) {
            //前回セット[!_flip_js]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!_flip_js]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

int GgafDxInput::getPushedDownJoyRgbButton() {
    int JOY_pressed = GgafDxInput::getBeingPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //今は押している
        if (_joy_state[!_flip_js].rgbButtons[JOY_pressed] & 0x80) {
            //前回セット[!_flip_js]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!_flip_js]は押されていないのでOK
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
    //デバイス解放
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
