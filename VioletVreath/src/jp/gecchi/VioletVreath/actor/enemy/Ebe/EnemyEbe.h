#ifndef ENEMYEBE_H_
#define ENEMYEBE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�G�[�x .
 * �t�F���}�[�����B
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class EnemyEbe : public GgafLib::DefaultMeshSetActor {

public:

    enum {
        PROG_MOVE01_1   ,
        PROG_SPLINE_MOVE,
        PROG_MOVE02_1   ,
        PROG_MOVE02_2   ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_effect_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyEbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�[�x�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�[�x�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�[�x�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�[�x�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�[�x�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_shot,
            GgafCore::GgafActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyEbe();
};

}
#endif /*ENEMYEBE_H_*/

