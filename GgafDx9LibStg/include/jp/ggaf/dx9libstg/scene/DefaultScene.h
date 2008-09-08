#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_

class DefaultScene : public GgafDx9Scene
{
public:

	DWORD* _paFrame_NextEvent;
	int _iCnt_Event;


	DefaultScene(string prm_name);

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

	virtual void processOccur(int prm_no) {
		TRACE("DefaultScene::processOccur " << getName() << "no:" << prm_no);
	};

	virtual void processFinal() {
		TRACE("DefaultScene::processFinally " << getName() << "frame:" << _dwFrame);
	};


	virtual ~DefaultScene();
};

#endif /*DEFAULTSCENE_H_*/
