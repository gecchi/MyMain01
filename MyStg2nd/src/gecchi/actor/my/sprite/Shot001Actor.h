#ifndef SHOT001PACTOR_H_
#define SHOT001PACTOR_H_


class Shot001Actor : public DefaultSpriteMyActor {

public:
	Shot001Actor(string prm_name, string prm_xname);

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
	void happen(int prm_event);


	virtual ~Shot001Actor();
};


#endif /*SHOT001PACTOR_H_*/

