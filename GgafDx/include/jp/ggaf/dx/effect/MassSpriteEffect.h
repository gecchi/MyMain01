#ifndef GGAF_DX_MASSSPRITEEFFECT_H_
#define GGAF_DX_MASSSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/MassEffect.h"

namespace GgafDx {

/**
 * MassSprite用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteEffect : public MassEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~MassSpriteEffect();

};

}
#endif /*GGAF_DX_MASSSPRITEEFFECT_H_*/
