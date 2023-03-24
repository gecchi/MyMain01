#ifndef GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#define GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * RegularPolygonSprite用エフェクトクラス .
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteEffect : public Effect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_far_rate;
    D3DXHANDLE _h_sin_rz;
    D3DXHANDLE _h_cos_rz;

    D3DXHANDLE _h_u_center;
    D3DXHANDLE _h_v_center;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    RegularPolygonSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはRegularPolygonSpriteEffectManagerである<BR>
     */
    virtual ~RegularPolygonSpriteEffect();

};

}
#endif /*GGAFDXREGULARPOLYGONSPRITEEFFECT_H_*/
