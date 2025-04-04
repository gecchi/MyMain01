#ifndef GGAF_LIB_COLLIAAPRISMACTOR_H_
#define GGAF_LIB_COLLIAAPRISMACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AAPrismActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用AAプリズム(直方三角柱)クラス
 * GgafDx::AAPrismActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDx::AAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

public:
    ColliAAPrismActor(const char* prm_name);

    //void processDraw() {} //オーバーライド未実装にする。
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

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker);

    virtual ~ColliAAPrismActor();

};

}
#endif /*GGAF_LIB_COLLIAAPRISMACTOR_H_*/
