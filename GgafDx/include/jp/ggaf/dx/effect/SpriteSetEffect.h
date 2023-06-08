#ifndef GGAF_DX_SPRITESETEFFECT_H_
#define GGAF_DX_SPRITESETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * SpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class SpriteSetEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_matWorld[18];
    D3DXHANDLE _ah_offset_u[18];
    D3DXHANDLE _ah_offset_v[18];
    D3DXHANDLE _ah_alpha[18];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    SpriteSetEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~SpriteSetEffect();

};

}
#endif /*GGAF_DX_SPRITESETEFFECT_H_*/
