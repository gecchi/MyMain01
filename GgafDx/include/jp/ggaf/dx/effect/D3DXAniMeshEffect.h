#ifndef GGAF_DX_D3DXANIMESHEFFECT_H_
#define GGAF_DX_D3DXANIMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * Mesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    D3DXAniMeshEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�D3DXAniMeshEffectManager�ł���<BR>
     */
    virtual ~D3DXAniMeshEffect();

};

}
#endif /*GGAF_DX_D3DXANIMESHEFFECT_H_*/
