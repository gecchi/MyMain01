#ifndef GGAFDXINPUT_H_
#define GGAFDXINPUT_H_
namespace GgafDxCore {

/**
 * 入力クラス .
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

    static const int BUFFER_SIZE;

    /** マウス状態（表、裏）*/
    static DIMOUSESTATE2 _dimousestate[2];
    static int _active_MouseState;

    /** キーボードの状態（表、裏） */
    static char _caKeyboardState[2][256];
    static int _active_KeyboardState;
    /** ジョイスティックの状態 */
    static DIJOYSTATE _dijoystate;

    /**
     * コンストラクタ<BR>
     */
    GgafDxInput();

    /**
     * 初期化<BR>
     */
    static HRESULT init();

    static void updateMouseState();
    static bool isBeingPressedMouseButton(int prm_iButtonNo);
    static bool isPushedDownMouseButton(int prm_iButtonNo);
    static bool isReleasedUpMouseButton(int prm_iButtonNo);
    static void getMousePointer(long* x, long* y, long* z);
    static void getMousePointer_REL(long* dx, long* dy, long* dz);

    static void updateKeyboardState();
    static bool isBeingPressedKey(int prm_DIK);
    static bool isPushedDownKey(int prm_DIK);
    static bool isReleasedUpDownKey(int prm_DIK);
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
#endif /*GGAFDXINPUT_H_*/
