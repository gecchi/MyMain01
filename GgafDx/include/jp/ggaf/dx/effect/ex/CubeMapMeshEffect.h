#ifndef GGAF_DX_CUBEMAPMESHEFFECT_H_
#define GGAF_DX_CUBEMAPMESHEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"

namespace GgafDx {

/**
 * CubeMapMeshModel�p�G�t�F�N�g�N���X.
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

    virtual ~CubeMapMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_CUBEMAPMESHEFFECT_H_*/
