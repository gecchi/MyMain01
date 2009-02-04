#ifndef DEFAULTSQUAREACTOR_H_
#define DEFAULTSQUAREACTOR_H_
namespace GgafDx9LibStg {


class DefaultSquareActor : public GgafDx9Core::GgafDx9SquareActor {

public:
	StgChecker* _pChecker;


	DefaultSquareActor(const char* prm_name, const char* prm_model);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9Core::GgafDx9SquareActor::processDrawPrior();
	};
	virtual void processDrawMain() {
		GgafDx9Core::GgafDx9SquareActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	/**
	 * オーバーライド
	 * @param prm_pActor_Opponent
	 * @return
	 */
	virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultSquareActor();

};


}
#endif /*DEFAULTSQUAREACTOR_H_*/
