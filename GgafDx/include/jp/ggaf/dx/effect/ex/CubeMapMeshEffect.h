#ifndef GGAF_DX_CUBEMAPMESHEFFECT_H_
#define GGAF_DX_CUBEMAPMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"

namespace GgafDx {

/**
 * CubeMapMeshModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshEffect : public MeshEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    CubeMapMeshEffect(const char* prm_effect_name);

    virtual ~CubeMapMeshEffect();

};

}
#endif /*GGAF_DX_CUBEMAPMESHEFFECT_H_*/
