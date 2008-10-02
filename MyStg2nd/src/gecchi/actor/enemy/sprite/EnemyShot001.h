#ifndef ENEMYSHOT001_H_
#define ENEMYSHOT001_H_


class EnemyShot001 : public EnemyShotSpriteActor {

public:
	EnemyShot001(string prm_name, string prm_xname);

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

	virtual ~EnemyShot001();
};


#endif /*ENEMYSHOT001_H_*/

