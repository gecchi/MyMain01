#ifndef FORMATIONHEBE_H_
#define FORMATIONHEBE_H_
namespace VioletVreath {

/**
 * �G�@�w�[�x�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationHebe : public GgafLib::DepositoryFormation {

public:
    /** �w�[�x�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConnection_HebeDepo_;
    /** �w�[�x�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConnection_ShotDepo_;

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
    FormationHebe(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpHebe(EnemyHebe* pEnemyHebe) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual ~FormationHebe();
};

}
#endif /*FORMATIONHEBE_H_*/
