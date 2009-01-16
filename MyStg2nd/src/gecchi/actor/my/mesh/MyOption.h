#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOption : public GgafDx9LibStg::DefaultMeshActor {

public:
	int _iMyNo;

	GgafDx9LibStg::RotationActor* _pMyLaserChipRotation;

	GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing;
	/** 対象アクター */
	GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;
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
 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

