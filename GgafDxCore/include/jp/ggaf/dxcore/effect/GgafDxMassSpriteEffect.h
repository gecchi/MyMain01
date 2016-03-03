#ifndef GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassSpriteEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_colMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMassSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxMassSpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_*/
