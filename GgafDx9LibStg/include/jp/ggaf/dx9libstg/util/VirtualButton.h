#ifndef VBRTUALBUTTON_H_
#define VBRTUALBUTTON_H_

typedef _MAP_<string, int> keymap;
typedef unsigned long int vbsta;

namespace GgafDx9LibStg {

#define VB_BUTTON1 (0x1)
#define VB_BUTTON2 (0x2)
#define VB_BUTTON3 (0x4)
#define VB_BUTTON4 (0x8)
#define VB_BUTTON5 (0x10)
#define VB_BUTTON6 (0x20)
#define VB_BUTTON7 (0x40)
#define VB_BUTTON8 (0x80)

#define VB_PAUSE   (0x400)
#define VB_UP      (0x800)
#define VB_DOWN    (0x1000)
#define VB_LEFT    (0x2000)
#define VB_RIGHT   (0x4000)

#define VB_UI_UP      (0x8000)
#define VB_UI_DOWN    (0x10000)
#define VB_UI_LEFT    (0x20000)
#define VB_UI_RIGHT   (0x40000)
#define VB_UI_EXECUTE (0x80000)
#define VB_UI_CANCEL  (0x100000)
#define VB_UI_DEBUG   (0x200000)

#define VB_NEUTRAL_STC    (0x400000)   //&B 00000000 01000000 00000000 00000000
#define VB_UP_RIGHT_STC   (0x800000)   //&B 00000000 10000000 00000000 00000000
#define VB_DOWN_RIGHT_STC (0x1000000)  //&B 00000001 00000000 00000000 00000000
#define VB_DOWN_LEFT_STC  (0x2000000)  //&B 00000010 00000000 00000000 00000000
#define VB_UP_LEFT_STC    (0x4000000)  //&B 00000100 00000000 00000000 00000000
#define VB_UP_STC         (0x8000000)  //&B 00001000 00000000 00000000 00000000
#define VB_RIGHT_STC      (0x10000000) //&B 00010000 00000000 00000000 00000000
#define VB_DOWN_STC       (0x20000000) //&B 00100000 00000000 00000000 00000000
#define VB_LEFT_STC       (0x40000000) //&B 01000000 00000000 00000000 00000000

#define VB_STC_CLIP_MASK  (0x803FFFFF) //&B 10000000 00111111 11111111 11111111
#define VB_STC_MASK       (0x7FC00000) //&B 01111111 11000000 00000000 00000000

#define VB_MAP_BUFFER 120
#define VB_NUM 29



/**
 * ���z�{�^�� .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VirtualButton {

public:

    struct KEYBOARDMAP {
        int BUTTON1;
        int BUTTON2;
        int BUTTON3;
        int BUTTON4;
        int BUTTON5;
        int BUTTON6;
        int BUTTON7;
        int BUTTON8;
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
        int PAUSE;
        int UI_EXECUTE;
        int UI_CANCEL;
    };

    static KEYBOARDMAP _tagKeymap;
    static JOYSTICKMAP _tagJoymap;

    /**
     * ���z�{�^���R���e�i .
     */
    class VBRecord {
    public :
        VBRecord* _next; //���n��Ŏ��̃t���[���̓��͏��
        VBRecord* _prev; //���n��őO�̃t���[���̓��͏��

        vbsta _state;

        VBRecord() {
            //for (int i = 0; i < VB_NUM; i++) {_state[i] = false;}
            _next = NULL;
            _prev = NULL;
            _state = (vbsta)0;
        }
        ~VBRecord() {
        }
    };
    /** �I�[�g���s�[�g����p�J�E���^�[ */
    _MAP_<vbsta, frame> _repeat_counter;
    /** �I�[�g���s�[�g���Ȃ�� true */
    bool _is_auto_repeat;

    static keymap _mapDIK;
    static bool _is_init;




    VirtualButton();

    VBRecord* _pVBRecord_Active; //���݃t���[���̓��͏��

    VBRecord* getPastVBRecord(frame prm_frame_ago);

    /**
     * ���݃{�^����������Ă��邩���� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true/false
     */
    vbsta isBeingPressed(vbsta prm_VB);

    /**
     * ���݃{�^����������Ă��Ȃ������� .
     * isBeingPressed(vbsta) �̔ے�̌��ʂ��Ԃ�B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true/false
     */
    vbsta isNotBeingPressed(vbsta prm_VB);

    /**
     * �ߋ��Ƀ{�^����������Ă������ǂ������� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isBeingPressed(vbsta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true/false
     */
    vbsta wasBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * �ߋ��Ƀ{�^����������Ă��Ȃ������̂��ǂ������� .
     * wasBeingPressed(vbsta, frame) �̔ے�̌��ʂ��Ԃ�B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isBeingPressed(vbsta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true/false
     */
    vbsta wasNotBeingPressed(vbsta prm_VB, frame prm_frame_ago);

    /**
     * ���݃{�^���������ꂽ�u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă���A���A�P�t���[���O�͉�����Ă��Ȃ��ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true/false
     */
    vbsta isPushedDown(vbsta prm_VB);

    /**
     * �ߋ��Ƀ{�^���������ꂽ�u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă����A���A(prm_frame_ago+1)�t���[���O�͉�����Ă��Ȃ������ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isPushedDown(vbsta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true/false
     */
    vbsta wasPushedDown(vbsta prm_VB, frame prm_frame_ago);

    /**
     * ���݃{�^���𗣂����u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă��Ȃ��A���A�P�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true/false
     */
    vbsta isReleasedUp(vbsta prm_VB);

    /**
     * �ߋ��Ƀ{�^���𗣂����u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă��Ȃ������A���A(prm_frame_ago+1)�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isReleasedUp(vbsta) �Ɠ����Ӗ��ɂȂ�B
     * @return true/false
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
     * @return true/false
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
     * @return true/false
     */
    vbsta isDoublePushedDown(vbsta prm_VB, frame prm_frame_push = 5, frame prm_frame_delay = 5);

    /**
     * �����{�^�������������� .
     * isPushedDown(vbsta) �̈����ɕ����{�^�����w�肵�Ĕ�����s���΁A������������͉\�ł���B
     * �������A�����{�^���������ۂ�1�t���[���ł��o���c�L������ΐ��������A���S�ɓ����ɉ����Ȃ����
     * �Ȃ�Ȃ��Ƃ������_������B
     * �����ŁA�{���\�b�h�́A���̃o���c�L���l������������������ł���B
     * ��̓I�ɂ́A�����̂��ꂼ��̊e�{�^���̌��݂Ɏ���܂ł̂S�t���[���̏�ԗ������A
     * ���̂����ꂩ�̏�ԑJ�ڂł����1�񐬗��Ƃ���������s���Ă���B
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
     * @param prm_aVB ������������Ώۉ��z�{�^���z��
     * @param prm_iButtonNum �z��̗v�f��
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_aVB[], int prm_iButtonNum);

    /**
     * �Q�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2) {
        vbsta vb[2];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        return arePushedDownAtOnce(vb, 2);
    }

    /**
     * �R�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @param prm_VB3 ����Ώۉ��z�{�^���R
     * @return true/false
     */
    vbsta arePushedDownAtOnce(vbsta prm_VB1, vbsta prm_VB2, vbsta prm_VB3) {
        vbsta vb[3];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        return arePushedDownAtOnce(vb, 3);
    }

    /**
     * �S�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @param prm_VB3 ����Ώۉ��z�{�^���R
     * @param prm_VB4 ����Ώۉ��z�{�^���S
     * @return true/false
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
     * @return true/false
     */
    vbsta isAutoRepeat(vbsta prm_VB);

    /**
     * �O���b�ƃ|�����ۂ����� .
     * �U���M�G�t�̃X�N�����[�p�C���h���C�o�[�R�}���h���͔���ł��B
     * ��̓I�ɂ́Aprm_frame_delay �ȓ���
     * �� �� �� �� �̂S�����{�^��������������AisPushedDown(prm_VB) �������B
     * �̏ꍇ�� true �Ƃ��Ă��܂��B
     * @param prm_VB �u�O���b�ƃ|���v�́u�|���v�̃{�^��
     * @param prm_frame_delay �u�O���b�ƃ|���v���������鋖�e�t���[��
     * @return true/false
     */
    bool isRoundPushDown(vbsta prm_VB, frame prm_frame_delay=30);


    /**
     * ���݉������ςȂ��̃X�e�B�b�N�̔ԍ���Ԃ��B
     * @return ���̉��ꂩ
     * VB_UP_STC
     * VB_UP_RIGHT_STC
     * VB_RIGHT_STC
     * VB_DOWN_RIGHT_STC
     * VB_DOWN_STC
     * VB_DOWN_LEFT_STC
     * VB_LEFT_STC
     * VB_UP_LEFT_STC
     * VB_NEUTRAL_STC
     */
    vbsta getBeingPressedStick();

    /**
     * ��PushedDown�X�e�B�b�N�̔ԍ���Ԃ��B
     * @return ���̉��ꂩ
     * VB_UP_STC
     * VB_UP_RIGHT_STC
     * VB_RIGHT_STC
     * VB_DOWN_RIGHT_STC
     * VB_DOWN_STC
     * VB_DOWN_LEFT_STC
     * VB_LEFT_STC
     * VB_UP_LEFT_STC
     * VB_NEUTRAL_STC
     */
    vbsta getPushedDownStick();


    vbsta isDoublePushedDownStick(frame prm_frame_push = 5, frame prm_frame_delay = 5);


//    /**
//     * ���Aprm_VB1�Ɠ�����PushedDown���ꂽ�X�e�B�b�N�̔ԍ���Ԃ��B
//     * @return ���̉��ꂩ
//     * VB_UP_STC
//     * VB_UP_RIGHT_STC
//     * VB_RIGHT_STC
//     * VB_DOWN_RIGHT_STC
//     * VB_DOWN_STC
//     * VB_DOWN_LEFT_STC
//     * VB_LEFT_STC
//     * VB_UP_LEFT_STC
//     * VB_NEUTRAL_STC
//     */
//    static vbsta getPushedDownStickWith(int prm_VB);


    //vbsta isClicked(vbsta prm_VB);

    void update();

    void init();

    void clear();




    virtual ~VirtualButton();
};

}
#endif /*VBRTUALBUTTON_H_*/
