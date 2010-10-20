#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace MyStg2nd {

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0
//Ternary numeral -1,0.1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ
#define TN(X,Y,Z) (((3*3)*(X+1)) + ((3)*(Y+1)) + (Z+1))

#define EQ_OPTION 1
#define EQ_MAX_OPTION 0



enum Switch {
    SW_ADD = 1,
    SW_NOP = 0,
    SW_SUB = -1
};

/**
 * 自機クラス
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyShip : public GgafDx9LibStg::DefaultD3DXMeshActor {
class MyShip : public GgafDx9LibStg::DefaultMeshActor {
//class MyShip : public GgafDx9LibStg::DefaultD3DXAniMeshActor {


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






    class WaySwitch {
    public :
        class SW {
            public:
            int X, Y, Z;
            SW() { X = Y = Z = SW_NOP; }
        };
        bool _sw_UP, _sw_LEFT, _sw_RIGHT, _sw_DOWN;
        SW _on_UP, _on_LEFT, _on_RIGHT, _on_DOWN;

        /** 現在の方向 */
        SW _way;



        WaySwitch() {
            _way.X = _way.Y = _way.Z = SW_NOP;
            _sw_UP = _sw_LEFT = _sw_RIGHT = _sw_DOWN = false;


        }
        void ON_UP(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_UP) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_UP.X = swX;
                _on_UP.Y = swY;
                _on_UP.Z = swZ;
                _sw_UP = true;
            }
        }
        void ON_LEFT(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_LEFT) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_LEFT.X = swX;
                _on_LEFT.Y = swY;
                _on_LEFT.Z = swZ;
                _sw_LEFT = true;
            }
        }
        void ON_RIGHT(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_RIGHT) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_RIGHT.X = swX;
                _on_RIGHT.Y = swY;
                _on_RIGHT.Z = swZ;
                _sw_RIGHT = true;
            }
        }
        void ON_DOWN(Switch swX, Switch swY, Switch swZ) {
            if (!_sw_DOWN) {
                _way.X += swX;
                _way.Y += swY;
                _way.Z += swZ;
                _on_DOWN.X = swX;
                _on_DOWN.Y = swY;
                _on_DOWN.Z = swZ;
                _sw_DOWN = true;
            }
        }
        void OFF_UP() {
            if (_sw_UP) {
                _way.X -= _on_UP.X;
                _way.Y -= _on_UP.Y;
                _way.Z -= _on_UP.Z;
                _sw_UP = false;
            }
        }
        void OFF_RIGHT() {
            if (_sw_RIGHT) {
                _way.X -= _on_RIGHT.X;
                _way.Y -= _on_RIGHT.Y;
                _way.Z -= _on_RIGHT.Z;
                _sw_RIGHT = false;
            }
        }
        void OFF_LEFT() {
            if (_sw_LEFT) {
                _way.X -= _on_LEFT.X;
                _way.Y -= _on_LEFT.Y;
                _way.Z -= _on_LEFT.Z;
                _sw_LEFT = false;
            }
        }
        void OFF_DOWN() {
            if (_sw_DOWN) {
                _way.X -= _on_DOWN.X;
                _way.Y -= _on_DOWN.Y;
                _way.Z -= _on_DOWN.Z;
                _sw_DOWN = false;
            }
        }
        int getIndex() {
            //3進数→10進数変換
            //_TRACE_("_way.X, _way.Y, _way.Z="<<_way.X<<","<<_way.Y<<","<< _way.Z);
            return (3*3*(sgn(_way.X)+1)) + (3*(sgn(_way.Y)+1)) + (sgn(_way.Z)+1);
        }
    };
public:
    /** 移動Y座標上限 */
    static int _lim_top;
    /** 移動Y座標下限 */
    static int _lim_bottom;
    /** 移動X座標上限 */
    static int _lim_front;
    /** 移動X座標下限 */
    static int _lim_behaind;
    /** 移動Z座標上限 */
    static int _lim_zleft;
    /** 移動Z座標下限 */
    static int _lim_zright;

    WaySwitch _way_switch;
    void (MyShip::*paFuncMove[3*3*3])();
    void (MyShip::*paFuncTurbo[3*3*3])();

//    void (MyShip::*fpaFunc[])() =  {
//          move_WAY_UP,
//          move_WAY_UP_FRONT
//    };




    /** 方向入力値 */
    int _stc;

    /** ターボ中、移動方角 */
    MoveWay _way;

    /** 移動スピードレベル */
    int _lv_MoveSpeed;
    /** 移動スピードレベルに相応する移動スピード */
    int _iMoveSpeed;

    int _iMoveVelo;


    int _iMvVelo_TurboTop;
    int _iMvVelo_TurboBottom;

    /** Turbo移動開始時の移動速度の初速度 */
    int _iMvVelo_BeginMT; //Move Velo when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** Turbo移動中の移動速度の加速度 */
    int _iMvAcce_MT; //Move Acce while I Move with Turbo
    //但し 値 < 0 であること。 ∵だんだん遅くなるようにしたいから
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動中の移動速度の最低速度 */
    int _iMvBtmVelo_MT; //Move Bottom Velo while I Move with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動が終了と判断される移動速度 */
    int _iMvVelo_FMT; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** 奥又は手前へ通常移動開始時のX軸回転角速度の初速度 */
    angle _angRXVelo_BeginMZ; //Rotation axisX angle Velo when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥又は手前へ通常移動中のX軸回転角速度の角加速度 */
    angle _angRXAcce_MZ; //Rotation axisX angle Acce while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥又は手前へ移動中のX軸回転角速度の上限角速度 */
    angle _angRXTopVelo_MZ; //Rotation axisX Top angle Velo while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥又は手前へ通常Z移動中のX軸回転角の停止角度 */
    angle _angRXStop_MZ; //Rotation axisX Stop angle while I Move Z


    /** 上又は下へTurbo移動開始時のZ軸回転角速度の初速度 */
    angle _angRXVelo_BeginMZT; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる

    State _state;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

    GgafCore::GgafActorDispatcher* _pDispatcher_MyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion001;
    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;

    MyOptionController* _pMyOptionController;
    EffectTurbo001* _pEffectTurbo001;

    /** ソフト連射開始からの経過フレーム数 */
    frame _frame_soft_rapidshot;
    /** ソフト連射中であるか否か */
    boolean _is_being_soft_rapidshot;
    /** ショットしたフレームのみ true になる */
    boolean _just_shot;
    /** レーザー発射かどうか */
    boolean _is_shooting_laser;
    /** SHOTボタン押しっぱなし経過フレーム数（レーザー発射開始判定のため） */
    frame _frame_shot_pressed;

    MyShip(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;
    /**
     *
     * 自機がアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    /**
     * ＜OverRide です＞
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void setMoveSpeedLv(int lv) {
        _lv_MoveSpeed = lv;
        _iMoveSpeed = _lv_MoveSpeed * 1000;
    }

    //画面手前へ移動初めX軸回転処理

    void doNotingMoveInput();

    static angle wk_dist, wk_angRx;
    void move_WAY_NONE() {
        //_way = WAY_NONE;
        _iMoveVelo = 0;
    }
    /**
     * 上移動
     */
    void move_WAY_UP() {
        _pMover->setRzRyMvAng(ANGLE90, 0);
        _Y += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 前方斜め上移動
     */
    void move_WAY_UP_FRONT() {
        _pMover->setRzRyMvAng(ANGLE45, 0);
        _Y += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 後方斜め上移動
     */
    void move_WAY_UP_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE135, 0);
        _Y += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 前移動
     */
    void move_WAY_FRONT() {
        _pMover->setRzRyMvAng(0, 0);
        _X += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 後ろ移動
     */
    void move_WAY_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE180, 0);
        _X -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 下移動
     */
    void move_WAY_DOWN() {
        _pMover->setRzRyMvAng(ANGLE270, 0);
        _Y -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 後方斜め下移動
     */
    void move_WAY_DOWN_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE225, 0);
        _Y -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 前方斜め下移動
     */
    void move_WAY_DOWN_FRONT() {
        _pMover->setRzRyMvAng(ANGLE315, 0);
        _Y -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 左移動
     */
    void move_WAY_ZLEFT() {
        _pMover->setRzRyMvAng(0, ANGLE270);
        _Z += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
        _pMover->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 前方斜め左移動
     */
    void move_WAY_ZLEFT_FRONT() {
        _pMover->setRzRyMvAng(0, ANGLE315);
        _Z += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2)); //反時計回り
        _pMover->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 後方斜め左移動
     */
    void move_WAY_ZLEFT_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE180, ANGLE45);
        _Z += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2));
        _pMover->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 前方斜め右移動
     */
    void move_WAY_ZRIGHT_FRONT() {
        _pMover->setRzRyMvAng(ANGLE180, ANGLE135);
        _Z -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
        _pMover->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 右移動
     */
    void move_WAY_ZRIGHT() {
        _pMover->setRzRyMvAng(0, ANGLE90);
        _Z -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
        _pMover->setStopTarget_FaceAng(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 後方斜め右
     */
    void move_WAY_ZRIGHT_BEHIND() {
        _pMover->setRzRyMvAng(0, ANGLE135);
        _Z -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
        _pMover->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 左斜め上移動
     */
    void move_WAY_ZLEFT_UP() {
        _pMover->setRzRyMvAng(ANGLE45, ANGLE270);
        _Z += _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
        _pMover->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN() {
        _pMover->setRzRyMvAng(ANGLE315, ANGLE270);
        _Z += _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ/2);
        _pMover->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 右斜め上移動
     */
    void move_WAY_ZRIGHT_UP() {
        _pMover->setRzRyMvAng(ANGLE45, ANGLE90);
        _Z -= _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
        _pMover->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    /**
     * 右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN() {
        _pMover->setRzRyMvAng(ANGLE315, ANGLE90);
        _Z -= _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
        //旋廻
        _pMover->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
        _pMover->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
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
        _pMover->setRzRyMvAng(ANGLE90, 0);
        _pMover->addVyMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * 前方斜め上ターボ開始
     */
    void turbo_WAY_UP_FRONT() {
        _pMover->setRzRyMvAng(ANGLE45, 0);
        _pMover->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 後方斜め上ターボ開始
     */
    void turbo_WAY_UP_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE135, 0);
        _pMover->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 前ターボ開始
     */
    void turbo_WAY_FRONT() {
        _pMover->setRzRyMvAng(0, 0);
        _pMover->addVxMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * 後ろターボ開始
     */
    void turbo_WAY_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE180, 0);
        _pMover->addVxMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * 下ターボ開始
     */
    void turbo_WAY_DOWN() {
        _pMover->setRzRyMvAng(ANGLE270, 0);
        _pMover->addVyMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * 後方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE225, 0);
        _pMover->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 前方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_FRONT() {
        _pMover->setRzRyMvAng(ANGLE315, 0);
        _pMover->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 左ターボ開始
     */
    void turbo_WAY_ZLEFT() {
        _pMover->addVzMvVelo(_iMvVelo_BeginMT);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
    }
    /**
     * 前方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_FRONT() {
        _pMover->setRzRyMvAng(0, ANGLE270);
        _pMover->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 後方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_BEHIND() {
        _pMover->setRzRyMvAng(ANGLE180, ANGLE45);
        _pMover->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 前方斜め右ターボ開始
     */
    void turbo_WAY_ZRIGHT_FRONT() {
        _pMover->setRzRyMvAng(ANGLE180, ANGLE135);
        _pMover->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右ターボ開始
     */
    void turbo_WAY_ZRIGHT() {
        _pMover->setRzRyMvAng(0, ANGLE90);
        _pMover->addVzMvVelo(-_iMvVelo_BeginMT);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT); //勢いよく回転開始
    }
    /**
     * 後方斜め右
     */
    void turbo_WAY_ZRIGHT_BEHIND() {
        _pMover->setRzRyMvAng(0, ANGLE135);
        _pMover->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP() {
        _pMover->setRzRyMvAng(ANGLE45, ANGLE270);
        _pMover->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN() {
        _pMover->setRzRyMvAng(ANGLE315, ANGLE270);
        _pMover->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pMover->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP() {
        _pMover->setRzRyMvAng(ANGLE45, ANGLE90);
        _pMover->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN() {
        _pMover->setRzRyMvAng(ANGLE315, ANGLE90);
        _pMover->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pMover->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pMover->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
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




    static void transactShot(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);

    /**オプション追加*/
    void equipOption();

    virtual ~MyShip();

    static bool isDoublePushedDown(vbsta prm_VB);






};

}
#endif /*MYSHIP_H_*/

