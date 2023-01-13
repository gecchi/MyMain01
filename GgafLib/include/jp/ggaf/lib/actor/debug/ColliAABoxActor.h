#ifndef GGAF_LIB_COLLIAABACTOR_H_
#define GGAF_LIB_COLLIAABACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AABActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用キューブクラス
 * GgafDx::AABActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class ColliAABoxActor : public GgafDx::AABActor {
    static ColliAABoxActor* _pObj;

public:
    static ColliAABoxActor* get();
    static void release();

public:
    ColliAABoxActor(const char* prm_name);

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

    virtual ~ColliAABoxActor();

};

}
#endif /*GGAF_LIB_COLLIAABACTOR_H_*/
