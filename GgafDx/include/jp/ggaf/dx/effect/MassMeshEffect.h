#ifndef GGAF_DX_MASSMESHEFFECT_H_
#define GGAF_DX_MASSMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MassMesh用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassMeshEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはMassMeshEffectManagerである<BR>
     */
    virtual ~MassMeshEffect();

};

}
#endif /*GGAF_DX_MASSMESHEFFECT_H_*/
