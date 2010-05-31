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

    /** �ړ��X�v���C���v���O���� */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;
public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void onCreateModel() override;

    /**
     * �C���X�̂����������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �C���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �C���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �C���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �C���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒eDispatcher�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pDispatcher
     */
    void setDispatcher_Shot(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pProgram_IrisMove
     */
    void setSplineProgram(GgafDx9Core::GgafDx9SplineProgram* prm_pProgram_IrisMove) {
        _pProgram_IrisMove = prm_pProgram_IrisMove;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDispatcher
     */
    void setDispatcher_ShotEffect(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

