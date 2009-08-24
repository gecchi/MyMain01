#ifndef DEFAULTBOARDSETACTOR_H_
#define DEFAULTBOARDSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9BoardSetActor を空実装した具象アクターです。
 */
class DefaultBoardSetActor : public GgafDx9Core::GgafDx9BoardSetActor {

public:
    DefaultBoardSetActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }


    virtual void processDraw() {
        GgafDx9Core::GgafDx9BoardSetActor::processDraw();
    }


    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*DEFAULTBOARDSETACTOR_H_*/
