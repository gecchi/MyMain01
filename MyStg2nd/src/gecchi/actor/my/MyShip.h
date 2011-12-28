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
        bool _sw_UP, _sw_LEFT, _sw_RIGHT, _sw_DOWN;
        SW _on_UP, _on_LEFT, _on_RIGHT, _on_DOWN;

        /** 現在の方向 */
        SW _way;



        MyShipWaySwitch() {
            _way.X = _way.Y = _way.Z = SW_NOP;
            _sw_UP = _sw_LEFT = _sw_RIGHT = _sw_DOWN = false;
        }

        void reset() {
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
    static coord _lim_top;
    /** 移動Y座標下限 */
    static coord _lim_bottom;
    /** 移動X座標上限 */
    static coord _lim_front;
    /** 移動X座標下限 */
    static coord _lim_behaind;
    /** 移動Z座標上限 */
    static coord _lim_zleft;
    /** 移動Z座標下限 */
    static coord _lim_zright;

    MyShipWaySwitch _way_switch;
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
    MoveWay _prev_way;
    bool _is_just_change_way;
    /** 移動スピードレベルに相応する移動スピード */
    int _iMoveSpeed;

    velo _iMoveVelo;


    velo _iMvVelo_TurboTop;
    velo _iMvVelo_TurboBottom;

    /** Turbo移動開始時の移動速度の初速度 */
    velo _iMvVelo_BeginMT; //Move Velo when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** Turbo移動中の移動速度の加速度 */
    acce _iMvAcce_MT; //Move Acce while I Move with Turbo
    //但し 値 < 0 であること。 ∵だんだん遅くなるようにしたいから
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動中の移動速度の最低速度 */
    velo _iMvBtmVelo_MT; //Move Bottom Velo while I Move with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動が終了と判断される移動速度 */
    velo _iMvVelo_FMT; //Rotation axisX angle Velo when I Finish Moveing with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** 奥(+Z)又は手前(-Z)へ通常移動開始時のX軸回転角速度の初速度 */
    ang_velo _angRXVelo_BeginMZ; //Rotation axisX angle Velo when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常移動中のX軸回転角速度の角加速度 */
    ang_acce _angRXAcce_MZ; //Rotation axisX angle Acce while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ移動中のX軸回転角速度の上限角速度 */
    ang_velo _angRXTopVelo_MZ; //Rotation axisX Top angle Velo while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥(+Z)又は手前(-Z)へ通常Z移動中のX軸回転角の停止角度 */
    angle _angRXStop_MZ; //Rotation axisX Stop angle while I Move Z


    /** 上(+Y)又は下(-Y)へTurbo移動開始時のZ軸回転角速度の初速度 */
    ang_velo _angRXVelo_BeginMZT; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる




    State _state;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* _pRing_GeoHistory;

    GgafCore::GgafActorDepository* _pDepo_MyShots001;
    GgafCore::GgafActorDepository* _pDP_EffectExplosion001;
    GgafLib::LaserChipDepository* _pLaserChipDepo;

//    MyOptionController* _pMyOptionController;
    EffectTurbo001* _pEffectTurbo001;

    /** ソフト連射開始からの経過フレーム数 */
    frame _frame_soft_rapidshot;
    /** ソフト連射中であるか否か */
    bool _is_being_soft_rapidshot;
    /** ショットしたフレームのみ true になる */
    bool _just_shot;
    /** レーザー発射かどうか */
    bool _is_shooting_laser;
    /** SHOTボタン押しっぱなし経過フレーム数（レーザー発射開始判定のため） */
    frame _frame_shot_pressed;

    /** シーン突入時かどうか */
    bool _is_diving;

    /** 操作可否 */
    bool _can_control;

    /** 吹っ飛びX成分 */
    int _blown_veloX;
    /** 吹っ飛びY成分 */
    int _blown_veloY;
    /** 吹っ飛びZ成分 */
    int _blown_veloZ;
    /** 吹っ飛びを抑える力 */
    int _anti_blown_velo;

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
        //_way = WAY_NONE;
        _iMoveVelo = 0;
    }
    /**
     * 上移動
     */
    void move_WAY_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D90ANG, 0);
        }
        _Y += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 前方斜め上移動
     */
    void move_WAY_UP_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, 0);
        }
        _Y += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 後方斜め上移動
     */
    void move_WAY_UP_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D135ANG, 0);
        }
        _Y += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 前移動
     */
    void move_WAY_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, 0);
        }
        _X += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 後ろ移動
     */
    void move_WAY_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, 0);
        }
        _X -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 下移動
     */
    void move_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _Y -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 後方斜め下移動
     */
    void move_WAY_DOWN_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D255ANG, 0);
        }
        _Y -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 前方斜め下移動
     */
    void move_WAY_DOWN_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, 0);
        }
        _Y -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 左移動
     */
    void move_WAY_ZLEFT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 前方斜め左移動
     */
    void move_WAY_ZLEFT_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D315ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2)); //反時計回り
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 後方斜め左移動
     */
    void move_WAY_ZLEFT_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, (_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 前方斜め右移動
     */
    void move_WAY_ZRIGHT_FRONT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 右移動
     */
    void move_WAY_ZRIGHT() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed;
        _iMoveVelo = _iMoveSpeed;
    }
    /**
     * 後方斜め右
     */
    void move_WAY_ZRIGHT_BEHIND() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(0, D135ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 左斜め上移動
     */
    void move_WAY_ZLEFT_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ - (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z += _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 左斜め下移動
     */
    void move_WAY_ZLEFT_DOWN() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, _angRXAcce_MZ/2);
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, _angRXStop_MZ + (_angRXStop_MZ/2), TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);

        }
        _Z += _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 右斜め上移動
     */
    void move_WAY_ZRIGHT_UP() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ - (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
    }
    /**
     * 右斜め下移動
     */
    void move_WAY_ZRIGHT_DOWN() {
        if (_is_just_change_way) {
            _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
            //旋廻
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*(_angRXAcce_MZ/2));
            _pKurokoA->setStopTarget_FaceAng(AXIS_X, -1*(_angRXStop_MZ + (_angRXStop_MZ/2)), TURN_CLOCKWISE, _angRXTopVelo_MZ);
        }
        _Z -= _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        _iMoveVelo = _iMoveSpeed * NANAME;
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
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * 前方斜め上ターボ開始
     */
    void turbo_WAY_UP_FRONT() {
        _pKurokoA->setRzRyMvAng(D45ANG, 0);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 後方斜め上ターボ開始
     */
    void turbo_WAY_UP_BEHIND() {
        _pKurokoA->setRzRyMvAng(D135ANG, 0);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 前ターボ開始
     */
    void turbo_WAY_FRONT() {
        _pKurokoA->setRzRyMvAng(0, 0);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT);
    }
    /**
     * 後ろターボ開始
     */
    void turbo_WAY_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, 0);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * 下ターボ開始
     */
    void turbo_WAY_DOWN() {
        _pKurokoA->setRzRyMvAng(D270ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT);
    }
    /**
     * 後方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_BEHIND() {
        _pKurokoA->setRzRyMvAng(D255ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 前方斜め下ターボ開始
     */
    void turbo_WAY_DOWN_FRONT() {
        _pKurokoA->setRzRyMvAng(D315ANG, 0);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
    }
    /**
     * 左ターボ開始
     */
    void turbo_WAY_ZLEFT() {
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
    }
    /**
     * 前方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_FRONT() {
        _pKurokoA->setRzRyMvAng(0, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 後方斜め左ターボ開始
     */
    void turbo_WAY_ZLEFT_BEHIND() {
        _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 前方斜め右ターボ開始
     */
    void turbo_WAY_ZRIGHT_FRONT() {
        _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右ターボ開始
     */
    void turbo_WAY_ZRIGHT() {
        _pKurokoA->setRzRyMvAng(0, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT); //勢いよく回転開始
    }
    /**
     * 後方斜め右
     */
    void turbo_WAY_ZRIGHT_BEHIND() {
        _pKurokoA->setRzRyMvAng(0, D135ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVxMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め上ターボ開始
     */
    void turbo_WAY_ZLEFT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 左斜め下ターボ開始
     */
    void turbo_WAY_ZLEFT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
        _pKurokoB->addVzMvVelo(_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, _angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め上ターボ開始
     */
    void turbo_WAY_ZRIGHT_UP() {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
    }
    /**
     * 右斜め下ターボ開始
     */
    void turbo_WAY_ZRIGHT_DOWN() {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
        _pKurokoB->addVzMvVelo(-_iMvVelo_BeginMT * NANAME);
        _pKurokoB->addVyMvVelo(-_iMvVelo_BeginMT * NANAME);
        //旋廻
        _pKurokoA->setFaceAngVelo(AXIS_X, -_angRXVelo_BeginMZT*NANAME); //勢いよく回転開始
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

