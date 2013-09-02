#ifndef GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMorphMesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_morph_target_num;
    D3DXHANDLE _ah_weight[MAX_MORPH_TARGET+1];
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
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
    GgafDxMorphMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxMorphMeshEffectManager�ł���<BR>
     */
    virtual ~GgafDxMorphMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_*/
