#ifndef ENEMYEUNOMIA_H_
#define ENEMYEUNOMIA_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyEunomia : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx9Core::SplineProgram* _pSplineProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorStore* _pStore_ShotEffect;

    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyEunomia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�E�m�~�A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�E�m�~�A�̏�ԃ��Z�b�g���� .
     */
    void onReset() override;

    /**
     * �G�E�m�~�A�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�E�m�~�A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�E�m�~�A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�E�m�~�A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pSplineProgram
     * @param prm_pStore_Shot
     * @param prm_pStore_ShotEffect
     */
    virtual void config(
            GgafDx9Core::SplineProgram* prm_pSplineProgram,
            GgafCore::GgafActorStore* prm_pStore_Shot,
            GgafCore::GgafActorStore* prm_pStore_ShotEffect
            ) {
        _pSplineProgram = prm_pSplineProgram;
        _pStore_Shot = prm_pStore_Shot;
        _pStore_ShotEffect = prm_pStore_ShotEffect;
    }


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

