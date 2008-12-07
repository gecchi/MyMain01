#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_

//�P���X
//��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B

class EnemyCeres : public DefaultMeshEnemyActor {

private:
	RotationActor* _pRotEnemyMeshShots001;

public:
	int _X_turn; // �܂�Ԃ�X���W
	int _Y_turn; // �܂�Ԃ�Y���W
	int _Z_turn; // �܂�Ԃ�Z���W
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

