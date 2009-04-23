#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public DefaultMeshEnemyActor {

private:

public:
    /** �e�X�g�b�N */
    GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;
    /** RotationActor���R���X�g���N�^�Ő����������ۂ� */
    bool _createRotationActor;

    int _X_turn; // �܂�Ԃ�X���W
    int _Y_turn; // �܂�Ԃ�Y���W
    int _Z_turn; // �܂�Ԃ�Z���W
    int _veloBegin;
    int _incZ;

    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g��
     * @param prm_model ���f����
     */
    EnemyAstraea(const char* prm_name);

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_model ���f��
     * @param prm_pRotEnemyMeshShots001 ���˒e�X�g�b�N�̃��[�e�[�V�����A�N�^�[
     * @return
     */
    EnemyAstraea(const char* prm_name, GgafDx9LibStg::RotationActor* prm_pRotEnemyMeshShots001);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

