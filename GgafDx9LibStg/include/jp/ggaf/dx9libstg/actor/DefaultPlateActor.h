#ifndef DEFAULTPLATEACTOR_H_
#define DEFAULTPLATEACTOR_H_


class DefaultPlateActor : public GgafDx9::GgafDx9PlateActor {

public:
	DefaultPlateActor(string prm_name, string prm_model);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {};

	virtual void processDrawMain() {
		GgafDx9::GgafDx9PlateActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(Ggaf::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(Ggaf::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultPlateActor();

};


#endif /*DEFAULTPLATEACTOR_H_*/
