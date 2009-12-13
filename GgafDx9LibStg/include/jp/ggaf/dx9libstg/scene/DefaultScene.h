#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafDx9LibStg {

/**
 * �V�[���̋�ۃN���X .
 * GgafDx9Core::GgafDx9Scene ���p�����A�����������ۃV�[���ł��B
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDx9Core::GgafDx9Scene {
public:

    /** �V�[���C�x���g�p�̃t���[���l�̔z�� */
    DWORD* _paFrame_NextEvent;
    /** �V�[���̃C�x���g���i_paFrame_NextEvent�̗v�f���j */
    int _iCnt_Event;

    DefaultScene(const char* prm_name);

    virtual void initialize() {
    }

    virtual void processBehavior() {
        TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _frame_of_life);
    }

    virtual void processJudgement() {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_life);
    }

    virtual void processDraw() {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_life);
    }

    virtual void processHappen(int prm_no) {
        TRACE("DefaultScene::processHappen " << getName() << "no:" << prm_no);
    }

    virtual void processFinal() {
        TRACE("DefaultScene::processFinally " << getName() << "frame:" << _frame_of_life);
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
