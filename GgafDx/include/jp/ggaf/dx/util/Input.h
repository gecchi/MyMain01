#ifndef GGAF_DX_INPUT_H_
#define GGAF_DX_INPUT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <dinput.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

//Pキーを押したときだけ_TRACE_(デバッグ用)
#define _PTRACE_(M) {if (Input::isPressedKey(DIK_P)) { _TRACE_(M); }}

#define P1_JOY_STICK 0
#define P2_JOY_STICK 1

#define MAX_JOY_STICK_NUM 2

namespace GgafDx {

/**
 * DirectInput ユーティリティクラス .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class Input {

public:
    /** IDirectInput8インターフェイス */
    static LPDIRECTINPUT8 _pIDirectInput8;
    /** キーボードインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pKeyboardInputDevice;
    /** ジョイスティックインプットデバイス, [0]:1P [1]:2P */
    static LPDIRECTINPUTDEVICE8 _apJoystickInputDevice[MAX_JOY_STICK_NUM];
    /** マウスインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pMouseInputDevice;
    /** ジョイスティックの性能 */
    static DIDEVCAPS _devcap;

    //static const int BUFFER_SIZE;

    /** マウス状態（表、裏）*/
    static DIMOUSESTATE2 _di_mouse_state[2];
    /** 現在アクティブなマウス状態の表裏(0:表／1:裏) */
    static int _flip_ms;
    /** キーボードの状態（表、裏） */
    static BYTE _keyboard_state[2][256];
    /** 現在アクティブなキーボード状態の表裏(0:表／1:裏) */
    static int _flip_ks;
    /** ジョイスティックの状態([0:1P/1:2P][0:表／1:裏])  */
    static DIJOYSTATE _joy_state[MAX_JOY_STICK_NUM][2];
    /** 実際に取得できたジョイスティック数 */
    static int _max_acquire_joy_stick_num;
    /** 現在アクティブなジョイスティック状態の表裏(0:表／1:裏) */
    static int _flip_js;


    struct MouseState {
         bool buttons[8];
    };
    static MouseState _win_mouse_state[2];

    static int count_joy_stick_device_no;
//    // マウス座標を取得する
//    static POINT _mouse_point[2];


public:
    /**
     * 初期化 .
     * 使用前１度だけ呼び出す必要がある。
     */
    static HRESULT init();

    static HRESULT initKeybord();
    static HRESULT initMouse();
    static HRESULT initJoyStick();

    /**
     * 軸ボタン列挙コールバック関数 .
     * 各軸の最低値を -255、最高値を 255 に設定
     * @param lpddoi
     * @param pvRef
     * @return
     */
    static BOOL CALLBACK enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

    /**
     * ゲームスティックデバイス列挙コールバック関数 .
     * @param pDIDeviceInstance
     * @param pContext
     * @return
     */
    static BOOL CALLBACK enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext);

    /**
     * マウスの状態を更新 .
     * 結果は _di_mouse_state の表か裏に格納される。
     */
    static void updateMouseState();

    /**
     * マウスのボタンの状態を調べる .
     * @param prm_button_no マウスボタン番号
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:未使用
     * @return true：そのボタンは押されている状態である／false：そうでは無い
     */
    static bool isPressedMouseButton(int prm_button_no);

    /**
     * マウスのボタンが押された直後の状態を調べる .
     * @param prm_button_no マウスボタン番号(0~7)
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:未使用
     * @return true：そのボタンは押された直後である／false：そうでは無い
     */
    static bool isPushedDownMouseButton(int prm_button_no);

    /**
     * マウスのボタンが離された直後の状態を調べる .
     * @param prm_button_no マウスボタン番号(0~7)
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:未使用
     * @return true：そのボタンは離された直後である／false：そうでは無い
     */
    static bool isReleasedUpMouseButton(int prm_button_no);

    /**
     * マウスポインタの座標を調べる .
     * @param x [out]ポインタのX座標が返される
     * @param y [out]ポインタのY座標が返される
     * @param z [out]ホイールの状態が返される
     */
    static void getMousePointer(long* x, long* y, long* z);

    /**
     * マウスポインタの移動量を調べる .
     * @param dx [out]ポインタのX座標の移動量が返される
     * @param dy [out]ポインタのY座標の移動量が返される
     * @param dz [out]ホイールの移動量が返される
     */
    static void getMousePointer_REL(long* dx, long* dy, long* dz);

    /**
     * キーボードの状態を更新 .
     * 結果は _keyboard_state の表か裏に格納される。
     */
    static void updateKeyboardState();

    /**
     * キーボードの状態を取得
     * @return BYTE[256] の配列
     */
    static inline BYTE* getKeyboardState() {
        return _keyboard_state[_flip_ks];
    }

    /**
     * キーボードのキーの状態を調べる .
     * @param prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは押されている状態である／false：そうでは無い
     */
    static inline bool isPressedKey(int prm_DIK) {
        return (_keyboard_state[_flip_ks][prm_DIK] & 0x80) ? true : false;
    }

    /**
     * 押されているキーボードのキーを調べる .
     * @return 押されたキー(DIK_* 定数) / -1:何も押されていない
     */
    static inline int getFirstPressedKey() {
        for (int i = 0x00; i <= 0xED; i ++) {
            if (_keyboard_state[_flip_ks][i] & 0x80) {
                return i;
            }
        }
        return -1;
    }

    /**
     * キーボードのキーが押された直後の状態を調べる .
     * @param prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは押された直後である／false：そうでは無い
     */
    static bool isPushedDownKey(int prm_DIK);

    /**
     * キーボードの押された直後のキーを調べる .
     * @return 押された直後のキー(DIK_*) / -1:何も押されていない
     */
    static int getFirstPushedDownKey();

    /**
     * キーボードのキーが離された直後の状態を調べる .
     * @param prm_DIK prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは離された直後である／false：そうでは無い
     */
    static bool isReleasedUpKey(int prm_DIK);

    static void updateAllJoystickState();

    /**
     * ジョイスティックの状態を更新 .
     * 結果は Input::_joy_state に格納される。
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     */
    static void updateJoystickState(int prm_joystic_no);

    /**
     * ジョイスティックのボタンの状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @param prm_joy_button_no ジョイスティックボタン番号
     * @return  true：そのボタンは押されている状態である／false：そうでは無い
     */
    static inline bool isPressedJoyButton(int prm_joystic_no, int prm_joy_button_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? true : false;
    }

    static inline bool isPushedDownJoyButton(int prm_joystic_no, int prm_joy_button_no) {
        if (Input::isPressedJoyButton(prm_joystic_no, prm_joy_button_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? false :  true;
        } else { //今は押して無い
            return false;
        }
    }

    /**
     * 押されているジョイスティックのボタンを調べ最初の１つの結果を返す .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 押されたジョイスティックボタン番号(0～15) / -1:何も押されていない
     */
    static inline int getFirstPressedJoyRgbButton(int prm_joystic_no) {
        for (int i = 0; i < 16; i ++) {
            if (Input::_joy_state[prm_joystic_no][Input::_flip_js].rgbButtons[i] & 0x80) {
                return i;
            }
        }
        return -1;
    }

    /**
     * ジョイスティックボタンが押された直後の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @param prm_joy_button_no ジョイスティックボタン番号
     * @return true：そのボタンは押された直後である／false：そうでは無い
     */
    static bool isPushedDownJoyRgbButton(int prm_joystic_no, int prm_joy_button_no);

    /**
     * 押されているジョイスティックボタン番号を調べ最初の１つの結果を返す .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 押されたジョイスティックボタン番号(0～15) / -1:何も押されていない
     */
    static int getFirstPushedDownJoyRgbButton(int prm_joystic_no);

    /**
     * ジョイスティックの上方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ジョイスティックの上方向はONである／false：そうでは無い
     */
    static inline bool isPressedJoyUp(int prm_joystic_no) {
        return Input::isPressedJoyYAxisMinus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyUp(int prm_joystic_no) {
        return Input::isPushedDownJoyYAxisMinus(prm_joystic_no);
    }

    /**
     * ジョイスティックの下方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ジョイスティックの下方向はONである／false：そうでは無い
     */
    static inline bool isPressedJoyDown(int prm_joystic_no) {
        return Input::isPressedJoyYAxisPlus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyDown(int prm_joystic_no) {
        return Input::isPushedDownJoyYAxisPlus(prm_joystic_no);
    }

    /**
     * ジョイスティックの左方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ジョイスティックの左方向はONである／false：そうでは無い
     */
    static inline bool isPressedJoyLeft(int prm_joystic_no) {
        return Input::isPressedJoyXAxisMinus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyLeft(int prm_joystic_no) {
        return Input::isPushedDownJoyXAxisMinus(prm_joystic_no);
    }

    /**
     * ジョイスティックの右方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ジョイスティックの右方向はONである／false：そうでは無い
     */
    static inline bool isPressedJoyRight(int prm_joystic_no) {
        return Input::isPressedJoyXAxisPlus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyRight(int prm_joystic_no) {
        return Input::isPushedDownJoyXAxisPlus(prm_joystic_no);
    }

    /**
     * ジョイスティックのアナログスティックの押している方向のを調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 方向番号1～9(８方向、テンキーの番号に対応、5番はニュートラル)
     */
    static int getPressedJoyDirection(int prm_joystic_no);

    /**
     * ジョイスティックのアナログスティックが押された瞬間なのかを調べる（5番はニュートラルとなった瞬間は返る） .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 1～9：方向番号８方向、テンキーの番号に対応、5番はニュートラルになった瞬間である。
     *         -1:アナログスティックの状態に変化なし。（入りっぱなしか、ずっとニュートラル）。
     */
    static int getPushedDownJoyDirection(int prm_joystic_no);

    static inline bool isPressedJoyXAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lX > 127) ? true : false;
    }

    static inline bool isPushedDownJoyXAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRight(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lX > 127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }


    static inline bool isPressedJoyXAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lX < -127) ? true : false;
    }

    static inline bool isPushedDownJoyXAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyXAxisMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lX < -127) ? false : true ;
        } else { //今は押して無い
            return false;
        }
    }


    static inline bool isPressedJoyYAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lY > 127) ? true : false;
    }

    static inline bool isPushedDownJoyYAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyYAxisPlus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lY > 127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyYAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lY < -127) ? true : false;
    }

    static inline bool isPushedDownJoyYAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyYAxisMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lY < -127) ?  false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyZAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lZ > 127) ? true : false;
    }

    static inline bool isPushedDownJoyZAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyZAxisPlus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lZ > 127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyZAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lZ < -127) ? true : false;
    }
    static inline bool isPushedDownJoyZAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyZAxisMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lZ < -127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyRxPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRx > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRxPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRxPlus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRx > 127) ? false  : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyRxMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRx < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRxMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRxMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRx < -127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }
    static inline bool isPressedJoyRyPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRy > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRyPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRyPlus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRy > 127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyRyMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRy < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRyMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRyMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRy < -127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyRzPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRz > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRzPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRzPlus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRz > 127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    static inline bool isPressedJoyRzMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRz < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRzMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRzMinus(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRz < -127) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    /**
     * ハットスイッチの上方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ハットスイッチの上方向はONである／false：そうでは無い
     */
    static inline bool isPressedPovUp(int prm_joystic_no) {
        if (Input::_apJoystickInputDevice[prm_joystic_no]) { //JoyStickが無い場合、rgdwPOV[0]=0のため、上と判定されることを防ぐ
            DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && ( (31500 <= n && n <= 36000) || (0 <= n && n <= 4500) ) ) ? true : false;
        } else {
            return false;
        }
    }

    static inline bool isPushedDownPovUp(int prm_joystic_no) {
        if (Input::isPressedPovUp(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && ( (31500 <= n && n <= 36000) || (0 <= n && n <= 4500) ) ) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }


    /**
     * ハットスイッチの右方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ハットスイッチの右方向はONである／false：そうでは無い
     */
    static inline bool isPressedPovRight(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (4500 <= n && n <= 13500)) ? true : false;
    }

    static inline bool isPushedDownPovRight(int prm_joystic_no) {
        if (Input::isPressedPovRight(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (4500 <= n && n <= 13500)) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    /**
     * ハットスイッチの下方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ハットスイッチの下方向はONである／false：そうでは無い
     */
    static inline bool isPressedPovDown(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (13500 <= n && n <= 22500)) ? true : false;
    }

    static inline bool isPushedDownPovDown(int prm_joystic_no) {
        if (Input::isPressedPovDown(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (13500 <= n && n <= 22500)) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    /**
     * ハットスイッチの左方向の状態を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true：ハットスイッチの左方向はONである／false：そうでは無い
     */
    static inline bool isPressedPovLeft(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (22500 <= n && n <= 31500)) ? true : false;
    }
    static inline bool isPushedDownPovLeft(int prm_joystic_no) {
        if (Input::isPressedPovLeft(prm_joystic_no)) { //今は押している
            //前回セット[!Input::_flip_js]は押して無い => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (22500 <= n && n <= 31500)) ? false : true;
        } else { //今は押して無い
            return false;
        }
    }

    /**
     * ジョイスティックのハットスイッチが押されている方向を調べる .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 方向番号1～9(８方向、テンキーの番号に対応、5番はニュートラル)
     */
    static int getPressedPovDirection(int prm_joystic_no);

    /**
     * ジョイスティックのハットスイッチが押された瞬間なのかを調べる（5番はニュートラルとなった瞬間は返る） .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 1～9：方向番号８方向、テンキーの番号に対応、5番はニュートラルになった瞬間である。
     *         -1:ハットスイッチの状態に変化なし。（入りっぱなしか、ずっとニュートラル）。
     */
    static int getPushedDownPovDirection(int prm_joystic_no);

    static void release();

};

}
#endif /*GGAF_DX_INPUT_H_*/
