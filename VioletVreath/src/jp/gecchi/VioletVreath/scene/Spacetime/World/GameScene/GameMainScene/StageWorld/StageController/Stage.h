#ifndef STAGE_H_
#define STAGE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージ基底 .
 * @version 1.00
 * @since 2009/02/05
 * @author Masatoshi Tsuge
 */
class Stage : public VvScene<GgafLib::DefaultScene> {

public:
    enum {
        PHASE_INIT    ,
        PHASE_BEGIN   ,
        PHASE_PLAYING ,
        PHASE_END     ,
        PHASE_BANPEI,
    };

    static bool pause_;

    StagePartController* pScene_StagePartCtrler_;

public:
    Stage(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    /**
     * 初期処理
     */
    //virtual void orderStageMain() = 0;

    virtual ~Stage();
};

}
#endif /*STAGE_H_*/
