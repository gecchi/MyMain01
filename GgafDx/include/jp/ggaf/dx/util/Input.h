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

#define P1_JOY_STICK 0
#define P2_JOY_STICK 1

#define MAX_JOY_STICK_NUM 2

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
    /** �W���C�X�e�B�b�N�C���v�b�g�f�o�C�X, [0]:1P [1]:2P */
    static LPDIRECTINPUTDEVICE8 _apJoystickInputDevice[MAX_JOY_STICK_NUM];
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
    /** �W���C�X�e�B�b�N�̏��([0:1P/1:2P][0:�\�^1:��])  */
    static DIJOYSTATE _joy_state[MAX_JOY_STICK_NUM][2];
    /** ���ۂɎ擾�ł����W���C�X�e�B�b�N�� */
    static int _max_acquire_joy_stick_num;
    /** ���݃A�N�e�B�u�ȃW���C�X�e�B�b�N��Ԃ̕\��(0:�\�^1:��) */
    static int _flip_js;


    struct MouseState {
         bool buttons[8];
    };
    static MouseState _win_mouse_state[2];

    static int count_joy_stick_device_no;
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
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:���g�p
     * @return true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static bool isPressedMouseButton(int prm_button_no);

    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�(0~7)
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:���g�p
     * @return true�F���̃{�^���͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownMouseButton(int prm_button_no);

    /**
     * �}�E�X�̃{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_button_no �}�E�X�{�^���ԍ�(0~7)
     * 0:VK_LBUTTON
     * 1:VK_RBUTTON
     * 2:VK_MBUTTON
     * 3:VK_XBUTTON1
     * 4:VK_XBUTTON2
     * 5~7:���g�p
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
     * �L�[�{�[�h�̏�Ԃ��擾
     * @return BYTE[256] �̔z��
     */
    static inline BYTE* getKeyboardState() {
        return _keyboard_state[_flip_ks];
    }

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

    static void updateAllJoystickState();

    /**
     * �W���C�X�e�B�b�N�̏�Ԃ��X�V .
     * ���ʂ� Input::_joy_state �Ɋi�[�����B
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     */
    static void updateJoystickState(int prm_joystic_no);

    /**
     * �W���C�X�e�B�b�N�̃{�^���̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @param prm_joy_button_no �W���C�X�e�B�b�N�{�^���ԍ�
     * @return  true�F���̃{�^���͉�����Ă����Ԃł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyButton(int prm_joystic_no, int prm_joy_button_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? true : false;
    }

    static inline bool isPushedDownJoyButton(int prm_joystic_no, int prm_joy_button_no) {
        if (Input::isPressedJoyButton(prm_joystic_no, prm_joy_button_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgbButtons[prm_joy_button_no] & 0x80) ? false :  true;
        } else { //���͉����Ė���
            return false;
        }
    }

    /**
     * ������Ă���W���C�X�e�B�b�N�̃{�^���𒲂׍ŏ��̂P�̌��ʂ�Ԃ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return �����ꂽ�W���C�X�e�B�b�N�{�^���ԍ�(0�`15) / -1:����������Ă��Ȃ�
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
     * �W���C�X�e�B�b�N�{�^���������ꂽ����̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @param prm_joy_button_no �W���C�X�e�B�b�N�{�^���ԍ�
     * @return true�F���̃{�^���͉����ꂽ����ł���^false�F�����ł͖���
     */
    static bool isPushedDownJoyRgbButton(int prm_joystic_no, int prm_joy_button_no);

    /**
     * ������Ă���W���C�X�e�B�b�N�{�^���ԍ��𒲂׍ŏ��̂P�̌��ʂ�Ԃ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return �����ꂽ�W���C�X�e�B�b�N�{�^���ԍ�(0�`15) / -1:����������Ă��Ȃ�
     */
    static int getFirstPushedDownJoyRgbButton(int prm_joystic_no);

    /**
     * �W���C�X�e�B�b�N�̏�����̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�W���C�X�e�B�b�N�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyUp(int prm_joystic_no) {
        return Input::isPressedJoyYAxisMinus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyUp(int prm_joystic_no) {
        return Input::isPushedDownJoyYAxisMinus(prm_joystic_no);
    }

    /**
     * �W���C�X�e�B�b�N�̉������̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�W���C�X�e�B�b�N�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyDown(int prm_joystic_no) {
        return Input::isPressedJoyYAxisPlus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyDown(int prm_joystic_no) {
        return Input::isPushedDownJoyYAxisPlus(prm_joystic_no);
    }

    /**
     * �W���C�X�e�B�b�N�̍������̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�W���C�X�e�B�b�N�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyLeft(int prm_joystic_no) {
        return Input::isPressedJoyXAxisMinus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyLeft(int prm_joystic_no) {
        return Input::isPushedDownJoyXAxisMinus(prm_joystic_no);
    }

    /**
     * �W���C�X�e�B�b�N�̉E�����̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�W���C�X�e�B�b�N�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedJoyRight(int prm_joystic_no) {
        return Input::isPressedJoyXAxisPlus(prm_joystic_no);
    }

    static inline bool isPushedDownJoyRight(int prm_joystic_no) {
        return Input::isPushedDownJoyXAxisPlus(prm_joystic_no);
    }

    /**
     * �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�̉����Ă�������̂𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getPressedJoyDirection(int prm_joystic_no);

    /**
     * �W���C�X�e�B�b�N�̃A�i���O�X�e�B�b�N�������ꂽ�u�ԂȂ̂��𒲂ׂ�i5�Ԃ̓j���[�g�����ƂȂ����u�Ԃ͕Ԃ�j .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 1�`9�F�����ԍ��W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g�����ɂȂ����u�Ԃł���B
     *         -1:�A�i���O�X�e�B�b�N�̏�Ԃɕω��Ȃ��B�i������ςȂ����A�����ƃj���[�g�����j�B
     */
    static int getPushedDownJoyDirection(int prm_joystic_no);

    static inline bool isPressedJoyXAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lX > 127) ? true : false;
    }

    static inline bool isPushedDownJoyXAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRight(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lX > 127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }


    static inline bool isPressedJoyXAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lX < -127) ? true : false;
    }

    static inline bool isPushedDownJoyXAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyXAxisMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lX < -127) ? false : true ;
        } else { //���͉����Ė���
            return false;
        }
    }


    static inline bool isPressedJoyYAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lY > 127) ? true : false;
    }

    static inline bool isPushedDownJoyYAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyYAxisPlus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lY > 127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyYAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lY < -127) ? true : false;
    }

    static inline bool isPushedDownJoyYAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyYAxisMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lY < -127) ?  false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyZAxisPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lZ > 127) ? true : false;
    }

    static inline bool isPushedDownJoyZAxisPlus(int prm_joystic_no) {
        if (Input::isPressedJoyZAxisPlus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lZ > 127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyZAxisMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lZ < -127) ? true : false;
    }
    static inline bool isPushedDownJoyZAxisMinus(int prm_joystic_no) {
        if (Input::isPressedJoyZAxisMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lZ < -127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyRxPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRx > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRxPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRxPlus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRx > 127) ? false  : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyRxMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRx < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRxMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRxMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRx < -127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }
    static inline bool isPressedJoyRyPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRy > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRyPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRyPlus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRy > 127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyRyMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRy < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRyMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRyMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRy < -127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyRzPlus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRz > 127) ? true : false;
    }
    static inline bool isPushedDownJoyRzPlus(int prm_joystic_no) {
        if (Input::isPressedJoyRzPlus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRz > 127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    static inline bool isPressedJoyRzMinus(int prm_joystic_no) {
        return (Input::_joy_state[prm_joystic_no][Input::_flip_js].lRz < -127) ? true : false;
    }
    static inline bool isPushedDownJoyRzMinus(int prm_joystic_no) {
        if (Input::isPressedJoyRzMinus(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            return (Input::_joy_state[prm_joystic_no][!Input::_flip_js].lRz < -127) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    /**
     * �n�b�g�X�C�b�`�̏�����̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�n�b�g�X�C�b�`�̏������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovUp(int prm_joystic_no) {
        if (Input::_apJoystickInputDevice[prm_joystic_no]) { //JoyStick�������ꍇ�ArgdwPOV[0]=0�̂��߁A��Ɣ��肳��邱�Ƃ�h��
            DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && ( (31500 <= n && n <= 36000) || (0 <= n && n <= 4500) ) ) ? true : false;
        } else {
            return false;
        }
    }

    static inline bool isPushedDownPovUp(int prm_joystic_no) {
        if (Input::isPressedPovUp(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && ( (31500 <= n && n <= 36000) || (0 <= n && n <= 4500) ) ) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }


    /**
     * �n�b�g�X�C�b�`�̉E�����̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�n�b�g�X�C�b�`�̉E������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovRight(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (4500 <= n && n <= 13500)) ? true : false;
    }

    static inline bool isPushedDownPovRight(int prm_joystic_no) {
        if (Input::isPressedPovRight(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (4500 <= n && n <= 13500)) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    /**
     * �n�b�g�X�C�b�`�̉������̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�n�b�g�X�C�b�`�̉�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovDown(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (13500 <= n && n <= 22500)) ? true : false;
    }

    static inline bool isPushedDownPovDown(int prm_joystic_no) {
        if (Input::isPressedPovDown(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (13500 <= n && n <= 22500)) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    /**
     * �n�b�g�X�C�b�`�̍������̏�Ԃ𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return true�F�n�b�g�X�C�b�`�̍�������ON�ł���^false�F�����ł͖���
     */
    static inline bool isPressedPovLeft(int prm_joystic_no) {
        DWORD n = Input::_joy_state[prm_joystic_no][Input::_flip_js].rgdwPOV[0];
        return (LOWORD(n) != 0xFFFF && (22500 <= n && n <= 31500)) ? true : false;
    }
    static inline bool isPushedDownPovLeft(int prm_joystic_no) {
        if (Input::isPressedPovLeft(prm_joystic_no)) { //���͉����Ă���
            //�O��Z�b�g[!Input::_flip_js]�͉����Ė��� => OK
            DWORD n = Input::_joy_state[prm_joystic_no][!Input::_flip_js].rgdwPOV[0];
            return (LOWORD(n) != 0xFFFF && (22500 <= n && n <= 31500)) ? false : true;
        } else { //���͉����Ė���
            return false;
        }
    }

    /**
     * �W���C�X�e�B�b�N�̃n�b�g�X�C�b�`��������Ă�������𒲂ׂ� .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return �����ԍ�1�`9(�W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g����)
     */
    static int getPressedPovDirection(int prm_joystic_no);

    /**
     * �W���C�X�e�B�b�N�̃n�b�g�X�C�b�`�������ꂽ�u�ԂȂ̂��𒲂ׂ�i5�Ԃ̓j���[�g�����ƂȂ����u�Ԃ͕Ԃ�j .
     * @param prm_joystic_no P1_JOY_STICK/P2_JOY_STICK
     * @return 1�`9�F�����ԍ��W�����A�e���L�[�̔ԍ��ɑΉ��A5�Ԃ̓j���[�g�����ɂȂ����u�Ԃł���B
     *         -1:�n�b�g�X�C�b�`�̏�Ԃɕω��Ȃ��B�i������ςȂ����A�����ƃj���[�g�����j�B
     */
    static int getPushedDownPovDirection(int prm_joystic_no);

    static void release();

};

}
#endif /*GGAF_DX_INPUT_H_*/
