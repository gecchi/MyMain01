#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOption : public DefaultMeshActor {

public:

	MyOption(string prm_name, string prm_xname);

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

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

