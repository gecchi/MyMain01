#ifndef GGAFLIB_COLLIAAPYRAMIDACTOR_H_
#define GGAFLIB_COLLIAAPYRAMIDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPyramidActor.h"

namespace GgafLib {

/**
 * 当たり判定表示用AAピラミッド(直方三角錐)クラス
 * GgafDxAAPyramidActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2016/01/18
 * @author Masatoshi Tsuge
 */
class ColliAAPyramidActor : public GgafDxCore::GgafDxAAPyramidActor {
    static ColliAAPyramidActor* _pObj;

public:
    static ColliAAPyramidActor* get();
    static void release();

public:
    ColliAAPyramidActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker* prm_pColliChecker);

    virtual ~ColliAAPyramidActor();

};

}
#endif /*GGAFLIB_COLLIAAPYRAMIDACTOR_H_*/
