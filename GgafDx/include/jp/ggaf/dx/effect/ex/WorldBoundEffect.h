#ifndef GGAF_DX_WORLDEFFECT_H_
#define GGAF_DX_WORLDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MorphMeshEffect.h"

namespace GgafDx {

/**
 * WorldBoundModel用エフェクトクラス.
 * @version 1.00
 * @since 2015/05/20
 * @author Masatoshi Tsuge
 */
class WorldBoundEffect : public MorphMeshEffect {
    friend class EffectManager;

public:
    WorldBoundEffect(const char* prm_effect_name);

    virtual ~WorldBoundEffect();
};

}
#endif /*GGAF_DX_WORLDEFFECT_H_*/
