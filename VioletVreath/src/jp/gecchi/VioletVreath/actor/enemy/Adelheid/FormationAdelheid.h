#ifndef FORMATIONADELHEID_H_
#define FORMATIONADELHEID_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid : public GgafLib::DepositoryFormation {

public:
    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_FROMATION_MOVE1,
        PROG_FROMATION_MOVE2,
        PROG_FROMATION_MOVE3,
        PROG_FROMATION_MOVE4,
        PROG_FROMATION_MOVE5,
        PROG_LEAVE ,
    };


    /** �A�[�f���n�C�h�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConne_AdelheidDepo_;
    /** �A�[�f���n�C�h�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConne_ShotDepo_;
    /** �n�_�E�I�_�̍��W�v�Z�̂��߂̃_�~�[ */
    EnemyAdelheid* pDummy_;

    /** �n�_�̃p���T�i */
    EnemyPalisana* pPalisana_start;
    /** �I�_�̃p���T�i */
    EnemyPalisana* pPalisana_goal;

    /** �ґ���(RANK�ϓ�) */
    int RV_NumFormation_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame RV_IntervalFrames_;
    /** �ґ������o�[�̏����ړ����x(RANK�ϓ�) */
    velo RV_MvVelo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     */
    FormationAdelheid(const char* prm_name) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;
    /**
     * �X�v���C�������擾�B
     * ���ʂŎ������ĉ������B
     * @return
     */
    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual void onSayonaraAll() override;


    static void order1(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2);

    static void order2(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2);

    static void order3(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2);


    virtual ~FormationAdelheid();
};

}
#endif /*FORMATIONADELHEID_H_*/
