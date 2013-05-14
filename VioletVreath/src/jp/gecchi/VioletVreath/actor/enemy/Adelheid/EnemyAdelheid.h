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
        PROG_INIT,
        PROG_MOVING,
        PROG_MOVING_AFTER_LEAD,
    };

    enum {
        PROG2_WAIT,
        PROG2_OPEN,
        PROG2_SHOT,
        PROG2_CLOSE,
    };


    enum {
        MPH_CLOSE,
        MPH_OPEN,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    GgafCore::GgafProgress* pProg2_;

    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;

    FormationAdelheid* pFormation_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAdelheid(const char* prm_name);

    void onCreateModel() override;


    void nextFrame() override;
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
     * @param prm_pKurokoLeader
     * @param prm_pDepo_Shot
     * @param prm_pDepo_ShotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot
            );

    void open_shot();

    virtual ~EnemyAdelheid();
};

}
#endif /*ENEMYADELHEID_H_*/

