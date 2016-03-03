#ifndef GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassSprite用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassSpriteEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_colMaterialDiffuse;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMassSpriteEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxMassSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEEFFECT_H_*/
