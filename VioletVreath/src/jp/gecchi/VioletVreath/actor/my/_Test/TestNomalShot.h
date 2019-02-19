#ifndef TESTNOMALSHOT_H_
#define TESTNOMALSHOT_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * ノーマルショット .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestNomalShot : public VvMyActor<GgafLib::SingleLaser> {

public:
    TestNomalShot(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~TestNomalShot();
};

}
#endif /*TESTNOMALSHOT_H_*/

