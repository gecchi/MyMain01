#ifndef ENEMYTALANTE_H_
#define ENEMYTALANTE_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�^�����e .
 * �n�b�`�G�����̂P
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyTalante : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT    ,
        PROG_MOVE01_1,
        PROG_MOVE01_2,
        PROG_MOVE01_3,
        PROG_MOVE01_4,
        PROG_FINISH  ,
    };

    enum {
        SE_DAMAGED  ,
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
    EnemyTalante(const char* prm_name);

    void onCreateModel() override;

    /**
     * �^�����e�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;


    /**
     * �^�����e�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �^�����e�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �^�����e�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �^�����e�̏Փˎ����� .
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


    virtual ~EnemyTalante();
};

}
#endif /*ENEMYTALANTE_H_*/

