#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;


class MyShip : public DefaultMeshActor {

public:

	bool _turboFlg;


	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;

	MyShip(string prm_name, string prm_xname);

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


	virtual ~MyShip();
};


#endif /*MYSHIP_H_*/

