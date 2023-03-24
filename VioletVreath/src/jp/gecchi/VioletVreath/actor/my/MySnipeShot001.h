#ifndef MYSNIPESHOT001_H_
#define MYSNIPESHOT001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 自機スナイプショット001 .
 * @version 1.00
 * @since 2014/13/06
 * @author Masatoshi Tsuge
 */
class MySnipeShot001 : public VvMyActor<GgafLib::SingleLaser> {

public:
    MySnipeShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MySnipeShot001();
};

}
#endif /*MYSNIPESHOT001_H_*/

