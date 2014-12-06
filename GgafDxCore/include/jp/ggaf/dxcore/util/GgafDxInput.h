#ifndef GGAFDXCORE_GGAFDXINPUT_H_
#define GGAFDXCORE_GGAFDXINPUT_H_
#include "GgafDxCommonHeader.h"

#include <dinput.h>

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
    static LPDIRECTINPUTDEVICE8 _pKeyboardInputDevice;
    /** �W���C�X�e�B�b�N�C���v�b�g�f�o�C�X */
    static LPDIRECTINPUTDEVICE8 _pJoystickInputDevice;
    /** �}�E�X�C���v�b�g�f�o�C�X */
    static LPDIRECTINPUTDEVICE8 _pMouseInputDevice;
    /** �W���C�X�e�B�b�N�̐��\ */
    static DIDEVCAPS _devcap;

    //static const int BUFFER_SIZE;

    /** �}�E�X��ԁi�\�A���j*/
    static DIMOUSESTATE2 _mouse_state[2];
    /** ���݃A�N�e�B�u�ȃ}�E�X��Ԃ̕\��(0:�\�^1:��) */
    static int _flip_ms;
    /** �L�[�{�[�h�̏�ԁi�\�A���j */
    static BYTE _keyboard_state[2][256];
    /** ���݃A�N�e�B�u�ȃL�[�{�[�h��Ԃ̕\��(0:�\�^1:��) */
    static int _flip_ks;
    /** �W���C�X�e�B�b�N�̏��(0:�\�^1:��)  */
    static DIJOYSTATE _joy_state[2];
    /** ���݃A�N�e�B�u�ȃW���C�X�e�B�b�N��Ԃ̕\��(0:�\�^1:��) */
    static int _flip_js;

public:
    /**
     * ������ .
     * �g�p�O�P�x�����Ăяo���K�v������B
     */
    static HRESULT init();

    static HRESULT initKeybord();
    static HRESULT initMouse();
    static HRESULT initJoyStick();

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
     * ���ʂ� _mouse_state �̕\�����Ɋi�[�����B
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
     * ���ʂ� _keyboard_state �̕\�����Ɋi�[�����B
     */
    static void updateKeyboardState();

    /**
     * �L�[�{�[�h�̃L�[�̏�Ԃ𒲂ׂ� .
     * @param prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedKey(int prm_DIK) {
        return (_keyboard_state[_flip_ks][prm_DIK] & 0x80) ? true : false;
    }

    /**
     * ������Ă���L�[�{�[�h�̃L�[�𒲂ׂ� .
     * @return �����ꂽ�L�[(DIK_* �萔) / -1:����������Ă��Ȃ�
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
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownKey(int prm_DIK);

    /**
     * �L�[�{�[�h�̉����ꂽ����̃L�[�𒲂ׂ� .
     * @return �����ꂽ����̃L�[(DIK_*) / 0:����������Ă��Ȃ�
     */
    static int getPushedDownKey();

    /**
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͗����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isReleasedUpDownKey(int prm_DIK);

    /**
     * �W���C�X�e�B�b�N�̏�Ԃ��X�V .
     * ���ʂ� _joy_state �Ɋi�[�����B
     */
    static void updateJoystickState();

    /**
     * �W���C�X�e�B�b�N�̃{�^���̏�Ԃ𒲂ׂ� .
     * @param prm_joy_button_no �W���C�X�e�B�b�N�{�^���ԍ�
     * @return  true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyButton(int prm_joy_button_no) {
        return (_joy_state[_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? true : false;
    }

    /**
     * ������Ă���W���C�X�e�B�b�N�̃{�^���𒲂ׂ� .
     * @return �����ꂽ�W���C�X�e�B�b�N�{�^���ԍ�(0�`15) / -1:����������Ă��Ȃ�
     */
    static inline int getBeingPressedJoyRgbButton() {
        for (int i = 0; i < 16; i ++) {
            if (_joy_state[_flip_js].rgbButtons[i] & 0x80) {
                return i;
            }
        }
        return -1;
    }

    static bool isPushedDownJoyRgbButton(int prm_joy_button_no);

    static int getPushedDownJoyRgbButton();

    /**
     * �W���C�X�e�B�b�N�̏�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyUp() {
        return (_joy_state[_flip_js].lY < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyDown() {
        return (_joy_state[_flip_js].lY > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̍������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyLeft() {
        return (_joy_state[_flip_js].lX < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉E�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedJoyRight() {
        return (_joy_state[_flip_js].lX > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�̉����Ă�������̂𒲂ׂ� .
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getBeingPressedJoyDirection();

    static inline bool isBeingPressedJoyXAxisPlus() {
        return (_joy_state[_flip_js].lX > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyXAxisMinus() {
        return (_joy_state[_flip_js].lX < -127) ? true : false;
    }
    static inline bool isBeingPressedJoyYAxisPlus() {
        return (_joy_state[_flip_js].lY > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyYAxisMinus() {
        return (_joy_state[_flip_js].lY < -127) ? true : false;
    }
    static inline bool isBeingPressedJoyZAxisPlus() {
        return (_joy_state[_flip_js].lZ > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyZAxisMinus() {
        return (_joy_state[_flip_js].lZ < -127) ? true : false;
    }
    static inline bool isBeingPressedJoyRxPlus() {
        return (_joy_state[_flip_js].lRx > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyRxMinus() {
        return (_joy_state[_flip_js].lRx < -127) ? true : false;
    }
    static inline bool isBeingPressedJoyRyPlus() {
        return (_joy_state[_flip_js].lRy > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyRyMinus() {
        return (_joy_state[_flip_js].lRy < -127) ? true : false;
    }
    static inline bool isBeingPressedJoyRzPlus() {
        return (_joy_state[_flip_js].lRz > 127) ? true : false;
    }
    static inline bool isBeingPressedJoyRzMinus() {
        return (_joy_state[_flip_js].lRz < -127) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̏�����̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedPovUp() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (29750 <= n || n < 7250)) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̉������̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedPovDown() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (11750 <= n && n < 24250) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̍������̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedPovLeft() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (20750 <= n && n < 33250) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̉E�����̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isBeingPressedPovRight() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (2750 <= n && n < 15250) ? true : false;
    }
    /**
     * �n�b�g�X�C�b�`�̉����Ă�������̂𒲂ׂ� .
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getBeingPressedPovDirection();

    static void release();

};

}
#endif /*GGAFDXCORE_GGAFDXINPUT_H_*/
