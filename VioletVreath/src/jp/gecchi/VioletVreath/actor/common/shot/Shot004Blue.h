#ifndef SHOT004BLUE_H_
#define SHOT004BLUE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 汎用弾004(小) .
 * 破壊不可能で等速直線移動の小さなレーザー片<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004Blue : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    bool view_in_;

public:
    Shot004Blue(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual ~Shot004Blue();
};

}
#endif /*SHOT004BLUE_H_*/

