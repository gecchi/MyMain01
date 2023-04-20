#ifndef GGAF_DX_ALPHAFADER_H_
#define GGAF_DX_ALPHAFADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

namespace GgafDx {

/**
 * フェーディング支援クラス .
 * アクターのα強度をなめらかに変化させ、<BR>
 * フェーディングを行うことを主な目的<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class AlphaFader : public GgafCore::ValueTransitioner<float, 1 > {

public:
    /** [r]対象アクター */
    FigureActor* const _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    explicit AlphaFader(FigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~AlphaFader();
};

}
#endif /*GGAF_DX_ALPHAFADER_H_*/

