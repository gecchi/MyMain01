#ifndef FORMATIONRIS001_H_
#define FORMATIONRIS001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationRis001 : public GgafLib::TreeFormation {
    /** ���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_depo_;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineSourceConnection* pSplSrcConnection_;
    GgafLib::SplineManufacture* pManufacture_;
public:
    /** �ґ���(RANK�ϓ�) */
    int num_Ris_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationRis001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationRis001();
};

}
#endif /*FORMATIONRIS001_H_*/
