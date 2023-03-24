#ifndef GGAF_LIB_COLLIAABOARDRECTACTOR_H_
#define GGAF_LIB_COLLIAABOARDRECTACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AABoardRectActor.h"

namespace GgafLib {

/**
 * Board四角当たり判定表示用クラス
 * GgafDx::AABoardRectActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2022/10/11
 * @author Masatoshi Tsuge
 */
class ColliAABoardRectActor : public GgafDx::AABoardRectActor {
    static ColliAABoardRectActor* _pObj;

public:
    static ColliAABoardRectActor* get();
    static void release();

public:
    ColliAABoardRectActor(const char* prm_name);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pChecker);

    virtual ~ColliAABoardRectActor();

};

}
#endif /*GGAF_LIB_COLLIAABOARDRECTACTOR_H_*/
