#ifndef ENEMYATALANTE_H_
#define ENEMYATALANTE_H_
namespace VioletVreath {

/**
 * �G�@�A�^�����e .
 * �n�b�`�G�����̂P
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyAtalante : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT = 1  ,
        PROG_MOVE01_1,
        PROG_MOVE01_2,
        PROG_MOVE01_3,
        PROG_MOVE01_4,
        PROG_FINISH  ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;

    /** Y����������t���O */
    bool Y_ok_;
    /** Z����������t���O */
    bool Z_ok_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAtalante(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�^�����e�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;


    /**
     * �A�^�����e�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�^�����e�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�^�����e�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�^�����e�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pDepo_Shot
     */
    virtual void config(
            GgafCore::GgafActorDepository* prm_pDepo_Shot
            );


    virtual ~EnemyAtalante();
};

}
#endif /*ENEMYATALANTE_H_*/

