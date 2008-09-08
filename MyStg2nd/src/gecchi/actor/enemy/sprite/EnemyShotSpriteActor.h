#ifndef ENEMYSHOTSPRITEACTOR_H_
#define ENEMYSHOTSPRITEACTOR_H_


class EnemyShotSpriteActor : public DefaultSpriteEnemyActor {

	DefaultSpriteEffectActor* _pEffectBegin;
	DefaultSpriteEffectActor* _pEffectFinish;
	int _iProgress; //êiÇ›ãÔçá

public:
	EnemyShotSpriteActor(string prm_name, string prm_xname);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void processJudgement();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	virtual void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual void begin();

	virtual void finish();

	virtual ~EnemyShotSpriteActor();
};


#endif /*ENEMYSHOTSPRITEACTOR_H_*/

