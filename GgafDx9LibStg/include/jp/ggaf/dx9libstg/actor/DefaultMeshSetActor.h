#ifndef DEFAULTMESHSETACTORH_
#define DEFAULTMESHSETACTORH_
namespace GgafDx9LibStg {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MeshActor �������������ۃA�N�^�[�ł��B
 */
class DefaultMeshSetActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:
    /** ���W�ړ��x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    DWORD _frame_offset;

    StgChecker* _pStgChecker;

    DefaultMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processPreDraw() {
        GgafDx9Core::GgafDx9MeshSetActor::processPreDraw();
    }

    virtual void processDraw() {
        GgafDx9Core::GgafDx9MeshSetActor::processDraw();
    }

    virtual void processAfterDraw();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultMeshSetActor();
};

}
#endif /*DEFAULTMESHSETACTORH_*/
