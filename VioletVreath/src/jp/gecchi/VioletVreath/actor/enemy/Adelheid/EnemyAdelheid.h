#ifndef ENEMYADELHEID_H_
#define ENEMYADELHEID_H_
namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h .
 * ���A��68K�̂R�ʂ̘A�Ȃ����ґ��̓G�̉��I
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyAdelheid : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        PROG_MOVE01_1 = 1  ,
        PROG_SPLINE_MOVE   ,
        PROG_MOVE02_1      ,
        PROG_MOVE02_2      ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineKurokoStepper* pKurokoStepper_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAdelheid(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�[�f���n�C�h�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;


    /**
     * �A�[�f���n�C�h�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�[�f���n�C�h�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�[�f���n�C�h�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�[�f���n�C�h�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoStepper
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoStepper* prm_pKurokoStepper,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            );


    virtual ~EnemyAdelheid();
};

}
#endif /*ENEMYADELHEID_H_*/

