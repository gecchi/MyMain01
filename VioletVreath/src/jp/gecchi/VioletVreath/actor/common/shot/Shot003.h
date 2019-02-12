#ifndef SHOT003_H_
#define SHOT003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 汎用弾003(小) .
 * 破壊不可能で等速直線移動<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot003 : public GgafLib::DefaultMassMeshActor {

public:
    Shot003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot003();
};

}
#endif /*SHOT003_H_*/

