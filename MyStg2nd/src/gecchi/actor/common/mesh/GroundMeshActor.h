#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
namespace MyStg2nd {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MeshActor �������������ۃA�N�^�[�ł��B
 */
class GroundMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    DWORD _frame_offset;

    GgafDx9LibStg::StgChecker* _pStgChecker;

    GroundMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

//    /**
//     * �t���[�����[�N�I�[�o�[���C�h
//     */
//    virtual void processPreDraw();
    virtual void processDraw();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) {
    }

    virtual void drawHitArea();


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
