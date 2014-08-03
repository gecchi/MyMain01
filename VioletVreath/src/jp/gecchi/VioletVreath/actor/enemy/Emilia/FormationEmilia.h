#ifndef FORMATIONASSALIA_H_
#define FORMATIONASSALIA_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�~���A�Q .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationEmilia : public GgafLib::DepositoryFormation {

public:
    /** �G�~���A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConn_Emilia_;
    /** �G�~���A�f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConn_Fragment_;
    /** �G�~���A�f�Ђ̒f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConn_Fragment_2_;
    /** �G�~���A�f�Ђ̒f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoConn_Fragment_3_;

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

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationEmilia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
