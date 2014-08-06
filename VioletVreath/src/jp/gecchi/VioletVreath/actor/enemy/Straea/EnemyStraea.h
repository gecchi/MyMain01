#ifndef ENEMYSTRAEA_H_
#define ENEMYSTRAEA_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * �X�g���G�A .
 * �@���B
 * @version 1.00
 * @since 2009/04/23
 * @author Masatoshi Tsuge
 */
class EnemyStraea : public GgafLib::DefaultMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int cnt_laserchip_;

    struct PosLaser {
        int x;
        int y;
        int z;
    };

public:
    enum {
        PROG_ENTRY,
        PROG_MOVE ,
        PROG_TURN ,
        PROG_FIRE ,
        PROG_BANPEI,
    };

    enum {
        SE_EXPLOSION,
        SE_FIRE     ,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

    /** ���[�U���ˊԊu(frame) */
    int laser_interval_;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int laser_length_;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int laser_way_;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle ang_clearance_;
    /** �����]���p���x */
    angvelo angvelo_turn_;
    /** ���[�U�[���˃��[�J�����W */
    PosLaser** papaPosLaser_;

    DepositoryConnection* pConn_pRefractionEffectDepository_;

    DepositoryConnection* pConn_pDepoStore_laser_set;

    GgafLib::LaserChipDepository*** papapLaserChipDepo_;

    DepositoryConnection* pConn_pShotDepo2_;
    DepositoryConnection* pConn_pShotDepo3_;

public:
    EnemyStraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyStraea();
};

}
#endif /*ENEMYSTRAEA_H_*/

