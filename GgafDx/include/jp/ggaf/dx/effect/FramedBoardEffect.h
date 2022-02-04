#ifndef GGAF_DX_FRAMEDBOARDEFFECT_H_
#define GGAF_DX_FRAMEDBOARDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * FramedBoard�p���f���N���X.
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardEffect : public Effect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_offset_u[9];
    D3DXHANDLE _ah_offset_v[9];
//    D3DXHANDLE _ah_offset_x[9];
//    D3DXHANDLE _ah_offset_y[9];
//    D3DXHANDLE _ah_x_width_rate[9];
//    D3DXHANDLE _ah_y_width_rate[9];

    D3DXHANDLE _h_frame_width;
    D3DXHANDLE _h_frame_height;
    D3DXHANDLE _h_center_width;
    D3DXHANDLE _h_center_height;

    D3DXHANDLE _h_local_offset_x;
    D3DXHANDLE _h_local_offset_y;

    D3DXHANDLE _h_x;
    D3DXHANDLE _h_y;
    D3DXHANDLE _h_z;
    D3DXHANDLE _h_rz;

    D3DXHANDLE _h_frame_width_rate;
    D3DXHANDLE _h_center_width_rate;

    D3DXHANDLE _h_frame_height_rate;
    D3DXHANDLE _h_center_height_rate;



    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_depth_z;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    FramedBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~FramedBoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_FRAMEDBOARDEFFECT_H_*/
