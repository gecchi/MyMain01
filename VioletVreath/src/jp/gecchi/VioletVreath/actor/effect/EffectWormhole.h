#ifndef EFFECTWORMHOLE_H_
#define EFFECTWORMHOLE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"

namespace VioletVreath {

/**
 * ワームホール(敵出現の根元)エフェクト、基底クラス .
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class EffectWormhole : public VvEffectActor<GgafLib::DefaultMorphMeshActor> {

public:
    EffectWormhole(const char* prm_name, const char* prm_model);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectWormhole();
};

}
#endif /*EFFECTWORMHOLE_H_*/

