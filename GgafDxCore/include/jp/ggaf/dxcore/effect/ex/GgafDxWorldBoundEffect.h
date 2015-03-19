#ifndef GGAFDXCORE_GGAFDXWORLDEFFECT_H_
#define GGAFDXCORE_GGAFDXWORLDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"

namespace GgafDxCore {

/**
 * GgafDxWorldBoundModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2015/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundEffect : public GgafDxMorphMeshEffect {
    friend class GgafDxEffectManager;

public:
    GgafDxWorldBoundEffect(const char* prm_effect_name);

    virtual ~GgafDxWorldBoundEffect(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXWORLDEFFECT_H_*/
