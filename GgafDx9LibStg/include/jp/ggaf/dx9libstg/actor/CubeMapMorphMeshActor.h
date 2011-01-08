#ifndef CUBEMAPMORPHMESHACTOR_H_
#define CUBEMAPMORPHMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���[�t���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MorphMeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshActor : public GgafDx9Core::GgafDx9CubeMapMorphMeshActor {

public:
    frame _frame_offset;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometricScaler* _pScaler;
    /** ���[�t�B���O�x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9Morpher* _pMorpher;
    /** �`�F�b�J�[ */
    CollisionChecker* _pCollisionChecker;

    CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id);

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

    virtual ~CubeMapMorphMeshActor();
};

}
#endif /*CUBEMAPMORPHMESHACTOR_H_*/