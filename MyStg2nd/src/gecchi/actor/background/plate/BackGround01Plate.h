#ifndef BACKGROUND01PLATE
#define BACKGROUND01PLATE


class BackGround01Plate : public GgafDx9TransformedActor {

	DefaultPlateActor** _papChipPlate;

public:
	BackGround01Plate(string prm_name);


	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		//�Ŕw�ʁ������΂�ŏ��ɕ`��
		GgafWorld::setDrawDepthLevel(MAX_DEPTH_LEVEL-1, this);
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

	/**
	 * ��OverRide �ł���
	 */
	void processDrawMain();


	virtual ~BackGround01Plate();
};


#endif /*BACKGROUND01PLATE*/

