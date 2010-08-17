#ifndef FORMATIONTHALIA001_H_
#define FORMATIONTHALIA001_H_
namespace MyStg2nd {

/**
 * �G�@�^���A�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia001 : public GgafDx9Core::GgafDx9FormationActor {
    /** �^���A�̔��˒e�̎؂���ꌳDispatcher�����ւ̐ڑ� */
    DispatcherConnection* _pDispatcherCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplineCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Thalia;
    /** �^���A�̔z��(RANK�ϓ�) */
    EnemyThalia** _papThalia;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _frame_interval;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationThalia001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual ~FormationThalia001();
};

}
#endif /*FORMATIONTHALIA001_H_*/
