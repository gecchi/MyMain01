#ifndef EFFECTVREATHMAGIC001_H_
#define EFFECTVREATHMAGIC001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * スピードアップのエフェクト .
 * @version 1.00
 * @since 2012/05/08
 * @author Masatoshi Tsuge
 */
class EffectVreathMagic001 : public GgafLib::DefaultSpriteActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectVreathMagic001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectVreathMagic001();
};

}
#endif /*EFFECTVREATHMAGIC001_H_*/

