#ifndef GGAF_DX_MASSMORPHMESHEFFECT_H_
#define GGAF_DX_MASSMORPHMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MassMorphMesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MassMorphMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_morph_target_num;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MassMorphMeshEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�MassMorphMeshEffectManager�ł���<BR>
     */
    virtual ~MassMorphMeshEffect();

};

}
#endif /*GGAF_DX_MASSMORPHMESHEFFECT_H_*/
