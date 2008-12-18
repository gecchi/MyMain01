#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOptionParent : public DefaultMeshActor {

public:

	/** 対象アクター */

	MyOptionParent(string prm_name, string prm_model);

	/**
	 * ＜OverRide です＞
	 */
	void initialize();

	/**
	 * ＜OverRide です＞
	 */
	void processBehavior();

 	/**
	 * ＜OverRide です＞
	 */
	void processJudgement();

	/**
	 * ＜OverRide です＞
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);


 	virtual ~MyOptionParent();
};


#endif /*MYOPTION_H_*/

