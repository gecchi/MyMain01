#ifndef ENEMYSHOT001ACTOR_H_
#define ENEMYSHOT001ACTOR_H_


class EnemyShot001Actor : public EnemyShotSpriteActor {

public:
	EnemyShot001Actor(string prm_name, string prm_xname);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	bool isOffScreen();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual ~EnemyShot001Actor();
};


#endif /*ENEMYSHOT001ACTOR_H_*/

