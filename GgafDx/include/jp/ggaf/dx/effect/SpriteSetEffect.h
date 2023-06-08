#ifndef GGAF_DX_SPRITESETEFFECT_H_
#define GGAF_DX_SPRITESETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * SpriteSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class SpriteSetEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_matWorld[18];
    D3DXHANDLE _ah_offset_u[18];
    D3DXHANDLE _ah_offset_v[18];
    D3DXHANDLE _ah_alpha[18];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    SpriteSetEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~SpriteSetEffect();

};

}
#endif /*GGAF_DX_SPRITESETEFFECT_H_*/
