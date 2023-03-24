#ifndef GGAF_DX_FRAMEDSPRITEEFFECT_H_
#define GGAF_DX_FRAMEDSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * FramedSprite用エフェクトクラス .
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteEffect : public Effect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorldRotMv;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_far_rate;

//    D3DXHANDLE _h_offset_u;
//    D3DXHANDLE _h_offset_v;

    D3DXHANDLE _ah_offset_u[9];
    D3DXHANDLE _ah_offset_v[9];
//    D3DXHANDLE _ah_offset_x[9];
//    D3DXHANDLE _ah_offset_y[9];

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
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    FramedSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはFramedSpriteEffectManagerである<BR>
     */
    virtual ~FramedSpriteEffect();

};

}
#endif /*GGAF_DX_FRAMEDSPRITEEFFECT_H_*/
