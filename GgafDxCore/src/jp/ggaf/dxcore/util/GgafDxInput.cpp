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
    _TRACE_("EnumGameCtrlCallback こーるばっく！");

    HRESULT hr;

    // ゲームスティックデバイスを探すする
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDxInput::_pIDirectInputDevice8_Joystick, NULL);
    if(hr != D3D_OK) {
        _TRACE_("EnumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    GgafDxInput::_didevcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDxInput::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDxInput::_didevcap );
    if( hr != D3D_OK ) {
        _TRACE_("EnumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        GgafDxInput::_pIDirectInputDevice8_Joystick->Release();
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
        _TRACE_("EnumPadAxisCallback ジョイスティックSetPropertyに失敗しました");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

GgafDxInput::GgafDxInput() {
    TRACE("GgafDxInput::GgafDxInput(HWND prm_pHWndPrimary) ");
}

HRESULT GgafDxInput::init() {

    HRESULT hr;
    // DirectInput の作成
    hr = DirectInput8Create(GgafDxGod::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, NULL);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT("GgafDxInput::initDx9Input() いきなりDirectInput8の作成に失敗しました。も～やる気もなくなりますわ；"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        return hr;
    }

    // マウスデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysMouse, &_pIDirectInputDevice8_Mouse, NULL);
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
    DIPROPDWORD dipropword;
    dipropword.diph.dwSize = sizeof(dipropword);
    dipropword.diph.dwHeaderSize = sizeof(dipropword.diph);
    dipropword.diph.dwObj = 0;
    dipropword.diph.dwHow = DIPH_DEVICE;
    dipropword.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
    hr = _pIDirectInputDevice8_Mouse->SetProperty(DIPROP_AXISMODE, &dipropword.diph);
    if (hr != D3D_OK) {
        _TRACE_( "軸モードの設定に失敗");
        return FALSE;
    }

    // マウスアクセス権取得
    if (_pIDirectInputDevice8_Mouse) {
        _pIDirectInputDevice8_Mouse->Acquire();
    }


    // キーボードデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pIDirectInputDevice8_Keyboard, NULL);
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
     //ばふぁなぞいらんｗ
     // バッファサイズの指定
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
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGameCtrlCallback, NULL, DIEDFL_ATTACHEDONLY);
    if (hr != D3D_OK || _pIDirectInputDevice8_Joystick == NULL) {
        _TRACE_("GgafDxInput::initDx9Input() EnumDevices列挙しましたが、でジョイスティックが見つかりませんでした");
        _pIDirectInputDevice8_Joystick = NULL;
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
        hr = _pIDirectInputDevice8_Joystick->EnumObjects(EnumPadAxisCallback, NULL, DIDFT_AXIS);
        if (hr != D3D_OK) {
            _TRACE_("GgafDxInput::initDx9Input() ジョイスティックEnumObjectsに失敗しました");
            return FALSE;
        }

        // 軸モードを設定
        DIPROPDWORD dipropword;
        dipropword.diph.dwSize = sizeof(dipropword);
        dipropword.diph.dwHeaderSize = sizeof(dipropword.diph);
        dipropword.diph.dwObj = 0;
        dipropword.diph.dwHow = DIPH_DEVICE;
        dipropword.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
        //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
        hr = _pIDirectInputDevice8_Joystick->SetProperty(DIPROP_AXISMODE, &dipropword.diph);
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


void GgafDxInput::updateMouseState() {
    if (_pIDirectInputDevice8_Mouse == NULL) {
        _TRACE_("GgafDxInput::updateKeyboardState() NULLっす");
        return;
    }

    _active_MouseState = !_active_MouseState; //ステートセットフリップ

    HRESULT hr;

again:
    hr = _pIDirectInputDevice8_Mouse->Poll(); //マウスは通常Poll不用と思うが呼び出しても無害と書いてあるので呼ぶ。
    hr = _pIDirectInputDevice8_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)&_dimousestate[_active_MouseState]);
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()を試みる。
        hr = _pIDirectInputDevice8_Mouse->Acquire();
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



bool GgafDxInput::isBeingPressedMouseButton(int prm_iButtonNo) {
    if (prm_iButtonNo < 0 || 8 < prm_iButtonNo) {
        _TRACE_("isBeingPressedMouseButton:範囲外");
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
    if (GgafDxInput::isBeingPressedMouseButton(prm_iButtonNo)) { //今は押している
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_iButtonNo] & 0x80) {
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

bool GgafDxInput::isReleasedUpMouseButton(int prm_iButtonNo) {
    if (!GgafDxInput::isBeingPressedMouseButton(prm_iButtonNo)) { //今は離している
        if (_dimousestate[!_active_MouseState].rgbButtons[prm_iButtonNo] & 0x80) {
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
    if (_pIDirectInputDevice8_Mouse == NULL) {
        _TRACE_("GgafDxInput::updateKeyboardState() NULLっす");
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

bool GgafDxInput::isBeingPressedKey(int prm_DIK) {
    if (prm_DIK < 0 || 255 < prm_DIK) {
        _TRACE_("isBeingPressedKey:範囲外");
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
    if (_pIDirectInputDevice8_Joystick == NULL) {
        return;
    }

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
        _TRACE_("isBeingPressedJoyRgbButton:範囲外");
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
    //デバイス解放
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
