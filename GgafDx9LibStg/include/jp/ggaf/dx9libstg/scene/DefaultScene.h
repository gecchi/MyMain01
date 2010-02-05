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

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
        TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processJudgement() override {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processDraw() {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processHappen(int prm_no) override {
        TRACE("DefaultScene::processHappen " << getName() << "no:" << prm_no);
    }

    virtual void processFinal() override {
        TRACE("DefaultScene::processFinally " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
