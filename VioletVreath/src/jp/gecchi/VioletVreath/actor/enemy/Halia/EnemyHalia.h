#ifndef ENEMYHALIA_H_
#define ENEMYHALIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�n���A .
 * �X�y�n���̃g���X���ǂ��H
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyHalia : public VvEnemyActor<GgafLib::DefaultMassMorphMeshActor> {
public:
    velo veloTopMv_;
    /** �ړ��X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** ���_���珉���J����Z�ʒu�̋��� */
    coord dZ_camera_init_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �n���A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �n���A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �n���A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �n���A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �n���A�̏Փˎ����� .
     */
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;


    void onInactive() override;

    /**
     * �J�[�u�ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pVehicleLeader
     */
    void setCurveLocusVehicleLeader(GgafDx::VehicleLeader* prm_pVehicleLeader) {
        pVehicleLeader_ = prm_pVehicleLeader;
    }

    virtual ~EnemyHalia();
};

}
#endif /*ENEMYHALIA_H_*/

