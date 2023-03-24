#ifndef EFFECTEXPLOSION003_H_
#define EFFECTEXPLOSION003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"

namespace VioletVreath {

/**
 * 爆発エフェクトスプライト003
 * @version 1.00
 * @since 2010/07/05
 * @author Masatoshi Tsuge
 */
class EffectExplosion003 : public GgafLib::DefaultPointSpriteSetActor {

public:
    EffectExplosion003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    int isOutOfView() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EffectExplosion003();
};

}
#endif /*EFFECTEXPLOSION003_H_*/

