#ifndef GGAF_DX_MASSBOARDEFFECT_H_
#define GGAF_DX_MASSBOARDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "Fix2DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * MassBoard用モデルクラス.
 * @version 1.00
 * @since 2015/02/25
 * @author Masatoshi Tsuge
 */
class MassBoardEffect : public Fix2DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassBoardEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~MassBoardEffect();

};

}
#endif /*GGAF_DX_MASSBOARDEFFECT_H_*/
