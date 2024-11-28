#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D敵弾001 .
 * 1)勢いよく設定方向に飛び出す<BR>
 * 2)徐々に勢いは遅くなり、自機の方向に方向転換<BR>
 * 3)その後自機をめがけて直線移動。再加速していく<BR>
 * 【上書き可能なメンバー】
 *
 */
class EnemyEresShot001 : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    //本Actorのカスタムプロパティ --->
    /** 出現時の初速 */
    int velo1st_;
    /** 出現時の加速度（負で遅くなる */
    int iMoveAcce_1st_;
    /** 自身が出現してから、自機の方向に方向転換を開始するフレーム */
    frame frame_TurnBegin_;
    /** 移動速度上限 */
    int veloTop_;
    /** 最低保証移動速度 */
    int veloBottom_;
    /** 方向転換に費やすことができるフレーム数 */
    frame frame_TurnInterval_;
    /** 方向転換中の角速度アングル値 */
    angle angVelo_Turn_;
    /** 方向転換を開始（frame_TurnBegin_）から再設定される加速度 */
    int iMoveAcce_2nd_;
    //<--- 本Actorのカスタムプロパティ

public:
    EnemyEresShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EnemyEresShot001();
};

}
#endif /*ENEMYCELESSHOT001_H_*/

