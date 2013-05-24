#ifndef MAGIC_H_
#define MAGIC_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

typedef int magic_point;
typedef frame magic_time;

#define MAGIC_CAST_NG_INVOKING_NOW          (-3)
#define MAGIC_CAST_NG_MP_IS_SHORT           (-2)
#define MAGIC_CAST_CANCEL                   (-1)
#define MAGIC_CAST_NOTHING                  (0)
#define MAGIC_CAST_OK_LEVELUP               (1)
#define MAGIC_CAST_OK_LEVELDOWN             (2)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN  (4)

#define MAGIC_INVOKE_NG_INVOKING_NOW (-3)
#define MAGIC_INVOKE_NG_MP_IS_SHORT (-2)
#define MAGIC_INVOKE_NOTHING        (0)
#define MAGIC_INVOKE_OK_LEVELUP     (1)
#define MAGIC_INVOKE_OK_LEVELDOWN   (2)

#define MAGIC_EFFECT_NG_MP_IS_SHORT (-2)
#define MAGIC_EFFECT_NOTHING        (0)
#define MAGIC_EFFECT_OK_LEVELUP     (1)
#define MAGIC_EFFECT_OK_LEVELDOWN   (2)

#define MMETER_MAX_LEVEL 9

/**
 * ���ۖ��@�N���X .
 * ���@��MP�ɂ��Ă̖{�N���X�̊�{�I�Ȑ����B<BR>
 * �E���@���g�p����Ɗe���@�ɐݒ肳�ꂽMP������܂��B������u��{���@�R�X�g�v�Ăт܂��B<BR>
 * �E���@�ɂ̓��x���Ƃ����T�O������A�����Ȃ���Ԃ̓��x���O�ł��B���x�����{�P����ꍇ�u��{���@�R�X�g�v�������܂��B<BR>
 *   �A���A��у��x��(�{�Q�ȏ�)�̏ꍇ�AMP����������ɂ���ݒ肪�\�ł��B<BR>
 * �E��у��x���A�b�v�ɂ��āA���Ƃ��΁u�X�s�[�h�v�ƌ������@�Ƀ��x���P�`�T������A��{���@�R�X�g�� 10 �������Ƃ��܂��B<BR>
 *   �u�X�s�[�h Level1�v���u�X�s�[�h Level2�v �ƂQ�񃌃x���A�b�v���s�����ꍇ�AMP�R�X�g�� 10+10=20 �ł����A<BR>
 *   �����Ȃ�u�X�s�[�h Level2�v�Ƃ����ꍇ�AMP�R�X�g�� (10+10)*0.8 = 16 �Ƃ����悤�Ȑݒ肪��у��x���A�b�v�ł͉\�ł��B<BR>
 *   ���� 0.8 �̂��Ƃ��u�팸�����v�ƌĂԎ��Ƃ��܂��B<BR>
 * �E���x���_�E���̊T�O�����݂��܂��B���x���_�E���͂��ł��s���܂��B<BR>
 *   ���x���_�E�����ɂ��̕���MP�Ɋ�炩�Ҍ�����Ƃ����ݒ���o���܂��B<BR>
 * �E���@�ɂ̓��C�t�T�C�N��������A���̃X�e�b�v�����݂��܂��B�e�p�����[�^���ݒ�\�ł��B<BR>
 *   a) ���@�̃��x���A�b�v���s<BR>
 *   b) �r���F���@�r���J�n���r�������r���I�� (�r���͓r���ŃL�����Z����)  <BR>
 *   c) �����F���@�����J�n�����@�������@�I�� (�����ɂȂ�ƃL�����Z���s��) <BR>
 *   d) �����F���@���ʎ����J�n(�R�X�g�����E���ʔ���) �����ʎ��������ʎ����I���i���@�̃��x���_�E���j<BR>
 * �E���@�̎�ނɂ́A���������@�A���ʎ������@ �̂Q��ނ�����܂��B
 *   ����Ɍ��ʎ��������@�ɂ́A���ʎ������ԂɈێ��R�X�g�L��A�ێ��R�X�g�����̂Q��ނ�����܂��B<BR>
 *   1)�u���������@�v�� �ud) �����v�̃v���Z�X���������@�ł���A���x���A�b�v�E�_�E���Ƃ����T�O�����݂��܂���B<BR>
 *   2)�u���ʎ��������@�v�́ud) �����v���ɐݒ肳�ꂽ���ʎ������Ԃ𒴂���Ǝ����Ń��x���_�E��(�|�P)���܂��B<BR>
 *      2-a)�u�ێ��R�X�g�L�v�� ����Ɂud) �����v����MP������܂��B�����A�r����MP��0�ɂȂ��Ă��܂����ꍇ�A
 *           �����I�Ƀ��x���O�Ƀ��x���_�E�����܂��B<BR>
 *      2-b)�u�ێ��R�X�g���v�� �ud) �����v����MP������܂���B�r����MP��0�ł����x���_�E���͋N����܂���B
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {
public:
    enum {
        STATE_NOTHING = 1,
        STATE_CAST_BEGIN,
        STATE_CASTING    ,
        STATE_INVOKE_BEGIN,
        STATE_INVOKING   ,
        STATE_EFFECT_BEGIN  ,
        STATE_EFFECTING  ,
        STATE_ABANDONING ,
    };

    /**
     * �e���x���̏�� .
     */
    class LevelInfo {
    public:
        /** [r]���@���ʎ����I���c�莞�� */
        magic_time remainingtime_of_effect_;
        /** [r/w]���@���ʎ������� */
        magic_time time_of_effect_;
        /** [r/w]���@���ʎ������R�X�g  */
        magic_point keep_cost_;
        /** [r/w]�A�j���p�^�[���ԍ� */
        int pno_;

        LevelInfo() : remainingtime_of_effect_(0),
                      time_of_effect_(0),
                      keep_cost_(0),
                      pno_(0) {
        }
    };

public:
    /** [r]�ō�������x�� */
    int max_level_;
    /** [r]���݂̃��x�� */
    int level_;
    /** [r]�V�������x�� */
    int new_level_;
    /** [r]�O��̃��x�� */
    int last_level_;
    /** [r]�P�t���[���O�̃��x�� */
    int prev_frame_level_;

    /** [r]�}�W�b�N�|�C���g���ʃo�[ */
    GgafLib::AmountGraph* pMP_;
    /** [r]�e���x���̏�� 0�`MMETER_MAX_LEVEL */
    LevelInfo lvinfo_[MMETER_MAX_LEVEL+1];

    /** [r]�{���@�����ɕK�v�ȃR�X�g�̊�{�P�� */
    magic_point cost_base_;
    /** [r]�{���@�r���J�n �` ���@�r���I���̊�{�P�ʎ���  */
    magic_time time_of_casting_base_;
    /** [r]�{���@�����J�n �` ���@�����I���̊�{�P�ʎ��� */
    magic_time time_of_invoking_base_;
    /** [r]�{���@���ʎ����J�n �` ���@���ʎ����I���̊�{�P�ʎ���  */
    magic_time time_of_effect_base_;
    /** [r]�{���@���ʎ������R�X�g�̊�{�P��  */
    magic_point keep_cost_base_;

    /** [r]��у��x�����̖��@�R�X�g�팸����(0.0�`1.0) */
    double r_cost_;
    /** [r]��у��x�����̉r�����ԍ팸����(0.0�`1.0) */
    double r_time_of_casting_;
    /** [r]��у��x�����̔������ԍ팸����(0.0�`1.0) */
    double r_time_of_invoking_;
    /** [r]�e���x�����̌��ʎ������ԍ팸����(0.0�`1.0) */
    double r_each_lv_time_of_effecting_;
    /** [r]�e���x�����̈ێ��R�X�g�������� (1.0�` )*/
    double r_keep_cost_;

    /** [r]���̐i����ԂɂȂ�ׂɕK�v�ȃt���[����(���ꎞ�ێ�) */
    magic_time time_of_next_state_;
    /** [r]���x���A�b�v�����ǂ��� */
    bool is_working_;


    /** [r]��у��x�����ʖ��@�R�X�g��� 0���`MMETER_MAX_LEVEL�� */
    magic_point interest_cost_[MMETER_MAX_LEVEL+1];
    /** [r]��у��x�����ʉr�����ԏ�� 0���`MMETER_MAX_LEVEL�� */
    magic_time  interest_time_of_casting_[MMETER_MAX_LEVEL+1];
    /** [r]��у��x�����ʔ������ԏ�� 0���`MMETER_MAX_LEVEL�� */
    magic_time  interest_time_of_invoking_[MMETER_MAX_LEVEL+1];


    progress temp_hold_status_;
    int temp_hold_new_level_;
public:

    /**
     * ���@�̒�`���s�� .
     * ��у��x���Ƃ̓��x�������P���傫��(���x�����Q�ȏ�)���w���B
     * @param prm_name ���@��
     * @param prm_pMP �}�W�b�N�|�C���g�̐��ʃo�[
     * @param prm_max_level �{���@�̍ō����x�� 1�`MMETER_MAX_LEVEL
     * @param prm_cost_base              ��{���@�R�X�g
     * @param prm_r_cost                 ��у��x�����̖��@�R�X�g�팸���� 0.0�`1.0
     *                                   (�y��z1.0:��у��x���ł����������A
     *                                          0.8:���x�����Q�ȏ㎞�A�R�X�g=prm_cost_base*���x����*0.8)
     * @param prm_time_of_casting_base   ��{���@�r������
     * @param prm_r_time_of_casting      ��у��x�����̉r�����ԍ팸����0.0�`1.0
     *                                   (�y��z1.0:��у��x���ł���������,
     *                                          0.8:���x�����Q�ȏ㎞�A�r������=prm_time_of_casting_base*���x����*0.8)
     * @param prm_time_of_invoking_base  ��{���@��������
     * @param prm_r_time_of_invoking     ��у��x�����̔������ԍ팸����0.0�`1.0
     *                                   (�y��z1.0:��у��x���ł���������,
     *                                          0.8:���x�����Q�ȏ㎞�A��������=prm_time_of_invoking_base*���x����*0.8)
     * @param prm_time_of_effect_base ��{���@���ʎ������ԁB
     *                                0���w�肷��ƁA�u���������@�v�Ɖ��߂����B
     *                                0���傫���l��ݒ肷��ƁA�u���ʎ��������@�v�Ɖ��߂����B
     * @param prm_r_each_lv_time_of_effecting �e���x�����̌��ʎ������ԍ팸����  0.0�`1.0
     *                      (�y��z1.0:���x���ɂ����ʎ������팸����,
     *                             0.8:���x��1�̂Ƃ� prm_time_of_effect
     *                                 ���x��2�̂Ƃ� prm_time_of_effect * 0.8
     *                                 ���x��3�̂Ƃ� prm_time_of_effect * 0.8 * 0.8
     *                                 ���x��4�̂Ƃ� prm_time_of_effect * 0.8 * 0.8 * 0.8  �Ƃ����������Ԃ��ݒ肳���)
     * @param prm_keep_cost_base ��{���@���ʎ������ێ��R�X�g�B0�Ȃ�΁u�ێ��R�X�g�����v0���傫���l��ݒ肷��Ɓu�ێ��R�X�g�L�v�ƂȂ�B
     * @param prm_r_each_lv_keep_cost �e���x�����̈ێ��R�X�g�������� 1.0�`
     *                      (�y��z1.0:���x���ɂ��ێ��R�X�g��������,
     *                             1.2:���x��1�̂Ƃ� prm_keep_cost_base
     *                                 ���x��2�̂Ƃ� prm_keep_cost_base * 1.2
     *                                 ���x��3�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2
     *                                 ���x��4�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2 * 1.2  �Ƃ����ێ��R�X�g���ݒ肳���)
     * @return
     */
    Magic(const char* prm_name, GgafLib::AmountGraph* prm_pMP,
          int prm_max_level,
          magic_point prm_cost_base            , double prm_r_cost,
          magic_time  prm_time_of_casting_base , double prm_r_time_of_casting,
          magic_time  prm_time_of_invoking_base, double prm_r_time_of_invoking,
          magic_time  prm_time_of_effect_base  , double prm_r_each_lv_time_of_effecting,
          magic_point prm_keep_cost_base       , double prm_r_each_lv_keep_cost);

    void init();

    void initialize() override {}

    void onReset() override;

    void processBehavior() override;

    void processJudgement() override {}

    void processDraw() override {}

    void processFinal() override {}

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    /**
     * �r���J�n���s .
     * @param prm_new_level
     */
    virtual int cast(int prm_new_level);

    /**
     * ���@�r���J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r������V�������x��(1�` )
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�r�����R�[���o�b�N(���t���[���R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r�����̐V�������x��(1�` )
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�r���I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r���������������\��̐V�������x��(1�` )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {};


    /**
     * �����J�n���s .
     * @param prm_new_level
     */
    virtual int invoke(int prm_new_level);

    /**
     * ���@�����J�n�R�[���o�b�N�B�����܂ł���Ɖr���L�����Z���͕s�Ƃ���B(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���������悤�Ƃ��Ă���V�������x��(1�` )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�������R�[���o�b�N(���t���[���R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���ݔ������̐V�������x��(1�` )
     */
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�����I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���@�����I�����O�́A���݂̃��x���B(0�` )
     * @param prm_new_level ���@�����I������́A���i���ׂ��V�������x���B(1�` )
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {};

    /**
     * ���ʔ������s .
     * @param prm_level ���ʔ��������x��
     */
    virtual int effect(int prm_level);

    /**
     * ���@���ʎ����J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * ���@�����I�� �� ���@���ʎ����J�n�A�̃^�C�~���O�ŌĂяo�����B����ɁA<BR>
     * ���@���ʎ����� �� ���x���A�b�v or ���x���_�E���A�̃^�C�~���O�ł��Ăяo�����B<BR>
     * prm_last_level < prm_now_level �̏ꍇ���x���A�b�v .
     * prm_last_level > prm_now_level �̏ꍇ���x���_�E�� .
     * @param prm_last_level ���ʎ������J�n�����O�̃��x���B(���x���A�b�v���F0�` �^���x���_�E�����F1�`)
     * @param prm_now_level ���ʎ������J�n���ꂽ���x���B(���x���A�b�v���F1�` �^���x���_�E�����F1�`)
     */
    virtual void processEffectBegin(int prm_last_level, int prm_now_level) {};

    /**
     * ���@���ʎ������R�[���o�b�N(���t���[���R�[���o�b�N) .
     * �y���Ӂz���������@(time_of_effect_base_==0)�̖��@�́A�{�R�[���o�b�N�͍s���܂���B
     * @param prm_last_level  �ȑO�̃��x���B
     * @param prm_now_level ����(������)�̃��x���B
     */
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) {};

    /**
     * ���@�����S�I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * ���x��0�ɂȂ郌�x���_�E�����s��ꂽ���O�ɌĂяo����܂��B<BR>
     * �ߑ��F���x��0�ɂȂ�Ȃ����x���_�E�� processEffectBegin() ���Ăяo����܂��B<BR>
     * @param prm_justbefore_level ���ʎ������I�����钼�O�̃��x��(���Ȃ݂Ɍ��݃��x���͕K��0)�B
     */
    virtual void processEffectFinish(int prm_justbefore_level) {};


    /**
     * ���̃��x���̖��@���r�����s�ł��邩���ׂ�
     * @param prm_new_level �r�����郌�x��
     * @return MAGIC_CAST_NG_INVOKING_NOW          (-3)  ���ݔ������̂��ׁA�s��
     *         MAGIC_CAST_NG_MP_IS_SHORT           (-2)  ���x���A�b�v�r���ƂȂ邪�AMP������Ȃ����ׁA�s��
     *         MAGIC_CAST_CANCEL                   (-1)  ���݉r�����ŁA�����̃��x���́A���݂̃��x���ƈ�v�B�܂�r���L�����Z���w���ɂȂ�B�i�\�E�s�\�Ō����Ή\�j
     *         MAGIC_CAST_NOTHING                  (0)   �����̃��x���́A���݂̃��x���ƈ�v�B�Ȃɂ��w�����ĂȂ����ƂɂȂ�B�i�\�E�s�\�Ō����Ή\�j
     *         MAGIC_CAST_OK_LEVELUP               (1)   ���x���A�b�v�r���ƂȂ�BMP�������׉\
     *         MAGIC_CAST_OK_LEVELDOWN             (2)   ���x���_�E���r���ƂȂ�B�������\
     *         MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)   ���݂̉r�����L�����Z�����Ẵ��x���A�b�v�r���ƂȂ�BMP�������׉\
     *         MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN  (4)   ���݂̉r�����L�����Z�����Ẵ��x���_�E���r���ƂȂ�B�������\
     */
    int chkCastAble(int prm_new_level);

    /**
     * ���̃��x���̖��@���������s���ł��邩���ׂ�
     * @param prm_new_level �������郌�x��
     * @return
     */
    int chkInvokeAble(int prm_new_level);

    /**
     * ���̃��x���̖��@�����ʂ����s���ł��邩���ׂ�
     * @param prm_level
     * @return
     */
    int chkEffectAble(int prm_level);

    /**
     * ���@���L�����Z������ .
     */
    virtual void cancel();

    /**
     * �_�E�����x�����s���̊Ҍ�MP���v�Z���ĕԂ� .
     * �c���ʎ����̊������悸��B
     * �������x���_�E�������ق��������ɂ��邽�߁B
     * @param prm_now_level ���݂̃��x��
     * @param prm_target_down_level �_�E�����x��
     * @return
     */
    magic_point calcReduceMp(int prm_now_level, int prm_target_down_level);

    /**
     * ���ʎ������ԍ��v�̎��Z .
     * @param prm_now_level ���݂̃��x��
     * @param prm_target_up_level ���x���A�b�v�̃��x��
     * @return ���Z���ꂽ���ʎ������ԍ��v
     */
    magic_time calcTotalEffecTime(int prm_now_level, int prm_target_up_level);


    virtual ~Magic();
};

}


#endif /*MAGIC_H_*/
