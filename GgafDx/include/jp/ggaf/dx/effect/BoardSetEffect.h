#ifndef GGAF_DX_BOARDSETEFFECT_H_
#define GGAF_DX_BOARDSETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "Fix2DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * BoardSet用モデルクラス.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class BoardSetEffect : public Fix2DimEffect, public IPlaneEffect {

    friend class EffectManager;

public:
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_offset_u[28];
    D3DXHANDLE _ah_offset_v[28];
    D3DXHANDLE _ah_transformed_x[28];
    D3DXHANDLE _ah_transformed_y[28];
    D3DXHANDLE _ah_alpha[28];
    D3DXHANDLE _ah_depth_z[28];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    BoardSetEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~BoardSetEffect();

};

}
#endif /*GGAF_DX_BOARDSETEFFECT_H_*/
