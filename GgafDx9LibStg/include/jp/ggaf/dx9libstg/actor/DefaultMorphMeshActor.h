#ifndef DEFAULTMORPHMESHACTOR_H_
#define DEFAULTMORPHMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���[�t���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9MorphMeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class DefaultMorphMeshActor : public GgafDx9Core::GgafDx9MorphMeshActor {

public:
    DWORD _frame_offset;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;
    GgafDx9Core::GgafDx9GeometryMorpher* _pMorpher;
    CollisionChecker* _pCollisionChecker;

    DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultMorphMeshActor();
};

}
#endif /*DEFAULTMORPHMESHACTOR_H_*/
