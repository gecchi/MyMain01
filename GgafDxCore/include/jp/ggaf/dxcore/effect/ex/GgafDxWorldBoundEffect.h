#ifndef GGAFDXCORE_GGAFDXWORLDEFFECT_H_
#define GGAFDXCORE_GGAFDXWORLDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"

namespace GgafDxCore {

/**
 * GgafDxWorldBoundModel用エフェクトクラス.
 * @version 1.00
 * @since 2015/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundEffect : public GgafDxMorphMeshEffect {
    friend class GgafDxEffectManager;

public:
    GgafDxWorldBoundEffect(const char* prm_effect_name);

    virtual ~GgafDxWorldBoundEffect(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXWORLDEFFECT_H_*/
