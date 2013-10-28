#ifndef GGAFDXCORE_GGAFDXSPRITESETEFFECT_H_
#define GGAFDXCORE_GGAFDXSPRITESETEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxSpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _ah_matWorld[18];
    D3DXHANDLE _ah_offset_u[18];
    D3DXHANDLE _ah_offset_v[18];
    D3DXHANDLE _ah_alpha[18];
    D3DXHANDLE _ah_x[18];
    D3DXHANDLE _ah_y[18];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxSpriteSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxSpriteSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXSPRITESETEFFECT_H_*/
