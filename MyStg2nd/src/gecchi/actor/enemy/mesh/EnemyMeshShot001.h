﻿#ifndef ENEMYMESHSHOT001_H_
#define ENEMYMESHSHOT001_H_
namespace MyStg2nd {

/**
 * 3D敵弾001 .
 * 1)勢いよく設定方向に飛び出す<BR>
 * 2)徐々に勢いは遅くなり、時機の方向に方向転換<BR>
 * 3)その後時機をめがけて直線移動。再加速していく<BR>
 * 【上書き可能なメンバー】
 *
 */
class EnemyMeshShot001 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    //本Actorのカスタムプロパティ --->
    /** 出現時の初速 */
    int _iMvVelo_1st;
    /** 出現時の加速度（負で遅くなる */
    int _iMoveAcce_1st;
    /** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
    DWORD _dwFrame_TurnBegin;
    /** 移動速度上限 */
    int _iMvVelo_Top;
    /** 最低保証移動速度 */
    int _iMvVelo_Bottom;
    /** 方向転換に費やすことができるフレーム数 */
    DWORD _dwFrameInterval_Turn;
    /** 方向転換中の角速度アングル値 */
    angle _angVelo_Turn;
    /** 方向転換を開始（_dwFrame_TurnBegin）から再設定される加速度 */
    int _iMoveAcce_2nd;
    /** 出現してからのフレーム数 */
    DWORD _frame_on_change_to_active_flg;
    //<--- 本Actorのカスタムプロパティ

public:
    EnemyMeshShot001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    virtual void initialize() override;

    /**
     * ＜OverRide です＞
     */
    virtual void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    virtual void processJudgement() override;


    /**
     * ＜OverRide です＞
     */
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyMeshShot001();
};

}
#endif /*ENEMYMESHSHOT001_H_*/

