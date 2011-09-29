#ifndef GGAFDXINPUT_H_
#define GGAFDXINPUT_H_
namespace GgafDxCore {

/**
 * ���̓N���X .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxInput {

public:
    /** IDirectInput8�C���^�[�t�F�C�X */
    static LPDIRECTINPUT8 _pIDirectInput8;
    /** �L�[�{�[�h�C���v�b�g�f�o�C�X */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Keyboard;
    /** �W���C�X�e�B�b�N�C���v�b�g�f�o�C�X */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Joystick;
    /** �}�E�X�C���v�b�g�f�o�C�X */
    static LPDIRECTINPUTDEVICE8 _pIDirectInputDevice8_Mouse;

    /** �W���C�X�e�B�b�N�̐��\ */
    static DIDEVCAPS _didevcap;

    static const int BUFFER_SIZE;

    /** �}�E�X��ԁi�\�A���j*/
    static DIMOUSESTATE2 _dimousestate[2];
    static int _active_MouseState;

    /** �L�[�{�[�h�̏�ԁi�\�A���j */
    static char _caKeyboardState[2][256];
    static int _active_KeyboardState;
    /** �W���C�X�e�B�b�N�̏�� */
    static DIJOYSTATE _dijoystate;

    /**
     * �R���X�g���N�^<BR>
     */
    GgafDxInput();

    /**
     * ������<BR>
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
