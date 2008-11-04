#ifndef STGMOVER_H_
#define STGMOVER_H_


class StgMover : public GgafDx9GeometryMover {

public:
	/** キャラの移動方角単位ベクトル */
	double _vX, _vY, _vZ;
	/** 移動方角のZ軸回転 */
	angle _angRz_Move;
	/** 移動方角のY軸回転 */
	angle _angRy_Move;

	/** Rz平面移動方角の角速度（Rz平面移動方角値に毎フレーム加算する方角値） */
	angle _angVelocity_MoveAngleRz;

	/** Rz平面移動方角値の角速度上限(最高値は360,000) */
	angle _angTopAngVelocity_MoveAngleRz;

	/** Rz平面移動方角値の角速度下限(最高値は-360,000) */
	angle _angBottomVelocity_MoveAngleRz;

	/** Rz平面移動方角の角加速度（角速度に毎フレーム加算する値） */
	angle _angAcceleration_MoveAngleRzVelocity;

	/** 目標のRz平面移動方角自動停止機能有効フラグ */
	bool _auto_move_angle_rz_target_Flg;
	/** 目標とするキャラのRz平面移動方角の方角値(0～360,000) */
	int _angRzTarget_Move;
	/** 目標のRz平面移動方角自動停止機能が有効になる回転方向 */
	int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** 目標のRz平面移動方角自動停止機能が有効になる移動方角角速度 */
	int _auto_move_angle_rz_target_allow_velocity;

///////////////////////////

	/** 移動速度 */
	int _iVelocity_Move;

	/** 移動速度上限 */
	int _iTopAngVelocity_Move;

	/** 移動速度下限 */
	int _iBottomVelocity_Move;

	/** 移動加速度 */
	int _iAcceleration_MoveVelocity;


	/** Z軸移動速度 */
	int _iVelocity_ZMove;

	/** Z軸移動速度上限 */
	int _iTopAngVelocity_ZMove;

	/** Z軸移動速度下限 */
	int _iBottomVelocity_ZMove;

	/** Z軸移動加速度 */
	int _iAcceleration_ZMoveVelocity;
//

	/** 自動前方向き機能有効フラグ */
	bool _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg;
	//true  : Rz平面移動方角を変更すると、それに伴い同じ方角値がZ軸軸回転方角にも設定される
	//false : Rz平面移動方角とZ軸軸回転方角は独立




	/**
	 * コンストラクタ<BR>
	 * @param	prm_pActor	適用Actor
	 */
	StgMover(GgafDx9UntransformedActor* prm_pActor);

	/**
	 * ActorのRz平面移動方角値を設定。<BR>
	 * 加算後のRz平面移動方角値が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
	 * 自動前方向き機能が有効(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)の場合、<BR>
	 * Actorの向きもRz平面移動方角と同じ方向を向くように setTargetAxisRotAngle(int) も実行されます。<BR>
	 *
	 * @param	prm_angXYMove	Rz平面移動方角値(0～360,000)
	 */
	void setMoveAngleRz(angle prm_angle);



	/**
	 * ActorのRz平面移動方角値を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
	 * 自動前方向き機能が有効(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)の場合、<BR>
	 * ActorのZ軸方角値（向き）もRz平面移動方角と同じ方向を向くように setTargetAxisRotAngle(int) が実行されます。<BR>
	 *
	 * @param	prm_tX	対象xXY座標
	 * @param	prm_tY	対象yXY座標
	 */
	void setMoveAngleRz(int prm_tX, int prm_tY);

	/**
	 * 現在の Actor のRz平面移動方角値へ加算（負で減算）。<BR>
	 *
	 * 引数に渡すのは、Rz平面移動方角値の増分です。ActorのRz平面移動方角値（_angXYMove）を相対指定でるメソッドです。<BR>
	 * 加算後のRz平面移動方角値が範囲外（0～360,000 以外）の値になっても、最終的には setMoveAngleRz(int) を呼び出しますので<BR>
	 * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
	 * 引数である加算（減算）するRz平面移動方角値は、Rz平面移動加速度の上限と下限の間の範囲に限ります。<BR>
	 * つまり、引数の有効な範囲は以下の通りとなります。<BR>
	 *
	 *   _angBottomVelocity_MoveAngleRz ≦ 引数の動方角値増分 ≦ _angTopAngVelocity_MoveAngleRz  です。<BR>
	 *
	 * もし範囲外の引数のRz平面移動方角値増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
	 * また、自動前方向き機能が有効(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)の場合、<BR>
	 * 加算後のRz平面移動方角値の値が、Z軸の目標の軸回転方角値として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
	 *
	 * 【補足：】<BR>
	 * 引数のRz平面移動方角値が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
	 * 逆に、引数のRz平面移動方角値が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
	 * デフォルトのRz平面移動加速度の上限と下限（_angBottomVelocity_MoveAngleRz、_angTopAngVelocity_MoveAngleRz) は<BR>
	 *
	 *  -360,000 ≦ 引数の動方角値増分 ≦ 360,000<BR>
	 *
	 * となっています。これは瞬時に（1フレームで）どんなRz平面移動方角にも向きを変えれることを意味します。<BR>
	 *
	 * @param	prm_iDistance_MoveAngleRz	Rz平面移動方角値増分(範囲：_angBottomVelocity_MoveAngleRz ～ _angTopAngVelocity_MoveAngleRz)
	 */
	void addMoveAngleRz(angle prm_iDistance_MoveAngleRz);




	/**
	 * Actorの目標のRz平面移動方角自動停止機能を有効(目標のRz平面移動方角値設定)<BR>
	 * 引数に設定されたRz平面移動方角値になるまで、Rz平面移動方角値を加算(減算)を毎フレーム行い続けます。<BR>
	 * 加算か減算かは、Rz平面移動方角の角速度（_angVelocity_MoveAngleRz）の正負で決定されます。<BR>
	 * Rz平面移動方角の角速度が 0 ならば、何も起こりません。<BR>
	 * 内部的には、addMoveAngleRz(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
	 * 目標のRz平面移動方角に到達したならば、この目標のRz平面移動方角自動停止機能は解除されます。<BR>
	 *
	 * @param	prm_angXYMove	到達目標のRz平面移動方角値(-360,000～360,000)
	 * @param	prm_iAllowRotWay  自動停止機能が有効になる回転方向
	 * @param	prm_angAllowVelocity 停止機能が有効になる移動方角角速度
	 */
	void setTargetMoveAngleRz(angle prm_angXYMove, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actorの目標のRz平面移動方角自動停止機能を有効(目標のRz平面移動方角を現在XY座標からの対象XY座標で設定)<BR>
	 * 機能はsetTargetMoveAngleRz(int)と同じ<BR>
	 *
	 * @param	prm_tX	xXY座標
	 * @param	prm_tY	yXY座標
	 * @param	prm_iAllowRotWay  自動停止機能が有効になる回転方向
	 * @param	prm_angAllowVelocity 停止機能が有効になる移動方角角速度
	 */
	void setTargetMoveAngleRzV(int prm_tX, int prm_tY, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);


	/**
	 * ActorのRz平面移動スピードを設定<BR>
	 * @param	prm_iVelocity_Move	Rz平面移動スピード
	 */
	void setMoveVelocity(int prm_iVelocity_Move);


	void setMoveVelocityRenge(int prm_iVelocity01_Move, int prm_iVelocity02_Move);

	void setMoveAcceleration(int prm_angAcceleration_MoveAngleRzVelocity);


	void setMoveAngleRzVelocity(int prm_angVelocity_MoveAngleRz);

	void setMoveAngleRzVelocityRenge(angle prm_angVelocity01_MoveAngleRz, angle prm_angVelocity02_MoveAngleRz);

	void setMoveAngleRzAcceleration(angle prm_angAcceleration_MoveAngleRzVelocity);



	angle getDistanceFromMoveAngleRzTo(int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromMoveAngleRzTo(angle prm_angRzTarget_Move, int prm_iWay);


	void setXYZMoveAngle(int prm_tX, int prm_tY, int prm_tZ);


	void setMoveAngleRy(angle prm_angle);


	/**
	 * 毎フレームのActorの振る舞い。<BR>
	 * 本インターフェースを利用する場合は、このbehave() を毎フレーム実行します。<BR>
	 * behave() の具体的な毎フレームの処理は以下の通り。<BR>
	 * ・加速度(_iAcceleration_MoveVelocity)が0でない場合、加速度によるスピード増加処理。<BR>
	 * 　　→加算後のスピードで setMoveVelocity(int) が毎フレーム実行されます。<BR>
	 * ・目標のRz平面移動方角自動停止機能が使用時の場合、Rz平面移動方角変更処理<BR>
	 * 　　→計算されたRz平面移動方角値で addMoveAngleRz(int) が毎フレーム実行されます。<BR>
	 * ・目標のRz平面移動方角自動停止機能使用時ではない場合、一定量Rz平面移動方角値加算処理<BR>
	 * 　　→addMoveAngleRz(int) が毎フレーム実行されます。<BR>
	 * ・目標の軸回転方角自動停止機能使用時の場合、軸回転方角変更処理<BR>
	 * 　　→計算された軸回転方角値で addAxisRotAngle(int) が毎フレーム実行されます。<BR>
	 * ・目標の軸回転方角自動停止機能が使用時ではない場合、一定量軸回転方角値加算処理<BR>
	 * 　　→addAxisRotAngle(int) が毎フレーム実行されます。<BR>
	 * 以上の処理を行った後、Actorの以下のメンバへ、座標増分情報、Z軸回転情報を設定します。<BR>
	 *  _X ･･･ Rz平面移動方角値とRz平面移動スピードからX座標増分計算し加算<BR>
	 *  _Y ･･･ Rz平面移動方角値とRz平面移動スピードからY座標増分計算し加算<BR>
	 *  _Z ･･･_iVelocity_ZMove を加算
	 *  _RX   ･･･ 軸回転方角値を代入<BR>
	 *  _RY   ･･･ 軸回転方角値を代入<BR>
	 *  _RZ   ･･･ 軸回転方角値を代入<BR>
	 * 【必ず値が設定されるメンバー】<BR>
	 * _iVelocity_Move,<BR>
	 * _pActor->_X += _vX_Move*_iVelocity_Move/LEN_UNIT;<BR>
	 * _pActor->_Y += _vY_Move*_iVelocity_Move/LEN_UNIT;<BR>
	 * _pActor->_Z += _iVelocity_ZMove
	 */
	virtual void behave();


	void setZMoveVelocity(int prm_iVelocity_ZMove);

	void setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove);

	void setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity);


	virtual ~StgMover();
};


#endif /*STGMOVER_H_*/

