#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_


class EffectExplosion001 : public DefaultSpriteActor {

public:
	EffectExplosion001(string prm_name, string prm_xname);

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
	void processJudgement();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void happen(int prm_event);


	virtual ~EffectExplosion001();
};


#endif /*EFFECTEXPLOSION001_H_*/

