#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_


class Laser001Actor : public DefaultSpriteActor {

	int _X_prevFrame;

public:
	Laser001Actor(string prm_name, string prm_xname);

	static Laser001Actor* _pHeadLaser001Actor;

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

