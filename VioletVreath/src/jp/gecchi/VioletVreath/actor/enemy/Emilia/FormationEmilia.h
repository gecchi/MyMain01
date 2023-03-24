#ifndef FORMATIONASSALIA_H_
#define FORMATIONASSALIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
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
    /** �v�����[�h�p */
    DepositoryConnection* pConn_depo_Fragment3_;
    /** �v�����[�h�p */
    DepositoryConnection* pConn_depo_Fragment2_;
    /** �v�����[�h�p */
    DepositoryConnection* pConn_depo_Fragment_;
    /** �G�~���A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_depo_Emilia_;

    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame R_interval_frames_;
    /** ������(RANK�ϓ�) */
    int R_num_;
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

    void appearFragment(EnemyEmiliaBase* prm_pOrg);
    void appearFragment2(EnemyEmiliaBase* prm_pOrg);
    void appearFragment3(EnemyEmiliaBase* prm_pOrg);

    virtual ~FormationEmilia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
