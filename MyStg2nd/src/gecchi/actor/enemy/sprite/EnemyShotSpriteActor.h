#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_


class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

	DefaultSpriteEffectActor* _pEffectBegin;
	DefaultSpriteEffectActor* _pEffectFinish;
	int _iProgress; //進み具合

public:
	EnemyShotSpriteActor(string prm_name, string prm_xname);

	/**
	 * ＜OverRide です＞
	 */
	virtual void initialize();

	/**
	 * ＜OverRide です＞
	 */
	virtual void processBehavior();

 	/**
	 * ＜OverRide です＞
	 */
	virtual void processJudgement();

	/**
	 * ＜OverRide です＞
	 */
 	virtual void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ＜OverRide です＞
	 */
 	virtual void processFinal();

	virtual ~EnemyShotSpriteActor();
};


#endif /*ENEMYSHOTSPRITEACTOR_H_*/

