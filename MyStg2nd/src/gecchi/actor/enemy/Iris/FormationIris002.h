#ifndef FORMATIONIRIS002_H_
#define FORMATIONIRIS002_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris002 : public GgafDx9Core::GgafDx9FormationActor {

    StoreConnection* _pStoreCon;
    Spline3DConnection* _pSplineCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Iris;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyIris** _papIris;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationIris002(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual ~FormationIris002();
};

}
#endif /*FORMATIONIRIS002_H_*/
