﻿#ifndef BACKGROUND01_H_
#define BACKGROUND01_H_
namespace MyStg2nd {

class BackGround01 : public GgafDx9Core::GgafDx9GeometricActor {

    BackGroundChipBoard*** _papapChipBoard;
//    BackGroundStar001** _papBackGroundStar001;

public:


    float _inc_x;
    float _inc_y;

    float _chip_width;
    float _chip_height;

    float _base_x[4];
    float _base_y[4];
    BackGround01(const char* prm_name, const char* prm_dummy);



    virtual void processPreDraw() override;



    virtual void processHappen(int prm_no) override {
    }


    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * ＜OverRide です＞
     */

    void initialize() override;

    void processJudgement() override {
    }

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    void processDraw() override {
    }

    virtual void processFinal() override {
    }

    virtual ~BackGround01();
};

}
#endif /*BACKGROUND01BOARD_H_*/

