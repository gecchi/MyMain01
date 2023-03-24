#ifndef GGAF_LIB_FKFORMATION_H_
#define GGAF_LIB_FKFORMATION_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/FkFormation.h"

namespace GgafLib {

/**
 * フォワードキネマテックのようなフォーメーションアクタークラス .
 * @version 1.00
 * @since 2013/06/21
 * @author Masatoshi Tsuge
 */
class FkFormation : public GgafDx::FkFormation {

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    FkFormation(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual ~FkFormation();
};

}
#endif /*GGAF_LIB_FKFORMATION_H_*/
