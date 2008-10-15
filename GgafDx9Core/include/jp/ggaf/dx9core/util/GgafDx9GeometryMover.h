#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_

//近い方向に回転
#define TURN_CLOSE_TO 0
//時計回りに回転
#define TURN_CLOCKWISE (-1)
//反時計回りに回転
#define TURN_COUNTERCLOCKWISE 1



//軸X
#define AXIS_X 0
//軸Y
#define AXIS_Y 1
//軸Z
#define AXIS_Z 2


class GgafDx9GeometryMover {

public:
	/** 対象アクター */
	GgafDx9UntransformedActor* _pActor;


	/** キャラの軸回転方角の方角値(0～360,000) */
	angle _angAxisRot[3];

	/** 軸回転方角の角速度（軸回転方角値に毎フレーム加算する方角値） */
	angle _angVelocity_AxisRotAngle[3];

	/** 軸回転方角値の角速度上限(最高値は360,000) */
	angle _angTopAngVelocity_AxisRotAngle[3];

	/** 軸回転方角値の角速度下限(最高値は-360,000) */
	angle _angBottomVelocity_AxisRotAngle[3];

	/** 軸回転方角の角加速度（角速度に毎フレーム加算する値） */
	angle _angAcceleration_AxisRotAngleVelocity[3];

	/** 目標とするキャラの軸回転方角の方角値(0～360,000) */
	angle _angTarget_AxisRot[3];

	/** 目標の軸回転方角自動制御機能有効フラグ */
	bool _auto_rot_angle_target_Flg[3];


	/**
	 * コンストラクタ<BR>
	 * @param	prm_pActor	適用Actor
	 */
	GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor);

	/**
	 * 方角値を簡単にする。
	 * @param prm_ang 方角値
	 * @return 簡単にされた方角値
	 */
	angle simplifyAngle(angle prm_ang);


	/**
	 * Actorの軸の回転方角値を設定。<BR>
	 *
	 * @param	prm_iAxis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_angAxisRot	方角値(-360,000～360,000)
	 */
	void setAxisRotAngle(int prm_iAxis, angle prm_angAxisRot);

	/**
	 * Actorの軸の回転方角値をを現在XY座標からの対象XY座標で設定。<BR>
	 * 今の所Z軸指定ぐらいしか用途が思い浮かびません。<BR>
	 *
	 * @param	prm_iAxis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_tX	x XY座標
	 * @param	prm_tY	y XY座標
	 */
	void setAxisRotAngle(int prm_iAxis, int prm_tX, int prm_tY);


	/**
	 * 現在の Actor の軸の回転方角値へ加算（負で減算）。<BR>
	 *
	 * 引数に渡すのは、軸と回転方角値増分です。Actorの回転方角値（_angAxisRot）を相対指定でるメソッドです。<BR>
	 * 加算後の回転方角値が範囲外（0～360,000）の値になっても、最終的には setAxisRotAngle(int) を呼び出しますので<BR>
	 * 正しい 0～360,000 の範囲内の値に設定されます。<BR>
	 * 引数である加算（減算）する回転方角値は、回転加速度の上限と下限の間の範囲に限ります。<BR>
	 * つまり、引数の有効な範囲は以下の通りとなります。<BR>
	 *
	 *   _iBottom_AxisRotVelocityAngle ≦ 引数の回転角値増分 ≦ _angTopAngVelocity_AxisRotAngle  です。<BR>
	 *
	 * もし範囲外の引数の回転方角値増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
	 * また、自動前方向き機能が有効(synchronize_ZaxisAxisRotAngle_to_AxisRotAngle_Flg)の場合、<BR>
	 * 加算後の回転方角値の値が、Z軸の目標の回転方角値として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
	 *
	 * 【補足：】<BR>
	 * 引数の回転方角値が、数直線上の 0 に、より近い値を加算し続けた場合は、ゆっくりな軸回転することを意味します。<BR>
	 * 逆に、引数の回転方角値が、0 から、より離れた値を加算し続けた場合は、速く軸回転することを意味します。<BR>
	 * デフォルトの回転加速度の上限と下限（_iBottom_AxisRotVelocityAngle、_angTopAngVelocity_AxisRotAngle) は<BR>
	 *
	 *  -360,000 ≦ 引数の動方角値増分 ≦ 360,000<BR>
	 *
	 * となっています。これは瞬時に（1フレームで）指定軸についてどんな回転方角にも向きを変えれることを意味します。<BR>
	 *
	 * @param	prm_iAxis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_iDistance_AxisRotAngle	回転方角値増分(範囲：_iBottom_AxisRotVelocityAngle ～ _angTopAngVelocity_AxisRotAngle)
	 */
	void addAxisRotAngle(int prm_iAxis, angle prm_iDistance_AxisRotAngle);

	/**
	 * Actorの目標の軸回転方角自動制御機能を有効(目標の軸回転方角値設定)<BR>
	 * 引数に設定された軸の回転方角値になるまで、回転方角値を加算(減算)を毎フレーム行い続けます。<BR>
	 * 加算か減算かは、現在の回転方角の角速度（_angVelocity_AxisRotAngle[prm_iAxis]）の正負で決定されます。<BR>
	 * 回転方角の角速度が 0 ならば、何も起こりません。<BR>
	 * 内部的には、addAxisRotAngle(prm_iAxis, int) が毎フレーム行われる仕組みです。<BR>
	 * 目標の回転方角に到達したならば、この目標の軸回転方角自動制御機能は解除されます。<BR>
	 * @param	prm_iAxis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_angXYMove	到達目標の回転方角値(0～360,000)
	 */
	 void setTargetAxisRotAngle(int prm_iAxis, angle prm_angXYMove);

	/**
	 * Actorの目標回転方向自動制御機能を有効(現在XY座標からの対象XY座標で設定)<BR>
	 * @param	prm_iAxis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_tX	対象X座標
	 * @param	prm_tY	対象Y座標
	 */
	void setTargetAxisRotAngle(int prm_iAxis, int prm_tX, int prm_tY);

	void setAxisRotAngleVelocity(int prm_iAxis, angle prm_angVelocity_AxisRotAngle);

	void setAxisRotAngleVelocityRenge(int prm_iAxis, angle prm_angVelocity01_AxisRotAngle, angle prm_angVelocity02_AxisRotAngle);

	void setAxisRotAngleAcceleration(int prm_iAxis, angle prm_angAcceleration_AxisRotAngleVelocity);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iWay);

/**
	 * 毎フレームのActorの振る舞い。<BR>
	 */
	virtual void behave();


	virtual ~GgafDx9GeometryMover();
};


#endif /*GGAFDX9GEOMETRYMOVER_H_*/

