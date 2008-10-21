#ifndef BACKGROUND01PLATE
#define BACKGROUND01PLATE


class BackGround01Plate : public GgafDx9TransformedActor {

	DefaultPlateActor** _papChipPlate;

public:
	BackGround01Plate(string prm_name);


	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		//ç≈îwñ ÅÅÇ¢ÇøÇŒÇÒç≈èâÇ…ï`âÊ
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
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processDrawMain();


	virtual ~BackGround01Plate();
};


#endif /*BACKGROUND01PLATE*/

