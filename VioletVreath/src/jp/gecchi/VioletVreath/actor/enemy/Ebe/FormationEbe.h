#ifndef FORMATIONEBE_H_
#define FORMATIONEBE_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�@�G�[�x�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe : public GgafLib::DepositoryFormation {

public:
    /** �G�[�x�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pEbeDepo_;
    /** �G�[�x�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pShotDepo_;

    /** �ґ���(RANK�ϓ�) */
    int RV_NumFormation_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame RV_IntervalFrames_;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo RV_MvVelo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationEbe(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpEbe(EnemyEbe* pEnemyEbe) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual ~FormationEbe();
};

}
#endif /*FORMATIONEBE_H_*/
