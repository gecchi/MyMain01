#ifndef GGAF_LIB_VIRTUALBUTTON_H_
#define GGAF_LIB_VIRTUALBUTTON_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <map>
#include "jp/ggaf/dx/util/Input.h"

typedef int_fast32_t vbk;
typedef int_fast32_t vbj;
typedef uint64_t vb_sta;

namespace GgafLib {

#define VBK_ESCAPE          DIK_ESCAPE
#define VBK_1               DIK_1
#define VBK_2               DIK_2
#define VBK_3               DIK_3
#define VBK_4               DIK_4
#define VBK_5               DIK_5
#define VBK_6               DIK_6
#define VBK_7               DIK_7
#define VBK_8               DIK_8
#define VBK_9               DIK_9
#define VBK_0               DIK_0
#define VBK_MINUS           DIK_MINUS
#define VBK_EQUALS          DIK_EQUALS
#define VBK_BACK            DIK_BACK
#define VBK_TAB             DIK_TAB
#define VBK_Q               DIK_Q
#define VBK_W               DIK_W
#define VBK_E               DIK_E
#define VBK_R               DIK_R
#define VBK_T               DIK_T
#define VBK_Y               DIK_Y
#define VBK_U               DIK_U
#define VBK_I               DIK_I
#define VBK_O               DIK_O
#define VBK_P               DIK_P
#define VBK_LBRACKET        DIK_LBRACKET
#define VBK_RBRACKET        DIK_RBRACKET
#define VBK_RETURN          DIK_RETURN
#define VBK_LCONTROL        DIK_LCONTROL
#define VBK_A               DIK_A
#define VBK_S               DIK_S
#define VBK_D               DIK_D
#define VBK_F               DIK_F
#define VBK_G               DIK_G
#define VBK_H               DIK_H
#define VBK_J               DIK_J
#define VBK_K               DIK_K
#define VBK_L               DIK_L
#define VBK_SEMICOLON       DIK_SEMICOLON
#define VBK_APOSTROPHE      DIK_APOSTROPHE
#define VBK_GRAVE           DIK_GRAVE
#define VBK_LSHIFT          DIK_LSHIFT
#define VBK_BACKSLASH       DIK_BACKSLASH
#define VBK_Z               DIK_Z
#define VBK_X               DIK_X
#define VBK_C               DIK_C
#define VBK_V               DIK_V
#define VBK_B               DIK_B
#define VBK_N               DIK_N
#define VBK_M               DIK_M
#define VBK_COMMA           DIK_COMMA
#define VBK_PERIOD          DIK_PERIOD
#define VBK_SLASH           DIK_SLASH
#define VBK_RSHIFT          DIK_RSHIFT
#define VBK_MULTIPLY        DIK_MULTIPLY
#define VBK_LMENU           DIK_LMENU
#define VBK_SPACE           DIK_SPACE
#define VBK_CAPITAL         DIK_CAPITAL
#define VBK_F1              DIK_F1
#define VBK_F2              DIK_F2
#define VBK_F3              DIK_F3
#define VBK_F4              DIK_F4
#define VBK_F5              DIK_F5
#define VBK_F6              DIK_F6
#define VBK_F7              DIK_F7
#define VBK_F8              DIK_F8
#define VBK_F9              DIK_F9
#define VBK_F10             DIK_F10
#define VBK_NUMLOCK         DIK_NUMLOCK
#define VBK_SCROLL          DIK_SCROLL
#define VBK_NUMPAD7         DIK_NUMPAD7
#define VBK_NUMPAD8         DIK_NUMPAD8
#define VBK_NUMPAD9         DIK_NUMPAD9
#define VBK_SUBTRACT        DIK_SUBTRACT
#define VBK_NUMPAD4         DIK_NUMPAD4
#define VBK_NUMPAD5         DIK_NUMPAD5
#define VBK_NUMPAD6         DIK_NUMPAD6
#define VBK_ADD             DIK_ADD
#define VBK_NUMPAD1         DIK_NUMPAD1
#define VBK_NUMPAD2         DIK_NUMPAD2
#define VBK_NUMPAD3         DIK_NUMPAD3
#define VBK_NUMPAD0         DIK_NUMPAD0
#define VBK_DECIMAL         DIK_DECIMAL
#define VBK_OEM_102         DIK_OEM_102
#define VBK_F11             DIK_F11
#define VBK_F12             DIK_F12
#define VBK_F13             DIK_F13
#define VBK_F14             DIK_F14
#define VBK_F15             DIK_F15
#define VBK_KANA            DIK_KANA
#define VBK_ABNT_C1         DIK_ABNT_C1
#define VBK_CONVERT         DIK_CONVERT
#define VBK_NOCONVERT       DIK_NOCONVERT
#define VBK_YEN             DIK_YEN
#define VBK_ABNT_C2         DIK_ABNT_C2
#define VBK_NUMPADEQUALS    DIK_NUMPADEQUALS
#define VBK_PREVTRACK       DIK_PREVTRACK
#define VBK_AT              DIK_AT
#define VBK_COLON           DIK_COLON
#define VBK_UNDERLINE       DIK_UNDERLINE
#define VBK_KANJI           DIK_KANJI
#define VBK_STOP            DIK_STOP
#define VBK_AX              DIK_AX
#define VBK_UNLABELED       DIK_UNLABELED
#define VBK_NEXTTRACK       DIK_NEXTTRACK
#define VBK_NUMPADENTER     DIK_NUMPADENTER
#define VBK_RCONTROL        DIK_RCONTROL
#define VBK_MUTE            DIK_MUTE
#define VBK_CALCULATOR      DIK_CALCULATOR
#define VBK_PLAYPAUSE       DIK_PLAYPAUSE
#define VBK_MEDIASTOP       DIK_MEDIASTOP
#define VBK_VOLUMEDOWN      DIK_VOLUMEDOWN
#define VBK_VOLUMEUP        DIK_VOLUMEUP
#define VBK_WEBHOME         DIK_WEBHOME
#define VBK_NUMPADCOMMA     DIK_NUMPADCOMMA
#define VBK_DIVIDE          DIK_DIVIDE
#define VBK_SYSRQ           DIK_SYSRQ
#define VBK_RMENU           DIK_RMENU
#define VBK_PAUSE           DIK_PAUSE
#define VBK_HOME            DIK_HOME
#define VBK_UP              DIK_UP
#define VBK_PRIOR           DIK_PRIOR
#define VBK_LEFT            DIK_LEFT
#define VBK_RIGHT           DIK_RIGHT
#define VBK_END             DIK_END
#define VBK_DOWN            DIK_DOWN
#define VBK_NEXT            DIK_NEXT
#define VBK_INSERT          DIK_INSERT
#define VBK_DELETE          DIK_DELETE
#define VBK_LWIN            DIK_LWIN
#define VBK_RWIN            DIK_RWIN
#define VBK_APPS            DIK_APPS
#define VBK_POWER           DIK_POWER
#define VBK_SLEEP           DIK_SLEEP
#define VBK_WAKE            DIK_WAKE
#define VBK_WEBSEARCH       DIK_WEBSEARCH
#define VBK_WEBFAVORITES    DIK_WEBFAVORITES
#define VBK_WEBREFRESH      DIK_WEBREFRESH
#define VBK_WEBSTOP         DIK_WEBSTOP
#define VBK_WEBFORWARD      DIK_WEBFORWARD
#define VBK_WEBBACK         DIK_WEBBACK
#define VBK_MYCOMPUTER      DIK_MYCOMPUTER
#define VBK_MAIL            DIK_MAIL
#define VBK_MEDIASELECT     DIK_MEDIASELECT

#define VBK_BACKSPACE       DIK_BACKSPACE
#define VBK_NUMPADSTAR      DIK_NUMPADSTAR
#define VBK_LALT            DIK_LALT
#define VBK_CAPSLOCK        DIK_CAPSLOCK
#define VBK_NUMPADMINUS     DIK_NUMPADMINUS
#define VBK_NUMPADPLUS      DIK_NUMPADPLUS
#define VBK_NUMPADPERIOD    DIK_NUMPADPERIOD
#define VBK_NUMPADSLASH     DIK_NUMPADSLASH
#define VBK_RALT            DIK_RALT
#define VBK_UPARROW         DIK_UPARROW
#define VBK_PGUP            DIK_PGUP
#define VBK_LEFTARROW       DIK_LEFTARROW
#define VBK_RIGHTARROW      DIK_RIGHTARROW
#define VBK_DOWNARROW       DIK_DOWNARROW
#define VBK_PGDN            DIK_PGDN



#define VBJ_BUTTON_01       (0x01)
#define VBJ_BUTTON_02       (0x02)
#define VBJ_BUTTON_03       (0x03)
#define VBJ_BUTTON_04       (0x04)
#define VBJ_BUTTON_05       (0x05)
#define VBJ_BUTTON_06       (0x06)
#define VBJ_BUTTON_07       (0x07)
#define VBJ_BUTTON_08       (0x08)
#define VBJ_BUTTON_09       (0x09)
#define VBJ_BUTTON_10       (0x0A)
#define VBJ_BUTTON_11       (0x0B)
#define VBJ_BUTTON_12       (0x0C)
#define VBJ_BUTTON_13       (0x0D)
#define VBJ_BUTTON_14       (0x0E)
#define VBJ_BUTTON_15       (0x0F)
#define VBJ_BUTTON_16       (0x10)
#define VBJ_BUTTON_MAX      (0x10) //rgb�{�^���ԕ�

#define VBJ_X_POS_MINUS     (0x80)
#define VBJ_X_POS_PLUS      (0x81)
#define VBJ_Y_POS_MINUS     (0x82)
#define VBJ_Y_POS_PLUS      (0x83)
#define VBJ_Z_POS_MINUS     (0x84)
#define VBJ_Z_POS_PLUS      (0x85)
#define VBJ_X_ROT_MINUS     (0x86)
#define VBJ_X_ROT_PLUS      (0x87)
#define VBJ_Y_ROT_MINUS     (0x88)
#define VBJ_Y_ROT_PLUS      (0x89)
#define VBJ_Z_ROT_MINUS     (0x8A)
#define VBJ_Z_ROT_PLUS      (0x8B)
#define VBJ_POV_UP          (0x8C)
#define VBJ_POV_DOWN        (0x8D)
#define VBJ_POV_LEFT        (0x8E)
#define VBJ_POV_RIGHT       (0x8F)

#define VB_BUTTON1                (0x1ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define VB_BUTTON2                (0x2ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define VB_BUTTON3                (0x4ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define VB_BUTTON4                (0x8ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000
#define VB_BUTTON5               (0x10ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define VB_BUTTON6               (0x20ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000
#define VB_BUTTON7               (0x40ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 01000000
#define VB_BUTTON8               (0x80ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10000000
#define VB_BUTTON9              (0x100ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000
#define VB_BUTTON10             (0x200ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000010 00000000
#define VB_BUTTON11             (0x400ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000100 00000000
#define VB_BUTTON12             (0x800ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00001000 00000000
#define VB_BUTTON13            (0x1000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00010000 00000000
#define VB_BUTTON14            (0x2000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00100000 00000000
#define VB_BUTTON15            (0x4000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 01000000 00000000
#define VB_BUTTON16            (0x8000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 10000000 00000000
#define VB_PAUSE              (0x10000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000
#define VB_UP                 (0x20000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000010 00000000 00000000
#define VB_DOWN               (0x40000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000100 00000000 00000000
#define VB_LEFT               (0x80000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00001000 00000000 00000000
#define VB_RIGHT             (0x100000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00010000 00000000 00000000
#define VB_S1_UP             (0x200000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00100000 00000000 00000000
#define VB_S1_DOWN           (0x400000ULL) //&B 00000000 00000000 00000000 00000000 00000000 01000000 00000000 00000000
#define VB_S1_LEFT           (0x800000ULL) //&B 00000000 00000000 00000000 00000000 00000000 10000000 00000000 00000000
#define VB_S1_RIGHT         (0x1000000ULL) //&B 00000000 00000000 00000000 00000000 00000001 00000000 00000000 00000000
#define VB_S2_UP            (0x2000000ULL) //&B 00000000 00000000 00000000 00000000 00000010 00000000 00000000 00000000
#define VB_S2_DOWN          (0x4000000ULL) //&B 00000000 00000000 00000000 00000000 00000100 00000000 00000000 00000000
#define VB_S2_LEFT          (0x8000000ULL) //&B 00000000 00000000 00000000 00000000 00001000 00000000 00000000 00000000
#define VB_S2_RIGHT        (0x10000000ULL) //&B 00000000 00000000 00000000 00000000 00010000 00000000 00000000 00000000
#define VB_UI_UP           (0x20000000ULL) //&B 00000000 00000000 00000000 00000000 00100000 00000000 00000000 00000000
#define VB_UI_DOWN         (0x40000000ULL) //&B 00000000 00000000 00000000 00000000 01000000 00000000 00000000 00000000
#define VB_UI_LEFT         (0x80000000ULL) //&B 00000000 00000000 00000000 00000000 10000000 00000000 00000000 00000000
#define VB_UI_RIGHT       (0x100000000ULL) //&B 00000000 00000000 00000000 00000001 00000000 00000000 00000000 00000000
#define VB_UI_EXECUTE     (0x200000000ULL) //&B 00000000 00000000 00000000 00000010 00000000 00000000 00000000 00000000
#define VB_UI_CANCEL      (0x400000000ULL) //&B 00000000 00000000 00000000 00000100 00000000 00000000 00000000 00000000
#define VB_UI_DEBUG       (0x800000000ULL) //&B 00000000 00000000 00000000 00001000 00000000 00000000 00000000 00000000

#define VB_MAP_BUFFER 120
#define VB_NUM 29

/**
 * ���z�{�^�� .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VirtualButton : public GgafCore::Object {

public:
    /**
     * ���z�{�^�����X�g .
     */
    class VBRecord {
    public :
        VBRecord* _next; //���n��Ŏ��̃t���[���̓��͏��
        VBRecord* _prev; //���n��őO�̃t���[���̓��͏��
        vb_sta _state;
    public:
        VBRecord() {
            _next = nullptr;
            _prev = nullptr;
            _state = (vb_sta)0;
        }
        ~VBRecord() {
        }
    };


    struct KEYBOARDMAP {
        vbk BUTTON1;
        vbk BUTTON2;
        vbk BUTTON3;
        vbk BUTTON4;
        vbk BUTTON5;
        vbk BUTTON6;
        vbk BUTTON7;
        vbk BUTTON8;
        vbk BUTTON9;
        vbk BUTTON10;
        vbk BUTTON11;
        vbk BUTTON12;
        vbk BUTTON13;
        vbk BUTTON14;
        vbk BUTTON15;
        vbk BUTTON16;
        vbk PAUSE;
        vbk UP;
        vbk DOWN;
        vbk LEFT;
        vbk RIGHT;
        vbk S1_UP;
        vbk S1_DOWN;
        vbk S1_LEFT;
        vbk S1_RIGHT;
        vbk S2_UP;
        vbk S2_DOWN;
        vbk S2_LEFT;
        vbk S2_RIGHT;
        vbk UI_UP;
        vbk UI_DOWN;
        vbk UI_LEFT;
        vbk UI_RIGHT;
        vbk UI_EXECUTE;
        vbk UI_CANCEL;
        vbk UI_DEBUG;
    };

    struct JOYSTICKMAP {
        vbj BUTTON1;
        vbj BUTTON2;
        vbj BUTTON3;
        vbj BUTTON4;
        vbj BUTTON5;
        vbj BUTTON6;
        vbj BUTTON7;
        vbj BUTTON8;
        vbj BUTTON9;
        vbj BUTTON10;
        vbj BUTTON11;
        vbj BUTTON12;
        vbj BUTTON13;
        vbj BUTTON14;
        vbj BUTTON15;
        vbj BUTTON16;
        vbj PAUSE;
        vbj UP;
        vbj DOWN;
        vbj LEFT;
        vbj RIGHT;
        vbj S1_UP;
        vbj S1_DOWN;
        vbj S1_LEFT;
        vbj S1_RIGHT;
        vbj S2_UP;
        vbj S2_DOWN;
        vbj S2_LEFT;
        vbj S2_RIGHT;
        vbj UI_UP;
        vbj UI_DOWN;
        vbj UI_LEFT;
        vbj UI_RIGHT;
        vbj UI_EXECUTE;
        vbj UI_CANCEL;
        //vbj UI_DEBUG;
    };

public:
    static std::map<std::string, int> _mapStr2VBK;
    static std::map<std::string, int> _mapStr2VBJ;
    static std::map<int, std::string> _mapVBK2Str;
    static std::map<int, std::string> _mapVBJ2Str;



    typedef bool (*funcVJBtn)(void);
    static std::map<int, funcVJBtn> _mapVBJ2Func;

public:
    /** �L�[�{�[�h���蓖�Ēl */
    KEYBOARDMAP _keyboardmap;
    /** �W���C�X�e�B�b�N���蓖�Ēl */
    JOYSTICKMAP _joystickmap;

    std::map<vb_sta, int*> _mapVB2keyboardmap;
    std::map<vb_sta, int*> _mapVB2joystickmap;

    /** �I�[�g���s�[�g����p�J�E���^�[ */
    std::map<vb_sta, frame> _auto_repeat_counter;
    /** �I�[�g���s�[�g���Ȃ�� true */
    bool _is_auto_repeat;

    bool _with_pov;
    VBReplayRecorder* _pRpy;

    /** [r]���v���C���[�h��:true�^���[�U�[���́i���v���C���[�h�L���j���[�h:false */
    bool _is_replaying;
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

    static bool initStatic();

    static bool isPressedVirtualJoyButton(vbj prm_VBJ);

    static int getPushedDownVirtualJoyButton();

    /**
     * ���z�{�^���̊��蓖�Ă�ύX�i�L�[�{�[�h���W���C�X�e�B�b�N�j .
     * @param prm_VB VB_... �Ŏn�܂鉼�z�{�^���A���蓖�đΏۂ̉��z�{�^�����w��
     * @param prm_VBK VBK_... �Ŏn�܂鉼�z�L�[�萔�A���z�{�^���֊��蓖�Ă�L�[�{�[�h���w��
     * @param prm_VBJ VBJ_... �Ŏn�܂鉼�zJOY�X�e�B�b�N�{�^���萔�A���z�{�^���֊��蓖�Ă�JOY�X�e�B�b�N�{�^�����w��
     */
    void remap(vb_sta prm_VB, vbk prm_VBK, vbj prm_VBJ);

    /**
     * ���z�{�^���̊��蓖�Ă�ύX�i�L�[�{�[�h�̂݁j .
     * @param prm_VB VB_... �Ŏn�܂鉼�z�{�^���A���蓖�đΏۂ̉��z�{�^�����w��
     * @param prm_VBK VBK_... �Ŏn�܂鉼�z�L�[�萔�A���z�{�^���֊��蓖�Ă�L�[�{�[�h���w��
     */
    void remapK(vb_sta prm_VB, vbk prm_VBK);

    /**
     * ���z�{�^���̊��蓖�Ă�ύX�i�W���C�X�e�B�b�N�̂݁j .
     * @param prm_VB VB_... �Ŏn�܂鉼�z�{�^���A���蓖�đΏۂ̉��z�{�^�����w��
     * @param prm_VBJ VBJ_... �Ŏn�܂鉼�zJOY�X�e�B�b�N�{�^���萔�A���z�{�^���֊��蓖�Ă�JOY�X�e�B�b�N�{�^�����w��
     */
    void remapJ(vb_sta prm_VB, vbj prm_VBJ);
    /**     * �ߋ��̓��͏�Ԃ��擾 .     * @param prm_frame_ago ���݂�艽�t���[���ߋ������w��     * @return �ߋ��̓��͏��     */    VirtualButton::VBRecord* getPastVBRecord(frame prm_frame_ago) const;

    /**
     * ���݃{�^����������Ă��邩���� .
     * @param prm_VB ����Ώۉ��z�{�^���萔�BVB_ �Ŏn�܂�萔(�̘_���a)
     * @retval 0   �����̃{�^���͂������������Ă��Ȃ�(=false)
     * @retval >0  �����̃{�^���̓��A���݉�����Ă���{�^���� VB_ �Ŏn�܂�萔(�̘_���a)
     * @code
     * VirtualButton vb_play = VirtualButton();
     * vb_play.update();
     *
     * if (vb_play.isPressed(VB_BUTTON1)) {
     *     //VB_BUTTON1 ��������Ă���ꍇ�̏���
     * }
     *
     * if (vb_play.isPressed(VB_BUTTON1|VB_BUTTON3)) {
     *     //VB_BUTTON1 ���� VB_BUTTON3 ��������Ă���ꍇ�̏���
     * }
     *
     * if (vb_play.isPressed(VB_BUTTON1|VB_BUTTON3) == (VB_BUTTON1|VB_BUTTON3)) {
     *     //VB_BUTTON1 �� VB_BUTTON3 ������������Ă���ꍇ�̏���
     * }
     * @endcode
     */
    inline vb_sta isPressed(vb_sta prm_VB) const {
        return (_pVBRecord_active->_state & prm_VB);
    }

    /**
     * �ߋ��Ƀ{�^����������Ă������ǂ������� .
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     * 1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isPressed(vb_sta) �Ɠ����Ӗ��ɂȂ�B
     * �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @retval 0   �ߋ��ɁA�����̃{�^���͂������������Ă��Ȃ�����(=false)
     * @retval >0  �����̃{�^���̓��A�ߋ��ɉ�����Ă����{�^���� VB_ �Ŏn�܂�萔(�̘_���a)
     */
    vb_sta wasPressed(vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * �ߋ��Ƀ{�^����������Ă��Ȃ������̂��ǂ������� .
     * wasPressed(vb_sta, frame) �̔ے�̌��ʂ��Ԃ�B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isPressed(vb_sta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true / false
     */
    inline bool wasNotPressed(vb_sta prm_VB, frame prm_frame_ago) const {
        return wasPressed(prm_VB, prm_frame_ago) ? false : true;
    }

    /**
     * ���݃{�^���������ꂽ�u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă���A���A�P�t���[���O�͉�����Ă��Ȃ��ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    inline bool isPushedDown(vb_sta prm_VB) const {
        return (!(_pVBRecord_active->_prev->_state & prm_VB) && (_pVBRecord_active->_state & prm_VB)) ? true : false;
    }

    /**
     * �ߋ��Ƀ{�^���������ꂽ�u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă����A���A(prm_frame_ago+1)�t���[���O�͉�����Ă��Ȃ������ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isPushedDown(vb_sta) �Ɠ����Ӗ��ɂȂ�B
     *                      �ő� (VB_MAP_BUFFER-1) �t���[���O�܂ŉ�
     * @return true / false
     */
    bool wasPushedDown(vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * ���݃{�^���𗣂����u�ԂȂ̂��ǂ������� .
     * ���݂͉�����Ă��Ȃ��A���A�P�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @return true / false
     */
    bool isReleasedUp(vb_sta prm_VB) const;

    /**
     * �ߋ��Ƀ{�^���𗣂����u�Ԃ��������̂��ǂ������� .
     * prm_frame_ago�t���[���O�͉�����Ă��Ȃ������A���A(prm_frame_ago+1)�t���[���O�͉�����Ă����ꍇ�� true
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_ago ���t���[���O(>0)�𔻒肷��̂��w��B
     *                      1 �� 1�t���[���O�A2 �� 2�t���[���O�A0 �� isReleasedUp(vb_sta) �Ɠ����Ӗ��ɂȂ�B
     * @return true / false
     */
    bool wasReleasedUp(vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * �`������������ .
     * �u�{�^���������Ă��Ȃ��������{�^�������������{�^���𗣂����v�Ƃ����t�F�[�Y���A
     * ���ݐ����������ǂ������肷��B
     * �A�������Ă������Ԃ� prm_frame_push �ȏ㉟���Ă���Ɛ������Ȃ��i�`���������ƔF�߂��Ȃ��j�B
     * �����Ƃ��Γƕ���G�{�^������Ȃ� prm_frame_push=2 ���w��B��ɺ���;
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_push ���e����{�^���������Ă������ԃt���[��(default=5)
     * @return true / false
     */
    bool isPushedUp(vb_sta prm_VB, frame prm_frame_push = 5) const;

    /**
     * �_�u���v�b�V������ .
     * �u(a)�{�^���������Ă��Ȃ�������(b)�{�^������������(c)�{�^���𗣂�����(d)�{�^�����������v�Ƃ����t�F�[�Y���A
     * ���ݐ����������ǂ������肷��B
     * �A��   (b)�`(c)�̉����Ă������Ԃ� prm_frame_push �ȏ㉟���Ă���Ɛ������Ȃ��B
     * ����� (c)�`(d)�̂Q��ڂ̃{�^�������܂ł̊��Ԃ� prm_frame_delay �ȏ�J���Ă���Ɛ������Ȃ��B
     * @param prm_VB ����Ώۉ��z�{�^���BVB_ �Ŏn�܂�萔(�̘_���a)
     * @param prm_frame_push ���e����(b)�`(c) �̊���
     * @param prm_frame_delay ���e����(c)�`(d) �̊���
     * @return true / false
     */
    bool isDoublePushedDown(vb_sta prm_VB, frame prm_frame_push = 5, frame prm_frame_delay = 5) const;

    /**
     * �����{�^�������������� .
     * isPushedDown(vb_sta) �̈����ɕ����{�^�����w�肵�Ĕ�����s���΁A������������͉\�ł���B
     * �������A���̔�����@�͕����{�^���������ۂ�1�t���[���ł��o���c�L������ΐ��������A
     * ���S�ɓ����ɉ����Ȃ���΂Ȃ�Ȃ����߁A�V�r�A������Ƃ������_������B
     * �����ŁA�{���\�b�h�́A���������̃o���c�L�����e�l������������������ł���B
     * ��̓I�ɂ́A�����̂��ꂼ��̊e�{�^���̌��݂Ɏ���܂ł̂S�t���[���̏�ԗ������A
     * ���̂����ꂩ�̃t�F�[�Y�ł����1�񐬗��Ƃ���������s���Ă���B(�܂�3�t���[���P�\)
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
    bool arePushedDownAtOnce(vb_sta prm_aVB[], int prm_num_button) const;

    /**
     * �R�t���P�\�̂Q�{�^�������������� .
     * @param prm_VB1 ����Ώۉ��z�{�^���P
     * @param prm_VB2 ����Ώۉ��z�{�^���Q
     * @return true / false
     */
    bool arePushedDownAtOnce(vb_sta prm_VB1, vb_sta prm_VB2) const {
        vb_sta vb[2];
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
    bool arePushedDownAtOnce(vb_sta prm_VB1, vb_sta prm_VB2, vb_sta prm_VB3) const {
        vb_sta vb[3];
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
    bool arePushedDownAtOnce(vb_sta prm_VB1, vb_sta prm_VB2, vb_sta prm_VB3, vb_sta prm_VB4) const {
        vb_sta vb[4];
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
    bool isAutoRepeat(vb_sta prm_VB, frame prm_begin_repeat = 20, frame prm_while_repeat = 5);

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
    bool isScrewPushDown(vb_sta prm_VB, frame prm_frame_delay=30) const;


    //vb_sta getPushedDownStick() const;


    inline vb_sta getState() const {
        return _pVBRecord_active->_state;
    }

    /**
     * ���͏����X�V .
     * �ʏ펞�̓L�[���́A�W���C�X�e�B�b�N�A�}�E�X�̃f�o�C�X�ɓ��͂ɂ��A�����X�e�[�g���X�V�B
     * �A���A���v���C�Đ����́A�ǂݍ��܂ꂽ�O���t�@�C���̃f�[�^�ŁA�����X�e�[�g���X�V�B
     */
    void update();

    void clear();

    virtual ~VirtualButton();
};

}
#endif /*GGAF_LIB_VIRTUALBUTTON_H_*/
