#ifndef GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#define GGAFDXREGULARPOLYGONSPRITEEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxRegularPolygonSprite用エフェクトクラス .
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonSpriteEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_far_rate;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxRegularPolygonSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxRegularPolygonSpriteEffectManagerである<BR>
     */
    virtual ~GgafDxRegularPolygonSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDXREGULARPOLYGONSPRITEEFFECT_H_*/
