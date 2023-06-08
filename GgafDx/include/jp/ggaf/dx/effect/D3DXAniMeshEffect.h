#ifndef GGAF_DX_D3DXANIMESHEFFECT_H_
#define GGAF_DX_D3DXANIMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    D3DXAniMeshEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはD3DXAniMeshEffectManagerである<BR>
     */
    virtual ~D3DXAniMeshEffect();

};

}
#endif /*GGAF_DX_D3DXANIMESHEFFECT_H_*/
