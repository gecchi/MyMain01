#ifndef TESTGUSHOT_H_
#define TESTGUSHOT_H_
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * グーショット .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestGuShot : public GgafLib::SingleLaser {

public:
    TestGuShot(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~TestGuShot();
};

}
#endif /*TESTGUSHOT_H_*/

