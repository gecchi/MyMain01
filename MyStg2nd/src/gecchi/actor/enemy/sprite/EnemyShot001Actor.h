#ifndef ENEMYSHOT001ACTOR_H_
#define ENEMYSHOT001ACTOR_H_


class EnemyMyShot001 : public EnemyShotSpriteActor {

public:
	EnemyMyShot001(string prm_name, string prm_xname);

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

	virtual ~EnemyMyShot001();
};


#endif /*ENEMYSHOT001ACTOR_H_*/

