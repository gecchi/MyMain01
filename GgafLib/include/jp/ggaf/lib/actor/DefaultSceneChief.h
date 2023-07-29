#ifndef GGAF_LIB_DEFAULTSCENECHIEF_H_
#define GGAF_LIB_DEFAULTSCENECHIEF_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/SceneChief.h"

namespace GgafLib {

/**
 * シーンのチーフクラス .
 * @version 1.00
 * @since 2017/12/07
 * @author Masatoshi Tsuge
 */
class DefaultSceneChief : public GgafDx::SceneChief {

public:
    DefaultSceneChief(DefaultScene* prm_pScene_platform);

    /**
     * 初期処理<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processJudgement() override {
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual ~DefaultSceneChief();
};

}
#endif /**GGAF_LIB_DEFAULTSCENECHIEF_H_*/
