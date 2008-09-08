#ifndef MYSHIPACTOR_H_
#define MYSHIPACTOR_H_


class MyShipActor : public DefaultMeshActor {

public:
	GgafDummyActor* _pShotParent;

	bool _turboFlg;

	MyShipActor(string prm_name, string prm_xname);

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


	virtual ~MyShipActor();
};


#endif /*MYSHIPACTOR_H_*/

