#ifndef DEFAULTSPRITESETACTOR_H_
#define DEFAULTSPRITESETACTOR_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9SpriteSetActor �������������ۃA�N�^�[�ł��B
 */
class DefaultSpriteSetActor : public GgafDx9Core::GgafDx9SpriteSetActor {

public:
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** ���W�ړ��x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9SpriteSetActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9SpriteSetActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
