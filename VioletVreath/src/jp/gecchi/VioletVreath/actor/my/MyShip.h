#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace VioletVreath {

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0
//Ternary numeral -1,0.1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ
#define TN(X,Y,Z) (((3*3)*(X+1)) + ((3)*(Y+1)) + (Z+1))

#define EQ_OPTION 1
#define EQ_MAX_OPTION 0
/** ソフト連射数 */
#define SOFT_RAPIDSHOT_NUM 3
/** ソフト連射間隔 */
#define SOFT_RAPIDSHOT_INTERVAL 4

#define MY_SHIP_VREATH_COST (500)
//無呼吸時 1000000/500/60 = 約33.3秒で死ぬ
/**
 * 自機クラス
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
class MyShip : public GgafLib::DefaultD3DXMeshActor {
//class MyShip : public GgafLib::DefaultMeshActor {
//class MyShip : public GgafLib::CubeMapMeshActor {
//class MyShip : public GgafLib::DefaultD3DXAniMeshActor {
public:
    enum Switch {
        SW_ADD = 1,
        SW_NOP = 0,
        SW_SUB = -1
    };

    enum MoveWay {
        WAY_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
        WAY_DOWN_BEHIND,              //1    TN(-1,-1, 0)
        WAY_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
        WAY_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
        WAY_BEHIND,                   //4    TN(-1, 0, 0)
        WAY_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
        WAY_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
        WAY_UP_BEHIND,                //7    TN(-1, 1, 0)
        WAY_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
        WAY_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
        WAY_DOWN,                     //10   TN( 0,-1, 0)
        WAY_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
        WAY_ZRIGHT,                   //12   TN( 0, 0,-1)
        WAY_NONE,                     //13   TN( 0, 0, 0)
        WAY_ZLEFT,                    //14   TN( 0, 0, 1)
        WAY_ZRIGHT_UP,                //15   TN( 0, 1,-1)
        WAY_UP,                       //16   TN( 0, 1, 0)
        WAY_ZLEFT_UP,                 //17   TN( 0, 1, 1)
        WAY_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
        WAY_DOWN_FRONT,               //19   TN( 1,-1, 0)
        WAY_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
        WAY_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
        WAY_FRONT,                    //22   TN( 1, 0, 0)
        WAY_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
        WAY_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
        WAY_UP_FRONT,                 //25   TN( 1, 1, 0)
        WAY_ZLEFT_UP_FRONT            //26   TN( 1, 1, 1)
    };

    enum {
        SE_DAMAGED = 0,
        SE_FIRE_LASER,
        SE_FIRE_SHOT,
        SE_FIRE_TORPEDO,
    };

    class MyShipWaySwitch {
    public :
        class SW {
            public:
            int X, Y, Z;
            SW() { X = Y = Z = SW_NOP; }
        };
        bool sw_UP_, sw_LEFT_, sw_RIGHT_, sw_DOWN_;
        SW on_UP_, on_LEFT_, on_RIGHT_, on_DOWN_;

        /** 現在の方向 */
        SW way_;
        MyShipWaySwitch() {
            way_.X = way_.Y = way_.Z = SW_NOP;
            sw_UP_ = sw_LEFT_ = sw_RIGHT_ = sw_DOWN_ = false;
        }

        void reset() {
            way_.X = way_.Y = way_.Z = SW_NOP;
            sw_UP_ = sw_LEFT_ = sw_RIGHT_ = sw_DOWN_ = false;
        }
        inline void ON_UP(Switch swX, Switch swY, Switch swZ) {
            if (!sw_UP_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_UP_.X = swX;
                on_UP_.Y = swY;
                on_UP_.Z = swZ;
                sw_UP_ = true;
            }
        }
        inline void ON_LEFT(Switch swX, Switch swY, Switch swZ) {
            if (!sw_LEFT_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_LEFT_.X = swX;
                on_LEFT_.Y = swY;
                on_LEFT_.Z = swZ;
                sw_LEFT_ = true;
            }
        }
        inline void ON_RIGHT(Switch swX, Switch swY, Switch swZ) {
            if (!sw_RIGHT_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_RIGHT_.X = swX;
                on_RIGHT_.Y = swY;
                on_RIGHT_.Z = swZ;
                sw_RIGHT_ = true;
            }
        }
        inline void ON_DOWN(Switch swX, Switch swY, Switch swZ) {
            if (!sw_DOWN_) {
                way_.X += swX;
                way_.Y += swY;
                way_.Z += swZ;
                on_DOWN_.X = swX;
                on_DOWN_.Y = swY;
                on_DOWN_.Z = swZ;
                sw_DOWN_ = true;
            }
        }
        inline void OFF_UP() {
            if (sw_UP_) {
                way_.X -= on_UP_.X;
                way_.Y -= on_UP_.Y;
                way_.Z -= on_UP_.Z;
                sw_UP_ = false;
            }
        }
        inline void OFF_RIGHT() {
            if (sw_RIGHT_) {
                way_.X -= on_RIGHT_.X;
                way_.Y -= on_RIGHT_.Y;
                way_.Z -= on_RIGHT_.Z;
                sw_RIGHT_ = false;
            }
        }
        inline void OFF_LEFT() {
            if (sw_LEFT_) {
                way_.X -= on_LEFT_.X;
                way_.Y -= on_LEFT_.Y;
                way_.Z -= on_LEFT_.Z;
                sw_LEFT_ = false;
            }
        }
        inline void OFF_DOWN() {
            if (sw_DOWN_) {
                way_.X -= on_DOWN_.X;
                way_.Y -= on_DOWN_.Y;
                way_.Z -= on_DOWN_.Z;
                sw_DOWN_ = false;
            }
        }
        inline int getIndex() {
            //3進数→10進数変換
            //_TRACE_("way_.X, way_.Y, way_.Z="<<way_.X<<","<<way_.Y<<","<< way_.Z);
            return (3*3*(SGN(way_.X)+1)) + (3*(SGN(way_.Y)+1)) + (SGN(way_.Z)+1);
        }
    };
public:
    /** 移動Y座標上限 */
    static coord lim_top_;
    /** 移動Y座標下限 */
    static coord lim_bottom_;
    /** 移動X座標上限 */
    static coord lim_front_;
    /** 移動X座標下限 */
    static coord lim_behaind_;
    /** 移動Z座標上限 */
    static coord lim_zleft_;
    /** 移動Z座標下限 */
    static coord lim_zright_;

    MyShipWaySwitch way_switch_;
    void (MyShip::*paFuncMove[3*3*3])();
    void (MyShip::*paFuncTurbo[3*3*3])();

    /** [r]ロックオンコントローラー */
    MyLockonController* pLockonCtrler_;
    /** [r]魚雷コントローラー */
    MyTorpedoController* pTorpedoCtrler_;
    /** 方向入力値 */
    int stc_;

    /** ターボ中、移動方角 */
    MoveWay way_;
    MoveWay prev_way_;
    bool is_just_change_way_;
    /** 移動スピードレベルに相応する移動スピード */
    int iMoveSpeed_;

    velo veloTurboTop_;
    velo veloTurboBottom_;

    /** Turbo移動開始時の移動速度の初速度 */
    velo veloBeginMT_; //Move Velo when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** Turbo移動中の移動速度の加速度 */
    acce acce_MT_; //Move Acce while I Move with Turbo
    //但し 値 < 0 であること。 ∵だんだん遅くなるようにしたいから
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動中の移動速度の最低速度 */
    velo iMvBtmVelo_MT_; //Move Bottom Velo while I Move with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動が終了と判断される移動速度 */
//    velo veloFMT_; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** 奥(+Z)又は手前(-Z)へ通常移動開始時のX軸回転角速度の初速度 */
    angvelo angRXVelo_BeginMZ_; //Rotation axisX angle Velo when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常移動中のX軸回転角速度の角加速度 */
    angacce angRXAcce_MZ_; //Rotation axisX angle Acce while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ移動中のX軸回転角速度の上限角速度 */
    angvelo angRXTopVelo_MZ_; //Rotation axisX Top angle Velo while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常Z移動中のX軸回転角の停止角度 */
    angle angRXStop_MZ_; //Rotation axisX Stop angle while I Move Z


    /** 上(+Y)又は下(-Y)へTurbo移動開始時のZ軸回転角速度の初速度 */
    angvelo angRXVelo_BeginMZT_; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_MyShipGeoHistory4OptCtrler_;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_MyShipGeoHistory2_;
    GgafCore::GgafActorDepository* pDepo_MyShots001_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    EffectTurbo001* pEffectTurbo001_;

//    //debug ---->
//    GgafCore::GgafActorDepository* pDepo_TestGuShot_;
//    GgafCore::GgafActorDepository* pDepo_TestChokiShot_;
//    GgafCore::GgafActorDepository* pDepo_TestPaShot_;
//    GgafCore::GgafActorDepository* pDepo_TestNomalShot_;
//    //<---- debug

    /** ソフト連射開始からの経過フレーム数 */
    frame frame_soft_rapidshot_;
    /** ソフト連射中であるか否か */
    bool is_being_soft_rapidshot_;
    /** ショットしたフレームのみ true になる */
    bool just_shot_;
    /** レーザー発射かどうか */
    bool is_shooting_laser_;
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
    double r_blown_velo_attenuate_;

    /** MP */
    GgafLib::AmountGraph mp_;
    /** Vreath */
    GgafLib::AmountGraph vreath_;

    int invincible_frames_;

    /** 魔法メーター */
    MagicMeter* pMagicMeter_;


public:
    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;
    void onInactive() override;
    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void setMoveSpeedLv(int lv);

    //画面手前へ移動初めX軸回転処理

    void doNotingMoveInput();

    static angle wk_dist, wk_angRx;
    void move_WAY_NONE();
    /**
     * 上移動
     */
    void move_WAY_UP();
    /**
     * 前方斜め上移動
     */
    void move_WAY_UP_FRONT();
    /**
     * 後方斜め上移動
     */
    void move_WAY_UP_BEHIND();
    /**
     * 前移動
     */
    void move_WAY_FRONT();
    /**
     * 後ろ移動
     */
    void move_WAY_BEHIND();
    /**
     * 下移動
     */
    void move_WAY_DOWN();
    /**
     * 後方斜め下移動
     */
    void move_WAY_DOWN_BEHIND();
    /**
     * 前方斜め下移動
     */
    void move_WAY_DOWN_FRONT();
    /**
     * 左移動
     */
    void move_WAY_ZLEFT();
    /**
     * 前方斜め左移動
     */
    void move_WAY_ZLEFT_FRONT();
    /**
     * 後方斜め左移動
     */
    void move_WAY_ZLEFT_BEHIND();
    /**
     * 前方斜め右移動
     */
    void move_WAY_ZRIGHT_FRONT();
    /**
     * 右移動
     */
    void move_WAY_ZRIGHT();
    /**
     * 後方斜め右
     */
    void move_WAY_ZRIGHT_BEHIND();
    /**
     * 左斜め上移動
     */
    void move_WAY_ZLEFT_UP();
    /**
     * 左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN();
    /**
     * 右斜め上移動
     */
    void move_WAY_ZRIGHT_UP();
    /**
     * 右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN();
    /**
     * 前方左斜め上移動
     */
    void move_WAY_ZLEFT_UP_FRONT();
    /**
     * 後方左斜め上移動
     */
    void move_WAY_ZLEFT_UP_BEHIND();
    /**
     * 前方左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN_FRONT();

    /**
     * 後方左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN_BEHIND();

    /**
     * 前方右斜め上移動
     */
    void move_WAY_ZRIGHT_UP_FRONT();
    /**
     * 後方右斜め上移動
     */
    void move_WAY_ZRIGHT_UP_BEHIND();
    /**
     * 前方右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN_FRONT();
    /**
     * 後方右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN_BEHIND();

    /////////////////TURBO_BEGIN

    void turbo_WAY_NONE();
    /**
     * 上ターボ開始
     */
    void turbo_WAY_UP();
    /**
     * 前方斜め上ターボ開始
     */
    void turbo_WAY_UP_FRONT();
    /**
     * 後方斜め上ターボ開始
     */
    void turbo_WAY_UP_BEHIND();
    /**
     * 前ターボ開始
     */
    void turbo_WAY_FRONT();
    /**
     * 後ろターボ開始
     */
    void turbo_WAY_BEHIND();
    /**
     * 下ターボ開始
     */
    void turbo_WAY_DOWN();
    /**
     * 後方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_BEHIND();
    /**
     * 前方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_FRONT();
    /**
     * 左ターボ開始
     */
    void turbo_WAY_ZLEFT();
    /**
     * 前方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_FRONT();
    /**
     * 後方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_BEHIND();
    /**
     * 前方斜め右ターボ開始
     */
    void turbo_WAY_ZRIGHT_FRONT();
    /**
     * 右ターボ開始
     */
    void turbo_WAY_ZRIGHT();
    /**
     * 後方斜め右
     */
    void turbo_WAY_ZRIGHT_BEHIND();
    /**
     * 左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP();
    /**
     * 左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN();
    /**
     * 右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP();
    /**
     * 右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN();
    /**
     * 前方左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP_FRONT();
    /**
     * 後方左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP_BEHIND();
    /**
     * 前方左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN_FRONT();
    /**
     * 後方左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN_BEHIND();
    /**
     * 前方右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP_FRONT();
    /**
     * 後方右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP_BEHIND();
    /**
     * 前方右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN_FRONT();
    /**
     * 後方右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN_BEHIND();

    void onChangeWay(MoveWay prev_way, MoveWay new_way) {

        switch(new_way) {
            case 0: {
                break;
            }
            default:
                break;
        }

    }

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
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

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

