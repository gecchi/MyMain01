#ifndef MYSHOT001_H_
#define MYSHOT001_H_


class MyShot001 : public DefaultSpriteMyActor {

public:
	MyShot001(string prm_name, string prm_xname);

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
	void onStop();

	virtual ~MyShot001();
};


#endif /*MYSHOT001_H_*/

