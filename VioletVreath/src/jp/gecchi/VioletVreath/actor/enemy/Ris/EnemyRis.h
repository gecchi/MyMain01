#ifndef ENEMYRIS_H_
#define ENEMYRIS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@���X .
 * �t���[����e�Ƃ��ďo���B
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyRis : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

//    /** �t�H�[���[�V����(��t�H�[���[�V��������nullptr) */
//    GgafLib::TreeFormation* pFormation_;
    /** �ړ��X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::ActorDepository* pDepo_effect_;

public:
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyRis(const char* prm_name);

    void onCreateModel() override;

    /**
     * ���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���X���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * ���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    void onInactive() override;


    virtual void config(
            GgafDx::VehicleLeader* prm_pVehicleLeader,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            ) {
        pVehicleLeader_ = prm_pVehicleLeader;
        pDepo_shot_ = prm_pDepo_shot;
        pDepo_effect_ = prm_pDepo_shotEffect;
    }

    virtual ~EnemyRis();
};

}
#endif /*ENEMYRIS_H_*/

