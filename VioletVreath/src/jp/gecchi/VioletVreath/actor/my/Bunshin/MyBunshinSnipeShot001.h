#ifndef MYBUNSHINSNIPESHOT001_H_
#define MYBUNSHINSNIPESHOT001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 分身用スナイプショット001 .
 * @version 1.00
 * @since 2014/13/06
 * @author Masatoshi Tsuge
 */
class MyBunshinSnipeShot001 : public VvMyActor<GgafLib::SingleLaser> {

public:
    MyBunshinSnipeShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MyBunshinSnipeShot001();
};

}
#endif /*MYBUNSHINSNIPESHOT001_H_*/

