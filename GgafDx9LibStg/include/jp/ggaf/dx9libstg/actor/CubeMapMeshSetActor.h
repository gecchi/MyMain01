#ifndef CUBEMAPMESHSETACTOR_H_
#define CUBEMAPMESHSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public GgafDx9Core::GgafDx9CubeMapMeshSetActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometricScaler* _pScaler;

    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;

    CubeMapMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*CUBEMAPMESHSETACTOR_H_*/
