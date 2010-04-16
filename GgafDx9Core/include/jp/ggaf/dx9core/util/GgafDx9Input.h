﻿#ifndef GGAFDX9INPUT_H_
#define GGAFDX9INPUT_H_
namespace GgafDx9Core {

/**
 * 入力クラス .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class GgafDx9Input {

public:
    /** IDirectInput8インターフェイス */
    static LPDIRECTINPUT8 _pIDirectInput8;
    /** キーボードインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Keyboard;
    /** ジョイスティックインプットデバイス */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Joystick;
    /** ジョイスティックの性能 */
    static DIDEVCAPS _didevcap;

    static const int BUFFER_SIZE;

    /** キーボードの状態 */
    static char _caKeyboardState[256];
    /** ジョイスティックの状態 */
    static DIJOYSTATE _dijoystate;

    /**
     * コンストラクタ<BR>
     */
    GgafDx9Input();

    /**
     * 初期化<BR>
     */
    static HRESULT init();

    static void updateKeyboardState();
    static bool isBeingPressedKey(int prm_DIK);

    static void updateJoystickState();
    static bool isBeingPressedJoyRgbButton(int prm_iRgbButtonNo);
    static bool isBeingPressedJoyUp();
    static bool isBeingPressedJoyDown();
    static bool isBeingPressedJoyLeft();
    static bool isBeingPressedJoyRight();
    static bool isBeingPressedJoyDirection(int prm_iDirectionNo);

    static void release();

};

}
#endif /*GGAFDX9INPUT_H_*/
