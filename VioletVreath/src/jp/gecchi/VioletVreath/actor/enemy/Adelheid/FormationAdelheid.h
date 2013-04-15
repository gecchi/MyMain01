#ifndef FORMATIONADELHEID_H_
#define FORMATIONADELHEID_H_
namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid : public GgafLib::DepositoryFormation {

public:
    /** �A�[�f���n�C�h�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConnection_AdelheidDepo_;
    /** �A�[�f���n�C�h�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConnection_ShotDepo_;

    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
    /** �ґ���(RANK�ϓ�) */
    int rr_num_formation_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame rr_interval_frames_;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo rr_mv_velo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationAdelheid(const char* prm_name, const char* prm_spl_id) ;

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

    virtual ~FormationAdelheid();
};

}
#endif /*FORMATIONADELHEID_H_*/
