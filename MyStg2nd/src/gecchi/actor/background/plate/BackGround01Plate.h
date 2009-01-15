#ifndef BACKGROUND01PLATE
#define BACKGROUND01PLATE


class BackGround01Plate : public GgafDx9::GgafDx9TransformedActor {

	BackGroundChipPlate** _papChipPlate;

public:
	BackGround01Plate(string prm_name, string prm_dummy);


	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		//�Ŕw�ʁ������΂�ŏ��ɕ`��
		GgafDx9::GgafDx9World::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1, this);
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(Ggaf::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(Ggaf::GgafActor* prm_pActor_Opponent) {};

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

