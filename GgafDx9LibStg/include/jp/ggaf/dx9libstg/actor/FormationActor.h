#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationActor : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;

	FormationActor(string prm_name);

	void initialize() {};

	void processBehavior() {};

 	/**
 	 * �T�u��������Ύ�
	 * ��OverRide �ł���<BR>
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
