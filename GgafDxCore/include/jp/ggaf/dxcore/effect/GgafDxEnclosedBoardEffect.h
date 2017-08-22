#ifndef GGAFDXCORE_GGAFDXENCLOSEDBOARDEFFECT_H_
#define GGAFDXCORE_GGAFDXENCLOSEDBOARDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxEnclosedBoard�p���f���N���X.
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class GgafDxEnclosedBoardEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_offset_u[9];
    D3DXHANDLE _ah_offset_v[9];
    D3DXHANDLE _ah_offset_x[9];
    D3DXHANDLE _ah_offset_y[9];
//    D3DXHANDLE _ah_x_width_rate[9];
//    D3DXHANDLE _ah_y_width_rate[9];

    D3DXHANDLE _h_unit_width;
    D3DXHANDLE _h_unit_height;

    D3DXHANDLE _h_local_offset_x;
    D3DXHANDLE _h_local_offset_y;

    D3DXHANDLE _h_x;
    D3DXHANDLE _h_y;
    D3DXHANDLE _h_z;
    D3DXHANDLE _h_rz;

    D3DXHANDLE _h_top_edge_size_rate;
    D3DXHANDLE _h_center_height_rate;
    D3DXHANDLE _h_bottom_edge_size_rate;

    D3DXHANDLE _h_left_edge_size_rate;
    D3DXHANDLE _h_center_width_rate;
    D3DXHANDLE _h_right_edge_size_rate;

    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_depth_z;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxEnclosedBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxEnclosedBoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXENCLOSEDBOARDEFFECT_H_*/
