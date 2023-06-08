#ifndef GGAF_DX_SPRITEEFFECT_H_
#define GGAF_DX_SPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * Sprite用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class SpriteEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
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
    SpriteEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはSpriteEffectManagerである<BR>
     */
    virtual ~SpriteEffect();

};

}
#endif /*GGAF_DX_SPRITEEFFECT_H_*/
