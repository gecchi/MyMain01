#ifndef TESTCHOKISHOT_H_
#define TESTCHOKISHOT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * �`���L�V���b�g .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestChokiShot : public GgafLib::SingleLaser {

public:
    TestChokiShot(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~TestChokiShot();
};

}
#endif /*TESTCHOKISHOT_H_*/

