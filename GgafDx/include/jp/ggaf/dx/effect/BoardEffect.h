#ifndef GGAF_DX_BOARDEFFECT_H_
#define GGAF_DX_BOARDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "Fix2DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * Board用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class BoardEffect : public Fix2DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_transformed_x;
    D3DXHANDLE _h_transformed_y;

    D3DXHANDLE _h_local_left_top_x;
    D3DXHANDLE _h_local_left_top_y;

    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_sx;
    D3DXHANDLE _h_sy;
    D3DXHANDLE _h_rz;
    D3DXHANDLE _h_depth_z;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    BoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはBoardEffectManagerである<BR>
     */
    virtual ~BoardEffect();

};

}
#endif /*GGAF_DX_BOARDEFFECT_H_*/
