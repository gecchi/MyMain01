#ifndef GGAF_CORE_DESTRUCTACTOR_H_
#define GGAF_CORE_DESTRUCTACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafCore {

/**
 * ダミーアクタークラス .
 * 子アクターが無くなれば、自動的に自殺する悲しい一時的なアクターです。<BR>
 * 団体行動を採るときに、親アクターにすると何かと便利かもしれないでしょう。<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class DestructActor : public MainActor {

public:
    DestructActor(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void processFinal() override {
        if (getChildFirst() == nullptr) {
            sayonara(1); //1フレーム後
        }
    }

    /**
     * 当たり判定不要のため常にfalseを返す .
     * @param prm_pOtherActor
     * @return false
     */
    virtual bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const Actor* prm_pOtherActor) override {
    }

    virtual ~DestructActor();
};

}
#endif /*GGAF_CORE_DESTRUCTACTOR_H_*/
