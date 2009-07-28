#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * アストラエア .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMeshSetActor {

private:
    /** 発射済みレーザーチップ数 */
    int _cnt_laserchip;

public:
    /** 方向転換間隔(frame) */
    int _shot_interval;
    /** 発射レーザーチップの数 */
    int _laser_length;
    /** Way数     */
    int _laser_way;

    GgafDx9Core::angle* _paWay;

    /** 方向転換角速度 */
    GgafDx9Core::angvelo _angveloTurn;

    LaserChipDispatcher** _papLaserChipDispatcher;

    EnemyAstraea(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

