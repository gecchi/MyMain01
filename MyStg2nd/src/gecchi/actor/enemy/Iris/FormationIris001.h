#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafDx9LibStg::FormationActor {

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
    GgafDx9Core::velo _move_velocity;

    FormationIris001(const char* prm_name);

    virtual void initialize();

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
