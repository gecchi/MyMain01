#ifndef GGAF_DX_FRAMEDBOARDEFFECT_H_
#define GGAF_DX_FRAMEDBOARDEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "Fix2DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * FramedBoard用モデルクラス.
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardEffect : public Fix2DimEffect, public IPlaneEffect {

    friend class EffectManager;

public:
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _ah_offset_u[9];
    D3DXHANDLE _ah_offset_v[9];

    D3DXHANDLE _h_frame_width;
    D3DXHANDLE _h_frame_height;
    D3DXHANDLE _h_center_width;
    D3DXHANDLE _h_center_height;

    D3DXHANDLE _h_local_offset_x;
    D3DXHANDLE _h_local_offset_y;

    D3DXHANDLE _h_x;
    D3DXHANDLE _h_y;
    D3DXHANDLE _h_z;
    D3DXHANDLE _h_rz;

    D3DXHANDLE _h_frame_sx;
    D3DXHANDLE _h_center_sx;

    D3DXHANDLE _h_frame_sy;
    D3DXHANDLE _h_center_sy;



    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_depth_z;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    FramedBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはEffectManagerである<BR>
     */
    virtual ~FramedBoardEffect();

};

}
#endif /*GGAF_DX_FRAMEDBOARDEFFECT_H_*/
