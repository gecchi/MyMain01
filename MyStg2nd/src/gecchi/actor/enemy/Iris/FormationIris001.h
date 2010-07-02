#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafDx9Core::GgafDx9FormationActor {
    /** �C���X�̔��˒e�̎؂���ꌳDispatcher�����ւ̐ڑ� */
    DispatcherConnection* _pDispatcherCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplineCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Iris;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyIris** _papIris;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    DWORD _frame_interval;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationIris001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
