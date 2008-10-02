#ifndef EXPLOSION001PACTOR_H_
#define EXPLOSION001PACTOR_H_


class Explosion001Actor : public DefaultSpriteActor {

public:
	Explosion001Actor(string prm_name, string prm_xname);

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
 	void playBegin();

	virtual ~Explosion001Actor();
};


#endif /*EXPLOSION001PACTOR_H_*/

