#ifndef GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassBoard用モデルクラス.
 * @version 1.00
 * @since 2015/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassBoardEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMassBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxMassBoardEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_*/
