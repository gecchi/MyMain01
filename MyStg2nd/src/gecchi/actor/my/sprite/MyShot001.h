#ifndef MYSHOT001_H_
#define MYSHOT001_H_


class MyShot001 : public DefaultSpriteMyActor {

public:
	MyShot001(string prm_name, string prm_xname);

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
	void processFinal();

	virtual ~MyShot001();
};


#endif /*MYSHOT001_H_*/

