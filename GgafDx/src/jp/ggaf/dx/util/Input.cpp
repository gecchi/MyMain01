#include "jp/ggaf/dx/util/Input.h"

#include "jp/ggaf/dx/Caretaker.h"

#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

//const int Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 Input::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pJoystickInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 Input::_di_mouse_state[2];
int  Input::_flip_ms = 0;

BYTE Input::_keyboard_state[2][256];
int Input::_flip_ks = 0;
DIDEVCAPS Input::_devcap;
DIJOYSTATE Input::_joy_state[2];
int Input::_flip_js = 0;

Input::MouseState Input::_win_mouse_state[2];

HRESULT Input::init() {
    if (Input::_pIDirectInput8) {
        //生成済み
    } else {
        HRESULT hr;
        // DirectInput の作成
        hr = DirectInput8Create(
                 pCARETAKER->_hInstance,
                 DIRECTINPUT_VERSION,
                 IID_IDirectInput8,
                 (LPVOID*)&Input::_pIDirectInput8,
                 nullptr
             );
        if (hr != D3D_OK) {
            MessageBox(pCARETAKER->_pHWndPrimary, "いきなりDirectInput8の作成に失敗しました。",
                       "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
            return hr;
        }

        hr = Input::initKeybord();
        if (hr == D3D_OK) {
            hr = Input::initMouse();
            hr = Input::initJoyStick();
        } else {
            MessageBox(pCARETAKER->_pHWndPrimary, "キーボードデバイスの初期化に失敗しました。",
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
        //取得済み
        Input::_pMouseInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pMouseInputDevice);
        return FALSE;
    }
    HRESULT hr;
    // マウスデバイスの作成
    hr = Input::_pIDirectInput8->CreateDevice(
                                           GUID_SysMouse,
                                           &Input::_pMouseInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "マウスデバイス作成に失敗しました",
                "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス取得データフォーマットの設定
    hr = Input::_pMouseInputDevice->SetDataFormat(&c_dfDIMouse2);
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "マウスのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }
    // マウス強調レベル設定
    hr = Input::_pMouseInputDevice->SetCooperativeLevel(
                                              pCARETAKER->_pHWndPrimary,
                                              DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                          );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "マウスのSetCooperativeLevelに失敗しました",
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
    hr = Input::_pMouseInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_m.diph);
    if (hr != D3D_OK) {
        _TRACE_("【警告】軸モードの設定に失敗");
        return FALSE;
    }

    // マウスアクセス権取得
    if (Input::_pMouseInputDevice) {
        Input::_pMouseInputDevice->Acquire();
    }
    _TRACE_("マウスデバイス取得OK");
    return D3D_OK;
}


HRESULT Input::initKeybord() {
    if (!Input::_pIDirectInput8) {
        Input::init();
    }
    if (Input::_pKeyboardInputDevice) {
        //取得済み
        Input::_pKeyboardInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pKeyboardInputDevice);
    }
    HRESULT hr;
    // キーボードデバイスの作成
    hr = Input::_pIDirectInput8->CreateDevice(
                                           GUID_SysKeyboard,
                                           &Input::_pKeyboardInputDevice,
                                           nullptr
                                       );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "キーボードデバイス作成に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード取得データフォーマットの設定
    hr = Input::_pKeyboardInputDevice->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "キーボードのSetDataFormat に失敗しました",
                   "ERROR", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST);
        return hr;
    }

    // キーボード強調レベル設定
    hr = Input::_pKeyboardInputDevice->SetCooperativeLevel(
                                                 pCARETAKER->_pHWndPrimary,
                                                 DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
                                             );
    if (hr != D3D_OK) {
        MessageBox(pCARETAKER->_pHWndPrimary, "キーボードのSetCooperativeLevelに失敗しました",
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
     dipropdword.dwData				= Input::BUFFER_SIZE;

     hr = Input::_pKeyboardInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(pCARETAKER->_pHWndPrimary,"キーボードのSetPropertyに失敗しました", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND |MB_TOPMOST);
     return hr;
     }
     */
    // キーボードアクセス権取得
    if (Input::_pKeyboardInputDevice) {
        Input::_pKeyboardInputDevice->Acquire();
    }
    _TRACE_("キーボードデバイス取得OK");
    return D3D_OK;
}
HRESULT Input::initJoyStick() {
    if (!Input::_pIDirectInput8) {
        Input::init();
    }
    if (Input::_pJoystickInputDevice) {
        //取得済み
        Input::_pJoystickInputDevice->Unacquire();
        GGAF_RELEASE(Input::_pJoystickInputDevice);
    }
    HRESULT hr;
    // ゲームスティックを列挙してデバイスを得る
    hr = Input::_pIDirectInput8->EnumDevices(
                                           DI8DEVCLASS_GAMECTRL,
                                           Input::enumGameCtrlCallback,
                                           nullptr,
                                           DIEDFL_ATTACHEDONLY
                                       );
    if (hr != D3D_OK || Input::_pJoystickInputDevice == nullptr) {
        _TRACE_("ジョイスティックが見つかりません");
        Input::_pJoystickInputDevice = nullptr;
        return FALSE;
    } else {
        _TRACE_("ジョイスティックデバイス取得");

        // ゲームスティックのデータ形式を設定する
        hr = Input::_pJoystickInputDevice->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("ジョイスティックSetDataFormatに失敗しました");
            return FALSE;
        }

        // ゲームスティック協調レベルを設定する
        hr = Input::_pJoystickInputDevice->SetCooperativeLevel(
                                                     pCARETAKER->_pHWndPrimary,
                                                     DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
                                                 );
        if (hr != D3D_OK) {
            _TRACE_("ジョイスティックSetCooperativeLevelに失敗しました");
            return FALSE;
        }

        // ゲームスティックの軸データの範囲を設定する
        hr = Input::_pJoystickInputDevice->EnumObjects(
                                                     Input::enumPadAxisCallback,
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
        hr = Input::_pJoystickInputDevice->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
        if (hr != D3D_OK) {
            _TRACE_( "軸モードの設定に失敗");
            return FALSE;
        }

        // ゲームスティックのアクセス権を取得する
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
    // ゲームスティックデバイスを探す
    hr = Input::_pIDirectInput8->CreateDevice(
                                           pDIDeviceInstance->guidInstance,
                                           &Input::_pJoystickInputDevice,
                                           nullptr
                                       );
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    Input::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = Input::_pJoystickInputDevice->GetCapabilities( &Input::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        Input::_pJoystickInputDevice->Release();
        return DIENUM_CONTINUE;
    }

    //生き残ればデバイス採用
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
        _TRACE_("enumPadAxisCallback ジョイスティックSetPropertyに失敗しました");
        return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

void Input::updateMouseState() {
#ifdef MY_DEBUG
    if (Input::_pMouseInputDevice == nullptr) {
        _TRACE_("【警告】 Input::updateKeyboardState() Input::_pMouseInputDevice == nullptr !!!!");
        return;
    }
#endif
    Input::_flip_ms ^= 1; //ステートセットフリップ
    HRESULT hr;
again:
    hr = Input::_pMouseInputDevice->Poll(); //マウスは通常Poll不用と思うが呼び出しても無害と書いてあるので呼ぶ。
    hr = Input::_pMouseInputDevice->GetDeviceState(
                                              sizeof(DIMOUSESTATE2),
                                              (void*)&Input::_di_mouse_state[Input::_flip_ms]
                                          );
    if (FAILED(hr)) {
        hr = Input::_pMouseInputDevice->Acquire();
        if (hr == DI_OK) {
            goto again;
        } else {
            //ダメならまた次回へ
        }
    }
    Input::MouseState& s = Input::_win_mouse_state[Input::_flip_ms];
    s.buttons[0] = GetAsyncKeyState(VK_LBUTTON);
    s.buttons[1] = GetAsyncKeyState(VK_RBUTTON);
    s.buttons[2] = GetAsyncKeyState(VK_MBUTTON);
    return;
}


//bool Input::isPressedMouseButton_old(int prm_button_no) {
//    if (prm_button_no < 0 || 8 < prm_button_no) {
//        _TRACE_("isPressedMouseButton:範囲外");
//        return false;
//    } else {
//        if (Input::_di_mouse_state[Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

bool Input::isPressedMouseButton(int prm_button_no) {
#ifdef MY_DEBUG
    if (prm_button_no < 0 || 8 < prm_button_no) {
        throwCriticalException("Input::isPressedMouseButton() 範囲外です prm_button_no="<<prm_button_no);
    }
#endif
    return Input::_win_mouse_state[Input::_flip_ms].buttons[prm_button_no];
}


//bool Input::isPushedDownMouseButton_old(int prm_button_no) {
//    if (Input::isPressedMouseButton(prm_button_no)) { //今は押している
//        if (Input::_di_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            //前回セット[!Input::_flip_ms]も押されている。押しっぱなし
//            return false;
//        } else {
//            //前回セット[!Input::_flip_ms]は押されていないのでOK
//            return true;
//        }
//    } else {
//        return false;
//    }
//}

bool Input::isPushedDownMouseButton(int prm_button_no) {
    if (Input::isPressedMouseButton(prm_button_no)) { //今は押している
        if (Input::_win_mouse_state[!Input::_flip_ms].buttons[prm_button_no]) {
            //前回セット[!Input::_flip_ms]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!Input::_flip_ms]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}


//
//bool Input::isReleasedUpMouseButton_old(int prm_button_no) {
//    if (!Input::isPressedMouseButton(prm_button_no)) { //今は離している
//        if (Input::_di_mouse_state[!Input::_flip_ms].rgbButtons[prm_button_no] & 0x80) {
//            //前回セット[!Input::_flip_ms]も押されていた。成立。
//            return true;
//        } else {
//            //前回セット[!Input::_flip_ms]は押されていない。離しっぱなし。
//            return false;
//        }
//    } else {
//        return false;
//    }
//}

bool Input::isReleasedUpMouseButton(int prm_button_no) {
    if (!Input::isPressedMouseButton(prm_button_no)) { //今は離している
        if (Input::_win_mouse_state[!Input::_flip_ms].buttons[prm_button_no]) {
            //前回セット[!Input::_flip_ms]も押されていた。成立。
            return true;
        } else {
            //前回セット[!Input::_flip_ms]は押されていない。離しっぱなし。
            return false;
        }
    } else {
        return false;
    }
}


void Input::getMousePointer(long* x, long* y, long* z) {
    //マウスの移動
    *x = Input::_di_mouse_state[Input::_flip_ms].lX;
    *y = Input::_di_mouse_state[Input::_flip_ms].lY;
    //ホイールの状態
    *z = Input::_di_mouse_state[Input::_flip_ms].lZ;
}

void Input::getMousePointer_REL(long* dx, long* dy, long* dz) {
    //マウスの移動
    *dx = Input::_di_mouse_state[Input::_flip_ms].lX - Input::_di_mouse_state[!Input::_flip_ms].lX;
    *dy = Input::_di_mouse_state[Input::_flip_ms].lY - Input::_di_mouse_state[!Input::_flip_ms].lY;
    //ホイールの状態
    *dz = Input::_di_mouse_state[Input::_flip_ms].lZ - Input::_di_mouse_state[!Input::_flip_ms].lZ;
}

void Input::updateKeyboardState() {
#ifdef MY_DEBUG
    if (Input::_pKeyboardInputDevice == nullptr) {
        throwCriticalException("Input::_pKeyboardInputDevice==nullptr");
    }
#endif
    Input::_flip_ks ^= 1;
    HRESULT hr;
again:
    hr = Input::_pKeyboardInputDevice->Poll(); //キーボードは通常Poll不用と思うが、必要なキーボードもあるかもしれない。
    hr = Input::_pKeyboardInputDevice->GetDeviceState(
                                                 256,
                                                 (void*)&Input::_keyboard_state[Input::_flip_ks]
                                             );
    if (FAILED(hr)) {
        //_TRACE_("GetDeviceState is FAILED");
        //Acquire()を試みる。
        hr = Input::_pKeyboardInputDevice->Acquire();
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

bool Input::isPushedDownKey(int prm_DIK) {
    if (Input::isPressedKey(prm_DIK)) { //今は押している
        if (Input::_keyboard_state[!Input::_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!Input::_flip_ks]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!Input::_flip_ks]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}
int Input::getFirstPushedDownKey() {
    int DIK_pressed = Input::getFirstPressedKey();
    if (DIK_pressed >= 0 ) { //今は押している
        if (Input::_keyboard_state[!Input::_flip_ks][DIK_pressed] & 0x80) {
            //前回セット[!Input::_flip_ks]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!Input::_flip_ks]は押されていないのでOK
            return DIK_pressed;
        }
    } else {
        return -1;
    }
}


bool Input::isReleasedUpKey(int prm_DIK) {
    if (!Input::isPressedKey(prm_DIK)) { //今は離している
        if (Input::_keyboard_state[!Input::_flip_ks][prm_DIK] & 0x80) {
            //前回セット[!Input::_flip_ks]は押されていた。成立
            return true;
        } else {
            //前回セット[!Input::_flip_ks]も押されていない。離しっぱなし。
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
    // ジョイスティックの状態を取得
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
    if (Input::isPressedJoyButton(prm_joy_button_no)) { //今は押している
        if (Input::_joy_state[!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) {
            //前回セット[!Input::_flip_js]も押されている。押しっぱなし
            return false;
        } else {
            //前回セット[!Input::_flip_js]は押されていないのでOK
            return true;
        }
    } else {
        return false;
    }
}

int Input::getFirstPushedDownJoyRgbButton() {
    int JOY_pressed = Input::getFirstPressedJoyRgbButton();
    if (JOY_pressed >= 0 ) { //今は押している
        if (Input::_joy_state[!Input::_flip_js].rgbButtons[JOY_pressed] & 0x80) {
            //前回セット[!Input::_flip_js]も押されている。押しっぱなし
            return -1;
        } else {
            //前回セット[!Input::_flip_js]は押されていないのでOK
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
    if (Input::_pJoystickInputDevice) { //JoyStickが無い場合、rgdwPOV[0]=0のため、上と判定されることを防ぐ
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
        //ジョイスティックが刺さってない
        return 5;
    }
}


void Input::release() {
    //デバイス解放
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
