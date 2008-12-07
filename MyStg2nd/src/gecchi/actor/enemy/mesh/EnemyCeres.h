#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_

//ケレス
//画面右端で折り返して左に直進します。

class EnemyCeres : public DefaultMeshEnemyActor {

private:
	RotationActor* _pRotEnemyMeshShots001;

public:
	int _X_turn; // 折り返すX座標
	int _Y_turn; // 折り返すY座標
	int _Z_turn; // 折り返すZ座標
	int _iBeginVelocity;
	int _incZ;

	int _iMovePatternNo;

	EnemyCeres(string prm_name, string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyCeres();
};

#endif /*ENEMYCERES_H_*/

