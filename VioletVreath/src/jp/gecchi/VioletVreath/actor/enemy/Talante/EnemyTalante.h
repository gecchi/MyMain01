#ifndef ENEMYTALANTE_H_
#define ENEMYTALANTE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�^�����e .
 * �n�b�`�G�����̂P
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyTalante : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot_;

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
     * �^�����e���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
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
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pDepo_shot
     */
    virtual void config(
            GgafCore::ActorDepository* prm_pDepo_shot
            );


    virtual ~EnemyTalante();
};

}
#endif /*ENEMYTALANTE_H_*/

