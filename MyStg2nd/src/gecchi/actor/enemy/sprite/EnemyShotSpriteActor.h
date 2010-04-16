#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_
namespace MyStg2nd {

class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

//    DefaultSpriteEffectActor* _pEffectBegin;
//    DefaultSpriteEffectActor* _pEffectFinish;
    int _iProgress; //進み具合

public:
    EnemyShotSpriteActor(const char* prm_name, const char* prm_model);

    /**
     * ＜OverRide です＞
     */
    virtual void initialize() override;

    /**
     * ＜OverRide です＞
     */
    virtual void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    virtual void processJudgement() override;

    /**
     * ＜OverRide です＞
     */
    virtual void onHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShotSpriteActor();
};

}
#endif /*ENEMYSHOTSPRITEACTOR_H_*/

