#ifndef GGAF_DX_WORLD3DIMEFFECT_H_
#define GGAF_DX_WORLD3DIMEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * World3D用エフェクトクラス .
 * @version 1.00
 * @since 2023/06/07
 * @author Masatoshi Tsuge
 */
class World3DimEffect : public Effect {
    friend class EffectManager;

public:

    D3DXHANDLE _h_matView;

    /**
     * コンストラクタ<BR>
     * @return
     */
    World3DimEffect(const char* prm_effect_name);

    void setParamPerFrame() override;
    /**
     * デストラクタ<BR>
     */
    virtual ~World3DimEffect();

};

}
#endif /*GGAF_DX_WORLD3DIMEFFECT_H_*/
