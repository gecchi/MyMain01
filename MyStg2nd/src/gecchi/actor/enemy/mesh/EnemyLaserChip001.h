﻿#ifndef ENEMYLASERCHIP001_H_
#define ENEMYLASERCHIP001_H_
namespace MyStg2nd {

class EnemyLaserChip001 : public HomingLaserChip {


public:
    EnemyLaserChip001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    void onActive() override;

    void processBehaviorHeadChip();



    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    /**
     * ＜OverRide です＞
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyLaserChip001();

};

}
#endif /*ENEMYLASERCHIP001_H_*/

