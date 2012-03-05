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

    class State {
    public:
        int eq_option;
        int eq_speed;
        int mp;
        State() {
            eq_option = 0;
            eq_speed = 1;
            mp = 10000;
        }

    };

    struct VERTEX {
        float x, y, z; // 頂点座標
        float nx, ny, nz; // 法線
        DWORD color; // 頂点の色
        float tu, tv; // テクスチャ座標
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
        void ON_UP(Switch swX, Switch swY, Switch swZ) {
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
        void ON_LEFT(Switch swX, Switch swY, Switch swZ) {
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
        void ON_RIGHT(Switch swX, Switch swY, Switch swZ) {
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
        void ON_DOWN(Switch swX, Switch swY, Switch swZ) {
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
        void OFF_UP() {
            if (sw_UP_) {
                way_.X -= on_UP_.X;
                way_.Y -= on_UP_.Y;
                way_.Z -= on_UP_.Z;
                sw_UP_ = false;
            }
        }
        void OFF_RIGHT() {
            if (sw_RIGHT_) {
                way_.X -= on_RIGHT_.X;
                way_.Y -= on_RIGHT_.Y;
                way_.Z -= on_RIGHT_.Z;
                sw_RIGHT_ = false;
            }
        }
        void OFF_LEFT() {
            if (sw_LEFT_) {
                way_.X -= on_LEFT_.X;
                way_.Y -= on_LEFT_.Y;
                way_.Z -= on_LEFT_.Z;
                sw_LEFT_ = false;
            }
        }
        void OFF_DOWN() {
            if (sw_DOWN_) {
                way_.X -= on_DOWN_.X;
                way_.Y -= on_DOWN_.Y;
                way_.Z -= on_DOWN_.Z;
                sw_DOWN_ = false;
            }
        }
        int getIndex() {
            //3進数→10進数変換
            //_TRACE_("way_.X, way_.Y, way_.Z="<<way_.X<<","<<way_.Y<<","<< way_.Z);
            return (3*3*(sgn(way_.X)+1)) + (3*(sgn(way_.Y)+1)) + (sgn(way_.Z)+1);
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

//    void (MyShip::*fpaFunc[])() =  {
//          move_WAY_UP,
//          move_WAY_UP_FRONT
//    };




    /** 方向入力値 */
    int stc_;

    /** ターボ中、移動方角 */
    MoveWay way_;
    MoveWay prev_way_;
    bool is_just_change_way_;
    /** 移動スピードレベルに相応する移動スピード */
    int iMoveSpeed_;

    velo iMoveVelo_;


    velo iMvVelo_TurboTop_;
    velo iMvVelo_TurboBottom_;

    /** Turbo移動開始時の移動速度の初速度 */
    velo iMvVelo_BeginMT_; //Move Velo when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** Turbo移動中の移動速度の加速度 */
    acce iMvAcce_MT_; //Move Acce while I Move with Turbo
    //但し 値 < 0 であること。 ∵だんだん遅くなるようにしたいから
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動中の移動速度の最低速度 */
    velo iMvBtmVelo_MT_; //Move Bottom Velo while I Move with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動が終了と判断される移動速度 */
    velo iMvVelo_FMT_; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** 奥(+Z)又は手前(-Z)へ通常移動開始時のX軸回転角速度の初速度 */
    ang_velo angRXVelo_BeginMZ_; //Rotation axisX angle Velo when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常移動中のX軸回転角速度の角加速度 */
    ang_acce angRXAcce_MZ_; //Rotation axisX angle Acce while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ移動中のX軸回転角速度の上限角速度 */
    ang_velo angRXTopVelo_MZ_; //Rotation axisX Top angle Velo while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常Z移動中のX軸回転角の停止角度 */
    angle angRXStop_MZ_; //Rotation axisX Stop angle while I Move Z


    /** 上(+Y)又は下(-Y)へTurbo移動開始時のZ軸回転角速度の初速度 */
    ang_velo angRXVelo_BeginMZT_; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる




    State state_;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_MyShipGeoHistory_;

    GgafCore::GgafActorDepository* pDepo_MyShots001_;
    GgafCore::GgafActorDepository* pDP_EffectExplosion001_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

//    MyOptionController* pMyOptionController_;
    EffectTurbo001* pEffectTurbo001_;

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
    /** 吹っ飛びを抑える力 */
    int anti_blown_velo_;

    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void setMoveSpeedLv(int lv);

    //画面手前へ移動初めX軸回転処理

    void doNotingMoveInput();

    static angle wk_dist, wk_angRx;
    void move_WAY_NONE() {
        //way_ = WAY_NONE;
        iMoveVelo_ = 0;
    }
    /**
     * 上移動
     */
    void move_WAY_UP() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D90ANG, 0);
        }
        _Y += iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 前方斜め上移動
     */
    void move_WAY_UP_FRONT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D45ANG, 0);
        }
        _Y += iMoveSpeed_ * NANAME;
        _X += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 後方斜め上移動
     */
    void move_WAY_UP_BEHIND() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D135ANG, 0);
        }
        _Y += iMoveSpeed_ * NANAME;
        _X -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 前移動
     */
    void move_WAY_FRONT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(0, 0);
        }
        _X += iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 後ろ移動
     */
    void move_WAY_BEHIND() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D180ANG, 0);
        }
        _X -= iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 下移動
     */
    void move_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _Y -= iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 後方斜め下移動
     */
    void move_WAY_DOWN_BEHIND() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D255ANG, 0);
        }
        _Y -= iMoveSpeed_ * NANAME;
        _X -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 前方斜め下移動
     */
    void move_WAY_DOWN_FRONT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D315ANG, 0);
        }
        _Y -= iMoveSpeed_ * NANAME;
        _X += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 左移動
     */
    void move_WAY_ZLEFT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(0, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, angRXStop_MZ_, TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z += iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 前方斜め左移動
     */
    void move_WAY_ZLEFT_FRONT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(0, D315ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2)); //反時計回り
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z += iMoveSpeed_ * NANAME;
        _X += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 後方斜め左移動
     */
    void move_WAY_ZLEFT_BEHIND() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z += iMoveSpeed_ * NANAME;
        _X -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 前方斜め右移動
     */
    void move_WAY_ZRIGHT_FRONT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z -= iMoveSpeed_ * NANAME;
        _X += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 右移動
     */
    void move_WAY_ZRIGHT() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(0, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*angRXStop_MZ_, TURN_CLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z -= iMoveSpeed_;
        iMoveVelo_ = iMoveSpeed_;
    }
    /**
     * 後方斜め右
     */
    void move_WAY_ZRIGHT_BEHIND() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(0, D135ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z -= iMoveSpeed_ * NANAME;
        _X -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 左斜め上移動
     */
    void move_WAY_ZLEFT_UP() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z += iMoveSpeed_ * NANAME;
        _Y += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/2);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);

        }
        _Z += iMoveSpeed_ * NANAME;
        _Y -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 右斜め上移動
     */
    void move_WAY_ZRIGHT_UP() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z -= iMoveSpeed_ * NANAME;
        _Y += iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN() {
        if (is_just_change_way_) {
            _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
        }
        _Z -= iMoveSpeed_ * NANAME;
        _Y -= iMoveSpeed_ * NANAME;
        iMoveVelo_ = iMoveSpeed_ * NANAME;
    }
    /**
     * 前方左斜め上移動
     */
    void move_WAY_ZLEFT_UP_FRONT() {
        _TRACE_("move_WAY_ZLEFT_UP_FRONTLEFT() came!");
    }
    /**
     * 後方左斜め上移動
     */
    void move_WAY_ZLEFT_UP_BEHIND() {
        _TRACE_("move_WAY_ZLEFT_UP_BEHINDLEFT() came!");
    }

    void move_WAY_ZLEFT_DOWN_FRONT() {
        _TRACE_("move_WAY_ZLEFT_DOWN_FRONTLEFT() came!");
    }

    void move_WAY_ZLEFT_DOWN_BEHIND() {
        _TRACE_("move_WAY_ZLEFT_DOWN_BEHINDLEFT() came!");
    }

    void move_WAY_ZRIGHT_UP_FRONT() {
        _TRACE_("move_WAY_ZRIGHT_UP_FRONTLEFT() came!");
    }

    void move_WAY_ZRIGHT_UP_BEHIND() {
        _TRACE_("move_WAY_ZRIGHT_UP_BEHINDLEFT() came!");
    }

    void move_WAY_ZRIGHT_DOWN_FRONT() {
        _TRACE_("move_WAY_ZRIGHT_DOWN_FRONTLEFT() came!");
    }

    void move_WAY_ZRIGHT_DOWN_BEHIND() {
        _TRACE_("move_WAY_ZRIGHT_DOWN_BEHIND() came!");
    }


    /////////////////TURBO_BEGIN

    void turbo_WAY_NONE() {

    }

    /**
     * 上ターボ開始
     */
    void turbo_WAY_UP() {
        _pKurokoA->setRzRyMvAng(D90ANG, 0);
        _pKurokoB->addVyMvVelo(iMvVelo_BeginMT_);
    }
    /**
     * 前方斜め上ターボ開始
     */
    void turbo_WAY_UP_FRONT() {
        _pKurokoA->setRzRyMvAng(D45ANG, 0);
        _pKurokoB->addVyMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(iMvVelo_BeginMT_ * NANAME);
    }
    /**
     * 後方斜め上ターボ開始
     */
    void turbo_WAY_UP_BEHIND() {
        _pKurokoA->setRzRyMvAng(D135ANG, 0);
        _pKurokoB->addVyMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(-iMvVelo_BeginMT_ * NANAME);
    }
    /**
     * 前ターボ開始
     */
    void turbo_WAY_FRONT() {
        _pKurokoA->setRzRyMvAng(0, 0);
        _pKurokoB->addVxMvVelo(iMvVelo_BeginMT_);
    }
    /**
     * 後ろターボ開始
     */
    void turbo_WAY_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, 0);
        _pKurokoB->addVxMvVelo(-iMvVelo_BeginMT_);
    }
    /**
     * 下ターボ開始
     */
    void turbo_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _pKurokoB->addVyMvVelo(-iMvVelo_BeginMT_);
    }
    /**
     * 後方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_BEHIND() {
        _pKurokoA->setRzRyMvAng(D255ANG, 0);
        _pKurokoB->addVyMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(-iMvVelo_BeginMT_ * NANAME);
    }
    /**
     * 前方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_FRONT() {
        _pKurokoA->setRzRyMvAng(D315ANG, 0);
        _pKurokoB->addVyMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(iMvVelo_BeginMT_ * NANAME);
    }
    /**
     * 左ターボ開始
     */
    void turbo_WAY_ZLEFT() {
        _pKurokoB->addVzMvVelo(iMvVelo_BeginMT_);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_); //勢いよく回転開始
    }
    /**
     * 前方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_FRONT() {
        _pKurokoA->setRzRyMvAng(0, D270ANG);
        _pKurokoB->addVzMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 後方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
        _pKurokoB->addVzMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(-iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 前方斜め右ターボ開始
     */
    void turbo_WAY_ZRIGHT_FRONT() {
        _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
        _pKurokoB->addVzMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 右ターボ開始
     */
    void turbo_WAY_ZRIGHT() {
        _pKurokoA->setRzRyMvAng(0, D90ANG);
        _pKurokoB->addVzMvVelo(-iMvVelo_BeginMT_);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_); //勢いよく回転開始
    }
    /**
     * 後方斜め右
     */
    void turbo_WAY_ZRIGHT_BEHIND() {
        _pKurokoA->setRzRyMvAng(0, D135ANG);
        _pKurokoB->addVzMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVxMvVelo(-iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
        _pKurokoB->addVzMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVyMvVelo(iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
        _pKurokoB->addVzMvVelo(iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVyMvVelo(-iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVyMvVelo(iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-iMvVelo_BeginMT_ * NANAME);
        _pKurokoB->addVyMvVelo(-iMvVelo_BeginMT_ * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME); //勢いよく回転開始
    }
    /**
     * 前方左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP_FRONT() {
        _TRACE_("turbo_WAY_ZLEFT_UP_FRONTLEFT() came!");
    }
    /**
     * 後方左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP_BEHIND() {
        _TRACE_("turbo_WAY_ZLEFT_UP_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZLEFT_DOWN_FRONT() {
        _TRACE_("turbo_WAY_ZLEFT_DOWN_FRONTLEFT() came!");
    }

    void turbo_WAY_ZLEFT_DOWN_BEHIND() {
        _TRACE_("turbo_WAY_ZLEFT_DOWN_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_UP_FRONT() {
        _TRACE_("turbo_WAY_ZRIGHT_UP_FRONTLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_UP_BEHIND() {
        _TRACE_("turbo_WAY_ZRIGHT_UP_BEHINDLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_DOWN_FRONT() {
        _TRACE_("turbo_WAY_ZRIGHT_DOWN_FRONTLEFT() came!");
    }

    void turbo_WAY_ZRIGHT_DOWN_BEHIND() {
        _TRACE_("turbo_WAY_ZRIGHT_DOWN_BEHIND() came!");
    }
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

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

