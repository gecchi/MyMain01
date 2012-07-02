#ifndef ENEMYTHISBE_H_
#define ENEMYTHISBE_H_
namespace VioletVreath {


/**
 * �G�@�V�Y�r�[ .
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyThisbe :
  public GgafLib::DefaultMorphMeshActor {
//class EnemyThisbe : public GgafLib::CubeMapMorphMeshActor {
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineSequence* pSplSeq_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:

    /** ���ˎ��G�t�F�N�g�f�|�W�g���ւ̐ڑ� */
    DepositoryConnection* pCon_RefractionEffectDepository_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThisbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * �V�Y�r�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �V�Y�r�[���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �V�Y�r�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �V�Y�r�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �V�Y�r�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒eDepository�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pDepo
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pSplSeq
     */
    void setSplineSequence(GgafLib::SplineSequence* prm_pSplSeq) {
        pSplSeq_ = prm_pSplSeq;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_ShotEffect_ = prm_pDepo;
    }

    virtual ~EnemyThisbe();
};

}
#endif /*ENEMYTHISBE_H_*/

