#ifndef GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_
#define GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/FramedBoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx::FramedBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * @version 1.00
 * @since 2017/08/22
 * @author Masatoshi Tsuge
 */
class DefaultFramedBoardActor : public GgafDx::FramedBoardActor {

public:
    DefaultFramedBoardActor(const char* prm_name, const char* prm_model);

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

    virtual ~DefaultFramedBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_*/
