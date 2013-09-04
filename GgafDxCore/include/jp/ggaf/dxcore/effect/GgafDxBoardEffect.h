#ifndef GGAFDXCORE_GGAFDXBOARDEFFECT_H_
#define GGAFDXCORE_GGAFDXBOARDEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxBoard用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxBoardEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;

    D3DXHANDLE _h_rot_center_X;
    D3DXHANDLE _h_rot_center_Y;

    D3DXHANDLE _hSx;
    D3DXHANDLE _hSy;
    D3DXHANDLE _h_Rz;
    D3DXHANDLE _h_alpha;
    D3DXHANDLE _hDepthZ;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxBoardEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxBoardEffectManagerである<BR>
     */
    virtual ~GgafDxBoardEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXBOARDEFFECT_H_*/
