#ifndef GGAFDXCORE_GGAFDXMESHSETEFFECT_H_
#define GGAFDXCORE_GGAFDXMESHSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMeshSet�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class GgafDxMeshSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[19];
    D3DXHANDLE _ah_materialDiffuse[19];
    D3DXHANDLE _ah_offset_u[19];
    D3DXHANDLE _ah_offset_v[19];
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMeshSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxMeshSetEffectManager�ł���<BR>
     */
    virtual ~GgafDxMeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETEFFECT_H_*/
