#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace VioletVreath {

/**
 * �G�@�p���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafLib::TreeFormation {

public:
    /** �p���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pDepoCon_;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufCon_;
    /** �ґ���(RANK�ϓ�) */
    int num_Pallas_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationPallas001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUpPallas(EnemyPallas* prm_pPallas) = 0;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/
