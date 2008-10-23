#ifndef BACKGROUND01PLATE
#define BACKGROUND01PLATE


class BackGround01Plate : public GgafDx9TransformedActor {

	BackGroundChipPlate** _papChipPlate;

public:
	BackGround01Plate(string prm_name);


	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		//最背面＝いちばん最初に描画
		GgafDx9World::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1, this);
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	/**
	 * ＜OverRide です＞
	 */
	void initialize();

	/**
	 * ＜OverRide です＞
	 */
	void processBehavior();

	/**
	 * ＜OverRide です＞
	 */
	void processDrawMain();


	virtual ~BackGround01Plate();
};


#endif /*BACKGROUND01PLATE*/

