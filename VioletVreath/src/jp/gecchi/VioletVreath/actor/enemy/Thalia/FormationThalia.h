#ifndef FORMATIONTHALIA_H_
#define FORMATIONTHALIA_H_
namespace VioletVreath {

/**
 * �G�@�^���A�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia : public GgafLib::TreeFormation {
public:
    /** �ґ���(RANK�ϓ�) */
    int num_Thalia_;
    /** �^���A�̔z��(RANK�ϓ�) */
    EnemyThalia** papThalia_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

    DepositoryConnection* pDpcon_;

    FormationThalia(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override {
    }

    virtual ~FormationThalia();
};

}
#endif /*FORMATIONTHALIA_H_*/
