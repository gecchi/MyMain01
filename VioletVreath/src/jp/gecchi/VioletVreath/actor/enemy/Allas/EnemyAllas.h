#ifndef ENEMYALLAS_H_
#define ENEMYALLAS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�A���X .
 * �H�̑����t�@��
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class EnemyAllas : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::ActorDepository* pDepo_effect_;
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAllas(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A���X���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pVehicleLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafDx::CurveManufacture* prm_pCurveManufacture,
            GgafCore::ActorDepository* prm_pDepo_shot,
            GgafCore::ActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyAllas();
};

}
#endif /*ENEMYALLAS_H_*/

