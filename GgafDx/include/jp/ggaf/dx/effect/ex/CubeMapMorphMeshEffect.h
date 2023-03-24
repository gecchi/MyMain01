#ifndef GGAF_DX_CUBEMAPMORPHMESHEFFECT_H_
#define GGAF_DX_CUBEMAPMORPHMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MorphMeshEffect.h"

namespace GgafDx {

/**
 * CubeMapMorphMeshModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshEffect : public MorphMeshEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    CubeMapMorphMeshEffect(const char* prm_effect_name);

    virtual ~CubeMapMorphMeshEffect();

};

}
#endif /*GGAF_DX_CUBEMAPMESHEFFECT_H_*/
