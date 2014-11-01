#ifndef GGAFLIB_VIRTUALBUTTON_H_
#define GGAFLIB_VIRTUALBUTTON_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <string>
#include <map>
#include "jp/ggaf/dxcore/util/GgafDxInput.h"

#include "GgafLibCommonHeader.h"
typedef unsigned long int vbsta;

namespace GgafLib {

#define VB_BUTTON1        (0x1)        //&B 00000000 00000000 00000000 00000001
#define VB_BUTTON2        (0x2)        //&B 00000000 00000000 00000000 00000010
#define VB_BUTTON3        (0x4)        //&B 00000000 00000000 00000000 00000100
#define VB_BUTTON4        (0x8)        //&B 00000000 00000000 00000000 00001000
#define VB_BUTTON5        (0x10)       //&B 00000000 00000000 00000000 00010000
#define VB_BUTTON6        (0x20)       //&B 00000000 00000000 00000000 00100000
#define VB_BUTTON7        (0x40)       //&B 00000000 00000000 00000000 01000000
#define VB_BUTTON8        (0x80)       //&B 00000000 00000000 00000000 10000000
#define VB_BUTTON9        (0x100)      //&B 00000000 00000000 00000001 00000000
#define VB_BUTTON10       (0x200)      //&B 00000000 00000000 00000010 00000000
#define VB_BUTTON11       (0x400)      //&B 00000000 00000000 00000100 00000000
#define VB_BUTTON12       (0x800)      //&B 00000000 00000000 00001000 00000000
#define VB_BUTTON13       (0x1000)     //&B 00000000 00000000 00010000 00000000
#define VB_BUTTON14       (0x2000)     //&B 00000000 00000000 00100000 00000000
#define VB_BUTTON15       (0x4000)     //&B 00000000 00000000 01000000 00000000
#define VB_BUTTON16       (0x8000)     //&B 00000000 00000000 10000000 00000000
#define VB_PAUSE          (0x10000)    //&B 00000000 00000001 00000000 00000000
#define VB_UP             (0x20000)    //&B 00000000 00000010 00000000 00000000
#define VB_DOWN           (0x40000)    //&B 00000000 00000100 00000000 00000000
#define VB_LEFT           (0x80000)    //&B 00000000 00001000 00000000 00000000
#define VB_RIGHT          (0x100000)   //&B 00000000 00010000 00000000 00000000
                        //(0x200000)   //&B 00000000 00100000 00000000 00000000
                        //(0x400000)   //&B 00000000 01000000 00000000 00000000
#define VB_UI_UP          (0x800000)   //&B 00000000 10000000 00000000 00000000
#define VB_UI_DOWN        (0x1000000)  //&B 00000001 00000000 00000000 00000000
#define VB_UI_LEFT        (0x2000000)  //&B 00000010 00000000 00000000 00000000
#define VB_UI_RIGHT       (0x4000000)  //&B 00000100 00000000 00000000 00000000
#define VB_UI_EXECUTE     (0x8000000)  //&B 00001000 00000000 00000000 00000000
#define VB_UI_CANCEL      (0x10000000) //&B 00010000 00000000 00000000 00000000
#define VB_UI_DEBUG       (0x20000000) //&B 00100000 00000000 00000000 00000000
                       // (0x40000000) //&B 01000000 00000000 00000000 00000000

#define VB_MAP_BUFFER 120
#define VB_NUM 29

/**
 * ���z�{�^�� .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VirtualButton : public GgafCore::GgafObject {

public:
    /**
     * ���z�{�^�����X�g .
     */
    class VBRecord {
    public :
        VBRecord* _next; //���n��Ŏ��̃t���[���̓��͏��
        VBRecord* _prev; //���n��őO�̃t���[���̓��͏��
        vbsta _state;
    public:
        VBRecord() {
            _next = nullptr;
            _prev = nullptr;
            _state = (vbsta)0;
        }
        ~VBRecord() {
        }
    };


    struct KEYBOARDMAP {
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
        int BUTTON7;
        int BUTTON8;
        int BUTTON9;
        int BUTTON10;
        int BUTTON11;
        int BUTTON12;
        int BUTTON13;
        int BUTTON14;
        int BUTTON15;
        int BUTTON16;
        int PAUSE;
        int UP;
        int DOWN;
        int LEFT;
        int RIGHT;
        int UI_UP;
        int UI_DOWN;
        int UI_LEFT;
        int UI_RIGHT;
        int UI_EXECUTE;
        int UI_CANCEL;
        int UI_DEBUG;
    };

    struct JOYSTICKMAP {
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
        int BUTTON7;
        int BUTTON8;
        int BUTTON9;
        int BUTTON10;
        int BUTTON11;
        int BUTTON12;
        int BUTTON13;
        int BUTTON14;
        int BUTTON15;
        int BUTTON16;
        int PAUSE;
        int UP;
        int DOWN;
        int LEFT;
        int RIGHT;
        int UI_UP;
        int UI_DOWN;
        int UI_LEFT;
        int UI_RIGHT;
        int UI_EXECUTE;
        int UI_CANCEL;
        int UI_DEBUG;
    };

public:
    /** �L�[�{�[�h���蓖�Ēl */
    static KEYBOARDMAP _keyboardmap;
    /** �W���C�X�e�B�b�N���蓖�Ēl */
    static JOYSTICKMAP _joystickmap;

    static std::map<std::string, int> _mapStr2Dik;
    static std::map<std::string, int> _mapStr2JoyBtn;
    static std::map<int, std::string> _mapDik2Str;
    static std::map<int, std::string> _mapJoyBtn2Str;

    typedef bool (*funcVJBtn)(void);
    static std::map<int, funcVJBtn> _mapVJoyBtn2Func;

    static bool _is_init;


    /** �I�[�g���s�[�g����p�J�E���^�[ */
    std::map<vbsta, frame> _auto_repeat_counter;
    /** �I�[�g���s�[�g���Ȃ�� true */
    bool _is_auto_repeat;

    bool _with_pov;
    VBReplayRecorder* _pRpy;

    /** [r]���v���C���[�h��:true�^���[�U�[���́i���v���C���[�h�L���j���[�h:false */
    bool _is_replaying;
    /** [r]�������:false�^���v���C���[�h�I��:true */
    bool _was_replay_done;
    /** ���݃t���[���̓��͏�� */
    VirtualButton::VBRecord* _pVBRecord_active;

public:
    /**
     * �R���X�g���N�^ .
     * �����̃��v���C�t�@�C�������݂���ꍇ�����v���C�[���[�h�B
     * �����̃��v���C�t�@�C�������݂��Ȃ��ꍇ�����[�U�[���͎�t �� ���v���C�t�@�C���L�����[�h�B
     * @param prm_replay_file ���v���C�t�@�C��
     */
    VirtualButton(const char* prm_replay_file = "VirtualButton.rep");
    /**     * �ߋ��̓��͏�Ԃ��擾 .     * @param prm_frame_ago ���݂�艽�t���[���ߋ������w��     * @return �ߋ��̓��͏��     */    VirtualButton::VBRecord* getPastVBRecord(frame prm_frame_ago);

    /**
     * ���݃{�^����������Ă��邩���� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    inline vbsta isBeingPressed(vbsta prm_VB) {
        return (_pVBRecord_active->_state & prm_VB);
    }

    /**
     * ���݃{�^����������Ă��Ȃ������� .
     * isBeingPressed(vbsta) �̔ے�̌��ʂ��Ԃ�B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    vbsta isNotBeingPressed(vbsta prm_VB);

    /**
     * �ߋ��Ƀ{�^����������Ă������ǂ������� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     * 1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isBeingPressed(vbsta) �Ɠ����Ӗ��ɂȂ�B
     * �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true / false
     */
    vbsta wasBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * �ߋ��Ƀ{�^����������Ă��Ȃ������̂��ǂ������� .
     * wasBeingPressed(vbsta, frame) �̔ے�̌��ʂ��Ԃ�B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isBeingPressed(vbsta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true / false
     */
    vbsta wasNotBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * ���݃{�^���������ꂽ�u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă���A���A�P�t���[���O�͉�����Ă��Ȃ��ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    inline vbsta isPushedDown(vbsta prm_VB) {
        return (!(_pVBRecord_active->_prev->_state & prm_VB) && (_pVBRecord_active->_state & prm_VB)) ? true : false;
    }

    /**
     * �ߋ��Ƀ{�^���������ꂽ�u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă����A���A(prm_frame_ago+1)�t���[���O�͉�����Ă��Ȃ������ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isPushedDown(vbsta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true / false
     */
    vbsta wasPushedDown(vbsta prm_VB, frame prm_frame_ago);

    /**
     * ���݃{�^���𗣂����u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă��Ȃ��A���A�P�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    vbsta isReleasedUp(vbsta prm_VB);

    /**
     * �ߋ��Ƀ{�^���𗣂����u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă��Ȃ������A���A(prm_frame_ago+1)�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isReleasedUp(vbsta) �Ɠ����Ӗ��ɂȂ�B
     * @return true / false
     */
    vbsta wasReleasedUp(vbsta prm_VB, frame prm_frame_ago);

    /**
     * �`������������ .
     * �u�{�^���������Ă��Ȃ��������{�^�������������{�^���𗣂����v�Ƃ�����ԑJ�ڂ��A
     * ���ݐ����������ǂ������肷��B
     * �A�������Ă������Ԃ� prm_frame_push �ȏ㉟���Ă���Ɛ������Ȃ��i�`���������ƔF�߂��Ȃ��j�B
     * �����Ƃ��Γƕ���G�{�^������Ȃ� prm_frame_push=2 ���w��B��ɺ���;
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_push ���e����{�^���������Ă������ԃt���[��(default=5)
     * @return true / false
     */
    vbsta isPushedUp(vbsta prm_VB, frame prm_frame_push = 5);

    /**
     * �_�u���v�b�V������ .
     * �u(a)�{�^���������Ă��Ȃ�������(b)�{�^������������(c)�{�^���𗣂�����(d)�{�^�����������v�Ƃ�����ԑJ�ڂ��A
     * ���ݐ����������ǂ������肷��B
     * �A��   (b)�`(c)�̉����Ă������Ԃ� prm_frame_push �ȏ㉟���Ă���Ɛ������Ȃ��B
     * ����� (c)�`(d)�̂Q��ڂ̃{�^�������܂ł̊��Ԃ� prm_frame_delay �ȏ�J���Ă���Ɛ������Ȃ��B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_push ���e����(b)�`(c) �̊���
     * @param prm_frame_delay ���e����(c)�`(d) �̊���
     * @return true / false
     */
    vbsta isDoublePushedDown(vbsta prm_VB, frame prm_frame_push = 5, frame prm_frame_delay = 5);

    /**
     * �����{�^�������������� .
     * isPushedDown(vbsta) �̈����ɕ����{�^�����w�肵�Ĕ�����s���΁A������������͉\�ł���B
     * �������A���̔�����@�͕����{�^���������ۂ�1�t���[���ł��o���c�L������ΐ��������A
     * ���S�ɓ����ɉ����Ȃ���΂Ȃ�Ȃ����߁A�V�r�A������Ƃ������_������B
     * �����ŁA�{���\�b�h�́A���������̃o���c�L�����e�l������������������ł���B
     * ��̓I�ɂ́A�����̂��ꂼ��̊e�{�^���̌��݂Ɏ���܂ł̂S�t���[���̏�ԗ������A
     * ���̂����ꂩ�̏�ԑJ�ڂł����1�񐬗��Ƃ���������s���Ă���B(�܂�3�t���[���P�\)
     * <pre>
     * �� > �H > �H > ��
     *       or
     * �H > �� > �H > ��
     *       or
     * �H > �H > �� > ��
     *
     * �����F�����Ă��� �^ ���F�����Ă��� �^ �H�F�C��
     * ����ԉE�����݂̏�ԁA�����ߋ�
     * </pre>
     * @param prm_aVB (3�t���P�\)������������Ώۉ��z�{�^���z��
     * @param prm_num_button �z��̗v�f��
     * @return true / false
     */
    vbsta arePushedDownAtOnce(vbsta prm_aVB[], int prm_num_button);

    /**
     * �R�t���P�\�̂Q�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @return true / false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2) {
        vbsta vb[2];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        return arePushedDownAtOnce(vb, 2);
    }

    /**
     * �R�t���P�\�̂R�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @param prm_VB3 ����Ώۉ��z�{�^���R
     * @return true / false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3) {
        vbsta vb[3];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        return arePushedDownAtOnce(vb, 3);
    }

    /**
     * �R�t���P�\�̂S�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @param prm_VB3 ����Ώۉ��z�{�^���R
     * @param prm_VB4 ����Ώۉ��z�{�^���S
     * @return true / false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3, vbsta prm_VB4) {
        vbsta vb[4];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        vb[3] = prm_VB4;
        return arePushedDownAtOnce(vb, 4);
    }

    /**
     * �I�[�g���s�[�g���͔��� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_begin_repeat �I�[�g���s�[�g�J�n�t���[����
     * @param prm_while_repeat �I�[�g���s�[�g�J�n��A���s�[�g�Ԋu�t���[����
     * @return true / false
     */
    vbsta isAutoRepeat(vbsta prm_VB, frame prm_begin_repeat = 20, frame prm_while_repeat = 5);

    /**
     * �O���b�ƃ|�����ۂ����� .
     * �U���M�G�t�̃X�N�����[�p�C���h���C�o�[�R�}���h���͔���ł��B
     * ��̓I�ɂ́Aprm_frame_delay �ȓ���
     * �� �� �� �� �̂S�����{�^��������������AisPushedDown(prm_VB) �������B
     * �̏ꍇ�� true �Ƃ��Ă��܂��B
     * @param prm_VB �u�O���b�ƃ|���v�́u�|���v�̃{�^��
     * @param prm_frame_delay �u�O���b�ƃ|���v����������S�̂̋��e�t���[��
     * @return true / false
     */
    bool isScrewPushDown(vbsta prm_VB, frame prm_frame_delay=30);


    vbsta getPushedDownStick();


    vbsta getState();

    /**
     * ���͏����X�V .
     * �ʏ펞�̓L�[���́A�W���C�X�e�B�b�N�A�}�E�X�̃f�o�C�X�ɓ��͂ɂ��A�����X�e�[�g���X�V�B
     * �A���A���v���C�Đ����́A�ǂݍ��܂ꂽ�O���t�@�C���̃f�[�^�ŁA�����X�e�[�g���X�V�B
     */
    void update();

    void init();

    void clear();

    static bool isBeingPressedVirtualJoyButton(int prm_virtual_joy_button_no);

    static int getPushedDownVirtualJoyButton();

    virtual ~VirtualButton();
};

}
#endif /*GGAFLIB_VIRTUALBUTTON_H_*/
