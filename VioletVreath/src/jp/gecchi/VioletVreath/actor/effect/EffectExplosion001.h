#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"

namespace VioletVreath {

/**
 * 爆発エフェクトスプライト001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class EffectExplosion001 : public VvEffectActor<GgafLib::DefaultMassSpriteActor> {

public:
    EffectExplosion001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectExplosion001();
};

}
#endif /*EFFECTEXPLOSION001_H_*/

