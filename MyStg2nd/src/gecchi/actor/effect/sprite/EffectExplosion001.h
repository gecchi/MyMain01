#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_


class EffectExplosion001 : public DefaultSpriteActor {

public:
	EffectExplosion001(string prm_name, string prm_model);

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
	void processJudgement();



	virtual ~EffectExplosion001();
};


#endif /*EFFECTEXPLOSION001_H_*/

