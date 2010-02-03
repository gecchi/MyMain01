#ifndef ENEMYSHOT001_H_
#define ENEMYSHOT001_H_
namespace MyStg2nd {

class EnemyShot001 : public EnemyShotSpriteActor {

public:
    EnemyShot001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    bool isOutOfGameSpace() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void onHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShot001();
};

}
#endif /*ENEMYSHOT001_H_*/

