#ifndef ENEMYSHOT001_H_
#define ENEMYSHOT001_H_
namespace MyStg2nd {

class EnemyShot001 : public EnemyShotSpriteActor {

public:
    EnemyShot001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    int isOutOfGameSpace();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processOnHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShot001();
};

}
#endif /*ENEMYSHOT001_H_*/

