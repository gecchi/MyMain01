#ifndef ENEMYHEBE_H_
#define ENEMYHEBE_H_
namespace VioletVreath {

/**
 * �G�@�w�[�x .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class EnemyHebe : public GgafLib::DefaultMeshSetActor {

public:

    enum {
        PROG_MOVE01_1 = 1  ,
        PROG_SPLINE_MOVE   ,
        PROG_MOVE02_1      ,
        PROG_MOVE02_2      ,
    };

    enum {
        SE_EXPLOSION = 0,
    };

    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineSequence* pSplSeq_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHebe(const char* prm_name);

    void onCreateModel() override;

    /**
     * �w�[�x�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;


    /**
     * �w�[�x�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �w�[�x�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �w�[�x�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �w�[�x�̏Փˎ����� .
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


    virtual ~EnemyHebe();
};

}
#endif /*ENEMYHEBE_H_*/

