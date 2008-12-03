#ifndef ENEMYMESHSHOT001_H_
#define ENEMYMESHSHOT001_H_

/**
 * 3D敵弾001 .
 * 1)勢いよく設定方向に飛び出す<BR>
 * 2)徐々に勢いは遅くなり、時機の方向に方向転換<BR>
 * 3)その後時機をめがけて直線移動。加速していく<BR>
 * 【上書き可能なメンバー】
 *
 */
class EnemyMeshShot001 : public DefaultMeshEnemyActor {

	/** 出現時の初速 */
	int _iMoveVelocity_Begin;
	/** 出現時の加速度 */
	int _iMoveAcceleration_Begin;
	/** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
	DWORD _dwFrame_TurnBegin;
	/** 自身が出現してから、時機の方向に方向転換を終了するフレーム */
	DWORD _dwFrame_TurnFinish;
	/** 時機の方向に方向転換を終了したフレーム時に再設定される速度(0を指定すると再設定は行わない) */
	int _iMoveVelocity_TurnAfter;
	/** 時機の方向に方向転換を終了したフレーム時に再設定される加速度(0を指定すると再設定は行わない) */
	int _iMoveAcceleration_TurnAfter;

	//angle

public:
	EnemyMeshShot001(string prm_name, string prm_model);

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
	bool isOffScreen();

	/**
	 * ＜OverRide です＞
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual ~EnemyMeshShot001();
};


#endif /*ENEMYMESHSHOT001_H_*/

