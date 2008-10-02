#ifndef ENEMYSHOT001ACTOR_H_
#define ENEMYSHOT001ACTOR_H_


class EnemyMyShot001 : public EnemyShotSpriteActor {

public:
	EnemyMyShot001(string prm_name, string prm_xname);

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

	virtual ~EnemyMyShot001();
};


#endif /*ENEMYSHOT001ACTOR_H_*/

