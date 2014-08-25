#ifndef EFFECTLASERMAGIC_H_
#define EFFECTLASERMAGIC_H_
#include "VioletVreath.h"
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
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

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

