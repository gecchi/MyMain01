#ifndef ALICESHOT_H_
#define ALICESHOT_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * アリス弾幕用ショット .
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class AliceShot : public VvEnemyActor<GgafLib::SingleLaser> {

public:
    AliceShot(const char* prm_name, const char* prm_model);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~AliceShot();
};

}
#endif /*SHOT004_H_*/

