#ifndef DEFAULTSPRITESETACTOR_H_
#define DEFAULTSPRITESETACTOR_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9SpriteSetActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/07/15
 * @author Masatoshi Tsuge
 */
class DefaultSpriteSetActor : public GgafDx9Core::GgafDx9SpriteSetActor {

public:
    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
