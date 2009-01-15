#ifndef DEFAULTSQUAREACTOR_H_
#define DEFAULTSQUAREACTOR_H_


class DefaultSquareActor : public GgafDx9::GgafDx9SquareActor {

public:
	StgChecker* _pChecker;


	DefaultSquareActor(string prm_name, string prm_model);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9::GgafDx9SquareActor::processDrawPrior();
	};
	virtual void processDrawMain() {
		GgafDx9::GgafDx9SquareActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	/**
	 * オーバーライド
	 * @param prm_pActor_Opponent
	 * @return
	 */
	virtual bool processBumpChkLogic(Ggaf::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(Ggaf::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultSquareActor();

};


#endif /*DEFAULTSQUAREACTOR_H_*/
