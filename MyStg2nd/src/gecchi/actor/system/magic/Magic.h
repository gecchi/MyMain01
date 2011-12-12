#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

typedef int magic_point;
typedef frame magic_time;

#define MAGIC_EXECUTE_NG_INVOKING    (-2)
#define MAGIC_EXECUTE_NG_MP_IS_SHORT (-1)
#define MAGIC_EXECUTE_NG             (-1)
#define MAGIC_EXECUTE_THE_SAME_LEVEL (0)
#define MAGIC_EXECUTE_OK             (1)
#define MAGIC_EXECUTE_OK_LEVELUP     (1)
#define MAGIC_EXECUTE_OK_LEVELDOWN   (2)

/**
 * ���ۖ��@�N���X .
 * ���@��MP�ɂ��Ă̖{�N���X�̊�{�I�Ȗ񑩎��B
 * �E���@���g�p����Ɗe�����@�ɐݒ肳�ꂽMP������܂��B������u��{���@�R�X�g�v�Ăт܂��B<BR>
 * �E���@�ɂ̓��x���Ƃ����T�O������A��{�I�Ƀ��x�����{�P����̂Ɂu��{���@�R�X�g�v�������܂��B<BR>
 *   �A���A��у��x��(�{�Q�ȏ�)�̏ꍇ�AMP����������ɂ���ݒ肪�o���܂��B<BR>
 *   ���Ƃ��΁u�X�s�[�h�v�ƌ������@�Ƀ��x���P�`�T������A��{���@�R�X�g�� 10 �������Ƃ��܂��B<BR>
 *   �u�X�s�[�h Level1�v���u�X�s�[�h Level2�v �Ƃ����ꍇ�AMP�R�X�g�� 10+10=20 �ł����A<BR>
 *   �����Ȃ�u�X�s�[�h Level2�v�Ƃ����ꍇ�AMP�R�X�g�� (10+10)*0.8 = 16 �Ƃ����ݒ肪�\�ł��B<BR>
 *   ���� 0.8 �̂��Ƃ��u�팸�����v�ƌĂԎ��Ƃ��܂��B
 * �E���x���_�E���̊T�O�����݂��܂��B���x���_�E���͂��ł��s���܂��B<BR>
 *   ���x���_�E�����ɂ��̕���MP�Ɋ�炩�߂��Ƃ����ݒ���o���܂��B<BR>
 * �E���@�ɂ̓��C�t�T�C�N��������A���̃X�e�b�v�����݂��܂��B�e�p�����[�^���ݒ�\�ł��B<BR>
 *   a) ���@�̃��x���A�b�v���s<BR>
 *   b) �r���F���@�r���J�n�E�r�����E�r���I��<BR>
 *   c) �����F���@�����J�n(�R�X�g����) �E���@���E���@�I��<BR>
 *   d) �����F���@���ʎ����J�n(���ʔ���) �E���ʎ������E�ʎ����I��<BR>
 *   e) ���@�̃��x���_�E��<BR>
 * �E�ub) �r���v�܂łȂ�Δj���i��~�j���\�ł��B<BR>
 *   �uc) �����v�܂ŃX�e�b�v���i�ނƁAMP�������r���j���͕s�\�ɂȂ�܂��B<BR>
 *   �ud) �����v�ɂȂ�܂ŁA���x���A�b�v�A���x���_�E���̑���͏o���Ȃ����ƂƂ��܂��B<BR>
 * �E���@�ɂ́A�ێ��R�X�g�����A�ێ��R�X�g�L�� �̂Q��ނ�����܂��B<BR>
 *   �ێ��R�X�g�����́A�ud) �����v����MP������܂���B<BR>
 *   �ێ��R�X�g�L��́A�ud) �����v����MP������܂��B<BR>
 *   �ێ��R�X�g�����́AMP���͊����Ă����x���_�E�����܂���B<BR>
 *   �ێ��R�X�g�L��́AMP���͊������ꍇ�����Ń��x���_�E�����܂��B<BR>
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {


public:
    /**
     * �e���x���̏�� .
     */
    class LevelInfo {
    public:
        /** �Y�����x���Ŗ��@���K�p���ł��邩�ǂ���(�����J�n�`���ʏI���܂�true) */
        bool _is_working;
        /** ���@���ʎ����I���c�莞�� */
        magic_time _remaining_time_of_effect;
        /** ���@���ʎ������� */
        magic_time _time_of_effect;
        /** ���@���ʎ������R�X�g  */
        magic_point _keep_cost;
        /** �A�j���p�^�[���ԍ� */
        int _pno;
        LevelInfo() : _is_working(false),
                      _remaining_time_of_effect(0),
                      _keep_cost(0),
                      _pno(0) {
        }
    };
//    GgafDxCore::GgafDxGeometricActor* _pCaster;
//    GgafDxCore::GgafDxGeometricActor* _pReceiver;

    char* _name;
    /** �ō����x�� */
    int _max_level;
    /** ���݂̃��x�� */
    int _level;


    /** �V�������x�� */
    int _new_level;
    /** �O��̃��x�� */
    int _last_level;


    /** �}�W�b�N�|�C���g���ʃo�[ */
    GgafLib::AmountGraph* _pMP;
    /** ���[�^�[�ւ̃|�C���^ */
    MagicMeter* _pMagicMeter;

    /** �e���x���̏�� 0�`MMETER_MAX_LEVEL */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL+1];
    /** ��у��x�����ʖ��@�R�X�g��� 0���`MMETER_MAX_LEVEL�� */
    magic_point _interest_cost[MMETER_MAX_LEVEL+1];
    /** ��у��x�����ʉr�����ԏ�� 0���`MMETER_MAX_LEVEL�� */
    magic_time  _interest_time_of_casting[MMETER_MAX_LEVEL+1];
    /** ��у��x�����ʔ������ԏ�� 0���`MMETER_MAX_LEVEL�� */
    magic_time  _interest_time_of_invoking[MMETER_MAX_LEVEL+1];

    /** �{���@�����ɕK�v�ȃR�X�g�̊�{�P�� */
    magic_point _cost_base;
    /** �{���@�r���J�n �` ���@�r���I���̊�{�P�ʎ���  */
    magic_time _time_of_casting_base;
    /** �{���@�����J�n �` ���@�����I���̊�{�P�ʎ��� */
    magic_time _time_of_invoking_base;
    /** �{���@���ʎ����J�n �` ���@���ʎ����I���̊�{�P�ʎ���  */
    magic_time _time_of_effect_base;
    /** �{���@���ʎ������R�X�g�̊�{�P��  */
    magic_point _keep_cost_base;

    /** ��у��x�����̖��@�R�X�g�팸����(0.0�`1.0) */
    float _fRate_cost;
    /** ��у��x�����̉r�����ԍ팸����(0.0�`1.0) */
    float _fRate_time_of_casting;
    /** ��у��x�����̔������ԍ팸����(0.0�`1.0) */
    float _fRate_time_of_invoking;
    /** �e���x�����̌��ʎ������ԍ팸����(0.0�`1.0) */
    float _fRate_time_of_effecting;
    /** �e���x�����̈ێ��R�X�g�������� (1.0�` )*/
    float _fRate_keep_cost;

    magic_time _time_of_next_state;

//    /** ��� */
//    int _state;
    /** ���x���A�b�v�����ǂ��� */
    bool _is_working;

    float _discount_rate;

    float _rr;
    float _velo_rr;

public:
    /**
     * ���@�̒�`���s�� .
     * ��у��x���Ƃ̓��x�������P���傫��(���x�����Q�ȏ�)���w���B
     * @param prm_name ���@��
     * @param prm_max_level �{���@�̍ō����x�� 1�`MMETER_MAX_LEVEL
     * @param prm_cost_base ��{���@�R�X�g
     * @param prm_fRate_cost ��у��x�����̖��@�R�X�g�팸���� 0.0�`1.0 (1.0:��у��x���ł����������A0.8:���x�����Q�ȏ㎞�A���@�R�X�g�Q����)
     * @param prm_time_of_casting_base ��{���@�r������
     * @param prm_fRate_time_of_casting ��у��x�����̉r�����ԍ팸����0.0�`1.0 (1.0:��у��x���ł���������, 0.8:���x�����Q�ȏ㎞�A�r�����ԂQ����)
     * @param prm_time_of_invoking_base ��{���@��������
     * @param prm_fRate_time_of_invoking ��у��x�����̔������ԍ팸����0.0�`1.0 (1.0:��у��x���ł���������, 0.8:���x�����Q�ȏ㎞�A�������ԂQ����)
     * @param prm_time_of_effect ��{���@���ʎ�������
     * @param prm_fRate_time_of_effecting �e���x�����̌��ʎ������ԍ팸����  0.0�`1.0
     *                            (1.0:���x���ɂ����ʎ������팸����,
     *                            (0.8:���x��1�̂Ƃ� prm_time_of_effect
     *                                 ���x��2�̂Ƃ� prm_time_of_effect * 0.8
     *                                 ���x��3�̂Ƃ� prm_time_of_effect * 0.8 * 0.8
     *                                 ���x��4�̂Ƃ� prm_time_of_effect * 0.8 * 0.8 * 0.8  �Ƃ����������Ԃ��ݒ肳���)
     * @param prm_keep_cost_base ��{���@���ʎ������ێ��R�X�g
     * @param prm_fRate_keep_cost_base �e���x�����̈ێ��R�X�g�������� 1.0�`
     *                            (1.0:���x���ɂ��ێ��R�X�g��������,
     *                            (1.2:���x��1�̂Ƃ� prm_keep_cost_base
     *                                 ���x��2�̂Ƃ� prm_keep_cost_base * 1.2
     *                                 ���x��3�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2
     *                                 ���x��4�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2 * 1.2  �Ƃ����ێ��R�X�g���ݒ肳���)
     * @return
     */
    Magic(const char* prm_name, GgafLib::AmountGraph* prm_pMP,
          int   prm_max_level,
          magic_point prm_cost_base, float prm_fRate_cost,
          magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
          magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
          magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
          magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDxCore::GgafDxGeometricActor* prm_pCaster,
//          GgafDxCore::GgafDxGeometricActor* prm_pReceiver);
    void initialize() override {
    }

    void onReset() override {
    }

    void processBehavior() override;

    void processJudgement() override {
    }
    void processDraw() override {
    }
    void processFinal()  override {
    }
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }


    void rollOpen();
    void rollClose();

    /**
     * ���̃��x���̖��@�����s�ł��邩���ׂ�
     * @param prm_new_level
     * @return
     */
    int chkExecuteAble(int prm_new_level);

    /**
     * �r���J�n���s .
     * @param prm_new_level
     */
    virtual void cast(int prm_new_level);

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
     * @param prm_new_level �r�������������V�������x��(1�` )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level) {};

    /**
     * �����J�n���s .
     * @param prm_new_level
     */
    virtual void invoke(int prm_new_level);

    /**
     * ���@�����J�n�R�[���o�b�N�B�����܂ł���Ɖr���L�����Z���͕s�Ƃ���B(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���������悤�Ƃ��Ă���V�������x��(1�` )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�������R�[���o�b�N(���t���[���R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���������悤�Ƃ��Ă���V�������x��(1�` )
     */
    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�����I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * @param prm_last_level ���������������́A���݂̃��x���B(0�` )
     * @param prm_now_level �����ɂ��A���ꂩ�珸�i����V�������x���B(1�` )
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level) {};

    /**
     * ���ʔ������s .
     * @param prm_new_level
     */
    virtual void effect(int prm_level);

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

//    /**
//     * ���@�j���R�[���o�b�N .
//     * @param prm_last_high_level �~�i�O�̌��݂̃��x��
//     * @param prm_new_low_level �V�����ς��~�i���x��
//     */
//    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};
//
//
//    /**
//     * ���@�j���R�[���o�b�N .
//     * @param prm_last_high_level �~�i�O�̌��݂̃��x��
//     * @param prm_new_low_level �V�����ς��~�i���x��
//     */
//    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};


    /**
     * ���@���������� .
     */
//    virtual void commit();
    /**
     * ���@���L�����Z������ .
     */
    virtual void cancel();

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
