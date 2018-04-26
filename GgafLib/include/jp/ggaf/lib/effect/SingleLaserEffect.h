#ifndef GGAFLIB_SINGLELASEREFFECT_H_
#define GGAFLIB_SINGLELASEREFFECT_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"

namespace GgafLib {

/**
 * SingleLaser用エフェクトクラス .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class SingleLaserEffect : public GgafDxCore::GgafDxMeshSetEffect {
    friend class DefaultEffectManager;

public:

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    SingleLaserEffect(const char* prm_effect_name);

    virtual ~SingleLaserEffect(); //デストラクタ

};

}
#endif /*GGAFLIB_SINGLELASEREFFECT_H_*/
