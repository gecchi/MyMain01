#ifndef GGAFDXCORE_GGAFDXBOARDEFFECT_H_
#define GGAFDXCORE_GGAFDXBOARDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxBoard�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxBoardEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_transformed_x;
    D3DXHANDLE _h_transformed_y;

    D3DXHANDLE _h_local_left_top_x;
    D3DXHANDLE _h_local_left_top_y;

    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_sx;
    D3DXHANDLE _h_sy;
    D3DXHANDLE _h_rz;
    D3DXHANDLE _h_depth_z;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxBoardEffectManager�ł���<BR>
     */
    virtual ~GgafDxBoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXBOARDEFFECT_H_*/
