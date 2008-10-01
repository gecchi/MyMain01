#ifndef MYSHIPACTOR_H_
#define MYSHIPACTOR_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

class State {
public:
	int n;
	string s;
	State** e;
	State() {};
	virtual ~State() {};
};

class MyShipActor : public DefaultMeshActor {

public:
	RotationActor* _pMyShots001Rotation;
	RotationActor* _pMyLaser001Rotation;

	bool _turboFlg;

	State* STATE;





	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;

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

