#ifndef DEFAULTPRIMITIVEACTOR_H_
#define DEFAULTPRIMITIVEACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9PrimitiveActor を空実装した具象アクターです。
 */
class DefaultPrimitiveActor : public GgafDx9Core::GgafDx9PrimitiveActor {

public:
    DWORD _dwFrameOffset;

    StgChecker* _pChecker;

    DefaultPrimitiveActor(const char* prm_name, const char* prm_model, const char* prm_effect);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9PrimitiveActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9PrimitiveActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultPrimitiveActor();
};

}
#endif /*DEFAULTPRIMITIVEACTOR_H_*/
