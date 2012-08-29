#ifndef ENEMYHESPERIA_H_
#define ENEMYHESPERIA_H_
namespace VioletVreath {

/**
 * 敵機ヘスペリア .
 * レーザー戦艦みたいな・・・
 * @version 1.00
 * @since 2012/08/29
 * @author Masatoshi Tsuge
 */
class EnemyHesperia : public GgafLib::DefaultMorphMeshActor {

private:
    /** 発射済みレーザーチップ数 */
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

    /** レーザ発射間隔(frame) */
    int laser_interval_;
    /** 発射レーザーチップの数（レーザー長さ） */
    int laser_length_;
    /** レーザーWay数(n×n)の一辺の本数 */
    int max_laser_way_;
    int laser_way_;
    /** レーザーとレーザーの間隔開き角度 */
    angle angClearance_;
    /** 方向転換角速度 */
    angvelo angveloTurn_;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** レーザー発射ローカル座標 */
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

