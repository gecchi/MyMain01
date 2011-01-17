#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_STAND_BY 0
#define MAGIC_CASTING 1
#define MAGIC_INVOKING 2
#define MAGIC_EXPIRING 3
#define MAGIC_ABANDONING 9


typedef int magic_point;
typedef int magic_time;
/**
 * ���ۖ��@�N���X .
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafObject {
public:
    class LevelInfo {
    public:
        bool _is_working;
        magic_time _time_of_abandon;
        magic_time _working_time;
        int _pno;
    };
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    char* _name;

    int _new_level;
    /** ���x�� */
    int _level;
    /** �ō����x�� 1 */
    int _max_level;
    /** �e���x�����̏�� */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL_Y];

    /** �{���@�����ɕK�v��MP�̊�{�P�� */
    magic_point _cost_base;
    /** ���񖂖@�����ɕK�v��MP */
    magic_point _cost;
    /** �{���@�����ɕK�v�ȉr�����Ԃ̊�{�P��  */
    magic_time _time_of_casting_base;
    /** ���񖂖@�����ɕK�v�ȉr������ */
    magic_time _time_of_casting;
    /** �r�����x�i�ʏ�͂P�j */
    magic_time _cast_speed;
    /** �{���@�����J�n�`�I���̎��� */
    magic_time _time_of_invoking;
    /** ���݂̖��@�����I���܂Ŏ��� */
    magic_time _left_time_to_expire;

    /** ��� */
    int _state;
    /** ���x���A�b�v�����ǂ��� */
    boolean _is_leveling;

    float _discount_rate;

    float _rr;
    float _velo_rr;

public:
    Magic(const char* prm_name,
                int   prm_max_level,
                int   prm_cost_base,
                int   prm_time_of_casting_base,
                int   prm_time_of_invoking);


//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

    void behave();

    void rollOpen();
    void rollClose();

    bool setLevel(int prm_new_level);

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
    virtual void expire();

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
     * ���@���������������R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     */
    virtual void processExpireBegin() = 0;

    /**
     * ���@�����������R�[���o�b�N .
     */
    virtual void processExpiringBehavior() = 0;

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
