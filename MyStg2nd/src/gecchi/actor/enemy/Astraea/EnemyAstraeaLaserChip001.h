#ifndef ENEMYASTRAEALASERCHIP001_H_
#define ENEMYASTRAEALASERCHIP001_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip001 : public HomingLaserChip {


public:
    EnemyAstraeaLaserChip001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    void onActive() override;

    void processBehaviorHeadChip();

    void processBehavior() override;

    void processJudgement() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraeaLaserChip001();

};

}
#endif /*ENEMYASTRAEALASERCHIP001_H_*/

