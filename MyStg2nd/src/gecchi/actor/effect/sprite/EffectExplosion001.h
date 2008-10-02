#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_


class EffectExplosion001 : public DefaultSpriteActor {

public:
	EffectExplosion001(string prm_name, string prm_xname);

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

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	/**
	 * ��OverRide �ł���
	 */
	void happen(int prm_event);


	virtual ~EffectExplosion001();
};


#endif /*EFFECTEXPLOSION001_H_*/

