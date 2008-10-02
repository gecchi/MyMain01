#ifndef EXPLOSION001PACTOR_H_
#define EXPLOSION001PACTOR_H_


class Explosion001Actor : public DefaultSpriteActor {

public:
	Explosion001Actor(string prm_name, string prm_xname);

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
 	void playBegin();

	virtual ~Explosion001Actor();
};


#endif /*EXPLOSION001PACTOR_H_*/

