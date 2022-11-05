#ifndef GGAF_LIB_COLLISPHEREACTOR_H_
#define GGAF_LIB_COLLISPHEREACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/SphereActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用球クラス
 * DefaultSphereActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class ColliSphereActor : public GgafDx::SphereActor {
    static ColliSphereActor* _pObj;

public:
    static ColliSphereActor* get();
    static void release();

public:
    ColliSphereActor(const char* prm_name);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }


    void drawHitarea(GgafDx::CollisionChecker* prm_pChecker);

    virtual ~ColliSphereActor();

};

}
#endif /*GGAF_LIB_COLLISPHEREACTOR_H_*/
