#ifndef GGAFDXINPUT_H_
#define GGAFDXINPUT_H_

//P�L�[���������Ƃ�����_TRACE_(�f�o�b�O�p)
#define _PTRACE_(M) {if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_P)) { _TRACE_(M); }}

namespace GgafDxCore {

/**
 * DirectInput ���[�e�B���e�B�N���X .
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

    //static const int BUFFER_SIZE;

    /** �}�E�X��ԁi�\�A���j*/
    static DIMOUSESTATE2 _dimousestate[2];
    /** ���݃A�N�e�B�u�ȃ}�E�X��Ԃ̕\��(0:�\�^1:��) */
    static int _active_MouseState;
    /** �L�[�{�[�h�̏�ԁi�\�A���j */
    static char _caKeyboardState[2][256];
    /** ���݃A�N�e�B�u�ȃL�[�{�[�h��Ԃ̕\��(0:�\�^1:��) */
    static int _active_KeyboardState;
    /** �W���C�X�e�B�b�N�̏�� */
    static DIJOYSTATE _dijoystate;

    /**
     * ������ .
     * �g�p�O�P�x�����Ăяo���K�v������B
     */
    static HRESULT init();

    /**
     * ���{�^���񋓃R�[���o�b�N�֐� .
     * �e���̍Œ�l�� -255�A�ō��l�� 255 �ɐݒ�
     * @param lpddoi
     * @param pvRef
     * @return
     */
    static BOOL CALLBACK enumPadAxisCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

    /**
     * �Q�[���X�e�B�b�N�f�o�C�X�񋓃R�[���o�b�N�֐� .
     * @param pDIDeviceInstance
     * @param pContext
     * @return
     */
    static BOOL CALLBACK enumGameCtrlCallback(const DIDEVICEINSTANCE *pDIDeviceInstance, VOID *pContext);

    /**
     * �}�E�X�̏�Ԃ��X�V .
     * ���ʂ� _dimousestate �̕\�����Ɋi�[�����B
     */
    static void updateMouseState();

    /**
     * �}�E�X�̃{�^���̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static bool isBeingPressedMouseButton(int prm_button_no);

    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownMouseButton(int prm_button_no);

    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͗����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isReleasedUpMouseButton(int prm_button_no);

    /**
     * �}�E�X�|�C���^�̍��W�𒲂ׂ� .
     * @param x [out]�|�C���^��X���W���Ԃ����
     * @param y [out]�|�C���^��Y���W���Ԃ����
     * @param z [out]�z�C�[���̏�Ԃ��Ԃ����
     */
    static void getMousePointer(long* x, long* y, long* z);

    /**
     * �}�E�X�|�C���^�̈ړ��ʂ𒲂ׂ� .
     * @param dx [out]�|�C���^��X���W�̈ړ��ʂ��Ԃ����
     * @param dy [out]�|�C���^��Y���W�̈ړ��ʂ��Ԃ����
     * @param dz [out]�z�C�[���̈ړ��ʂ��Ԃ����
     */
    static void getMousePointer_REL(long* dx, long* dy, long* dz);

    /**
     * �L�[�{�[�h�̏�Ԃ��X�V .
     * ���ʂ� _caKeyboardState �̕\�����Ɋi�[�����B
     */
    static void updateKeyboardState();

    /**
     * �L�[�{�[�h�̃L�[�̏�Ԃ𒲂ׂ� .
     * @param prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedKey(int prm_DIK) {
        return (_caKeyboardState[_active_KeyboardState][prm_DIK] & 0x80) ? true : false;
    }

    /**
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownKey(int prm_DIK);

    /**
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͗����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isReleasedUpDownKey(int prm_DIK);

    /**
     * �W���C�X�e�B�b�N�̏�Ԃ��X�V .
     * ���ʂ� _dijoystate �Ɋi�[�����B
     */
    static void updateJoystickState();

    /**
     * �W���C�X�e�B�b�N�̃{�^���̏�Ԃ𒲂ׂ� .
     * @param prm_rgb_button_no �W���C�X�e�B�b�N�{�^���ԍ�
     * @return  true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyRgbButton(int prm_rgb_button_no) {
        return (_dijoystate.rgbButtons[prm_rgb_button_no] & 0x80) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̏�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyUp() {
        return (_dijoystate.lY < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyDown() {
        return (_dijoystate.lY > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̍������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyLeft() {
        return (_dijoystate.lX < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉E�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyRight() {
        return (_dijoystate.lX > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�̕����̏�Ԃ𒲂ׂ� .
     * @param prm_direction_no ���ׂ��������ԍ�(�W�����A�e���L�[�̔ԍ��ɑΉ�)
     * @return true�F���̕����ԍ���ON�ł���^false�F�����ł͖���
     */
    static bool isBeingPressedJoyDirection(int prm_direction_no);

    static void release();

};

}
#endif /*GGAFDXINPUT_H_*/
