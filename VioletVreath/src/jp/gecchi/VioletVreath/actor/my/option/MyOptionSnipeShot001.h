#ifndef MYOPTIONSNIPESHOT001_H_
#define MYOPTIONSNIPESHOT001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 自機オプションスナイプショット001 .
 * @version 1.00
 * @since 2014/13/06
 * @author Masatoshi Tsuge
 */
class MyOptionSnipeShot001 : public GgafLib::SingleLaser {

public:
    MyOptionSnipeShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MyOptionSnipeShot001();
};

}
#endif /*MYOPTIONSNIPESHOT001_H_*/

