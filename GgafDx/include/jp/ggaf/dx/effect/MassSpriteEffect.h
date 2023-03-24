#ifndef GGAF_DX_MASSSPRITEEFFECT_H_
#define GGAF_DX_MASSSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MassEffect.h"

namespace GgafDx {

/**
 * MassSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteEffect : public MassEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    MassSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~MassSpriteEffect();

};

}
#endif /*GGAF_DX_MASSSPRITEEFFECT_H_*/
