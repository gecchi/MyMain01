#include "jp/ggaf/dxcore/util/GgafDxInput.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
using namespace GgafCore;
using namespace GgafDxCore;

//const int GgafDxInput::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDxInput::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pJoystickInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 GgafDxInput::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 GgafDxInput::_mouse_state[2];
int  GgafDxInput::_flip_ms = 0;

BYTE GgafDxInput::_keyboard_state[2][256];
int GgafDxInput::_flip_ks = 0;
DIDEVCAPS GgafDxInput::_devcap;
DIJOYSTATE GgafDxInput::_joy_state[2];
int GgafDxInput::_flip_js = 0;


HRESULT GgafDxInput::init() {
    if (GgafDxInput::_pIDirectInput8) {
        //生成済み
    } else {
        HRESULT hr;
        // DirectInput の作成
        hr = DirectInput8Create(
                 GgafDxGod::_hInstance,
                 DIRECTINPUT_VERSION,
                 IID_IDirectInput8,
                 (LPVOID*)&GgafDxInput::_pIDirectInput8,
                 nullptr
             );
        if (hr != D3D_OK) {
            MessageBox(GgafDxGod::_pHWndPrimary, "いきなりDirectInput8の作成に失敗しました。",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }

        hr = GgafDxInput::initKeybord();
        if (hr == D3D_OK) {
            hr = GgafDxInput::initMouse();
            hr = GgafDxInput::initJoyStick();
        } else {
            MessageBox(GgafDxGod::_pHWndPrimary, "キーボードデバイスの初期化に失敗しました。",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }
    }
    return D3D_OK;
}

HRESULT GgafDxInput::initMouse() {
    if (!GgafDxInput::_pIDirectInput8) {
        GgafDxInput::init();
    }
    if (GgafDxInput::_pMouseInputDevice) {
        //取得済み
        GgafDxInput::_pMouseInputDevice->Unacquire();
        GGAF_RELEASE(GgafDxInput::_pMouseInputDevice);
        return FALSE;
    }
    HRESULT hr;
    // マウスデバイスの作成
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(
                                           GUID_SysMouse,
                                           &GgafDxInput::_pMouseInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "マウスデバイス作成に失敗しました",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス取得データフォーマットの設定
    hr = GgafDxInput::_pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "マウスのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス強調レベル設定
    hr = GgafDxInput::_pMouseInputDevice->SetCooperativeLevel(
                                              GgafDxGod::_pHWndPrimary,
                                              DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                          );
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "マウスのSetCooperativeLevelに失敗しました",
                 "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // マウス軸モードを設定
    DIPROPDWORD dipropword_m;
    dipropword_m.diph.dwSize = sizeof(dipropword_m);
    dipropword_m.diph.dwHeaderSize = sizeof(dipropword_m.diph);
    dipropword_m.diph.dwObj = 0;
    dipropword_m.diph.dwHow = DIPH_DEVICE;
    dipropword_m.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
    //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
    hr = GgafDxInput::_pMouseInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_("＜警告＞軸モードの設定に失敗");
        return FALSE;
    }

    // マウスアクセス権取得
    if (GgafDxInput::_pMouseInputDevice) {
        GgafDxInput::_pMouseInputDevice->Acquire();
    }
    _TRACE_("マウスデバイス取得OK");
    return D3D_OK;
}


HRESULT GgafDxInput::initKeybord() {
    if (!GgafDxInput::_pIDirectInput8) {
        GgafDxInput::init();
    }
    if (GgafDxInput::_pKeyboardInputDevice) {
        //取得済み
        GgafDxInput::_pKeyboardInputDevice->Unacquire();
        GGAF_RELEASE(GgafDxInput::_pKeyboardInputDevice);
    }
    HRESULT hr;
    // キーボードデバイスの作成
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(
                                           GUID_SysKeyboard,
                                           &GgafDxInput::_pKeyboardInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "キーボードデバイス作成に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード取得データフォーマットの設定
    hr = GgafDxInput::_pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "キーボードのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード強調レベル設定
    hr = GgafDxInput::_pKeyboardInputDevice->SetCooperativeLevel(
                                                 GgafDxGod::_pHWndPrimary,
                                                 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                             );
    if (hr != D3D_OK) {
        MessageBox(GgafDxGod::_pHWndPrimary, "キーボードのSetCooperativeLevelに失敗しました",
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

     hr = GgafDxInput::_pKeyboardInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDxGod::_pHWndPrimary,"キーボードのSetPropertyに失敗しました", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
     return hr;
     }
     */
    // キーボードアクセス権取得
    if (GgafDxInput::_pKeyboardInputDevice) {
        GgafDxInput::_pKeyboardInputDevice->Acquire();
    }
    _TRACE_("キーボードデバイス取得OK");
    return D3D_OK;
}
HRESULT GgafDxInput::initJoyStick() {
    if (!GgafDxInput::_pIDirectInput8) {
        GgafDxInput::init();
    }
    if (GgafDxInput::_pJoystickInputDevice) {
        //取得済み
        GgafDxInput::_pJoystickInputDevice->Unacquire();
        GGAF_RELEASE(GgafDxInput::_pJoystickInputDevice);
    }
    HRESULT hr;
    // ゲームスティックを列挙してデバイスを得る
    hr = GgafDxInput::_pIDirectInput8->EnumDevices(
                                           DI8DEVCLASS_GAMECTRL,
                                           GgafDxInput::enumGameCtrlCallback,
                                           nullptr,
                                           DIEDFL_ATTACHEDONLY
                                       );
    if (hr != D3D_OK || GgafDxInput::_pJoystickInputDevice == nullptr) {
        _TRACE_("ジョイスティックが見つかりません");
        GgafDxInput::_pJoystickInputDevice = nullptr;
        return FALSE;
    } else {
        _TRACE_("ジョイスティックデバイス取得");

        // ゲームスティックのデータ形式を設定する
        hr = GgafDxInput::_pJoystickInputDevice->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("ジョイスティックSetDataFormatに失敗しました");
            return FALSE;
        }

        // ゲームスティック協調レベルを設定する
        hr = GgafDxInput::_pJoystickInputDevice->SetCooperativeLevel(
                                                     GgafDxGod::_pHWndPrimary,
                                                     DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
                                                 );
        if (hr != D3D_OK) {
            _TRACE_("ジョイスティックSetCooperativeLevelに失敗しました");
            return FALSE;
        }

        // ゲームスティックの軸データの範囲を設定する
        hr = GgafDxInput::_pJoystickInputDevice->EnumObjects(
                                                     GgafDxInput::enumPadAxisCallback,
                                                     nullptr,
                                                     DIDFT_AXIS
                                                 );
        if (hr != D3D_OK) {
            _TRACE_("ジョイスティックEnumObjectsに失敗しました");
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
        hr = GgafDxInput::_pJoystickInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "軸モードの設定に失敗");
            return FALSE;
        }

        // ゲームスティックのアクセス権を取得する
        hr = GgafDxInput::_pJoystickInputDevice->Poll();
        if (hr != D3D_OK) {
            do {
                hr = GgafDxInput::_pJoystickInputDevice->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return D3D_OK;
}

BOOL CALLBACK GgafDxInput::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("call back");
    HRESULT hr;
    // ゲームスティックデバイスを探す
    hr = GgafDxInput::_pIDirectInput8->CreateDevice(
                                           pDIDeviceInstance->guidInstance,
                                           &GgafDxInput::_pJoystickInputDevice,
                                           nullptr
                                       );
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
    _TRACE_("call back");
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
    if (GgafDxInput::_pMouseInputDevice == nullptr) {
        _TRACE_("＜警告＞ GgafDxInput::updateKeyboardState() GgafDxInput::_pMouseInputDevice == nullptr !!!!");
        return;
    }
#endif
    GgafDxInput::_flip_ms = !GgafDxInput::_flip_ms; //ステートセットフリップ
    HRESULT hr;
again:
    hr = GgafDxInput::_pMouseInputDevice->Poll(); //マウスは通常Poll不用と思うが呼び出しても無害と書いてあるので呼ぶ。
    hr = GgafDxInput::_pMouseInputDevice->GetDeviceState(
                                              sizeof(DIMOUSESTATE2),
                                              (void*)&GgafDxInput::_mouse_state[GgafDxInput::_flip_ms]
                                          );
    if (FAILED(hr)) {
        hr = GgafDxInput::_pMouseInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //ダメならまた次回へ
        }
    }
    return;
}


bool GgafDxInput::isPressedMouseButton(int prm_button_no) {
    if (prm_button_no < 0 || 8 < prm_button_no) {
        _TRACE_("isPressedMouseButton:範囲外");
        return false;
    } else {
        if (GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

bool GgafDxInput::isPushedDownMouseButton(int prm_button_no) {
    if (GgafDxInput::isPressedMouseButton(prm_button_no)) { //今は押している
        if (GgafDxInput::_mouse_state[!GgafDxInput::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!GgafDxInput::_flip_ms]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!GgafDxInput::_flip_ms]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

bool GgafDxInput::isReleasedUpMouseButton(int prm_button_no) {
    if (!GgafDxInput::isPressedMouseButton(prm_button_no)) { //今は離している
        if (GgafDxInput::_mouse_state[!GgafDxInput::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
            //前回セット[!GgafDxInput::_flip_ms]も押されていた。成立。
            return true;
        } else {
            //前回セット[!GgafDxInput::_flip_ms]は押されていない。離しっぱなし。
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::getMousePointer(long* x, long* y, long* z) {
    //マウスの移動
    *x = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lX;
    *y = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lY;
    //ホイールの状態
    *z = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lZ;
}

void GgafDxInput::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //マウスの移動
    *dx = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lX - GgafDxInput::_mouse_state[!GgafDxInput::_flip_ms].lX;
    *dy = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lY - GgafDxInput::_mouse_state[!GgafDxInput::_flip_ms].lY;
    //ホイールの状態
    *dz = GgafDxInput::_mouse_state[GgafDxInput::_flip_ms].lZ - GgafDxInput::_mouse_state[!GgafDxInput::_flip_ms].lZ;
}

void GgafDxInput::updateKeyboardState() {
#ifdef MY_DEBUG
    if (GgafDxInput::_pKeyboardInputDevice == nullptr) {
        _TRACE_("GgafDxInput::_pKeyboardInputDevice==nullptr !!!!");
        return;
    }
#endif
    GgafDxInput::_flip_ks = !GgafDxInput::_flip_ks; //ステートセットフリップ
    HRESULT hr;
again:
    hr = GgafDxInput::_pKeyboardInputDevice->Poll(); //キーボードは通常Poll不用と思うが、必要なキーボードもあるかもしれない。
    hr = GgafDxInput::_pKeyboardInputDevice->GetDeviceState(
                                                 256,
                                                 (void*)&GgafDxInput::_keyboard_state[GgafDxInput::_flip_ks]
                                             );
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()を試みる。
        hr = GgafDxInput::_pKeyboardInputDevice->Acquire();
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
    if (GgafDxInput::isPressedKey(prm_DIK)) { //今は押している
        if (GgafDxInput::_keyboard_state[!GgafDxInput::_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!GgafDxInput::_flip_ks]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!GgafDxInput::_flip_ks]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}
int GgafDxInput::getPushedDownKey() {
    int DIK_pressed = GgafDxInput::getPressedKey();
    if (DIK_pressed >= 0 ) { //今は押している
        if (GgafDxInput::_keyboard_state[!GgafDxInput::_flip_ks][DIK_pressed] & 0x80) {
            //前回セット[!GgafDxInput::_flip_ks]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!GgafDxInput::_flip_ks]は押されていないのでOK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool GgafDxInput::isReleasedUpKey(int prm_DIK) {
    if (!GgafDxInput::isPressedKey(prm_DIK)) { //今は離している
        if (GgafDxInput::_keyboard_state[!GgafDxInput::_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!GgafDxInput::_flip_ks]は押されていた。成立
            return true;
        } else {
            //前回セット[!GgafDxInput::_flip_ks]も押されていない。離しっぱなし。
            return false;
        }
    } else {
        return false;
    }
}

void GgafDxInput::updateJoystickState() {
    if (GgafDxInput::_pJoystickInputDevice == nullptr) {
        return;
    }
    GgafDxInput::_flip_js = !GgafDxInput::_flip_js; //ステートセットフリップ
    // ジョイスティックの状態を取得
    HRESULT hr;

again1:
    hr = GgafDxInput::_pJoystickInputDevice->Poll();
    if (hr != DI_OK) {
        hr = GgafDxInput::_pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again1;
        } else {
        }
    }

again2:
    hr = GgafDxInput::_pJoystickInputDevice->GetDeviceState(
                                                 sizeof(DIJOYSTATE),
                                                 &GgafDxInput::_joy_state[GgafDxInput::_flip_js]
                                             );
    if (hr != DI_OK) {
        hr = GgafDxInput::_pJoystickInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again2;
        } else {
        }
    }

//    _TRACE_("lX="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX);
//    _TRACE_("lY="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lY);
//    _TRACE_("lZ="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lZ);
//    _TRACE_("lRx="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lRx);
//    _TRACE_("lRy="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lRy);
//    _TRACE_("lRz="<<GgafDxInput::_joy_state[GgafDxInput::_flip_js].lRz);
}

bool GgafDxInput::isPushedDownJoyRgbButton(int prm_joy_button_no) {
    if (GgafDxInput::isPressedJoyButton(prm_joy_button_no)) { //今は押している
        if (GgafDxInput::_joy_state[!GgafDxInput::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) {
            //前回セット[!GgafDxInput::_flip_js]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!GgafDxInput::_flip_js]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

int GgafDxInput::getPushedDownJoyRgbButton() {
    int JOY_pressed = GgafDxInput::getPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //今は押している
        if (GgafDxInput::_joy_state[!GgafDxInput::_flip_js].rgbButtons[JOY_pressed] & 0x80) {
            //前回セット[!GgafDxInput::_flip_js]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!GgafDxInput::_flip_js]は押されていないのでOK
            return JOY_pressed;
        }
    } else {
        return -1;
    }
}


int GgafDxInput::getPressedJoyDirection() {
    if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lY < -127) {
        if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX > 127) {
            return 9;
        } else if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX < -127) {
            return 7;
        } else {
            return 8;
        }
    } else if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lY > 127) {
        if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX > 127) {
            return 3;
        } else if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX < -127) {
            return 1;
        } else {
            return 2;
        }
    } else if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX > 127) {
        return 6;
    } else if (GgafDxInput::_joy_state[GgafDxInput::_flip_js].lX < -127) {
        return 4;
    } else {
        return 5;
    }
}


int GgafDxInput::getPressedPovDirection() {
    if (GgafDxInput::_pJoystickInputDevice) { //JoyStickが無い場合、rgdwPOV[0]=0のため、上と判定されることを防ぐ
        DWORD n = GgafDxInput::_joy_state[GgafDxInput::_flip_js].rgdwPOV[0];
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
        //ジョイスティックが刺さってない
        return 5;
    }
}


void GgafDxInput::release() {
    //デバイス解放
    if (GgafDxInput::_pIDirectInput8) {
        if (GgafDxInput::_pKeyboardInputDevice) {
            GgafDxInput::_pKeyboardInputDevice->Unacquire();
            GGAF_RELEASE(GgafDxInput::_pKeyboardInputDevice);
        }
        if (GgafDxInput::_pJoystickInputDevice) {
            GgafDxInput::_pJoystickInputDevice->Unacquire();
            GGAF_RELEASE(GgafDxInput::_pJoystickInputDevice);
        }
        if (GgafDxInput::_pMouseInputDevice) {
            GgafDxInput::_pMouseInputDevice->Unacquire();
            GGAF_RELEASE(GgafDxInput::_pMouseInputDevice);
        }
        GGAF_RELEASE(GgafDxInput::_pIDirectInput8);
    }
}
