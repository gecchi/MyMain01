#ifndef GGAFDXCORE_GGAFDXPOINTSPRITEEFFECT_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITEEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxPointSprite用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_dist_VpFrontPlane;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxPointSpriteEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxPointSpriteEffectManagerである<BR>
     */
    virtual ~GgafDxPointSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITEEFFECT_H_*/
