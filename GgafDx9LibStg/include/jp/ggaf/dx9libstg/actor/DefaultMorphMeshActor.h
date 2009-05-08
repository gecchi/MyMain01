#ifndef DEFAULTMORPHMESHACTOR_H_
#define DEFAULTMORPHMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class DefaultMorphMeshActor : public GgafDx9Core::GgafDx9MorphMeshActor {

public:
    DWORD _frame_offset;

    StgChecker* _pChecker;

    DefaultMorphMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9MorphMeshActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9MorphMeshActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultMorphMeshActor();
};

}
#endif /*DEFAULTMORPHMESHACTOR_H_*/
