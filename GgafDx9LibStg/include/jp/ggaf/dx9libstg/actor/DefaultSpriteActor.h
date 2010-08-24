#ifndef DEFAULTSPRITEACTOR_H_
#define DEFAULTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9SpriteActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2008/02/25
 * @author Masatoshi Tsuge
 */
class DefaultSpriteActor : public GgafDx9Core::GgafDx9SpriteActor {

public:
    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteActor(const char* prm_name, const char* prm_model_id);

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

    virtual ~DefaultSpriteActor();

};

}
#endif /*DEFAULTSPRITEACTOR_H_*/
