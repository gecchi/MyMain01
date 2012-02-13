#ifndef FORMATIONMASSALIA_H_
#define FORMATIONMASSALIA_H_
namespace VioletVreath {

/**
 * �}�b�T���A�Q .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationMassalia : public GgafLib::DepositoryFormation {

public:
    /** �}�b�T���A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Massalia;
    /** �}�b�T���A�f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Fragment;
    /** �}�b�T���A�f�Ђ̒f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Fragment2;
    /** �}�b�T���A�f�Ђ̒f�Ў؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Fragment3;

    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame _R_interval_frames;
    /** �ґ������o�[�̏����ړ����x(RANK�ϓ�) */
    velo _R_mv_velo;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     */
    FormationMassalia(const char* prm_name);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

//    virtual void processOnActiveMassalia(EnemyMassalia* pEnemyMassalia, int col) = 0;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationMassalia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
