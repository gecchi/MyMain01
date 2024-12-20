#ifndef GGAF_DX_MASSSPRITEEFFECT_H_
#define GGAF_DX_MASSSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * MassSprite用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassSpriteEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~MassSpriteEffect();

};

}
#endif /*GGAF_DX_MASSSPRITEEFFECT_H_*/
