#ifndef MYWAVE001_H_
#define MYWAVE001_H_


class MyWave001 : public DefaultMeshActor {

public:
	MyWave001(string prm_name, string prm_model);

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

	virtual ~MyWave001();
};


#endif /*MYWAVE001_H_*/

