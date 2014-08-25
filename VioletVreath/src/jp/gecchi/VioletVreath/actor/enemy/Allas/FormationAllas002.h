#ifndef FORMATIONALLAS002_H_
#define FORMATIONALLAS002_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationAllas002 : public GgafLib::TreeFormation {
    /** ���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_depo_;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Allas_;
    /** ���X�̔z��(RANK�ϓ�) */
    EnemyAllas** papAllas_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationAllas002(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationAllas002();
};

}
#endif /*FORMATIONALLAS002_H_*/
