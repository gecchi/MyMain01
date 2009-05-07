#ifndef DEFAULTMORPHTWOMESHACTOR_H_
#define DEFAULTMORPHTWOMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MeshActor �������������ۃA�N�^�[�ł��B
 */
class DefaultMorphTwoMeshActor : public GgafDx9Core::GgafDx9MorphTwoMeshActor {

public:
    DWORD _frame_offset;

    StgChecker* _pChecker;

    DefaultMorphTwoMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9MorphTwoMeshActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9MorphTwoMeshActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultMorphTwoMeshActor();
};

}
#endif /*DEFAULTMORPHTWOMESHACTOR_H_*/
