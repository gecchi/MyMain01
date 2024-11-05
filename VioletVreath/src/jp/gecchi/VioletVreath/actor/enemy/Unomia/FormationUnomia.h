#ifndef FORMATIONUNOMIA_H_
#define FORMATIONUNOMIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia : public VvFormationActor<GgafLib::TreeFormation> {

public:
    /** �E�[�m�~�A�̋ʁA�؂���ꌳDepository�����ւ̐ڑ� */
    GgafCore::ActorDepository* pDepo_shot_;

    /** �Ȑ��ړ��̏�񎑌��ւ̐ڑ� */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    /** �ґ���(RANK�ϓ�) */
    int num_formation_col_;
    /** �P��̕ґ���(RANK�ϓ�) */
    int num_formation_row_;
    /** �ґ��� */
    int num_formation_member_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame launch_interval_;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo mv_velo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_ldr_id �Ȑ��ړ��̏��ID(XXX.ldr �� XXX)
     * @param prm_pFunc_StatusReset �X�e�[�^�X���Z�b�g�֐�
     */
    FormationUnomia(const char* prm_name, const char* prm_ldr_id, void* prm_pFunc_StatusReset = nullptr);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) = 0;

    virtual void processBehavior() override;

    virtual ~FormationUnomia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
