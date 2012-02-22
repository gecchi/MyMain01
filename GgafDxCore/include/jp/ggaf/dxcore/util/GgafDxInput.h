#ifndef GGAFDXINPUT_H_
#define GGAFDXINPUT_H_

//Pキーを押したときだけ_TRACE_(デバッグ用)
#define _KTRACE_(M) {if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_P)) { _TRACE_(M); }}

namespace GgafDxCore {

/**
 * 入力インターフェイスユーティリティ .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxInput {

public:
    /** IDirectInput8インターフェイス */
    static LPDIRECTINPUT8 _pIDirectInput8;
    /** キーボードインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Keyboard;
    /** ジョイスティックインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Joystick;
    /** マウスインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Mouse;
    /** ジョイスティックの性能 */
    static DIDEVCAPS _didevcap;

    //static const int BUFFER_SIZE;

    /** マウス状態（表、裏）*/
    static DIMOUSESTATE2 _dimousestate[2];
    /** 現在アクティブなマウス状態の表裏(0:表／1:裏) */
    static int _active_MouseState;
    /** キーボードの状態（表、裏） */
    static char _caKeyboardState[2][256];
    /** 現在アクティブなキーボード状態の表裏(0:表／1:裏) */
    static int _active_KeyboardState;
    /** ジョイスティックの状態 */
    static DIJOYSTATE _dijoystate;

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
     * 結果は _dimousestate の表か裏に格納される。
     */
    static void updateMouseState();

    /**
     * マウスのボタンの状態を調べる .
     * @param prm_iButtonNo マウスボタン番号
     * @return true：そのボタンは押されている状態である／false：そうでは無い
     */
    static bool isBeingPressedMouseButton(int prm_iButtonNo);

    /**
     * マウスのボタンが押された直後の状態を調べる .
     * @param prm_iButtonNo マウスボタン番号
     * @return true：そのボタンは押された直後である／false：そうでは無い
     */
    static bool isPushedDownMouseButton(int prm_iButtonNo);

    /**
     * マウスのボタンが離された直後の状態を調べる .
     * @param prm_iButtonNo マウスボタン番号
     * @return true：そのボタンは離された直後である／false：そうでは無い
     */
    static bool isReleasedUpMouseButton(int prm_iButtonNo);

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
     * 結果は _caKeyboardState の表か裏に格納される。
     */
    static void updateKeyboardState();

    /**
     * キーボードのキーの状態を調べる .
     * @param prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは押されている状態である／false：そうでは無い
     */
    static bool isBeingPressedKey(int prm_DIK);

    /**
     * キーボードのキーが押された直後の状態を調べる .
     * @param prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは押された直後である／false：そうでは無い
     */
    static bool isPushedDownKey(int prm_DIK);

    /**
     * キーボードのキーが離された直後の状態を調べる .
     * @param prm_DIK prm_DIK 調べたいキー(DIK_*)
     * @return true：そのキーは離された直後である／false：そうでは無い
     */
    static bool isReleasedUpDownKey(int prm_DIK);

    /**
     * ジョイスティックの状態を更新 .
     * 結果は _dijoystate に格納される。
     */
    static void updateJoystickState();

    /**
     * ジョイスティックのボタンの状態を調べる .
     * @param prm_iRgbButtonNo ジョイスティックボタン番号
     * @return  true：そのボタンは押されている状態である／false：そうでは無い
     */
    static bool isBeingPressedJoyRgbButton(int prm_iRgbButtonNo);

    /**
     * ジョイスティックの上方向の状態を調べる .
     * @return true：ジョイスティックの上方向はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyUp();

    /**
     * ジョイスティックの下方向の状態を調べる .
     * @return true：ジョイスティックの下方向はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyDown();

    /**
     * ジョイスティックの左方向の状態を調べる .
     * @return true：ジョイスティックの左方向はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyLeft();

    /**
     * ジョイスティックの右方向の状態を調べる .
     * @return true：ジョイスティックの右方向はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyRight();

    /**
     * ジョイスティックのアナログスティックの方向の状態を調べる .
     * @param prm_iDirectionNo 調べたい方向番号(８方向、テンキーの番号に対応)
     * @return true：その方向番号はONである／false：そうでは無い
     */
    static bool isBeingPressedJoyDirection(int prm_iDirectionNo);

    static void release();

};

}
#endif /*GGAFDXINPUT_H_*/
