#ifndef ALICESHOT_H_
#define ALICESHOT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * アリス弾幕用ショット .
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class AliceShot : public GgafLib::SingleLaser {

public:
    AliceShot(const char* prm_name, const char* prm_model_id);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~AliceShot();
};

}
#endif /*SHOT004_H_*/

