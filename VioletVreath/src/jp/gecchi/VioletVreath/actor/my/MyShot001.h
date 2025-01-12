#ifndef MYSHOT001_H_
#define MYSHOT001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 自機ショット001 .
 * @version 1.00
 * @since 2010/07/04
 * @author Masatoshi Tsuge
 */
class MyShot001 : public VvMyActor<GgafLib::SingleLaser> {

public:
    MyShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

//    void drawHitArea() override;

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

