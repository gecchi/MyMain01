#ifndef STAGE02_H_
#define STAGE02_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"

namespace VioletVreath {

HASHVAL(EVENT_STG02_CTRLER_WAS_END);

/**
 * ステージ02 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage02 : public Stage {

public:
    WorldBound002* pWorldBound_;
    HoshiBoshi001* pHoshiBoshi_;

    LabelGecchi16Font* pMessage_;

public:
    Stage02(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage02();
};

}
#endif /*STAGE02_H_*/
