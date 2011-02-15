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
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;

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
     * @param prm_pDispatcher_Shot
     * @param prm_pDispatcher_ShotEffect
     */
    virtual void config(
            GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Shot,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_ShotEffect
            ) {
        _pSplineProgram = prm_pSplineProgram;
        _pDispatcher_Shot = prm_pDispatcher_Shot;
        _pDispatcher_ShotEffect = prm_pDispatcher_ShotEffect;
    }


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

