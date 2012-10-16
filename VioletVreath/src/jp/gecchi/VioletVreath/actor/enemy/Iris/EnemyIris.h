#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace VioletVreath {

/**
 * �G�@�C���X .
 * �t���[����e�Ƃ��ďo���B
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris :
  public GgafLib::DefaultMeshSetActor {

//    /** �t�H�[���[�V����(��t�H�[���[�V��������NULL) */
//    GgafLib::TreeFormation* pFormation_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineSequence* pSplSeq_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;
public:

    enum {
        SE_EXPLOSION = 0,
    };

    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIris(const char* prm_name);

    void onCreateModel() override;

    /**
     * �C���X�̏��������i�C���X�^���X������ۏ؁j
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


    virtual void config(
            GgafLib::SplineSequence* prm_pSplSeq,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pSplSeq_ = prm_pSplSeq;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

