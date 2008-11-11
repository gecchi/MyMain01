#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_


class EffectExplosion001 : public DefaultSpriteActor {

public:
	EffectExplosion001(string prm_name, string prm_model);

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



	virtual ~EffectExplosion001();
};


#endif /*EFFECTEXPLOSION001_H_*/

