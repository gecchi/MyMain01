#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafDx9LibStg::FormationActor {
    /** �C���X�̔��˒e�̎؂���ꌳDispatcher�����ւ̐ڑ� */
    DispatcherConnection* _pDispatcherCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplineCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Pallas;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyPallas** _papPallas;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    DWORD _frame_interval;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationPallas001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/