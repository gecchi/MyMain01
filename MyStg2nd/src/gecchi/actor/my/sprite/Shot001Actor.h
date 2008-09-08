#ifndef SHOT001PACTOR_H_
#define SHOT001PACTOR_H_


class Shot001Actor : public DefaultSpriteActor {

public:
	Shot001Actor(string prm_name, string prm_xname);

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

	virtual ~Shot001Actor();
};


#endif /*SHOT001PACTOR_H_*/

