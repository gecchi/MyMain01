#include "jp/ggaf/dx/util/Input.h"

#include "jp/ggaf/dx/Caretaker.h"

#include "jp/ggaf/dx/exception/CriticalException.h"

using namespace GgafDx;

//const int Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 Input::_pIDirectInput8 = nullptr;
LPDIRECTINPUTDEVICE8 Input::_pKeyboardInputDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::_apJoystickInputDevice[MAX_JOY_STICK_NUM];
LPDIRECTINPUTDEVICE8 Input::_pMouseInputDevice  = nullptr;
DIMOUSESTATE2 Input::_di_mouse_state[2];
int  Input::_flip_ms = 0;

BYTE Input::_keyboard_state[2][256];
int Input::_flip_ks = 0;
DIDEVCAPS Input::_devcap;
DIJOYSTATE Input::_joy_state[MAX_JOY_STICK_NUM][2];
int Input::_max_acquire_joy_stick_num = 0;
int Input::_flip_js = 0;

Input::MouseState Input::_win_mouse_state[2];

int Input::count_joy_stick_device_no = 0;

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

    if (Input::_apJoystickInputDevice[P1_JOY_STICK]) {
        //取得済み
        Input::_apJoystickInputDevice[P1_JOY_STICK]->Unacquire();
        GGAF_RELEASE(Input::_apJoystickInputDevice[P1_JOY_STICK]);
    }
    if (Input::_apJoystickInputDevice[P2_JOY_STICK]) {
        //取得済み
        Input::_apJoystickInputDevice[P2_JOY_STICK]->Unacquire();
        GGAF_RELEASE(Input::_apJoystickInputDevice[P2_JOY_STICK]);
    }
    Input::_apJoystickInputDevice[P1_JOY_STICK] = nullptr;
    Input::_apJoystickInputDevice[P2_JOY_STICK] = nullptr;
    Input::count_joy_stick_device_no = 0;
    Input::_max_acquire_joy_stick_num = 0;

    HRESULT hr;
    // ゲームスティックを列挙してデバイスを得る
    hr = Input::_pIDirectInput8->EnumDevices(
                                           DI8DEVCLASS_GAMECTRL,
                                           Input::enumGameCtrlCallback,
                                           nullptr,
                                           DIEDFL_ATTACHEDONLY
                                       );
    for (int n = 0; n < MAX_JOY_STICK_NUM; n++) {
        if (hr != D3D_OK || Input::_apJoystickInputDevice[n] == nullptr) {
            _TRACE_("P"<<n+1<<" ジョイスティックが見つかりませんでした。");
            Input::_apJoystickInputDevice[n] = nullptr;
            continue;
        } else {
            _TRACE_("P"<<n+1<<" ジョイスティックは見つかりました");
            // ゲームスティックのデータ形式を設定する
            hr = Input::_apJoystickInputDevice[n]->SetDataFormat(&c_dfDIJoystick);
            if (hr != D3D_OK) {
                _TRACE_("P"<<n+1<<" ジョイスティック SetDataFormatに失敗しました");
                GGAF_RELEASE(Input::_apJoystickInputDevice[n]);
                Input::_apJoystickInputDevice[n] = nullptr;
                continue;
            }
            // ゲームスティック協調レベルを設定する
            hr = Input::_apJoystickInputDevice[n]->SetCooperativeLevel(
                                                         pCARETAKER->_pHWndPrimary,
                                                         DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
                                                     );
            if (hr != D3D_OK) {
                _TRACE_("P"<<n+1<<" ジョイスティック SetCooperativeLevelに失敗しました");
                GGAF_RELEASE(Input::_apJoystickInputDevice[n]);
                Input::_apJoystickInputDevice[n] = nullptr;
                continue;
            }

            // ゲームスティックの軸データの範囲を設定する
            hr = Input::_apJoystickInputDevice[n]->EnumObjects(
                                                         Input::enumPadAxisCallback,
                                                         Input::_apJoystickInputDevice[n],
                                                         DIDFT_AXIS
                                                     );
            if (hr == D3D_OK) {
                // 軸モードを設定
                DIPROPDWORD dipropword_j;
                dipropword_j.diph.dwSize = sizeof(dipropword_j);
                dipropword_j.diph.dwHeaderSize = sizeof(dipropword_j.diph);
                dipropword_j.diph.dwObj = 0;
                dipropword_j.diph.dwHow = DIPH_DEVICE;
                dipropword_j.dwData = DIPROPAXISMODE_ABS; // 絶対値モード
                //  dipropword.dwData       = DIPROPAXISMODE_REL;   // 相対値モード
                hr = Input::_apJoystickInputDevice[n]->SetProperty(DIPROP_AXISMODE, &dipropword_j.diph);
                if (hr != D3D_OK) {
                    _TRACE_("P"<<n+1<<" ジョイスティック 軸モードの設定に失敗 SetProperty(DIPROP_AXISMODE)");
                }
            } else {
                _TRACE_("P"<<n+1<<" ジョイスティック DIDFT_AXIS EnumObjectsに失敗しました");
            }

            // ゲームスティックのアクセス権を取得する
            hr = Input::_apJoystickInputDevice[n]->Poll();
            if (hr != D3D_OK) {
                do {
                    hr = Input::_apJoystickInputDevice[n]->Acquire();
                } while (hr == DIERR_INPUTLOST);
            }
            Input::_max_acquire_joy_stick_num ++;
        }
    }
    return D3D_OK;
}

BOOL CALLBACK Input::enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    HRESULT hr;
    // ゲームスティックデバイスを探す
    LPDIRECTINPUTDEVICE8 pJoystickInputDevice;
    hr = Input::_pIDirectInput8->CreateDevice(
                                           pDIDeviceInstance->guidInstance,
                                           &pJoystickInputDevice,
                                           nullptr
                                       );
    if(hr != D3D_OK) {
        _TRACE_("enumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    Input::_devcap.dwSize = sizeof(DIDEVCAPS);
    hr = pJoystickInputDevice->GetCapabilities( &Input::_devcap );
    if( hr != D3D_OK ) {
        _TRACE_("enumGameCtrlCallback 能力取得できない。ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        pJoystickInputDevice->Release();
        return DIENUM_CONTINUE;
    }

    //生き残ればデバイス採用
    _TRACE_("enumGameCtrlCallback ジョイスティックのデバイス番号["<<count_joy_stick_device_no<<"] "<< pDIDeviceInstance->tszInstanceName<<"/"<<pDIDeviceInstance->tszProductName<<" を発見");
    if (Input::count_joy_stick_device_no == Config::P1_JOY_STICK_DEVICE_NO) {
        Input::_apJoystickInputDevice[P1_JOY_STICK] = pJoystickInputDevice;
        _TRACE_("enumGameCtrlCallback デバイス番号["<<count_joy_stick_device_no<<"] を 1P ジョイスティックとして使用されます。理由、Config::P1_JOY_STICK_DEVICE_NO="<<Config::P1_JOY_STICK_DEVICE_NO);
    } else if (Input::count_joy_stick_device_no == Config::P2_JOY_STICK_DEVICE_NO) {
        Input::_apJoystickInputDevice[P2_JOY_STICK] = pJoystickInputDevice;
        _TRACE_("enumGameCtrlCallback デバイス番号["<<count_joy_stick_device_no<<"] を 2P ジョイスティックとして使用されます。理由、Config::P2_JOY_STICK_DEVICE_NO="<<Config::P2_JOY_STICK_DEVICE_NO);
    } else {
        pJoystickInputDevice->Release();
        _TRACE_("enumGameCtrlCallback デバイス番号["<<count_joy_stick_device_no<<"] は使用されません。理由、P1_JOY_STICK_DEVICE_NO="<<Config::P1_JOY_STICK_DEVICE_NO<<"/P2_JOY_STICK_DEVICE_NO="<<Config::P2_JOY_STICK_DEVICE_NO);

    }
    Input::count_joy_stick_device_no++;
    return DIENUM_CONTINUE;
}

BOOL CALLBACK Input::enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef) {
    LPDIRECTINPUTDEVICE8 pJoystickInputDevice = (LPDIRECTINPUTDEVICE8)pvRef;
    DIPROPRANGE diproprange;
    ZeroMemory( &diproprange, sizeof(diproprange) );
    diproprange.diph.dwSize = sizeof(diproprange);
    diproprange.diph.dwHeaderSize = sizeof(diproprange.diph);
    diproprange.diph.dwHow = DIPH_BYID;
    diproprange.diph.dwObj = lpddoi->dwType;
    diproprange.lMin = -255;
    diproprange.lMax = +255;
    HRESULT hr = pJoystickInputDevice->SetProperty(DIPROP_RANGE, &diproprange.diph);
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
void Input::updateAllJoystickState() {
    Input::_flip_js ^= 1;
    for (int joy_stick_no = 0; joy_stick_no < MAX_JOY_STICK_NUM; joy_stick_no++) {
        GgafDx::Input::updateJoystickState(joy_stick_no);
    }
}
void Input::updateJoystickState(int prm_joystic_no) {

    if (Input::_apJoystickInputDevice[prm_joystic_no] == nullptr) {
        //Input::_joy_state[prm_joystic_no][Input::_flip_js] = {0};
        return;
    }
    if (prm_joystic_no+1 > Input::_max_acquire_joy_stick_num) {
        //Input::_joy_state[prm_joystic_no][Input::_flip_js] = {0};
        return;
    }

    HRESULT hr;

again1:
    hr = Input::_apJoystickInputDevice[prm_joystic_no]->Poll();
    if (hr != DI_OK) {
        hr = Input::_apJoystickInputDevice[prm_joystic_no]->Acquire();
        if (hr == DI_OK) {
            //１回だけ頑張る
            goto again1;
        }
    }

again2:
    hr = Input::_apJoystickInputDevice[prm_joystic_no]->GetDeviceState(
                                                 sizeof(DIJOYSTATE),
                                                 &Input::_joy_state[prm_joystic_no][Input::_flip_js]
                                             );
    if (hr != DI_OK) {
        hr = Input::_apJoystickInputDevice[prm_joystic_no]->Acquire();
        if (hr == DI_OK) {
            //１回だけ頑張る
            goto again2;
        }
    }
    //DEBUG
//    DIJOYSTATE& sta_dbg =  Input::_joy_state[prm_joystic_no][Input::_flip_js];
//    _TRACE_("Input::_joy_state prm_joystic_no="<<prm_joystic_no<<"/Input::_flip_js="<<Input::_flip_js);
//    _TRACE_("sta_dbg="<<sta_dbg.lX<<","<<sta_dbg.lY<<","<<sta_dbg.lZ<<"/"<<sta_dbg.lRx<<","<<sta_dbg.lRy<<","<<sta_dbg.lRz);
//    _TRACE_("sta_dbg.rglSlider="<<sta_dbg.rglSlider<<",[0]="<<sta_dbg.rglSlider[0]<<",[1]="<<sta_dbg.rglSlider[1]);
//    _TRACE_("sta_dbg.rgdwPOV="<<sta_dbg.rgdwPOV<<",[0]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[0])<<",[1]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[1])<<",[2]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[2])<<",[3]=0x"<<UTIL::dec2hex(sta_dbg.rgdwPOV[3]));
//    _TRACE_("sta_dbg.rgbButtons="<<sta_dbg.rgbButtons<<
//            ",[0]=" << (int)(sta_dbg.rgbButtons[0]  & 0x80) <<
//            ",[1]=" << (int)(sta_dbg.rgbButtons[1]  & 0x80) <<
//            ",[2]=" << (int)(sta_dbg.rgbButtons[2]  & 0x80) <<
//            ",[3]=" << (int)(sta_dbg.rgbButtons[3]  & 0x80) <<
//            ",[4]=" << (int)(sta_dbg.rgbButtons[4]  & 0x80) <<
//            ",[5]=" << (int)(sta_dbg.rgbButtons[5]  & 0x80) <<
//            ",[6]=" << (int)(sta_dbg.rgbButtons[6]  & 0x80) <<
//            ",[7]=" << (int)(sta_dbg.rgbButtons[7]  & 0x80) <<
//            ",[8]=" << (int)(sta_dbg.rgbButtons[8]  & 0x80) <<
//            ",[9]=" << (int)(sta_dbg.rgbButtons[9]  & 0x80) <<
//            ",[10]="<< (int)(sta_dbg.rgbButtons[10] & 0x80) <<
//            ",[11]="<< (int)(sta_dbg.rgbButtons[11] & 0x80) <<
//            ",[12]="<< (int)(sta_dbg.rgbButtons[12] & 0x80) <<
//            ",[13]="<< (int)(sta_dbg.rgbButtons[13] & 0x80) <<
//            ",[14]="<< (int)(sta_dbg.rgbButtons[14] & 0x80) <<
//            ",[15]="<< (int)(sta_dbg.rgbButtons[15] & 0x80) <<
//            ",[16]="<< (int)(sta_dbg.rgbButtons[16] & 0x80) <<
//            ",[17]="<< (int)(sta_dbg.rgbButtons[17] & 0x80) <<
//            ",[18]="<< (int)(sta_dbg.rgbButtons[18] & 0x80) <<
//            ",[19]="<< (int)(sta_dbg.rgbButtons[19] & 0x80) <<
//            ",[20]="<< (int)(sta_dbg.rgbButtons[20] & 0x80) <<
//            ",[21]="<< (int)(sta_dbg.rgbButtons[21] & 0x80) <<
//            ",[22]="<< (int)(sta_dbg.rgbButtons[22] & 0x80) <<
//            ",[23]="<< (int)(sta_dbg.rgbButtons[23] & 0x80) <<
//            ",[24]="<< (int)(sta_dbg.rgbButtons[24] & 0x80) <<
//            ",[25]="<< (int)(sta_dbg.rgbButtons[25] & 0x80) <<
//            ",[26]="<< (int)(sta_dbg.rgbButtons[26] & 0x80) <<
//            ",[27]="<< (int)(sta_dbg.rgbButtons[27] & 0x80) <<
//            ",[28]="<< (int)(sta_dbg.rgbButtons[28] & 0x80) <<
//            ",[29]="<< (int)(sta_dbg.rgbButtons[29] & 0x80) <<
//            ",[30]="<< (int)(sta_dbg.rgbButtons[30] & 0x80) <<
//            ",[31]="<< (int)(sta_dbg.rgbButtons[31] & 0x80)  );
}

bool Input::isPushedDownJoyRgbButton(int prm_joystic_no, int prm_joy_button_no) {
    if (Input::isPressedJoyButton(prm_joystic_no, prm_joy_button_no)) { //今は押している
        if (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) {
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

int Input::getFirstPushedDownJoyRgbButton(int prm_joystic_no) {
    int JOY_pressed = Input::getFirstPressedJoyRgbButton(prm_joystic_no);
    if (JOY_pressed >= 0 ) { //今は押している
        if (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[JOY_pressed] & 0x80) {
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


int Input::getPressedJoyDirection(int prm_joystic_no) {
    DIJOYSTATE& sta = Input::_joy_state[prm_joystic_no][Input::_flip_js];
    if (sta.lY < -127) {
        if (sta.lX > 127) {
            return 9;
        } else if (sta.lX < -127) {
            return 7;
        } else {
            return 8;
        }
    } else if (sta.lY > 127) {
        if (sta.lX > 127) {
            return 3;
        } else if (sta.lX < -127) {
            return 1;
        } else {
            return 2;
        }
    } else if (sta.lX > 127) {
        return 6;
    } else if (sta.lX < -127) {
        return 4;
    } else {
        return 5;
    }
}

int Input::getPressedPovDirection(int prm_joystic_no) {
    if (Input::_apJoystickInputDevice[prm_joystic_no]) { //JoyStickが無い場合、rgdwPOV[0]=0のため、上と判定されることを防ぐ
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        if (LOWORD(n) != 0xFFFF) {
            if (n == 0 ) {
                return 8; //UP
            } else if (n == 4500) {
                return 9; //RIGHT+UP
            } else if (n == 9000) {
                return 6; //RIGHT
            } else if (n == 13500) {
                return 3; //RIGHT+DOWN
            } else if (n == 18000) {
                return 2; //DOWN
            } else if (n == 22500) {
                return 1; //LEFT+DOWN
            } else if (n == 27000) {
                return 4; //LEFT
            } else if (n == 31500) {
                return 7; //LEFT+UP
            } else {
                _TRACE_("【警告】ありえない getPressedPovDirection n="<<n);
                return 5;
            }
        } else {
            return 5;
        }
    } else {
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
        if (Input::_apJoystickInputDevice[P1_JOY_STICK]) {
            Input::_apJoystickInputDevice[P1_JOY_STICK]->Unacquire();
            GGAF_RELEASE(Input::_apJoystickInputDevice[P1_JOY_STICK]);
        }
        if (Input::_apJoystickInputDevice[P2_JOY_STICK]) {
            Input::_apJoystickInputDevice[P2_JOY_STICK]->Unacquire();
            GGAF_RELEASE(Input::_apJoystickInputDevice[P2_JOY_STICK]);
        }
        if (Input::_pMouseInputDevice) {
            Input::_pMouseInputDevice->Unacquire();
            GGAF_RELEASE(Input::_pMouseInputDevice);
        }
        GGAF_RELEASE(Input::_pIDirectInput8);
    }
}
