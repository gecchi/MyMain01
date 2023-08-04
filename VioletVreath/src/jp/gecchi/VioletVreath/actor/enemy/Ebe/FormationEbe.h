#ifndef FORMATIONEBE_H_
#define FORMATIONEBE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�@�G�[�x�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe : public VvFormationActor<GgafLib::DepositoryFormation> {

public:
    /** �G�[�x�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pEbeDepo_;
    /** �G�[�x�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pShotDepo_;

    /** �ґ���(RANK�ϓ�) */
    int RV_Num_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame RV_LaunchInterval;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo RV_MvVelo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_ldr_id �Ȑ��ړ��̏��ID(XXX.ldr �� XXX)
     * @param prm_pFunc_StatusReset �X�e�[�^�X���Z�b�g�֐�
     */
    FormationEbe(const char* prm_name, const char* prm_ldr_id, void* prm_pFunc_StatusReset = nullptr);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpEbe(EnemyEbe* pEnemyEbe) = 0;

    virtual void processBehavior() override;

    virtual GgafDx::CurveManufacture* getSplManuf() = 0;

    virtual ~FormationEbe();
};

}
#endif /*FORMATIONEBE_H_*/
