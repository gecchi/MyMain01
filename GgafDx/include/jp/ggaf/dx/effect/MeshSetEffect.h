#ifndef GGAF_DX_MESHSETEFFECT_H_
#define GGAF_DX_MESHSETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MeshSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class MeshSetEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_materialDiffuse[32];
    D3DXHANDLE _ah_offset_u[32];
    D3DXHANDLE _ah_offset_v[32];
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MeshSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�MeshSetEffectManager�ł���<BR>
     */
    virtual ~MeshSetEffect();

};

}
#endif /*GGAF_DX_MESHSETEFFECT_H_*/
