#ifndef GGAF_LIB_DEFAULTSCENEMEDIATOR_H_
#define GGAF_LIB_DEFAULTSCENEMEDIATOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/SceneMediator.h"

namespace GgafLib {

/**
 * シーンの仲介者クラス .
 * @version 1.00
 * @since 2017/12/07
 * @author Masatoshi Tsuge
 */
class DefaultSceneMediator : public GgafDx::SceneMediator {

public:
    DefaultSceneMediator(DefaultScene* prm_pScene_platform);

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

    virtual ~DefaultSceneMediator();
};

}
#endif /**GGAF_LIB_DEFAULTSCENEMEDIATOR_H_*/
