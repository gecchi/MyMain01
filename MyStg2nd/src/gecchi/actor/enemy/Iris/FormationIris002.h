#ifndef FORMATIONIRIS002_H_
#define FORMATIONIRIS002_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris002 : public GgafDx9LibStg::FormationActor {

    /** �ړ��p�X�v���C�� */
    static GgafDx9Core::GgafDx9Spline3D _sp;

    /** */
    DispatcherConnection* _pDispatcherCon;

public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Iris;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyIris** _papIris;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    DWORD _frame_interval;
    /** �ړ����x(RANK�ϓ�) */
    velo _move_velocity;

    FormationIris002(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationIris002();
};

}
#endif /*FORMATIONIRIS002_H_*/
