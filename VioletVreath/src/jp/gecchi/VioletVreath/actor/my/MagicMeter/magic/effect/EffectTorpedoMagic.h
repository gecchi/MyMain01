#ifndef EFFECTTORPEDOMAGIC_H_
#define EFFECTTORPEDOMAGIC_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * 魚雷魔法装備時のエフェクト .
 * @version 1.00
 * @since 2012/07/30
 * @author Masatoshi Tsuge
 */
class EffectTorpedoMagic : public GgafLib::DefaultSpriteActor {

public:
    EffectTorpedoMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectTorpedoMagic();
};

}
#endif /*EFFECTTORPEDOMAGIC_H_*/

