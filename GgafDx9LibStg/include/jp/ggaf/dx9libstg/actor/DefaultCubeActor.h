#ifndef DEFAULTCUBEACTOR_H_
#define DEFAULTCUBEACTOR_H_


class DefaultCubeActor : public GgafDx9CubeActor {

public:
	StgChecker* _pChecker;


	DefaultCubeActor(string prm_name);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9CubeActor::processDrawPrior();
	};

	virtual void processDrawMain() {
		GgafDx9CubeActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	/**
	 * オーバーライド
	 * @param prm_pActor_Opponent
	 * @return
	 */
	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultCubeActor();

};


#endif /*DEFAULTCUBEACTOR_H_*/
