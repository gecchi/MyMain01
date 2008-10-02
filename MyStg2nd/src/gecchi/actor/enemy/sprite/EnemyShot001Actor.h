#ifndef ENEMYSHOT001ACTOR_H_
#define ENEMYSHOT001ACTOR_H_


class EnemyShot001Actor : public EnemyShotSpriteActor {

public:
	EnemyShot001Actor(string prm_name, string prm_xname);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	bool isOffScreen();

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual ~EnemyShot001Actor();
};


#endif /*ENEMYSHOT001ACTOR_H_*/

