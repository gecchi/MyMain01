#ifndef ENEMYSHOT001ACTOR_H_
#define ENEMYSHOT001ACTOR_H_


class EnemyShot001Actor : public EnemyShotSpriteActor {

public:
	EnemyShot001Actor(string prm_name, string prm_xname);

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
	bool isOffScreen();

	/**
	 * ＜OverRide です＞
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ＜OverRide です＞
	 */
 	void begin();

	virtual ~EnemyShot001Actor();
};


#endif /*ENEMYSHOT001ACTOR_H_*/

