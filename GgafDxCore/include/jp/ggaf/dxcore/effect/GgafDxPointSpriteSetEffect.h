#ifndef GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxPointSpriteSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
//    D3DXHANDLE _h_tex_blink_power;
//    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_colMaterialDiffuse[32];
//    D3DXHANDLE _ah_offset_u[32];
//    D3DXHANDLE _ah_offset_v[32];
//    D3DXHANDLE _h_specular;
//    D3DXHANDLE _h_specular_power;
//    D3DXHANDLE _h_posCam;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxPointSpriteSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxPointSpriteSetEffectManager�ł���<BR>
     */
    virtual ~GgafDxPointSpriteSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_*/
