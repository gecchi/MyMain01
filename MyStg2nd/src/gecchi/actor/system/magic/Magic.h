#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_NOTHING 0
#define MAGIC_STAND_BY 1
#define MAGIC_CASTING 2
#define MAGIC_INVOKING 3
#define MAGIC_EFFECTING 4
#define MAGIC_ABANDONING 9

#define MAGIC_EXECUTE_NG_INVOKING    (-2)
#define MAGIC_EXECUTE_NG_MP_IS_SHORT (-1)
#define MAGIC_EXECUTE_NG             (-1)
#define MAGIC_EXECUTE_THE_SAME_LEVEL 0
#define MAGIC_EXECUTE_OK             1
#define MAGIC_EXECUTE_OK_LEVELUP     1
#define MAGIC_EXECUTE_OK_LEVELDOWN   2

typedef int magic_point;
typedef frame magic_time;
/**
 * ���ۖ��@�N���X .
 * ���@�ɂ��Ă̖{�N���X�̊�{�I�Ȗ񑩎��B
 * �@���̃X�e�b�v������܂��B
 * a) �r���F���@�r���J�n �` ���@�r���I��
 * b) �����F���@�����J�n�E���@�R�X�g���� �` ���@�����I��
 * c) �����F���@���ʎ����J�n �` ���@���ʎ����I��
 * �A���x���̊T�O������܂��B
 * ���x���ɂ���āAa)b)c) �� "�`"�̎��ԁA�y�і��@�R�X�g���ʂŕێ��ł��܂��B
 * �A�@�\
 * �Ea) �r���Ȃ�Ζ��@�j���i��~�j���\
 * �E�r���͊�{�r�����Ԃ�ݒ肵�A�r�����x�����������\
 * �E���@�R�X�g�͊�{���@�R�X�g��ݒ肵�A�R�X�g�����������\
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {
    /** �V�������x�� */
    int _new_level;
    /** �O��̃��x�� */
    int _last_level;


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
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    char* _name;
    /** ���݂̃��x�� */
    int _level;
    /** �ō����x�� */
    int _max_level;
    /** �}�W�b�N�|�C���g���ʃo�[ */
    GgafDx9LibStg::AmountGraph* _pMP;
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

    float _fRate_cost;
    float _fRate_time_of_casting;
    float _fRate_time_of_invoking;
    float _fRate_time_of_effecting;
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
     *
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
     * @param prm_fRate_keep_cost �e���x�����̌��ʎ������Ԍ�����  0.0�`1.0
     *                            (1.0:���x���ɂ����ʎ������팸����,
     *                            (0.8:���x��1�̂Ƃ� prm_time_of_effect
     *                                 ���x��2�̂Ƃ� prm_time_of_effect * 0.8
     *                                 ���x��3�̂Ƃ� prm_time_of_effect * 0.8 * 0.8
     *                                 ���x��4�̂Ƃ� prm_time_of_effect * 0.8 * 0.8 * 0.8  �Ƃ����������Ԃ��ݒ肳���)
     * @param prm_keep_cost_base ��{���@���ʎ������ێ��R�X�g
     * @param prm_fRate_keep_cost �e���x�����̈ێ��R�X�g��������  1.0�`
     *                            (1.0:���x���ɂ��ێ��R�X�g��������,
     *                            (1.2:���x��1�̂Ƃ� prm_keep_cost_base
     *                                 ���x��2�̂Ƃ� prm_keep_cost_base * 1.2
     *                                 ���x��3�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2
     *                                 ���x��4�̂Ƃ� prm_keep_cost_base * 1.2 * 1.2 * 1.2  �Ƃ����ێ��R�X�g���ݒ肳���)
     * @return
     */
    Magic(const char* prm_name,
          int   prm_max_level,
          magic_point prm_cost_base, float prm_fRate_cost,
          magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
          magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
          magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
          magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);
    void initialize() override;

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
     * ���s .
     * @param prm_new_level
     */
    void execute(int prm_new_level);


    /**
     * �r���J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) {};

    /**
     * �r�����R�[���o�b�N .
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * �r���I���R�[���o�b�N .
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�����J�n�R�[���o�b�N�B�����܂ł���Ɖr���L�����Z���͕s�Ƃ���B(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * ���@�������R�[���o�b�N .
     */
    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) {};

    virtual void processInvokeFinish(int prm_last_level, int prm_now_level) {};
    /**
     * ���@�����J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processEffectBegin(int prm_now_level) {};

    /**
     * ���@�������R�[���o�b�N .
     */
    virtual void processEffectingBehavior(int prm_now_level) {};

    virtual void processEffectFinish(int prm_now_level) {};

    /**
     * ���@�j���R�[���o�b�N .
     */
    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};


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
