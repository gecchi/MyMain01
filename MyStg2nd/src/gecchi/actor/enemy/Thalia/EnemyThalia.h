#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_
namespace MyStg2nd {


/**
 * �G�@�^���A .
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyThalia : public GgafLib::DefaultMorphMeshActor {
//class EnemyThalia : public GgafLib::CubeMapMorphMeshActor {
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineSequence* _pSplSeq;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* _pDepo_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* _pDepo_ShotEffect;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int _dZ_camera_init;
public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    velo _veloTopMv;

    GgafLib::LaserChipDepository* _pLaserChipDepo;
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
        _pDepo_Shot = prm_pDepo;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pSplSeq
     */
    void setSplineSequence(GgafLib::SplineSequence* prm_pSplSeq) {
        _pSplSeq = prm_pSplSeq;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        _pDepo_ShotEffect = prm_pDepo;
    }

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

