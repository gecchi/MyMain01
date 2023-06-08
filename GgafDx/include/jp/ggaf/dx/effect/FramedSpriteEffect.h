#ifndef GGAF_DX_FRAMEDSPRITEEFFECT_H_
#define GGAF_DX_FRAMEDSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * FramedSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteEffect : public World3DimEffect, public IPlaneEffect {

    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matWorldRotMv;
    D3DXHANDLE _h_colMaterialDiffuse;

    D3DXHANDLE _ah_offset_u[9];
    D3DXHANDLE _ah_offset_v[9];

    D3DXHANDLE _h_frame_width;
    D3DXHANDLE _h_frame_height;
    D3DXHANDLE _h_center_width;
    D3DXHANDLE _h_center_height;

    D3DXHANDLE _h_local_offset_x;
    D3DXHANDLE _h_local_offset_y;

    D3DXHANDLE _h_frame_sx;
    D3DXHANDLE _h_center_sx;

    D3DXHANDLE _h_frame_sy;
    D3DXHANDLE _h_center_sy;

    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_depth_z;


public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    FramedSpriteEffect(const char* prm_effect_name);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�FramedSpriteEffectManager�ł���<BR>
     */
    virtual ~FramedSpriteEffect();

};

}
#endif /*GGAF_DX_FRAMEDSPRITEEFFECT_H_*/
