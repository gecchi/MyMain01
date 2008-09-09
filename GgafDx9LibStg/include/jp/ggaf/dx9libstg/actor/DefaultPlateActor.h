#ifndef DEFAULTPLATEACTOR_H_
#define DEFAULTPLATEACTOR_H_


class DefaultPlateActor : public GgafDx9PlateActor {

public:
	DefaultPlateActor(string prm_name, string prm_xname);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {};

	virtual void processDrawMain() {
		GgafDx9PlateActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultPlateActor();

};


#endif /*DEFAULTPLATEACTOR_H_*/
