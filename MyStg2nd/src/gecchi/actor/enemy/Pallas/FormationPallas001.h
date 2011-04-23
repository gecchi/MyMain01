#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace MyStg2nd {

/**
 * �G�@�p���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafDx9Core::GgafDx9FormationActor {

public:
    /** �p���X�̔��˒e�̎؂���ꌳDispatcher�����ւ̐ڑ� */
    DispatcherConnection* _pDispatcherCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    SplineConnection* _pSplineCon;
    /** �ґ���(RANK�ϓ�) */
    int _num_Pallas;
    /** �p���X�̔z��(RANK�ϓ�) */
    EnemyPallas** _papPallas;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationPallas001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ
     * @param prm_pActorLast �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/
