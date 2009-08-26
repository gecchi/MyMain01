#ifndef DEFAULTSPRITEACTOR_H_
#define DEFAULTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9SpriteActor �������������ۃA�N�^�[�ł��B
 */
class DefaultSpriteActor : public GgafDx9Core::GgafDx9SpriteActor {

public:
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteActor(const char* prm_name, const char* prm_model_id);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual void drawHitArea();

    virtual ~DefaultSpriteActor();

};

}
#endif /*DEFAULTSPRITEACTOR_H_*/
