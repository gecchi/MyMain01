#ifndef MYOPTIONSHOT001_H_
#define MYOPTIONSHOT001_H_
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 自機オプションショット001 .
 * @version 1.00
 * @since 2014/04/09
 * @author Masatoshi Tsuge
 */
class MyOptionShot001 : public GgafLib::SingleLaser {

public:
    MyOptionShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MyOptionShot001();
};

}
#endif /*MYOPTIONSHOT001_H_*/

