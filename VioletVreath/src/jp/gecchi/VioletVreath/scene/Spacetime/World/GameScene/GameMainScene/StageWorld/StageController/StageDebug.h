#ifndef STAGEDEBUG_H_
#define STAGEDEBUG_H_
#include "VioletVreath.h"
#include "Stage.h"

namespace VioletVreath {

DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END);

/**
 * ステージ01 .
 * @version 1.00
 * @since 2018/09/08
 * @author Masatoshi Tsuge
 */
class StageDebug : public Stage {

public:
    WorldBound001* pWorldBound_;
    HoshiBoshi001* pHoshiBoshi_;

    Planet001* pPlanet_;
    Horizon001* pHorizon_;

    LabelGecchi16Font* pMessage_;

public:
    StageDebug(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageDebug();
};

}
#endif /*STAGEDEBUG_H_*/
