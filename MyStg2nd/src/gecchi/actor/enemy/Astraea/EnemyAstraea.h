#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * アストラエア .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMeshActor {

private:
    /** 発射済みレーザーチップ数 */
    int _cnt_laserchip;
public:
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** レーザ発射間隔(frame) */
    int _laser_interval;
    /** 発射レーザーチップの数（レーザー長さ） */
    int _laser_length;
    /** レーザーWay数(n×n)の一辺の本数 */
    int _laser_way;
    /** レーザーとレーザーの間隔開き角度 */
    angle _angClearance;
    /** 方向転換角速度 */
    angvelo _angveloTurn;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** レーザー発射ローカル座標 */
    PosLaser** _papaPosLaser;

    GgafDx9LibStg::LaserChipDispatcher*** _papapLaserChipDispatcher;

    /** 出現エフェクト */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_Appearance;

    EnemyAstraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    void processFinal() override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

