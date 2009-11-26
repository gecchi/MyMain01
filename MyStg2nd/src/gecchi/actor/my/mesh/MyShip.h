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
//1/√2
#define NANAME 0.7
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
//class MyShip : public GgafDx9LibStg::DefaultMeshActor {
class MyShip : public GgafDx9LibStg::DefaultD3DXAniMeshActor {


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


    WaySwitch _way_switch;
    void (MyShip::*fpaMoveFunc[3*3*3])();

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

    /** Turbo移動開始時の移動速度の初速度 */
    int _iMvVelo_BeginMT; //Move Velocity when I Begin To Move with Turbo
    //Z軸が絡む場合、うまくこの値から計算しよう（Z軸の移動速度は正負で管理してるため）

    /** Turbo移動中の移動速度の加速度 */
    int _iMvAcce_MT; //Move Acceleration while I Move with Turbo
    //但し 値 < 0 であること。 ∵だんだん遅くなるようにしたいから
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動中の移動速度の最低速度 */
    int _iMvBtmVelo_MT; //Move Bottom Velocity while I Move with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** Turbo移動が終了と判断される移動速度 */
    int _iMvVelo_FMT; //Rotation axisX angle Velocity when I Finish Moveing with Turbo
    //但し 値 < 0 であること。
    //これもZ軸が絡む場合、うまくこの値から計算しよう

    /** 奥又は手前へ通常移動開始時のX軸回転角速度の初速度 */
    GgafDx9Core::angle _angRXVelo_BeginMZ; //Rotation axisX angle Velocity when I Begin To Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥又は手前へ通常移動中のX軸回転角速度の角加速度 */
    GgafDx9Core::angle _angRXAcce_MZ; //Rotation axisX angle Acceleration while I Move Z
    //奥の場合は正、手前の場合はこれに -1 を乗ずる

    /** 奥又は手前へ移動中のX軸回転角速度の上限角速度 */
    GgafDx9Core::angle _angRXTopVelo_MZ; //Rotation axisX Top angle Velocity while I Move Z
    //下限角速度はこれに -1 を乗ずる

    /** 奥又は手前へ通常Z移動中のX軸回転角の停止角度 */
    GgafDx9Core::angle _angRXStop_MZ; //Rotation axisX Stop angle while I Move Z


    /** 上又は下へTurbo移動開始時のZ軸回転角速度の初速度 */
    GgafDx9Core::angle _angRXVelo_BeginMZT; //Rotation axisX angle Velocity when I Begin To Move Z with Turbo
    //上の場合は正、下の場合はこれに -1 を乗ずる



    State _state;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

    GgafDx9LibStg::ActorDispatcher* _pDispatcher_MyWaves001;
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_MyShots001;
//    GgafDx9LibStg::ActorDispatcher* _pLaserChipDispatcher;
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_EnemyShots001;
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_EffectExplosion001;
    LaserChipDispatcher* _pLaserChipDispatcher;

    MyShip(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    virtual void initialize();

    /**
     * ＜OverRide です＞
     */
    virtual void processBehavior();

    /**
     * ＜OverRide です＞
     */
    virtual void processJudgement();

    /**
     * ＜OverRide です＞
     */
    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual void setMoveSpeedLv(int lv) {
        _lv_MoveSpeed = lv;
        _iMoveSpeed = _lv_MoveSpeed * 1000;
    }

    //画面手前へ移動初めX軸回転処理
    virtual void beginTurboXY(GgafDx9LibStg::vbsta prm_VB);
    virtual void beginTurboZY(GgafDx9LibStg::vbsta prm_VB);
    virtual void beginTurboZX(GgafDx9LibStg::vbsta prm_VB);

    virtual void moveZY(GgafDx9LibStg::vbsta prm_VB);
    virtual void turnZY(GgafDx9LibStg::vbsta prm_VB);

    virtual void moveXY(GgafDx9LibStg::vbsta prm_VB);
    virtual void turnXY(GgafDx9LibStg::vbsta prm_VB);

    virtual void moveZX(GgafDx9LibStg::vbsta prm_VB);
    virtual void turnZX(GgafDx9LibStg::vbsta prm_VB);

    virtual void turnFaceXYMove(GgafDx9LibStg::vbsta prm_VB);
    virtual void turnFaceZYMove(GgafDx9LibStg::vbsta prm_VB);
    virtual void turnFaceZXMove(GgafDx9LibStg::vbsta prm_VB);

    virtual void doNotingMoveInput();

    virtual void turnFaceNeutralXY();
    virtual void turnFaceNeutralZY();
    virtual void turnFaceNeutralZX();

    static GgafDx9Core::angle wk_dist, wk_angRx;
    void move_WAY_NONE() {
        //_way = WAY_NONE;
    }
    void move_WAY_UP() {
        //_way = WAY_UP;
        _Y += _iMoveSpeed;
    }
    void move_WAY_UP_FRONT() {
        //_way = WAY_UP_FRONT;
        _Y += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
    }
    void move_WAY_UP_BEHIND() {
        //_way = WAY_UP_BEHIND;
        _Y += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
    }
    void move_WAY_FRONT() {
        //_way = WAY_FRONT;
        _X += _iMoveSpeed;
    }
    void move_WAY_BEHIND() {
        //_way = WAY_BEHIND;
        _X -= _iMoveSpeed;
    }
    void move_WAY_DOWN() {
        //_way = WAY_DOWN;
        _Y -= _iMoveSpeed;
    }
    void move_WAY_DOWN_BEHIND() {
        //_way = WAY_DOWN_BEHIND;
        _Y -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
    }
    void move_WAY_DOWN_FRONT() {
        //_way = WAY_DOWN_FRONT;
        _Y -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
    }
    void move_WAY_ZLEFT() {
        //_way = WAY_ZLEFT;
        _Z += _iMoveSpeed;
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE); //反時計回りの距離
        if (0 < wk_dist && wk_dist <= ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (ANGLE180 < wk_dist && wk_dist < ANGLE360) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZLEFT_FRONT() {
        //_way = WAY_ZLEFT_FRONT;
        _Z += _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ - (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE); //反時計回りの距離
        if (0 < wk_dist && wk_dist <= ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (ANGLE180 < wk_dist && wk_dist < ANGLE360) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZLEFT_BEHIND() {
        //_way = WAY_ZLEFT_BEHIND;
        _Z += _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ + (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE); //反時計回りの距離
        if (0 < wk_dist && wk_dist <= ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (ANGLE180 < wk_dist && wk_dist < ANGLE360) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZRIGHT_FRONT() {
        //_way = WAY_ZRIGHT_FRONT;
        _Z -= _iMoveSpeed * NANAME;
        _X += _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ - (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE); //時計回りの距離
        if (-1*ANGLE360 < wk_dist && wk_dist < -1*ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 <= wk_dist && wk_dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }

    void move_WAY_ZRIGHT() {
        //_way = WAY_ZRIGHT;
        _Z -= _iMoveSpeed;
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE); //時計回りの距離
        if (-1*ANGLE360 < wk_dist && wk_dist < -1*ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 <= wk_dist && wk_dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZRIGHT_BEHIND() {
        //_way = WAY_ZRIGHT_BEHIND;
        _Z -= _iMoveSpeed * NANAME;
        _X -= _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ + (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE); //時計回りの距離
        if (-1*ANGLE360 < wk_dist && wk_dist < -1*ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 <= wk_dist && wk_dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }

    void move_WAY_ZLEFT_UP() {
        //_way = WAY_ZLEFT_UP;
        _Z += _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ - (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE); //反時計回りの距離
        if (0 < wk_dist && wk_dist <= ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (ANGLE180 < wk_dist && wk_dist < ANGLE360) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZLEFT_DOWN() {
        //_way = WAY_ZLEFT_DOWN;
        _Z += _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ + (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE); //反時計回りの距離
        if (0 < wk_dist && wk_dist <= ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (ANGLE180 < wk_dist && wk_dist < ANGLE360) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, wk_angRx, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
    }

    void move_WAY_ZRIGHT_UP() {
        //_way = WAY_ZRIGHT_UP;
        _Z -= _iMoveSpeed * NANAME;
        _Y += _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ - (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE); //時計回りの距離
        if (-1*ANGLE360 < wk_dist && wk_dist < -1*ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 <= wk_dist && wk_dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZRIGHT_DOWN() {
        //_way = WAY_ZRIGHT_DOWN;
        _Z -= _iMoveSpeed * NANAME;
        _Y -= _iMoveSpeed * NANAME;
        wk_angRx = _angRXStop_MZ + (_angRXStop_MZ/2);
        wk_dist = _pMover->getFaceAngleDistance(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE); //時計回りの距離
        if (-1*ANGLE360 < wk_dist && wk_dist < -1*ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 <= wk_dist && wk_dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setStopTarget_FaceAngle(AXIS_X, -1*wk_angRx, TURN_CLOCKWISE, _angRXTopVelo_MZ);
    }
    void move_WAY_ZLEFT_UP_FRONT() {
        _TRACE_("move_WAY_ZLEFT_UP_FRONTLEFT() came!");
    }

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






































    //virtual void beginMoveZX(int prm_VB);

    //virtual void beginMoveXY(int prm_VB);

    static void transactShot(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);

    /**オプション追加*/
    void equipOption();

    virtual ~MyShip();

    static bool isDoublePushedDown(GgafDx9LibStg::vbsta prm_VB);






};

}
#endif /*MYSHIP_H_*/

