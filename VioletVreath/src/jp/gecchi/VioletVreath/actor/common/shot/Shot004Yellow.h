#ifndef SHOT004YELLOW_H_
#define SHOT004YELLOW_H_
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * 汎用弾004(小) .
 * 破壊不可能で等速直線移動の小さなレーザー片<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004Yellow : public GgafLib::SingleLaser {

public:
    bool view_in_;

public:
    Shot004Yellow(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot004Yellow();
};

}
#endif /*SHOT004YELLOW_H_*/

