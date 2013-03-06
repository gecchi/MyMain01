#ifndef FORMATIONPALLAS002_H_
#define FORMATIONPALLAS002_H_
namespace VioletVreath {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas002 : public GgafLib::TreeFormation {
    /** �C���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoCon_;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufCon_;

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Pallas_;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyPallas** papPallas_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationPallas002(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationPallas002();
};

}
#endif /*FORMATIONPALLAS002_H_*/
