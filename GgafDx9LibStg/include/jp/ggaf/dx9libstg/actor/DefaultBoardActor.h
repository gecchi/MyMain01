#ifndef DEFAULTBOARDACTOR_H_
#define DEFAULTBOARDACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9BoardActor を空実装した具象アクターです。
 */
class DefaultBoardActor : public GgafDx9Core::GgafDx9BoardActor {

public:
    DefaultBoardActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }


    virtual void processDraw() {
        GgafDx9Core::GgafDx9BoardActor::processDraw();
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

    virtual ~DefaultBoardActor();

};

}
#endif /*DEFAULTBOARDACTOR_H_*/
