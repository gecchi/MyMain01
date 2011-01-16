#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_STAND_BY 0
#define MAGIC_CASTING 1
#define MAGIC_INVOKEING 2
#define MAGIC_EXPIRING 3
#define MAGIC_ABANDONING 9

class Magic : public GgafCore::GgafObject {
public:
    class LevelInfo {
    public:
        float _z;
        float _alpha;
        int _pno;
    };
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;


    float _x;

    char* _name;
    int _new_level;
    /** レベル */
    int _level;
    int _max_level;

    LevelInfo _lvinfo[MMETER_MAX_LEVEL_Y];

    /** 現在のコスト */
    int _cost;
    /** 詠唱速度 */
    int _cast_speed;
    /** 持続期間 */
    int _duration;
    /** 状態 */
    int _state;

    int _dec_cost;
    boolean _is_leveling;
    float _rr;
    float _velo_rr;

public:
    Magic(const char* prm_name, int prm_max_level);
//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

    void behave();

    void rollOpen();
    void rollClose();

    void setLevel(int prm_new_level);

    virtual void cast();

    virtual void invoke();

    virtual void expire();

    virtual void abandon();

    virtual void processCastBegin() = 0;

    virtual void processCastingBehavior() = 0;

    virtual void processInvokeBegin() = 0;

    virtual void processInvokeingBehavior() = 0;

    virtual void processExpireBegin() = 0;

    virtual void processExpiringBehavior() = 0;

    virtual void processAbandonBegin() = 0;

    virtual void processAbandoningBehavior() = 0;

    virtual void commit();
    virtual void cancel();
    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
