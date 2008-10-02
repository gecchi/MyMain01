#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class Laser001Actor : public DefaultSpriteMyActor {

	int _X_prevFrame;

public:
	Laser001Actor(string prm_name, string prm_xname);

	static Laser001Actor* _pHeadLaser001Actor;

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

	virtual ~Laser001Actor();
};


#endif /*LASER001PACTOR_H_*/

