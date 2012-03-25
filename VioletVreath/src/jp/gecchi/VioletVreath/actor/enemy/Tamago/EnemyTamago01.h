#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
namespace VioletVreath {

/**
 * �e�X�g�p .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafLib::SpriteMeshSetActor {

public:
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineSequence* pProgram_Tamago01Move_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    DepositoryConnection* pDepoCon_;


    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

    /**
     * ���܂����f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * ���܂��̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���܂��̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���܂��̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * ���܂��̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * ���܂��̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒e�ݒ� .
     * @param prm_pDepo (GgafDxDrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    /**
     * ���ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo (GgafDxDrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_ShotEffect_ = prm_pDepo;
    }

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/
