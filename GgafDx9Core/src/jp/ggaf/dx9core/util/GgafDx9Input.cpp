#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

const int GgafDx9Input::BUFFER_SIZE = 256;
LPDIRECTINPUT8 GgafDx9Input::_pIDirectInput8 = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_pIDirectInputDevice8_Keyboard = NULL;
LPDIRECTINPUTDEVICE8 GgafDx9Input::_pIDirectInputDevice8_Joystick = NULL;
char GgafDx9Input::_caKeyboardState[256];
DIDEVCAPS GgafDx9Input::_didevcap;
DIJOYSTATE GgafDx9Input::_dijoystate;

BOOL CALLBACK EnumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext) {
    _TRACE_("EnumGameCtrlCallback こーるばっく！");

    HRESULT hr;

    // ゲームスティックデバイスを探すする

    hr = GgafDx9Input::_pIDirectInput8->CreateDevice(pDIDeviceInstance->guidInstance, &GgafDx9Input::_pIDirectInputDevice8_Joystick, NULL);
    if(hr != D3D_OK) {
        _TRACE_("EnumGameCtrlCallback ジョイスティックCreateDeviceに失敗しました");
        // デバイスの作成に失敗したら列挙を続ける（さらに探す）
        return DIENUM_CONTINUE;
    }

    // ジョイスティックの能力を取得
    GgafDx9Input::_didevcap.dwSize = sizeof(DIDEVCAPS);
    hr = GgafDx9Input::_pIDirectInputDevice8_Joystick->GetCapabilities( &GgafDx9Input::_didevcap );
    if( hr != D3D_OK ) {
        _TRACE_("EnumGameCtrlCallback ジョイスティックGetCapabilitiesに失敗しました");
        // ジョイスティックの能力を取得出来ないようなら、勘弁願う
        GgafDx9Input::_pIDirectInputDevice8_Joystick->Release();
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

    HRESULT hr = GgafDx9Input::_pIDirectInputDevice8_Joystick->SetProperty(DIPROP_RANGE, &diproprange.diph);
    if(hr != D3D_OK) {
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
    hr = DirectInput8Create(GgafDx9God::_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (LPVOID*)&_pIDirectInput8, NULL);
    if (hr != D3D_OK) {
        MessageBox(GgafDx9God::_hWnd, TEXT("GgafDx9Input::initDx9Input() いきなりDirectInput8の作成に失敗しました。も〜やる気もなくなりますわ；"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP);
        return hr;
    }

    // キーボードデバイスの作成
    hr = _pIDirectInput8->CreateDevice(GUID_SysKeyboard, &_pIDirectInputDevice8_Keyboard, NULL);
    if (hr != D3D_OK) {
        MessageBox(GgafDx9God::_hWnd, TEXT("GgafDx9Input::initDx9Input() キーボードデバイス作成に失敗しました"), TEXT("ERROR"), MB_OK
                | MB_ICONSTOP);
        return hr;
    }

    // 取得データフォーマットの設定
    hr = _pIDirectInputDevice8_Keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (hr != D3D_OK) {
        MessageBox(GgafDx9God::_hWnd, TEXT("GgafDx9Input::initDx9Input() キーボードのSetDataFormat に失敗しました"), TEXT("ERROR"),
                   MB_OK | MB_ICONSTOP);
        return hr;
    }

    // 強調レベル設定
    hr = _pIDirectInputDevice8_Keyboard->SetCooperativeLevel(GgafDx9God::_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
    );
    if (hr != D3D_OK) {
        MessageBox(GgafDx9God::_hWnd, TEXT("GgafDx9Input::initDx9Input() キーボードのSetCooperativeLevelに失敗しました"),
                   TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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

     hr = _pIDirectInputDevice8_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipropdword.diph);
     if(hr != D3D_OK) {
     MessageBox(GgafDx9God::_hWnd,TEXT("GgafDx9Input::initDx9Input() キーボードのSetPropertyに失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
     return hr;
     }
     */
    // アクセス権取得
    if (_pIDirectInputDevice8_Keyboard) {
        _pIDirectInputDevice8_Keyboard->Acquire();
    }

    // ゲームスティックを列挙してデバイスを得る
    hr = _pIDirectInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGameCtrlCallback, NULL, DIEDFL_ATTACHEDONLY
    );
    if (hr != D3D_OK || _pIDirectInputDevice8_Joystick == NULL) {
        _TRACE_("GgafDx9Input::initDx9Input() EnumDevices列挙しましたが、でジョイスティックが見つかりませんでした");
        _pIDirectInputDevice8_Joystick = NULL;
    } else {
        _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックデバイス取得");

        // ゲームスティックのデータ形式を設定する
        hr = _pIDirectInputDevice8_Joystick->SetDataFormat(&c_dfDIJoystick);
        if (hr != D3D_OK) {
            _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックSetDataFormatに失敗しました");
            return FALSE;
        }

        // 協調レベルを設定する
        hr = _pIDirectInputDevice8_Joystick->SetCooperativeLevel(GgafDx9God::_hWnd, DISCL_FOREGROUND
                | DISCL_NONEXCLUSIVE );
        if (hr != D3D_OK) {
            _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックSetCooperativeLevelに失敗しました");
            return FALSE;
        }

        // ゲームスティックの軸データの範囲を設定する
        hr = _pIDirectInputDevice8_Joystick->EnumObjects(EnumPadAxisCallback, NULL, DIDFT_AXIS);
        if (hr != D3D_OK) {
            _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックEnumObjectsに失敗しました");
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
            _TRACE_("GgafDx9Input::initDx9Input() ジョイスティックPollに失敗しました");
            do {
                hr = _pIDirectInputDevice8_Joystick->Acquire();
            } while (hr == DIERR_INPUTLOST);
        }
    }
    return S_OK;
}

void GgafDx9Input::updateKeyboardState() {
    if (_pIDirectInputDevice8_Keyboard == NULL) {
        _TRACE_("GgafDx9Input::updateKeyboardState() NULLっす");
        return;
    }

    static HRESULT hr;
    again: hr = _pIDirectInputDevice8_Keyboard->Poll(); //キーボードは通常Poll不用と思うが、必要なキーボードもあるかもしれない。
    hr = _pIDirectInputDevice8_Keyboard->GetDeviceState(256, (void*)&_caKeyboardState);
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

bool GgafDx9Input::isBeingPressedKey(int prm_DIK) {
    if (prm_DIK < 0 || 255 < prm_DIK) {
        _TRACE_("isBeingPressedKey:範囲外");
        return false;
    } else {
        if (_caKeyboardState[prm_DIK] & 0x80) {
            return true;
        } else {
            return false;
        }
    }
}

void GgafDx9Input::updateJoystickState() {
    if (_pIDirectInputDevice8_Joystick == NULL) {
        return;
    }

    // ジョイスティックの状態を取得
    static HRESULT hr;

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

bool GgafDx9Input::isBeingPressedJoyRgbButton(int prm_iRgbButtonNo) {
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

bool GgafDx9Input::isBeingPressedJoyUp() {
    if (_dijoystate.lY < -127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDx9Input::isBeingPressedJoyDown() {
    if (_dijoystate.lY > 127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDx9Input::isBeingPressedJoyLeft() {
    if (_dijoystate.lX < -127) {
        return true;
    } else {
        return false;
    }
}

bool GgafDx9Input::isBeingPressedJoyRight() {
    if (_dijoystate.lX > 127) {
        return true;
    } else {
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

void GgafDx9Input::release() {
    TRACE("GgafDx9Input::~GgafDx9Input()");
    //デバイス解放
    _pIDirectInputDevice8_Keyboard->Unacquire();
    RELEASE_IMPOSSIBLE_NULL(_pIDirectInputDevice8_Keyboard);
    if (_pIDirectInputDevice8_Joystick != NULL) {
        _pIDirectInputDevice8_Joystick->Unacquire();
        RELEASE_IMPOSSIBLE_NULL(_pIDirectInputDevice8_Joystick);
    }
    RELEASE_IMPOSSIBLE_NULL(_pIDirectInput8);
}
