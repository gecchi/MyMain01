#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace MyStg2nd {

/**
 * �P���X .
 * ��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B<BR>
 * initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^<BR>
 * �E_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j<BR>
 * �E_X_turn, _Y_turn �܂�Ԃ��ڕWXY���W�B�����ʒu���炱�̂��̒n�_��ڎw���b�X�B<BR>
 * �E_veloBegin �܂�Ԃ��n�_�ɍs���܂ł̉����x<BR>
 *
 */
class EnemyCeres : public DefaultMeshEnemyActor {

private:

public:
    /** �e�X�g�b�N */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_EnemyMeshShots001;
    /** ActorDispatcher���R���X�g���N�^�Ő����������ۂ� */
    bool _createActorDispatcher;

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
    EnemyCeres(const char* prm_name);

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_model ���f��
     * @param prm_pDispatcher_EnemyMeshShots001 ���˒e�X�g�b�N�̃A�N�^�[������
     * @return
     */
    EnemyCeres(const char* prm_name, GgafDx9LibStg::ActorDispatcher* prm_pDispatcher_EnemyMeshShots001);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyCeres();
};

}
#endif /*ENEMYCERES_H_*/

