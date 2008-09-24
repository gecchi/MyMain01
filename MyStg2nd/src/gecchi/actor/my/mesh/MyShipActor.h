#ifndef MYSHIPACTOR_H_
#define MYSHIPACTOR_H_

#define SH_NOMAL 0;
#define SH_LASER 1;


class MyShipActor : public DefaultMeshActor {

public:
	RotationActor* _pMyShots001Rotation;
	RotationActor* _pMyLaser001Rotation;

	bool _turboFlg;

	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;

	MyShipActor(string prm_name, string prm_xname);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processJudgement();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);


	virtual ~MyShipActor();
};


#endif /*MYSHIPACTOR_H_*/

