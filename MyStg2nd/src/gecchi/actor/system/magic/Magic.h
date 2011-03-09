#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_NOTHING 0
#define MAGIC_STAND_BY 1
#define MAGIC_CASTING 2
#define MAGIC_INVOKING 3
#define MAGIC_EFFECTING 4
#define MAGIC_ABANDONING 9


typedef int magic_point;
typedef int magic_time;
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
class Magic : public GgafCore::GgafObject {
public:
    /**
     * �e���x���̏�� .
     */
    class LevelInfo {
    public:
        /** �Y�����x���Ŗ��@���K�p���ł��邩�ǂ��� */
        bool _is_effecting;
        /** ���@���ʎ����I���c�莞�� */
        magic_time _remaining_time_of_effect;
        /** ���@���ʎ������R�X�g  */
        magic_point _keep_cost;
        /** �A�j���p�^�[���ԍ� */
        int _pno;
        LevelInfo() : _is_effecting(false),
                      _remaining_time_of_effect(0),
                      _keep_cost(0),
                      _pno(0) {
        }
    };
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    char* _name;
    magic_point* _pMP;
    MagicMeter* _pMagicMeter;
    /** �V�������x�� */
    int _new_level;
    /** ���݂̃��x�� */
    int _level;
    /** �ō����x�� 1 */
    int _max_level;
    /** �e���x�����̏�� */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL_Y];

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

    magic_time _executing_time;
    magic_time _time_of_next_state;

    /** ��� */
    int _state;
    /** ���x���A�b�v�����ǂ��� */
    boolean _is_leveling;

    float _discount_rate;

    float _rr;
    float _velo_rr;

public:
    /**
     *
     * @param prm_name ���@��
     * @param prm_pMagicMeter ���@���[�^�[
     * @param prm_pMP
     * @param prm_max_level �{���@�̍ō����x�� 1�`MMETER_MAX_LEVEL_Y
     * @param prm_cost_base ��{���@�R�X�g
     * @param prm_fRate_cost ��у��x�����̖��@�R�X�g�팸���� 0.0�`1.0 (1.0:��у��x���ł���������)
     * @param prm_time_of_casting_base ��{���@�r������
     * @param prm_fRate_time_of_casting ��у��x�����̉r�����ԍ팸����0.0�`1.0 (1.0:��у��x���ł���������)
     * @param prm_time_of_invoking_base ��{���@��������
     * @param prm_fRate_time_of_invoking ��у��x�����̔������ԍ팸����0.0�`1.0 (1.0:��у��x���ł���������)
     * @param prm_time_of_effect_base ��{���@���ʎ�������
     * @param prm_fRate_time_of_effecting ��у��x�����̉ʎ������ԍ팸����0.0�`1.0 (1.0:��у��x���ł���������)
     * @param prm_keep_cost_base ��{���@���ʎ������ێ��R�X�g
     * @param prm_fRate_keep_cost ���x�����̉ʎ������ێ��R�X�g�������� 0.0�`1.0 (0.0:���x���ɂ��ێ��R�X�g��������)
     * @return
     */
    Magic(const char* prm_name,
          MagicMeter* prm_pMagicMeter,
          magic_point* prm_pMP,
                int   prm_max_level,
                magic_point prm_cost_base, float prm_fRate_cost,
                magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
                magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
                magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
                magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

    void behave();

    void rollOpen();
    void rollClose();

    bool execute(int prm_new_level);


    /**
     * �r������ .
     */
    virtual void cast();

    /**
     * ��������.
     */
    virtual void invoke();

    /**
     * �I������ .
     */
    virtual void effect();

    /**
     * ������� .
     */
    virtual void abandon(int prm_last_level);

    /**
     * �r���J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processCastBegin() = 0;

    /**
     * �r�����R�[���o�b�N .
     */
    virtual void processCastingBehavior() = 0;

    /**
     * ���@�����J�n�R�[���o�b�N�B�����܂ł���Ɖr���L�����Z���͕s�Ƃ���B(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processInvokeBegin() = 0;

    /**
     * ���@�������R�[���o�b�N .
     */
    virtual void processInvokeingBehavior() = 0;

    /**
     * ���@�����J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processEffectBegin() = 0;

    /**
     * ���@�������R�[���o�b�N .
     */
    virtual void processEffectingBehavior() = 0;

    /**
     * ���@�j���R�[���o�b�N .
     */
    virtual void processOnAbandon(int prm_last_level) = 0;


    /**
     * ���@���������� .
     */
    virtual void commit();
    /**
     * ���@���L�����Z������ .
     */
    virtual void cancel();

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
