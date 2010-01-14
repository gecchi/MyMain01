#ifndef DEFAULTBOARDSETACTOR_H_
#define DEFAULTBOARDSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9BoardSetActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetActor : public GgafDx9Core::GgafDx9BoardSetActor {

public:
    DefaultBoardSetActor(const char* prm_name, const char* prm_model);

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

    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) {
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*DEFAULTBOARDSETACTOR_H_*/
