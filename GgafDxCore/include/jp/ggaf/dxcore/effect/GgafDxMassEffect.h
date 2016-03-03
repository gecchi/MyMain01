#ifndef GGAFDXCORE_GGAFDXMASSEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMass用エフェクトクラス .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMassEffect(const char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMassEffectManagerである<BR>
     */
    virtual ~GgafDxMassEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMASSEFFECT_H_*/
