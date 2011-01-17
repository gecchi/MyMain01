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
 * 抽象魔法クラス .
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
    /** レベル */
    int _level;
    /** 最高レベル 1 */
    int _max_level;
    /** 各レベル毎の情報 */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL_Y];

    /** 本魔法発動に必要なMPの基本単位 */
    magic_point _cost_base;
    /** 今回魔法発動に必要なMP */
    magic_point _cost;
    /** 本魔法発動に必要な詠唱時間の基本単位  */
    magic_time _time_of_casting_base;
    /** 今回魔法発動に必要な詠唱時間 */
    magic_time _time_of_casting;
    /** 詠唱速度（通常は１） */
    magic_time _cast_speed;
    /** 本魔法発動開始～終了の時間 */
    magic_time _time_of_invoking;
    /** 現在の魔法発動終了まで時間 */
    magic_time _left_time_to_expire;

    /** 状態 */
    int _state;
    /** レベルアップ中かどうか */
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
     * 詠唱する .
     */
    virtual void cast();

    /**
     * 発動する.
     */
    virtual void invoke();

    /**
     * 終了する .
     */
    virtual void expire();

    /**
     * 遺棄する .
     */
    virtual void abandon(int prm_last_level);

    /**
     * 詠唱開始コールバック(１回だけコールバック) .
     */
    virtual void processCastBegin() = 0;

    /**
     * 詠唱中コールバック .
     */
    virtual void processCastingBehavior() = 0;

    /**
     * 魔法発動開始コールバック。ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック) .
     */
    virtual void processInvokeBegin() = 0;

    /**
     * 魔法発動中コールバック .
     */
    virtual void processInvokeingBehavior() = 0;

    /**
     * 魔法発動完了時初期コールバック(１回だけコールバック) .
     */
    virtual void processExpireBegin() = 0;

    /**
     * 魔法発動完了中コールバック .
     */
    virtual void processExpiringBehavior() = 0;

    /**
     * 魔法破棄コールバック .
     */
    virtual void processOnAbandon(int prm_last_level) = 0;


    /**
     * 魔法を完了する .
     */
    virtual void commit();
    /**
     * 魔法をキャンセルする .
     */
    virtual void cancel();

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
