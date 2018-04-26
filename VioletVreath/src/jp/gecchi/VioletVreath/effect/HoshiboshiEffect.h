#ifndef HOSHIBOSHIEFFECT_H_
#define HOSHIBOSHIEFFECT_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"

namespace VioletVreath {

/**
 * Hoshiboshi用エフェクトクラス .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class HoshiboshiEffect : public GgafDxCore::GgafDxPointSpriteEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE h_fX_MyShip_;
    D3DXHANDLE h_fY_MyShip_;
    D3DXHANDLE h_fZ_MyShip_;
    D3DXHANDLE h_far_rate_;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    HoshiboshiEffect(const char* prm_effect_name);


    virtual ~HoshiboshiEffect(); //デストラクタ

};

}
#endif /*HOSHIBOSHIEFFECT_H_*/
