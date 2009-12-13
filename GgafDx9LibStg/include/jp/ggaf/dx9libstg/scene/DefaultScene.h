#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafDx9LibStg {

/**
 * シーンの具象クラス .
 * GgafDx9Core::GgafDx9Scene を継承し、空実装した具象シーンです。
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDx9Core::GgafDx9Scene {
public:

    /** シーンイベント用のフレーム値の配列 */
    DWORD* _paFrame_NextEvent;
    /** シーンのイベント数（_paFrame_NextEventの要素数） */
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
