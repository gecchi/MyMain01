#ifndef GGAF_DX_FIX2DIMEFFECT_H_
#define GGAF_DX_FIX2DIMEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * Fix2D用エフェクトクラス .
 * @version 1.00
 * @since 2023/06/07
 * @author Masatoshi Tsuge
 */
class Fix2DimEffect : public Effect {
    friend class EffectManager;

public:
    /**
     * コンストラクタ<BR>
     * @return
     */
    Fix2DimEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     */
    virtual ~Fix2DimEffect();

};

}
#endif /*GGAF_DX_FIX2DIMEFFECT_H_*/
