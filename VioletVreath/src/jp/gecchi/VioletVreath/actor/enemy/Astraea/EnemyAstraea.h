#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafLib::DefaultMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

    struct PosLaser {
        int X;
        int Y;
        int Z;
    };

public:
    enum {
        PROG_ENTRY,
        PROG_MOVE ,
        PROG_TURN ,
        PROG_FIRE ,
    };

    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };

    /** ���[�U���ˊԊu(frame) */
    int laser_interval_;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int laser_way_;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle angClearance_;
    /** �����]���p���x */
    angvelo angveloTurn_;
    /** ���[�U�[���˃��[�J�����W */
    PosLaser** papaPosLaser_;

    DepositoryConnection* pConn_RefractionEffectDepository_;

    DepositoryConnection* pConn_LaserChipDepoStore_;

    GgafLib::LaserChipDepository*** papapLaserChipDepo_;

    DepositoryConnection* pConn_ShotDepo_;
    DepositoryConnection* pConn_ShotDepo2_;
    DepositoryConnection* pConn_ShotDepo3_;

public:
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

