#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_
namespace MyStg2nd {

class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

    DefaultSpriteEffectActor* _pEffectBegin;
    DefaultSpriteEffectActor* _pEffectFinish;
    int _iProgress; //�i�݋

public:
    EnemyShotSpriteActor(const char* prm_name, const char* prm_model);

    /**
     * ��OverRide �ł���
     */
    virtual void initialize() override;

    /**
     * ��OverRide �ł���
     */
    virtual void processBehavior() override;

    /**
     * ��OverRide �ł���
     */
    virtual void processJudgement() override;

    /**
     * ��OverRide �ł���
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShotSpriteActor();
};

}
#endif /*ENEMYSHOTSPRITEACTOR_H_*/

