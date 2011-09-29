#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
namespace MyStg2nd {

/**
 * 3D敵弾001 .
 * 1)勢いよく設定方向に飛び出す<BR>
 * 2)徐々に勢いは遅くなり、自機の方向に方向転換<BR>
 * 3)その後自機をめがけて直線移動。再加速していく<BR>
 * 【上書き可能なメンバー】
 *
 */
class EnemyCeresShot001 : public GgafLib::DefaultMeshSetActor {
public:
    //本Actorのカスタムプロパティ --->
    /** 出現時の初速 */
    int _iMvVelo_1st;
    /** 出現時の加速度（負で遅くなる */
    int _iMoveAcce_1st;
    /** 自身が出現してから、自機の方向に方向転換を開始するフレーム */
    frame _frame_TurnBegin;
    /** 移動速度上限 */
    int _iMvVelo_Top;
    /** 最低保証移動速度 */
    int _iMvVelo_Bottom;
    /** 方向転換に費やすことができるフレーム数 */
    frame _frame_TurnInterval;
    /** 方向転換中の角速度アングル値 */
    angle _angVelo_Turn;
    /** 方向転換を開始（_frame_TurnBegin）から再設定される加速度 */
    int _iMoveAcce_2nd;
    //<--- 本Actorのカスタムプロパティ

public:
    EnemyCeresShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyCeresShot001();
};

}
#endif /*ENEMYCELESSHOT001_H_*/

