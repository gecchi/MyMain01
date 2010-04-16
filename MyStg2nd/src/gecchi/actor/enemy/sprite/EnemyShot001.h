#ifndef ENEMYSHOT001_H_
#define ENEMYSHOT001_H_
namespace MyStg2nd {

class EnemyShot001 : public EnemyShotSpriteActor {

public:
    EnemyShot001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    bool isOutOfGameSpace() override;

    /**
     * ＜OverRide です＞
     */
    void onHit(GgafActor* prm_pOtherActor);

    virtual ~EnemyShot001();
};

}
#endif /*ENEMYSHOT001_H_*/

