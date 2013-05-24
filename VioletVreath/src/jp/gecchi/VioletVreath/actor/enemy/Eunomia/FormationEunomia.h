#ifndef FORMATIONEUNOMIA_H_
#define FORMATIONEUNOMIA_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia : public GgafLib::DepositoryFormation {

public:
    /** �G�E�m�~�A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConnection_Eunomia_;
    /** �G�E�m�~�A�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConnection_ShotDepo_;
    GgafCore::GgafActorDepository* pDepo_Shot_;

    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection** papSplManufConnection_;
    /** �ґ���(RANK�ϓ�) */
    int RF_num_formation_col_;
    /** �P��̕ґ���(RANK�ϓ�) */
    int RF_num_formation_row_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame RF_interval_frames_;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo RF_mv_velo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationEunomia(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationEunomia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
