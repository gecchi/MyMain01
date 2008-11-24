#ifndef RANGENMYLASER_H_
#define RANGENMYLASER_H_

/**
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RangeMyLaser : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;


 	RangeMyLaser(string prm_name);

	void initialize() {};

	void processBehavior() {};

	void processJudgement() {};

	void processDrawPrior() {};

	void processDrawMain() {};

	void processDrawTerminate() {};

	void processHappen(int prm_no) {};

	void processFinal() {};

 	void processOnHit(GgafActor* prm_pChip_Opponent) {};


 	MyLaserChip* obtain();

 	void release(MyLaserChip* prm_pChipSub) ;


 	virtual ~RangeMyLaser() {
 	};
};


#endif /*RANGENMYLASER_H_*/
