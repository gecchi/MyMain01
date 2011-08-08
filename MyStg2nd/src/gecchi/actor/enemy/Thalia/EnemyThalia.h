#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_
namespace MyStg2nd {


/**
 * �G�@�^���A .
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyThalia : public GgafDx9LibStg::DefaultMorphMeshActor {
//class EnemyThalia : public GgafDx9LibStg::CubeMapMorphMeshActor {
    /** �ړ��X�v���C���v���O���� */
    GgafDx9LibStg::SplineProgram* _pSplProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorStore* _pStore_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorStore* _pStore_ShotEffect;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int _dZ_camera_init;
public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    velo _veloTopMv;

    GgafDx9LibStg::LaserChipStore* _pLaserChipStore;
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
     * @param prm_pSplProgram
     */
    void setSplineProgram(GgafDx9LibStg::SplineProgram* prm_pSplProgram) {
        _pSplProgram = prm_pSplProgram;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pStore
     */
    void setStore_ShotEffect(GgafCore::GgafActorStore* prm_pStore) {
        _pStore_ShotEffect = prm_pStore;
    }

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

