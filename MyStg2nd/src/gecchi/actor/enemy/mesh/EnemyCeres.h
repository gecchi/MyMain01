#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_

//ケレス
//画面右端で折り返して左に直進します。

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
	EnemyCeres(string prm_name, string prm_model);

	/**
	 * コンストラクタ
	 * @param prm_name オブジェクト
	 * @param prm_model モデル
	 * @param prm_pRotEnemyMeshShots001 発射弾ストックのローテーションアクター
	 * @return
	 */
	EnemyCeres(string prm_name, string prm_model, GgafDx9LibStg::RotationActor* prm_pRotEnemyMeshShots001);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyCeres();
};

#endif /*ENEMYCERES_H_*/

