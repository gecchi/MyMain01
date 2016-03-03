#ifndef EFFECTEXPLOSION003_H_
#define EFFECTEXPLOSION003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {

/**
 * 爆発エフェクトスプライト003
 * @version 1.00
 * @since 2010/07/05
 * @author Masatoshi Tsuge
 */
class EffectExplosion003 : public GgafLib::DefaultMassSpriteActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectExplosion003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EffectExplosion003();
};

}
#endif /*EFFECTEXPLOSION003_H_*/

