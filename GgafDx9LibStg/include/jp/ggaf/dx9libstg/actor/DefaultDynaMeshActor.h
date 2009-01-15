#ifndef DEFAULTDYNAMESHACTOR_H_
#define DEFAULTDYNAMESHACTOR_H_


class DefaultDynaMeshActor : public GgafDx9::GgafDx9DynaMeshActor {

public:
	DWORD _dwFrameOffset;

	StgChecker* _pChecker;

	DefaultDynaMeshActor(string prm_name, string prm_model);


	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9::GgafDx9DynaMeshActor::processDrawPrior();
	};

	virtual void processDrawMain() {
		GgafDx9::GgafDx9DynaMeshActor::processDrawMain();
	};

	virtual void processDrawTerminate();

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(Ggaf::GgafActor* prm_pActor_Opponent) {};

	virtual bool isOffScreen();

	virtual ~DefaultDynaMeshActor();
};


#endif /*DEFAULTDYNAMESHACTOR_H_*/
