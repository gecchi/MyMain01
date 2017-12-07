#ifndef GGAFLIB_DEFAULTSCENEMEDIATOR_H_
#define GGAFLIB_DEFAULTSCENEMEDIATOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxSceneMediator.h"

namespace GgafLib {

/**
 * シーンの仲介者クラス .
 * @version 1.00
 * @since 2017/12/07
 * @author Masatoshi Tsuge
 */
class DefaultSceneMediator : public GgafDxCore::GgafDxSceneMediator {

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

    void processPreJudgement() override {
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


    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~DefaultSceneMediator();
};

}
#endif /**GGAFLIB_DEFAULTSCENEMEDIATOR_H_*/
