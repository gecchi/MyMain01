#ifndef GGAFDXCORE_GGAFDXD3DXANIMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXD3DXANIMESHEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMesh�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxD3DXAniMeshEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxD3DXAniMeshEffectManager�ł���<BR>
     */
    virtual ~GgafDxD3DXAniMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXD3DXANIMESHEFFECT_H_*/
