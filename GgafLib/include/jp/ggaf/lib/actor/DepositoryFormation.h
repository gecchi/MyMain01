#ifndef GGAF_LIB_DEPOSITORYFORMATION_H_
#define GGAF_LIB_DEPOSITORYFORMATION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/actor/ex/DepositoryFormation.h"

namespace GgafLib {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class DepositoryFormation : public GgafCore::DepositoryFormation {

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    DepositoryFormation(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual ~DepositoryFormation();
};

}
#endif /*GGAF_LIB_DEPOSITORYFORMATION_H_*/
