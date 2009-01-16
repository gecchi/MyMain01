#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_

//�P���X
//��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B

class EnemyCeres : public DefaultMeshEnemyActor {

private:

public:
	/** �e�X�g�b�N */
	GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;
	/** RotationActor���R���X�g���N�^�Ő����������ۂ� */
	bool _createRotationActor;

	int _X_turn; // �܂�Ԃ�X���W
	int _Y_turn; // �܂�Ԃ�Y���W
	int _Z_turn; // �܂�Ԃ�Z���W
	int _iBeginVelocity;
	int _incZ;

	int _iMovePatternNo;

	/**
	 * �R���X�g���N�^
	 * @param prm_name �I�u�W�F�N�g��
	 * @param prm_model ���f����
	 */
	EnemyCeres(string prm_name, string prm_model);

	/**
	 * �R���X�g���N�^
	 * @param prm_name �I�u�W�F�N�g
	 * @param prm_model ���f��
	 * @param prm_pRotEnemyMeshShots001 ���˒e�X�g�b�N�̃��[�e�[�V�����A�N�^�[
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

