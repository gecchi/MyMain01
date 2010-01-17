#ifndef ENEMYASTRAEALASERCHIP001_H_
#define ENEMYASTRAEALASERCHIP001_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip001 : public HomingLaserChip {


public:
    EnemyAstraeaLaserChip001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    void onActive();

    void processBehaviorHeadChip();

    void processBehavior();

    void processJudgement() {
    }

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    void onInctive();

    virtual ~EnemyAstraeaLaserChip001();

};

}
#endif /*ENEMYASTRAEALASERCHIP001_H_*/

