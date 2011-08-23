#ifndef FORMATIONTHALIA_H_
#define FORMATIONTHALIA_H_
namespace MyStg2nd {

/**
 * �G�@�^���A�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia : public GgafDx9Core::GgafDx9FormationActor {
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Thalia;
    /** �^���A�̔z��(RANK�ϓ�) */
    EnemyThalia** _papThalia;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    DepositoryConnection* _pDpcon;

    FormationThalia(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;


    virtual ~FormationThalia();
};

}
#endif /*FORMATIONTHALIA_H_*/
