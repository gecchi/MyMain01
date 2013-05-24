#ifndef COLLIAAPRISMACTOR_H_
#define COLLIAAPRISMACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPrismActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用AAプリズム(直方三角柱)クラス
 * GgafDxAAPrismActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDxCore::GgafDxAAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

public:
    ColliAAPrismActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

    //void processDraw() {} //オーバーライド未実装にする。
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

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker3D* prm_pChecker);

    virtual ~ColliAAPrismActor();

};

}
#endif /*COLLIAAPRISMACTOR_H_*/
