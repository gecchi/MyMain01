#ifndef GGAFDXCORE_GGAFDXALPHAFADER_H_
#define GGAFDXCORE_GGAFDXALPHAFADER_H_
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * フェーディング支援クラス .
 * GgafDxDrawableActor のメンバの
 * _alpha(アクターのα強度)をなめらかに変化させ、<BR>
 * フェーディングを行うことを主な目的<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaFader : public GgafCore::GgafValueTransitioner<float, 1 > {

public:
    /** [r]対象アクター */
    GgafDxDrawableActor* const _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~GgafDxAlphaFader();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHAFADER_H_*/

