#ifndef EFFECTTURBO002_H_
#define EFFECTTURBO002_H_
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * ターボ発動エフェクト
 * @version 1.00
 * @since 2010/02/25
 * @author Masatoshi Tsuge
 */
class EffectTurbo002 : public GgafLib::DefaultSpriteActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectTurbo002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectTurbo002();
};

}
#endif /*EFFECTTURBO002_H_*/

