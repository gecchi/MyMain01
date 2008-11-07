#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

/**
 * フォーメーションアクタークラス .
 */
class FormationActor : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;

	FormationActor(string prm_name);

	void initialize() {};

	void processBehavior() {};

 	/**
 	 * サブが無ければ死
	 * ＜OverRide です＞<BR>
	 */
	void processJudgement() {
		if (getSubFirst() == NULL) {
			declareFinishLife();
		}
	};

	void processDrawPrior() {};

	void processDrawMain() {};

	void processDrawTerminate() {};

	void processHappen(int prm_no) {};

	void processFinal() {};

	void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~FormationActor();
};

#endif /*FORMATIONACTOR_H_*/
