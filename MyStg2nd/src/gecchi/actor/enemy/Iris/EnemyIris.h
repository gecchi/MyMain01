#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * �G�@�C���X .
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;
    /** �X�v���C���v���O���� */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;
    /** �e�X�g�b�N */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot;
    /** ���ʃG�t�F�N�g */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_ShotEffect;

    EnemyIris(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * ���˒e�ݒ� .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�B�X�p�b�`���[�̃|�C���^
     */
    void setDispatcher_Shot(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * ���ʃG�t�F�N�g�ݒ� .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�B�X�p�b�`���[�̃|�C���^
     */
    void setDispatcher_ShotEffect(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

