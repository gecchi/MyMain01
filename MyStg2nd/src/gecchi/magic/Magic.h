#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_STAND_BY 0
#define MAGIC_CASTING 1
#define MAGIC_INVOKEING 2
#define MAGIC_EXPIRING 3
#define MAGIC_ABANDONING 9

class Magic : public GgafDx9LibStg::DefaultSpriteActor {
public:
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    /** 現在のコスト */
    int _cost;
    /** 詠唱速度 */
    int _cast_speed;
    /** 持続期間 */
    int _duration;
    /** 状態 */
    int _state;

    int _dec_cost;

public:
    Magic(const char* prm_name,
          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

    void processBehavior() override;


    virtual void cast() {
        _dec_cost = _cost / _cast_speed;
        _state = MAGIC_INVOKEING;
        processCastBegin();
    }

    virtual void invoke() {
        _state = MAGIC_INVOKEING;
        processInvokeBegin();
    }

    virtual void expire() {
        _state = MAGIC_EXPIRING;
        processExpireBegin();
    };

    virtual void abandon() {
         _state = MAGIC_ABANDONING;
         processAbandonBegin();
     };

    virtual void processCastBegin() = 0;

    virtual void processCastingBehavior() = 0;

    virtual void processInvokeBegin() = 0;

    virtual void processInvokeingBehavior() = 0;

    virtual void processExpireBegin() = 0;

    virtual void processExpiringBehavior() = 0;

    virtual void processAbandonBegin() = 0;

    virtual void processAbandoningBehavior() = 0;

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
