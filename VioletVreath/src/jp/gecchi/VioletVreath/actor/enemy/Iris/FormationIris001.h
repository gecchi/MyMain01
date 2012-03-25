#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
namespace VioletVreath {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafLib::TreeFormation {
    /** �C���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoCon_;
    /** �X�v���C����`�����ւ̐ڑ� */
    SplineLineConnection* pSplLineCon_;
public:
    /** �ґ���(RANK�ϓ�) */
    int num_Iris_;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyIris** papIris_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

    FormationIris001(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override {
    }

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/