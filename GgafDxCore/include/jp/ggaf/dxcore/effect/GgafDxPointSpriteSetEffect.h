#ifndef GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxPointSpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
//    D3DXHANDLE _h_tex_blink_power;
//    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_colMaterialDiffuse[32];
//    D3DXHANDLE _ah_offset_u[32];
//    D3DXHANDLE _ah_offset_v[32];
//    D3DXHANDLE _h_specular;
//    D3DXHANDLE _h_specular_power;
//    D3DXHANDLE _h_posCam;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxPointSpriteSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxPointSpriteSetEffectManagerである<BR>
     */
    virtual ~GgafDxPointSpriteSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITESETEFFECT_H_*/
