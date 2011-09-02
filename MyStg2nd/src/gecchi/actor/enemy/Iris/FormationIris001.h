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
    /** �C���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Iris;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyIris** _papIris;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationIris001(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
