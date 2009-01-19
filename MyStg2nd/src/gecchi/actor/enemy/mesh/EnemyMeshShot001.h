#ifndef ENEMYMESHSHOT001_H_
#define ENEMYMESHSHOT001_H_
namespace MyStg2nd {

/**
 * 3D敵弾001 .
 * 1)勢いよく設定方向に飛び出す<BR>
 * 2)徐々に勢いは遅くなり、時機の方向に方向転換<BR>
 * 3)その後時機をめがけて直線移動。再加速していく<BR>
 * 【上書き可能なメンバー】
 *
 */
class EnemyMeshShot001 : public DefaultMeshEnemyActor {
public:
	//本Actorのカスタムプロパティ --->
	/** 出現時の初速 */
	int _iMoveVelocity_1st;
	/** 出現時の加速度（負で遅くなる */
	int _iMoveAcceleration_1st;
	/** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
	DWORD _dwFrame_TurnBegin;
	/** 移動速度上限 */
	int _iMoveVelocity_Top;
	/** 最低保証移動速度 */
	int _iMoveVelocity_Bottom;
	/** 方向転換に費やすことができるフレーム数 */
	DWORD _dwFrameInterval_Turn;
	/** 方向転換中の角速度アングル値 */
	GgafDx9Core::angle _angVelocity_Turn;
	/** 方向転換を開始（_dwFrame_TurnBegin）から再設定される加速度 */
	int _iMoveAcceleration_2nd;
	/** 出現してからのフレーム数 */
	DWORD _dwFrame_switchedToPlay;
	//<--- 本Actorのカスタムプロパティ

public:
	EnemyMeshShot001(string prm_name, string prm_model);

	/**
	 * ＜OverRide です＞
	 */
	virtual void initialize();

	/**
	 * ＜OverRide です＞
	 */
	virtual void processBehavior();

 	/**
	 * ＜OverRide です＞
	 */
	virtual void processJudgement();

 	/**
	 * ＜OverRide です＞
	 */
	virtual bool isOffScreen();

	/**
	 * ＜OverRide です＞
	 */
	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	virtual ~EnemyMeshShot001();
};


}
#endif /*ENEMYMESHSHOT001_H_*/

