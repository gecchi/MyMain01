#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_


class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

	DefaultSpriteEffectActor* _pEffectBegin;
	DefaultSpriteEffectActor* _pEffectFinish;
	int _iProgress; //�i�݋

public:
	EnemyShotSpriteActor(string prm_name, string prm_xname);

	/**
	 * ��OverRide �ł���
	 */
	virtual void initialize();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	virtual void processJudgement();

	/**
	 * ��OverRide �ł���
	 */
 	virtual void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual void begin();

	virtual void finish();

	virtual ~EnemyShotSpriteActor();
};


#endif /*ENEMYSHOTSPRITEACTOR_H_*/

