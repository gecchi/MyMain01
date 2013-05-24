#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafLib::TreeFormation {
    /** �C���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConnection_;
    /** �X�v���C����`�����ւ̐ڑ� */
    SplineLineConnection* pSplLineConnection_;

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Iris_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationIris001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
