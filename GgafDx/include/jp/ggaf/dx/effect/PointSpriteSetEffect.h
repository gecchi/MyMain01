#ifndef GGAF_DX_POINTSPRITESETEFFECT_H_
#define GGAF_DX_POINTSPRITESETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * PointSpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetEffect : public Effect {
    friend class EffectManager;

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
    D3DXHANDLE _hInvTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    PointSpriteSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはPointSpriteSetEffectManagerである<BR>
     */
    virtual ~PointSpriteSetEffect();

};

}
#endif /*GGAF_DX_POINTSPRITESETEFFECT_H_*/
