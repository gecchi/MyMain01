#ifndef ENEMYEUNOMIA_H_
#define ENEMYEUNOMIA_H_
namespace VioletVreath {

/**
 * �G�@�G�E�m�~�A .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyEunomia :
  public GgafLib::DefaultMeshSetActor {

public:
    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineSequence* pSplSeq_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

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
     * @param prm_pSplSeq
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
//            GgafLib::TreeFormation* prm_pFormation,
            GgafLib::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            );


    virtual ~EnemyEunomia();
};

}
#endif /*ENEMYEUNOMIA_H_*/

