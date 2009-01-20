#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafDx9LibStg {

/**
 * シーンの具象クラス
 * GgafDx9Core::GgafDx9Scene を継承し、空実装した具象シーンです。
 */
class DefaultScene : public GgafDx9Core::GgafDx9Scene
{
public:

	DWORD* _paFrame_NextEvent;
	int _iCnt_Event;


	DefaultScene(std::string prm_name);

	virtual void initialize() {
	};

	virtual void processBehavior() {
		TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _dwFrame);
	};

	virtual void processJudgement() {
		TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _dwFrame);
	};

	virtual void processDrawPrior() {
		TRACE("DefaultScene::processDrawPrior " << getName() << "frame:" << _dwFrame);
	};

	virtual void processDrawMain() {
		TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _dwFrame);
	};

	virtual void processDrawTerminate() {
		TRACE("DefaultScene::processDrawTerminate " << getName() << "frame:" << _dwFrame);
	};

	virtual void processHappen(int prm_no) {
		TRACE("DefaultScene::processHappen " << getName() << "no:" << prm_no);
	};

	virtual void processFinal() {
		TRACE("DefaultScene::processFinally " << getName() << "frame:" << _dwFrame);
	};


	virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
