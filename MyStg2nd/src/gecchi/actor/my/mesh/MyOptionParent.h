#ifndef MYOPTIONPARENT
#define MYOPTIONPARENT

class MyOptionParent : public DefaultMeshActor {

public:

	/** �ΏۃA�N�^�[ */

	MyOptionParent(string prm_name, string prm_model);

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


 	virtual ~MyOptionParent();
};


#endif /*MYOPTIONPARENT*/

