#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class Laser001Actor : public DefaultSpriteActor {

public:
	Laser001Actor(string prm_name, string prm_xname);

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


	void shotBegin();

	void shotFinish();

	virtual ~Laser001Actor();
};


#endif /*LASER001PACTOR_H_*/

