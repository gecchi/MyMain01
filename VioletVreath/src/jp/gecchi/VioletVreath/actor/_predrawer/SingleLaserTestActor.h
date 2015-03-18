#ifndef SINGLELASEREFFECTACTOR_H_
#define SINGLELASEREFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class SingleLaserTestActor : public GgafLib::SingleLaser {
public:

    SingleLaserTestActor(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~SingleLaserTestActor();
};

}
#endif /*SINGLELASEREFFECTACTOR_H_*/

