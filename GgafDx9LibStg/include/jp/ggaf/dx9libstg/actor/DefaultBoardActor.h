﻿#ifndef DEFAULTBOARDACTOR_H_
#define DEFAULTBOARDACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9BoardActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/03/11
 * @author Masatoshi Tsuge
 */
class DefaultBoardActor : public GgafDx9Core::GgafDx9BoardActor {

public:
    DefaultBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardActor();

};

}
#endif /*DEFAULTBOARDACTOR_H_*/
