#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOption : public DefaultMeshActor {

public:
	int _iMyNo;

	RotationActor* _pMyLaserChipRotation;

	GgafLinkedListRing<GeoElement>* _pRing;
	/** 対象アクター */
	GgafDx9UntransformedActor* _pActor_Radical;
	/** 対象アクター前フレームからの増分 */
	int _incX_Radical, _incY_Radical, _incZ_Radical;

	MyOption(string prm_name, string prm_model);

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
	void processJudgement();

	/**
	 * ＜OverRide です＞
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

