#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafDx9LibStg {

/**
 * シーンの具象クラス
 * GgafDx9Core::GgafDx9Scene を継承し、空実装した具象シーンです。
 */
class DefaultScene : public GgafDx9Core::GgafDx9Scene {
public:

    DWORD* _paFrame_NextEvent;
    int _iCnt_Event;

    DefaultScene(const char* prm_name);

    virtual void initialize() {
    }

    virtual void processBehavior() {
        TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _lifeframe);
    }

    virtual void processJudgement() {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _lifeframe);
    }

    virtual void processPreDraw() {
        TRACE("DefaultScene::processPreDraw " << getName() << "frame:" << _lifeframe);
    }

    virtual void processDraw() {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _lifeframe);
    }

    virtual void processAfterDraw() {
        TRACE("DefaultScene::processAfterDraw " << getName() << "frame:" << _lifeframe);
    }

    virtual void processHappen(int prm_no) {
        TRACE("DefaultScene::processHappen " << getName() << "no:" << prm_no);
    }

    virtual void processFinal() {
        TRACE("DefaultScene::processFinally " << getName() << "frame:" << _lifeframe);
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
