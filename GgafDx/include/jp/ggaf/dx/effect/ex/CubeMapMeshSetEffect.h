#ifndef GGAF_DX_CUBEMAPMESHSETEFFECT_H_
#define GGAF_DX_CUBEMAPMESHSETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"

namespace GgafDx {

/**
 * CubeMapMeshsModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetEffect : public MeshSetEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    CubeMapMeshSetEffect(const char* prm_effect_name);

    virtual ~CubeMapMeshSetEffect();

};

}
#endif /*GGAF_DX_CUBEMAPMESHEFFECT_H_*/
