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
    DWORD _frame_shot_after;
public:
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 方向転換間隔(frame) */
    int _laser_interval;
    int _shot_interval;
    /** 発射レーザーチップの数 */
    int _laser_length;
    /** Way数     */
    int _laser_way;

    angle* _paWayRz;
    angle* _paWayRy;
    /** 方向転換角速度 */
    angvelo _angveloTurn;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    PosLaser** papaPosLaser;


    LaserChipDispatcher*** _papapLaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    DispatcherConnection* _pDpcon;
    EnemyAstraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

