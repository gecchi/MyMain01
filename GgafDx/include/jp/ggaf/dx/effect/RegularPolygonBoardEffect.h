#ifndef GGAF_DX_REGULARPOLYGONBOARDEFFECT_H_
#define GGAF_DX_REGULARPOLYGONBOARDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * RegularPolygonBoard�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class RegularPolygonBoardEffect : public Effect {
    friend class EffectManager;

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

    D3DXHANDLE _h_sin_rz;
    D3DXHANDLE _h_cos_rz;
    D3DXHANDLE _h_x_center;
    D3DXHANDLE _h_y_center;
    D3DXHANDLE _h_u_center;
    D3DXHANDLE _h_v_center;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    RegularPolygonBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�RegularPolygonBoardEffectManager�ł���<BR>
     */
    virtual ~RegularPolygonBoardEffect();

};

}
#endif /*GGAF_DX_REGULARPOLYGONBOARDEFFECT_H_*/
