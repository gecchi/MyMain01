#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0


class MyShip : public DefaultMeshActor {

public:

	/** ターボ中かどうか */
	bool _isTurbo;

	/** 奥手前ターボ中かどうか */
	bool _isZTurbo;

	int _iVB_turbo;
	/** 移動スピードレベル */
	int _lv_MoveSpeed;
	/** 移動スピードレベルに相応する移動スピード */
	int _iMoveSpeed;

	bool _isMoveZX;


	//奥又は手前へ通常移動開始時のX軸回転角速度の初速度
	//奥の場合は正、手前の場合はこれに -1 を乗ずる
	//Rotation axisX Velocity when I Begin To Move Z
	int _iRXVelo_BMZ;
	//奥又は手前へ通常移動中のX軸回転角速度の角加速度
	//奥の場合は正、手前の場合はこれに -1 を乗ずる
	//Rotation axisX Acceleration while I Move Z
	int _iRXAcce_MZ;
	//奥又は手前へ移動中のX軸回転角速度の上限角速度
	//下限角速度はこれに -1 を乗ずる
	//Rotation axisX Top Velocity while I Move Z
	int _iRXTopVelo_MZ;
	//奥又は手前へ通常Z移動中のX軸回転角の停止角度位置
	//Rotation axisX Stop Angle while I Move Z
	angle _iRXStopAng_MZ;

	//TURBO移動開始時の移動速度の初速度
	//Move Velocity when I Begin To Move with Turbo
	int _iMVelo_BMT;
	//TURBO移動中の移動速度の加速度(<0 ∵だんだん遅くなるようにするため)
	//Move Acceleration while I Move with Turbo
	int _iMAcce_MT;
	//TURBO移動中の移動速度の最低速度
	//Move Bottom Velocity while I Move with Turbo
	int _iMBtmVelo_MT;


	//奥又は手前へTURBO移動開始時のX軸回転角速度の初速度
	//奥の場合は正、手前の場合はこれに -1 を乗ずる
	//Rotation axisX Velocity when I Begin To Move Z with Turbo
	int _iRXVelo_BMZT;
	//奥又は手前へTURBO移動中のX軸回転角速度の角加速度(<0 ∵だんだん回転力が少なくなるようにするため)
	//奥の場合は正、手前の場合はこれに -1 を乗ずる
	//Rotation axisX Acceleration while I Move Z with Turbo
	int _iRXAcce_MZT;
	//奥又は手前へTURBO移動中のX軸回転角速度の最低速度
	//奥の場合は範囲を _iRXBtmVelo_MZT < X軸回転角速度正 < 360,000
	//手前の場合は     -360,000 < X軸回転角速度正 < -1*_iRXBtmVelo_MZT
	//として、TURBO移動中最低限の回転力を保証する。
	//Rotation axisX Bottom Angle Velocity while I Move Z with Turbo
	int _iRXBtmVelo_MZT;
	//奥又は手前へTURBO移動中のTURBO移動が終了と判断されるX軸回転角速度
	//奥の場合は正、手前の場合はこれに -1 を乗ずる
	//Rotation axisX Velocity when I Finish Moveing Z with Turbo
	int _iRXVelo_FMZT;









	//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとするX軸回転角速度の上限角速度
	//下限角速度はこれに -1 を乗ずる
	//Rotation X Top Velocity while I do Not Move Z
	int _iRXTopVelo_NMZ;
	//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとする時のX軸回転角加速度(正負共通)
	//Rotation X Acceleration while I do Not Move Z
	int _iRXAcce_NMZ;


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
 	void beginTurboZX(int prm_VB);

 	//画面手前へ移動初めX軸回転処理
 	void beginTurboXY(int prm_VB);


 	void beginMoveZX(int prm_VB);

 	void beginMoveXY(int prm_VB);

 	//画面奥へ移動終了X軸回転処理
 	void onMoveZFinish();
 	virtual ~MyShip();
};


#endif /*MYSHIP_H_*/

