#ifndef FORMATIONEUNOMIA_H_
#define FORMATIONEUNOMIA_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia : public GgafLib::DepositoryFormation {

public:
    /** �G�E�m�~�A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Eunomia;

    /** �G�E�m�~�A�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_shot;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection** _papSplManufCon;
    /** �ґ���(RANK�ϓ�) */
    int _num_formation_col;
    /** �P��̕ґ���(RANK�ϓ�) */
    int _num_formation_row;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    int _n;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationEunomia(const char* prm_name, const char* prm_spl_id) ;

    virtual void initialize() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ
     * @param prm_pActorLast �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationEunomia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
