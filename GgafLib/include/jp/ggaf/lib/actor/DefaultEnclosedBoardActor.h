#ifndef GGAFLIB_DEFAULTENCLOSEDBOARDACTOR_H_
#define GGAFLIB_DEFAULTENCLOSEDBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxEnclosedBoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDxCore::GgafDxEnclosedBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * @version 1.00
 * @since 2017/08/22
 * @author Masatoshi Tsuge
 */
class DefaultEnclosedBoardActor : public GgafDxCore::GgafDxEnclosedBoardActor {

public:
    DefaultEnclosedBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual ~DefaultEnclosedBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTENCLOSEDBOARDACTOR_H_*/
