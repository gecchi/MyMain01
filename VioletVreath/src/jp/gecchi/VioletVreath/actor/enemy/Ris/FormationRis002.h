#ifndef FORMATIONRIS002_H_
#define FORMATIONRIS002_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationRis002 : public GgafLib::TreeFormation {

    DepositoryConnection* pDepoConn_;
    SplineLineConnection* pSplLineConnection_;

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Ris_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationRis002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationRis002();
};

}
#endif /*FORMATIONRIS002_H_*/
