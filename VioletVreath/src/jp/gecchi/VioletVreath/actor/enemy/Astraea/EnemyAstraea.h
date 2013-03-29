#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace VioletVreath {

/**
 * アストラエア .
 */
class EnemyAstraea : public GgafLib::DefaultMeshActor {

private:
    /** 発射済みレーザーチップ数 */
    int cnt_laserchip_;

    struct PosLaser {
        int X;
        int Y;
        int Z;
    };

public:
    enum {
        PROG_ENTRY = 1,
        PROG_MOVE,
        PROG_TURN,
        PROG_FIRE,
    };

    enum {
        SE_EXPLOSION = 0,
        SE_FIRE,
    };

    /** レーザ発射間隔(frame) */
    int laser_interval_;
    /** 発射レーザーチップの数（レーザー長さ） */
    int laser_length_;
    /** レーザーWay数(n×n)の一辺の本数 */
    int laser_way_;
    /** レーザーとレーザーの間隔開き角度 */
    angle angClearance_;
    /** 方向転換角速度 */
    angvelo angveloTurn_;
    /** レーザー発射ローカル座標 */
    PosLaser** papaPosLaser_;

    DepositoryConnection* pConnection_RefractionEffectDepository_;

    DepositoryConnection* pConnection_LaserChipDepoStore_;

    GgafLib::LaserChipDepository*** papapLaserChipDepo_;

    DepositoryConnection* pConnection_ShotDepo_;
    DepositoryConnection* pConnection_ShotDepo2_;
    DepositoryConnection* pConnection_ShotDepo3_;

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

