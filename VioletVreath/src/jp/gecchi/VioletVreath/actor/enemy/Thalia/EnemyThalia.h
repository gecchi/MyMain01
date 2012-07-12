#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_
namespace VioletVreath {


/**
 * �G�@�^���A .
 * �X�y�n���̃g���X���ǂ�
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyThalia :
  public GgafLib::DefaultMorphMeshActor {
//class EnemyThalia : public GgafLib::CubeMapMorphMeshActor {
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineSequence* pSplSeq_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int dZ_camera_init_;
public:
    enum {
        PROG_MOVE = 1  ,
        PROG_TURN_OPEN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_CLOSE     ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
        SE_FIRE,
    };
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

    velo veloTopMv_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �^���A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �^���A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �^���A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �^���A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �^���A�̏Փˎ����� .
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

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

