#ifndef FORMATIONDELHEID_H_
#define FORMATIONDELHEID_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * �G�@�f���n�C�h�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid : public GgafLib::DepositoryFormation {

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


    /** �f���n�C�h�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_DelheidDepo_;
    /** �f���n�C�h�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_ShotDepo_;
    /** �n�_�E�I�_�̍��W�v�Z�̂��߂̃_�~�[ */
    EnemyDelheid* pDummy_;

    /** �n�_�̃A���T�i */
    EnemyAlisana* pAlisana_start;
    /** �I�_�̃A���T�i */
    EnemyAlisana* pAlisana_goal;

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
    FormationDelheid(const char* prm_name) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpDelheid(EnemyDelheid* pEnemyDelheid) = 0;

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


    static void order1(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order2(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order3(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);


    virtual ~FormationDelheid();
};

}
#endif /*FORMATIONDELHEID_H_*/
