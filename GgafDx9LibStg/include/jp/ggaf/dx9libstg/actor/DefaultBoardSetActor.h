#ifndef DEFAULTBOARDSETACTOR_H_
#define DEFAULTBOARDSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9BoardSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetActor : public GgafDx9Core::GgafDx9BoardSetActor {

public:
    DefaultBoardSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*DEFAULTBOARDSETACTOR_H_*/
