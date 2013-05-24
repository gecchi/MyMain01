#ifndef EFFECTEXPLOSION004_H_
#define EFFECTEXPLOSION004_H_
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * 爆発エフェクトスプライト004
 * トーラス用爆発大
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion004 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectExplosion004(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EffectExplosion004();
};

}
#endif /*EFFECTEXPLOSION004_H_*/

