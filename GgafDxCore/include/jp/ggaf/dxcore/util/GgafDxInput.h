#ifndef GGAFDXCORE_GGAFDXINPUT_H_
#define GGAFDXCORE_GGAFDXINPUT_H_
#include "GgafDxCommonHeader.h"

#include <dinput.h>

//Pキーを押したときだけ_TRACE_(デバッグ用)
#define _PTRACE_(M) {if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_P)) { _TRACE_(M); }}

namespace GgafDxCore {

/**
 * DirectInput ユーティリティクラス .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxInput {

public:
    /** IDirectInput8インターフェイス */
    static LPDIRECTINPUT8 _pIDirectInput8;
    /** キーボードインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pKeyboardInputDevice;
    /** ジョイスティックインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pJoystickInputDevice;
    /** マウスインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pMouseInputDevice;
    /** ジョイスティックの性能 */
    static DIDEVCAPS _devcap;

    //static const int BUFFER_SIZE;

    /** マウス状態（表、裏）*/
    static DIMOUSESTATE2 _mouse_state[2];
    /** 現在アクティブなマウス状態の表裏(0:表／1:裏) */
    static int _flip_ms;
    /** キーボードの状態（表、裏） */
    static char _keyboard_state[2][256];
    /** 現在アクティブなキーボード状態の表裏(0:表／1:裏) */
    static int _flip_ks;
    /** ジョイスティックの状態(0:表／1:裏)  */
    static DIJOYSTATE _joy_state[2];
    /** 現在アクティブなジョイスティック状態の表裏(0:表／1:裏) */
    static int _flip_js;

public:
    /**
     * 初期化 .
     * 使用前１度だけ呼び出す必要がある。
     */
    static HRESULT init();

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
     * 結果は _mouse_state の表か裏に格納される。
     */
    static void updateMouseState();

    /**
     * マウスのボタンの状態を調べる .
     * @param prm_button_no マウスボタン番号
     * @return true：そのボタンは押されている状態である／false：そうでは無い
     */
    static bool isBeingPressedMouseButton(int prm_button_no);

    /**
     * マウスのボタンが押された直後の状態を調べる .
     * @param prm_button_no マウスボタン番号
     * @return true：そのボタンは押された直後である／false：そうでは無い
     */
    static bool isPushedDownMouseButton(int prm_button_no);

    /**
     * マウスのボタンが離された直後の状態を調べる .
     * @param prm_button_no マウスボタン番号
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
     * キーボードのキーの状態を調べる .
     * @param prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは押されている状態である／false：そうでは無い
     */
    static inline bool isBeingPressedKey(int prm_DIK) {
        return (_keyboard_state[_flip_ks][prm_DIK] & 0x80) ? true : false;
    }

    /**
     * 押されているキーボードのキーを調べる .
     * @return 押されたキー(DIK_* 定数) / -1:何も押されていない
     */
    static inline int getBeingPressedKey() {
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
     * @return 押された直後のキー(DIK_*) / 0:何も押されていない
     */
    static int getPushedDownKey();

    /**
     * キーボードのキーが離された直後の状態を調べる .
     * @param prm_DIK prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは離された直後である／false：そうでは無い
     */
    static bool isReleasedUpDownKey(int prm_DIK);

    /**
     * ジョイスティックの状態を更新 .
     * 結果は _joy_state に格納される。
     */
    static void updateJoystickState();

    /**
     * ジョイスティックのボタンの状態を調べる .
     * @param prm_rgb_button_no ジョイスティックボタン番号
     * @return  true：そのボタンは押されている状態である／false：そうでは無い
     */
    static inline bool isBeingPressedJoyRgbButton(int prm_rgb_button_no) {
        return (_joy_state[_flip_js].rgbButtons[prm_rgb_button_no] & 0x80) ? true : false;
    }

    /**
     * 押されているジョイスティックのボタンを調べる .
     * @return 押されたジョイスティックボタン番号(0～12) / -1:何も押されていない
     */
    static inline int getBeingPressedJoyRgbButton() {
        for (int i = 0; i < 13; i ++) {
            if (_joy_state[_flip_js].rgbButtons[i] & 0x80) {
                return i;
            }
        }
        return -1;
    }

    static bool isPushedDownJoyRgbButton(int prm_rgb_button_no);

    static int getPushedDownJoyRgbButton();

    /**
     * ジョイスティックの上方向の状態を調べる .
     * @return true：ジョイスティックの上方向はONである／false：そうでは無い
     */
    static inline bool isBeingPressedJoyUp() {
        return (_joy_state[_flip_js].lY < -127) ? true : false;
    }

    /**
     * ジョイスティックの下方向の状態を調べる .
     * @return true：ジョイスティックの下方向はONである／false：そうでは無い
     */
    static inline bool isBeingPressedJoyDown() {
        return (_joy_state[_flip_js].lY > 127) ? true : false;
    }

    /**
     * ジョイスティックの左方向の状態を調べる .
     * @return true：ジョイスティックの左方向はONである／false：そうでは無い
     */
    static inline bool isBeingPressedJoyLeft() {
        return (_joy_state[_flip_js].lX < -127) ? true : false;
    }

    /**
     * ジョイスティックの右方向の状態を調べる .
     * @return true：ジョイスティックの右方向はONである／false：そうでは無い
     */
    static inline bool isBeingPressedJoyRight() {
        return (_joy_state[_flip_js].lX > 127) ? true : false;
    }

    /**
     * ジョイスティックのアナログスティックの方向の状態を調べる .
     * @param prm_direction_no 調べたい方向番号(８方向、テンキーの番号に対応)
     * @return true：その方向番号はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyDirection(int prm_direction_no);

    static void release();

};

}
#endif /*GGAFDXCORE_GGAFDXINPUT_H_*/
