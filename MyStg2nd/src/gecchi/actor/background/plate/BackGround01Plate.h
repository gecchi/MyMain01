#ifndef BACKGROUND01PLATE_H_
#define BACKGROUND01PLATE_H_
namespace MyStg2nd {


class BackGround01Plate : public GgafDx9Core::GgafDx9TransformedActor {

	BackGroundChipPlate** _papChipPlate;

public:
	BackGround01Plate(char* prm_name, char* prm_dummy);


	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		//最背面＝いちばん最初に描画
		GgafDx9Core::GgafDx9World::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1, this);
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

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


}
#endif /*BACKGROUND01PLATE_H_*/

