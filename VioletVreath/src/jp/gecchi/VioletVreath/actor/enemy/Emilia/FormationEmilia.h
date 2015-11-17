#ifndef FORMATIONASSALIA_H_
#define FORMATIONASSALIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �G�~���A�Q .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationEmilia : public GgafLib::DefaultGeometricActor {

public:
    /** �G�~���A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_depo_Emilia_;

    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame R_interval_frames_;
    /** �ґ������o�[�̏����ړ����x(RANK�ϓ�) */
    velo R_mv_velo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     */
    FormationEmilia(const char* prm_name);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

//    virtual void processOnActiveEmilia(EnemyEmilia* pEnemyEmilia, int col) = 0;

    virtual void processBehavior() override;

    virtual ~FormationEmilia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
