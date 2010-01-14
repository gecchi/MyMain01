#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_
namespace MyStg2nd {

class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

    DefaultSpriteEffectActor* _pEffectBegin;
    DefaultSpriteEffectActor* _pEffectFinish;
    int _iProgress; //êiÇ›ãÔçá

public:
    EnemyShotSpriteActor(const char* prm_name, const char* prm_model);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void initialize();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processJudgement();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShotSpriteActor();
};

}
#endif /*ENEMYSHOTSPRITEACTOR_H_*/

