#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0


class MyShip : public DefaultMeshActor {

public:

	bool _turboFlg;

	/** 移動スピードレベル */
	int _lv_MoveSpeed;
	/** 移動スピードレベルに相応する移動スピード */
	int _iMoveSpeed;

	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;

	MyShip(string prm_name, string prm_xname);

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


 	void setMoveSpeedLv(int lv) {
 		_lv_MoveSpeed = lv;
 		_iMoveSpeed = _lv_MoveSpeed*1000;
 	}
 	//画面奥へ移動初めX軸回転処理
 	void onMoveZPlusBegin();

 	//画面手前へ移動初めX軸回転処理
 	void onMoveZMinusBegin();

 	//画面奥へ移動終了X軸回転処理
 	void onMoveZFinish();
 	virtual ~MyShip();
};


#endif /*MYSHIP_H_*/

