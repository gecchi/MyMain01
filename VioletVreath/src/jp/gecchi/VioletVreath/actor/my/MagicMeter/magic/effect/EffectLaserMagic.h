#ifndef EFFECTLASERMAGIC_H_
#define EFFECTLASERMAGIC_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * レーザーのエフェクト .
 * @version 1.00
 * @since 2013/07/26
 * @author Masatoshi Tsuge
 */
class EffectLaserMagic : public GgafLib::DefaultSpriteActor {

public:
    EffectLaserMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectLaserMagic();
};

}
#endif /*EFFECTLASERMAGIC_H_*/

