#ifndef GGAF_LIB_SINGLELASEREFFECT_H_
#define GGAF_LIB_SINGLELASEREFFECT_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"

namespace GgafLib {

/**
 * SingleLaser用エフェクトクラス .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class SingleLaserEffect : public GgafDx::MeshSetEffect {
    friend class DefaultEffectManager;
    friend class DefaultModelManager;
public:

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    SingleLaserEffect(const char* prm_effect_name);

    virtual ~SingleLaserEffect();

};

}
#endif /*GGAF_LIB_SINGLELASEREFFECT_H_*/
