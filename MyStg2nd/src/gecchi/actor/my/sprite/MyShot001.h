#ifndef MYSHOT001_H_
#define MYSHOT001_H_


class MyShot001 : public DefaultSpriteMyActor {

public:

	GgafDx9UntransformedActor* _pActor_Radical;


	MyShot001(string prm_name, string prm_model);

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

	/**
	 * ＜OverRide です＞
	 */
	void onStop();

	/**
	 * 親元対象アクター
	 * @param prm_pActor
	 */
	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

	virtual ~MyShot001();
};


#endif /*MYSHOT001_H_*/

