#ifndef ENEMYSHOT001_H_
#define ENEMYSHOT001_H_
namespace MyStg2nd {

class EnemyShot001 : public EnemyShotSpriteActor {

public:
    EnemyShot001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    int isGone();

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafActor* prm_pActor_Opponent);

    virtual ~EnemyShot001();
};

}
#endif /*ENEMYSHOT001_H_*/

