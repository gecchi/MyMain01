#ifndef GGAF_DX_SKINANIMESHEFFECT_H_
#define GGAF_DX_SKINANIMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

//DefaultSkinAniMeshEffect.fx �� �萔����v�����鎖
#define SkinAniMeshModel_MAX_BONE_WORLD_MATRIX (50) //2�ȏ�łȂ��ƃu���C�N���Ȃ��̂Ń_��

namespace GgafDx {

/**
 * Mesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class SkinAniMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;
    D3DXHANDLE _ah_matBone[SkinAniMeshModel_MAX_BONE_WORLD_MATRIX];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    SkinAniMeshEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�SkinAniMeshEffectManager�ł���<BR>
     */
    virtual ~SkinAniMeshEffect();

};

}
#endif /*GGAF_DX_SKINANIMESHEFFECT_H_*/
