#ifndef FORMATIONEUNOMIA001_H_
#define FORMATIONEUNOMIA001_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001 : public GgafDx9Core::GgafDx9FormationActor {

public:
    /** �G�E�m�~�A�̔��˒e�̎؂���ꌳDispatcher�����ւ̐ڑ� */
    DispatcherConnection* _pDispatcherCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    SplineConnection** _papSplineCon;
    /** �ґ���(RANK�ϓ�) */
    int _num_formation_col;
    /** �P��̕ґ���(RANK�ϓ�) */
    int _num_formation_row;
    /** �G�E�m�~�A��2�����z��(RANK�ϓ�) */
    EnemyEunomia*** _papapEunomia;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _frame_interval;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    int _n;

    FormationEunomia001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    virtual void processBehavior() override;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ
     * @param prm_pActorLast �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override;

    virtual ~FormationEunomia001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
