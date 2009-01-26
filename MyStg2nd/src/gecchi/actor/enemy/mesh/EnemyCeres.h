#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace MyStg2nd {

/**
 * ケレス .
 * 画面右端で折り返して左に直進します。<BR>
 * initialize()までに上書き可能な設定可能なパラメータ<BR>
 * ・_X,_Y,_Z 初期位置、但し _Z<0 であること。（折り返しが逆になって変だから）<BR>
 * ・_X_turn, _Y_turn 折り返し目標XY座標。初期位置からこのこの地点を目指すッス。<BR>
 * ・_iBeginVelocity 折り返し地点に行くまでの加速度<BR>
 *
 */
class EnemyCeres : public DefaultMeshEnemyActor {

private:

public:
	/** 弾ストック */
	GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;
	/** RotationActorをコンストラクタで生成したか否か */
	bool _createRotationActor;

	int _X_turn; // 折り返すX座標
	int _Y_turn; // 折り返すY座標
	int _Z_turn; // 折り返すZ座標
	int _iBeginVelocity;
	int _incZ;

	int _iMovePatternNo;

	/**
	 * コンストラクタ
	 * @param prm_name オブジェクト名
	 * @param prm_model モデル名
	 */
	EnemyCeres(std::string prm_name, std::string prm_model);

	/**
	 * コンストラクタ
	 * @param prm_name オブジェクト
	 * @param prm_model モデル
	 * @param prm_pRotEnemyMeshShots001 発射弾ストックのローテーションアクター
	 * @return
	 */
	EnemyCeres(std::string prm_name, std::string prm_model, GgafDx9LibStg::RotationActor* prm_pRotEnemyMeshShots001);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyCeres();
};

}
#endif /*ENEMYCERES_H_*/

