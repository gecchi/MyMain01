#ifndef DEFAULTPRIMITIVEACTOR_H_
#define DEFAULTPRIMITIVEACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class DefaultMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    DWORD _dwFrameOffset;

    StgChecker* _pChecker;

    DefaultMeshActor(const char* prm_name, const char* prm_model, const char* prm_technique);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9MeshActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultMeshActor();
};

}
#endif /*DEFAULTPRIMITIVEACTOR_H_*/
