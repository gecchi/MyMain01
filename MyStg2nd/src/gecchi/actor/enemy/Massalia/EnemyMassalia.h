#ifndef ENEMYMASSALIA_H_
#define ENEMYMASSALIA_H_
namespace MyStg2nd {

/**
 * マッサリア  .
 */
class EnemyMassalia : public GgafDx9LibStg::DefaultMeshActor {

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

    StoreConnection* _pStoreCon_RefractionEffect;

    StoreConnection* _pStoreCon_DpEnemyMassaliaLaserChip;



    GgafDx9LibStg::LaserChipStore*** _papapLaserChipStore;

    /** 出現エフェクト */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_Appearance;

    EnemyMassalia(const char* prm_name);

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

    virtual ~EnemyMassalia();
};

}
#endif /*ENEMYMASSALIA_H_*/

