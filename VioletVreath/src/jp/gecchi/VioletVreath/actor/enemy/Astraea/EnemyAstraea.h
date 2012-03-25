#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace VioletVreath {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafLib::DefaultMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

public:
    /** ���[�U���ˊԊu(frame) */
    int laser_interval_;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int laser_way_;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle angClearance_;
    /** �����]���p���x */
    ang_velo ang_veloTurn_;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** ���[�U�[���˃��[�J�����W */
    PosLaser** papaPosLaser_;

    DepositoryConnection* pCon_RefractionEffectDepository_;

    DepositoryConnection* pCon_LaserChipDepoStore_;



    GgafLib::LaserChipDepository*** papapLaserChipDepo_;

    /** �o���G�t�F�N�g */
    GgafDxCore::GgafDxDrawableActor* pEffect_Appearance_;

    EnemyAstraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/
