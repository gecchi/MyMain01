#ifndef GGAFDXCORE_GGAFDXMASSMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSMESHEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassMesh�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMassMeshEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxMassMeshEffectManager�ł���<BR>
     */
    virtual ~GgafDxMassMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMASSMESHEFFECT_H_*/
