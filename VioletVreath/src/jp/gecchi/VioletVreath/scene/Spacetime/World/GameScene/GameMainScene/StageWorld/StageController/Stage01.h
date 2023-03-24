#ifndef STAGE01_H_
#define STAGE01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "Stage.h"

namespace VioletVreath {

DECLARE_EVENT_VAL(EVENT_STAGE01_PART_CTRLER_WAS_END);

/**
 * ステージ01 .
 * @version 1.00
 * @since 2018/09/08
 * @author Masatoshi Tsuge
 */
class Stage01 : public Stage {

public:
    WorldBound001* pWorldBound_;
    HoshiBoshi001* pHoshiBoshi_;

    Planet001* pPlanet_;
    Horizon001* pHorizon_;

    LabelGecchi16Font* pMessage_;

public:
    Stage01(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~Stage01();
};

}
#endif /*STAGE01_H_*/
