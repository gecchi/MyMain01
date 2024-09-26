#ifndef GGAF_LIB_COLLIAAPYRAMIDACTOR_H_
#define GGAF_LIB_COLLIAAPYRAMIDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AAPyramidActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用AAピラミッド(直方三角錐)クラス
 * GgafDx::AAPyramidActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2016/01/18
 * @author Masatoshi Tsuge
 */
class ColliAAPyramidActor : public GgafDx::AAPyramidActor {
    static ColliAAPyramidActor* _pObj;

public:
    static ColliAAPyramidActor* get();
    static void release();

public:
    ColliAAPyramidActor(const char* prm_name);

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

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pChecker);

    virtual ~ColliAAPyramidActor();

};

}
#endif /*GGAF_LIB_COLLIAAPYRAMIDACTOR_H_*/
