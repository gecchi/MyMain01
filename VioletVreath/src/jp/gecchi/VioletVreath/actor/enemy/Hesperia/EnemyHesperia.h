#ifndef ENEMYHESPERIA_H_
#define ENEMYHESPERIA_H_
namespace VioletVreath {

/**
 * �G�@�w�X�y���A .
 * ���[�U�[��݂͂����ȁE�E�E
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyHesperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

public:
    enum {
        PROG_ENTRY = 1,
        PROG_MOVE,
        PROG_HATCH_OPEN,
        PROG_FIRE,
        PROG_NOTHING,

    };

    enum {
        SE_EXPLOSION = 0,
        SE_DAMAGED,
        SE_FIRE,
    };

    /** ���[�U���ˊԊu(frame) */
    int laser_interval_;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int max_laser_way_;
    int laser_way_;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle angClearance_;
    /** �����]���p���x */
    angvelo angveloTurn_;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** ���[�U�[���˃��[�J�����W */
    PosLaser* paPosLaser_;

    DepositoryConnection* pCon_LaserChipDepoStore_;

    GgafLib::LaserChipDepository** papLaserChipDepo_;

    EnemyHesperia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyHesperia();
};

}
#endif /*ENEMYHESPERIA_H_*/

