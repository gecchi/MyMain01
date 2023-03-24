#ifndef GGAF_DX_MASSEFFECT_H_
#define GGAF_DX_MASSEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * Mass用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassEffect : public Effect {
    friend class EffectManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassEffect(const char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはMassEffectManagerである<BR>
     */
    virtual ~MassEffect();

};

}
#endif /*GGAF_DX_MASSEFFECT_H_*/
