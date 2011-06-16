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
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorStore* _pStore_ShotEffect;
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
     * ���˒eStore�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pStore
     */
    void setStore_Shot(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_Shot = prm_pStore;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pSplineProgram
     */
    void setSplineProgram(GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram) {
        _pSplineProgram = prm_pSplineProgram;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pStore
     */
    void setStore_ShotEffect(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_ShotEffect = prm_pStore;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

