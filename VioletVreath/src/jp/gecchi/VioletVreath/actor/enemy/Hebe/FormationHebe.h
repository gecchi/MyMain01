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
    DepositoryConnection* pDepoCon_Hebe_;
    /** �w�[�x�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pCon_ShotDepo_;
    GgafCore::GgafActorDepository* pDepo_Shot_;


    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufCon_;
    /** �ґ���(RANK�ϓ�) */
    int r_num_formation_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame r_interval_frames_;
    /** �ґ������o�[�̈ړ����x(RANK�ϓ�) */
    velo r_mv_velo_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationHebe(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processOnActiveHebe(EnemyHebe* pEnemyHebe) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_LastDestroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationHebe();
};

}
#endif /*FORMATIONHEBE_H_*/
