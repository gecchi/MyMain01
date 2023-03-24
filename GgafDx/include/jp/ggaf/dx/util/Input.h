#ifndef GGAF_DX_INPUT_H_
#define GGAF_DX_INPUT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <dinput.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

//P�L�[���������Ƃ�����_TRACE_(�f�o�b�O�p)
#define _PTRACE_(M) {if (Input::isPressedKey(DIK_P)) { _TRACE_(M); }}

namespace GgafDx {

/**
 * DirectInput ���[�e�B���e�B�N���X .
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class Input {

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
    static DIMOUSESTATE2 _di_mouse_state[2];
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


    struct MouseState {
         bool buttons[8];
    };
    static MouseState _win_mouse_state[2];

//    // �}�E�X���W���擾����
//    static POINT _mouse_point[2];


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
     * ���ʂ� _di_mouse_state �̕\�����Ɋi�[�����B
     */
    static void updateMouseState();

    /**
     * �}�E�X�̃{�^���̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
//    static bool isPressedMouseButton_old(int prm_button_no);
    static bool isPressedMouseButton(int prm_button_no);
    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͉����ꂽ����ł���^false�F�����ł͖���
     */
//    static bool isPushedDownMouseButton_old(int prm_button_no);
    static bool isPushedDownMouseButton(int prm_button_no);
    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�
     * @return true�F���̃{�^���͗����ꂽ����ł���^false�F�����ł͖���
     */
//    static bool isReleasedUpMouseButton_old(int prm_button_no);
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
    static inline bool isPressedKey(int prm_DIK) {
        return (_keyboard_state[_flip_ks][prm_DIK] & 0x80) ? true : false;
    }

    /**
     * ������Ă���L�[�{�[�h�̃L�[�𒲂ׂ� .
     * @return �����ꂽ�L�[(DIK_* �萔) / -1:����������Ă��Ȃ�
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
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownKey(int prm_DIK);

    /**
     * �L�[�{�[�h�̉����ꂽ����̃L�[�𒲂ׂ� .
     * @return �����ꂽ����̃L�[(DIK_*) / -1:����������Ă��Ȃ�
     */
    static int getFirstPushedDownKey();

    /**
     * �L�[�{�[�h�̃L�[�������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_DIK prm_DIK ���ׂ����L�[(DIK_*)
     * @return true�F���̃L�[�͗����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isReleasedUpKey(int prm_DIK);

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
    static inline bool isPressedJoyButton(int prm_joy_button_no) {
        return (_joy_state[_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? true : false;
    }

    /**
     * ������Ă���W���C�X�e�B�b�N�̃{�^���𒲂׍ŏ��̂P�̌��ʂ�Ԃ� .
     * @return �����ꂽ�W���C�X�e�B�b�N�{�^���ԍ�(0�`15) / -1:����������Ă��Ȃ�
     */
    static inline int getFirstPressedJoyRgbButton() {
        for (int i = 0; i < 16; i ++) {
            if (_joy_state[_flip_js].rgbButtons[i] & 0x80) {
                return i;
            }
        }
        return -1;
    }

    /**
     * �W���C�X�e�B�b�N�{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_joy_button_no �W���C�X�e�B�b�N�{�^���ԍ�
     * @return true�F���̃{�^���͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownJoyRgbButton(int prm_joy_button_no);

    /**
     * ������Ă���W���C�X�e�B�b�N�{�^���ԍ��𒲂׍ŏ��̂P�̌��ʂ�Ԃ� .
     * @return �W���C�X�e�B�b�N�{�^���ԍ�
     */
    static int getFirstPushedDownJoyRgbButton();

    /**
     * �W���C�X�e�B�b�N�̏�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyUp() {
        return (_joy_state[_flip_js].lY < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyDown() {
        return (_joy_state[_flip_js].lY > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̍������̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyLeft() {
        return (_joy_state[_flip_js].lX < -127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̉E�����̏�Ԃ𒲂ׂ� .
     * @return true�F�W���C�X�e�B�b�N�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyRight() {
        return (_joy_state[_flip_js].lX > 127) ? true : false;
    }

    /**
     * �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�̉����Ă�������̂𒲂ׂ� .
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getPressedJoyDirection();

    static inline bool isPressedJoyXAxisPlus() {
        return (_joy_state[_flip_js].lX > 127) ? true : false;
    }
    static inline bool isPressedJoyXAxisMinus() {
        return (_joy_state[_flip_js].lX < -127) ? true : false;
    }
    static inline bool isPressedJoyYAxisPlus() {
        return (_joy_state[_flip_js].lY > 127) ? true : false;
    }
    static inline bool isPressedJoyYAxisMinus() {
        return (_joy_state[_flip_js].lY < -127) ? true : false;
    }
    static inline bool isPressedJoyZAxisPlus() {
        return (_joy_state[_flip_js].lZ > 127) ? true : false;
    }
    static inline bool isPressedJoyZAxisMinus() {
        return (_joy_state[_flip_js].lZ < -127) ? true : false;
    }
    static inline bool isPressedJoyRxPlus() {
        return (_joy_state[_flip_js].lRx > 127) ? true : false;
    }
    static inline bool isPressedJoyRxMinus() {
        return (_joy_state[_flip_js].lRx < -127) ? true : false;
    }
    static inline bool isPressedJoyRyPlus() {
        return (_joy_state[_flip_js].lRy > 127) ? true : false;
    }
    static inline bool isPressedJoyRyMinus() {
        return (_joy_state[_flip_js].lRy < -127) ? true : false;
    }
    static inline bool isPressedJoyRzPlus() {
        return (_joy_state[_flip_js].lRz > 127) ? true : false;
    }
    static inline bool isPressedJoyRzMinus() {
        return (_joy_state[_flip_js].lRz < -127) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̏�����̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovUp() {
        if (Input::_pJoystickInputDevice) { //JoyStick�������ꍇ�ArgdwPOV[0]=0�̂��߁A��Ɣ��肳��邱�Ƃ�h��
            DWORD n = _joy_state[_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (29750 <= n || n < 7250)) ? true : false;
        } else {
            return false;
        }

    }

    /**
     * �n�b�g�X�C�b�`�̉������̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovDown() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (11750 <= n && n < 24250) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̍������̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovLeft() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (20750 <= n && n < 33250) ? true : false;
    }

    /**
     * �n�b�g�X�C�b�`�̉E�����̏�Ԃ𒲂ׂ� .
     * @return true�F�n�b�g�X�C�b�`�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovRight() {
        DWORD n = _joy_state[_flip_js].rgdwPOV[0];
        return (2750 <= n && n < 15250) ? true : false;
    }
    /**
     * �n�b�g�X�C�b�`�̉����Ă�������̂𒲂ׂ� .
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getPressedPovDirection();

    static void release();

};

}
#endif /*GGAF_DX_INPUT_H_*/
