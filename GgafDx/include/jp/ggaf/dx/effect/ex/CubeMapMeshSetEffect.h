#ifndef GGAF_DX_CUBEMAPMESHSETEFFECT_H_
#define GGAF_DX_CUBEMAPMESHSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"

namespace GgafDx {

/**
 * CubeMapMeshsModel�p�G�t�F�N�g�N���X.
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

    virtual ~CubeMapMeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_CUBEMAPMESHEFFECT_H_*/
