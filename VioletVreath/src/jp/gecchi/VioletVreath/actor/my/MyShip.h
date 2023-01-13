#ifndef MYSHIP_H_
#define MYSHIP_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

//#define MY_SHIP_VREATH_COST (500)
//無呼吸時 1000000/500/60 = 約33.3秒で死ぬ

/** 毎フレーム減るVreath */
#define MY_SHIP_VREATH_COST (5)
//無呼吸時 10000/5/60 = 約33.3秒で死ぬ

/** 最大MP */
#define MY_SHIP_MAX_MP   (500000)
/** 初期MP */
#define MY_SHIP_START_MP (500000)
/** 自機の移動が停止しても、トレースな状態を維持できるフレーム数 */
#define TRACE_DELAY_WAIT_FRAME (0x7fffffff)

#define MYSHIP_SHOT_MATRIX (7)
/** 最大分身数 */
#define MAX_BUNSHIN_NUM (10)
/** １オプション当たりの最大可能ロックオン数 */
#define MAX_LOCKON_NUM (8)
/**
 * 自機クラス
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
class MyShip : public VvMyActor<GgafLib::DefaultD3DXMeshActor> {
//class MyShip : public GgafLib::DefaultMeshActor {
//class MyShip : public GgafLib::CubeMapMeshActor {
//class MyShip : public GgafLib::DefaultD3DXAniMeshActor {
public:
    enum Switch {
        SW_ADD = 1,
        SW_NOP = 0,
        SW_SUB = -1
    };
public:
    /** 移動Y座標上限 */
    static coord lim_y_top_;
    /** 移動Y座標下限 */
    static coord lim_y_bottom_;
    /** 移動X座標上限 */
    static coord lim_x_infront_;
    /** 移動X座標下限 */
    static coord lim_x_behaind_;
    /** 移動Z座標上限 */
    static coord lim_z_left_;
    /** 移動Z座標下限 */
    static coord lim_z_right_;

    static uint32_t shot2_matrix_[4][MYSHIP_SHOT_MATRIX];
    static uint32_t shot3_matrix_[2][MYSHIP_SHOT_MATRIX];

    angle senakai_[3*3*3];
    angle* pSenakai_;

    /** [r]ロックオンコントローラー */
    MyLockonController* pLockonCtrler_;
    /** [r]魚雷コントローラー */
    MyTorpedoController* pTorpedoCtrler_;

    /** 現在移動方角 */
    dir26 mv_way_;
    /** 現在移動方角のX軸正負 */
    int mv_way_sgn_x_;
    /** 現在移動方角のY軸正負 */
    int mv_way_sgn_y_;
    /** 現在移動方角のZ軸正負 */
    int mv_way_sgn_z_;
    /** 前回移動方角 */
    dir26 prev_way_;
    /** 移動方角に変化があった場合 true となる */
    bool is_just_change_mv_way_;

    /** 移動スピードレベルに相応する移動スピード */
    velo mv_speed_;

    velo veloTurboTop_;
    velo veloTurboBottom_;

    /** Turbo移動開始時の移動速度の初速度 */
    velo veloBeginMT_; //Move Velo when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** 奥(+Z)又は手前(-Z)へ通常移動開始時のX軸回転角速度の初速度 */
    angvelo angRxVelo_BeginMZ_; //Rotation axisX angle Velo when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常移動中のX軸回転角速度の角加速度 */
    angacce angRxAcce_MZ_; //Rotation axisX angle Acce while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ移動中のX軸回転角速度の上限角速度 */
    angvelo angRxTopVelo_MZ_; //Rotation axisX Top angle Velo while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常Z移動中のX軸回転角の停止角度 */
    angle angRxStop_MZ_; //Rotation axisX Stop angle while I Move Z


    /** 上(+Y)又は下(-Y)へTurbo移動開始時のZ軸回転角速度の初速度 */
    angvelo angRxVelo_BeginMZT_; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる

    GgafCore::ActorDepository* pDepo_MyShots001_;
    GgafCore::ActorDepository* pDepo_MySnipeShots001_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    EffectTurbo001* pEffectTurbo001_;
    MyMagicEnergyCore* pMyMagicEnergyCore_;
//    //debug ---->
//    GgafCore::ActorDepository* pDepo_TestGuShot_;
//    GgafCore::ActorDepository* pDepo_TestChokiShot_;
//    GgafCore::ActorDepository* pDepo_TestPaShot_;
//    GgafCore::ActorDepository* pDepo_TestNomalShot_;
//    //<---- debug


    /** ソフト連射発動中であるか否か */
    bool is_being_soft_rapidshot_;

    /** ソフト連射が発動開始してからの発射数カウント合計 */
    uint32_t soft_rapidshot_shot_count_;
    /** ソフト連射が発動開始してからのプッシュカウント */
    int soft_rapidshot_push_cnt_;

    /** １プッシュ内のソフト連射開始からの経過フレーム数 */
    frame soft_rapidshot_frames_in_one_push;
    /** １プッシュ内のソフト連射開始からの発射数カウント */
    int soft_rapidshot_shot_count_in_one_push_;

    /** ショットが発生したフレームのみ true になる */
    bool is_just_shot_;
    /** ショットが先頭の一発目のスナイプショットか否か、スナイプショットの時のみ true になる */
    bool is_snipe_shot_;

    /** レーザー発射中かどうか */
    bool is_shooting_laser_;
    /** レーザー発射可能かどうか */
    bool can_shoot_laser_;
    /** SHOTボタン押しっぱなし経過フレーム数（レーザー発射開始判定のため） */
    frame frame_shot_pressed_;
    /** シーン突入時かどうか */
    bool is_diving_;

    /** 操作可否 */
    bool can_control_;

    /** 吹っ飛びX成分 */
    int blown_veloX_;
    /** 吹っ飛びY成分 */
    int blown_veloY_;
    /** 吹っ飛びZ成分 */
    int blown_veloZ_;

    /** 吹っ飛び減衰率 */
    double r_blown_velo_decay_;

    /** MP */
    int mp_;

    int invincible_frames_;

    /** 魔法メーター */
    MagicMeter* pMagicMeter_;
    /** オプショントレース→自機停止の際に、自動的にオプションが巻き戻るまでの猶予による停止中true */
    bool is_trace_waiting_;
    /** is_trace_waiting_のフラグを切り替えるための時間カウンタ */
    frame trace_delay_count_;


    int shot_level_;

    /** SHOT1+SHOT2同時押しの武器のカウンター */
    int center_wepon_launch_count_;


    coord prev_x_;
    coord prev_y_;
    coord prev_z_;
    coord mv_offset_x_;
    coord mv_offset_y_;
    coord mv_offset_z_;
    bool is_move_;

public:
    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;
    void onInactive() override;
    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    /**
     * 移動方向の状態を更新 .
     * 入力方向に応じて mv_way_, mv_way_sgn_x_, mv_way_sgn_y_, mv_way_sgn_z_,is_just_change_mv_way_の状態を更新します .
     */
    void updateMoveWay();
    dir26 getMoveWay() {
        return mv_way_;
    }

    void setMoveSpeed(velo prm_speed_velo);

    void moveNomal();

    void moveTurbo();


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    /**
     * 自機吹っ飛び .
     * @param prm_blown_veloX X方向吹っ飛び速度
     * @param prm_blown_veloY Y方向吹っ飛び速度
     * @param prm_blown_veloZ Z方向吹っ飛び速度
     * @param prm_r_blown_velo_attenuate 吹っ飛び減衰率
     */
    void setBlownVelo(velo prm_blown_veloX, velo prm_blown_veloY, velo prm_blown_veloZ, double prm_r_blown_velo_attenuate);
    /**
     * 自機無敵設定 .
     * @param prm_frames 無敵時間(フレーム)
     */
    void setInvincibleFrames(int prm_frames);

    /**
     * 自機が操作可能な状態かどうか 。
     * @return
     */
    inline bool canControl() {
        return can_control_;
    }

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

