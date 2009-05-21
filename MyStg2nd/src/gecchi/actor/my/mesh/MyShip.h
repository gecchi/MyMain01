#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace MyStg2nd {

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0

#define EQ_OPTION 1
#define EQ_MAX_OPTION 0

enum MoveWay {
    WAY_NONE,
    WAY_UP,
    WAY_UP_FRONT,
    WAY_UP_BEHIND,
    WAY_DOWN,
    WAY_DOWN_FRONT,
    WAY_DOWN_BEHIND,
    WAY_FRONT,
    WAY_BEHIND,
    WAY_ZLEFT,
    WAY_ZLEFT_FRONT,
    WAY_ZLEFT_BEHIND,
    WAY_ZRIGHT,
    WAY_ZRIGHT_FRONT,
    WAY_ZRIGHT_BEHIND
};

class MyShip : public GgafDx9LibStg::DefaultMorphMeshActor {
//class MyShip : public GgafDx9LibStg::DefaultD3DXMeshActor {

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

public:
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
    virtual void beginTurboXY(int prm_VB);
    virtual void beginTurboXZ(int prm_VB);

    virtual void moveXZ(int prm_VB);

    virtual void moveXY(int prm_VB);

    virtual void turnFaceXYMove(int prm_VB);
    virtual void turnFaceXZMove(int prm_VB);

    virtual void doNotingMoveInput();

    virtual void turnFaceNeutralXY();
    virtual void turnFaceNeutralXZ();

    //virtual void beginMoveZX(int prm_VB);

    //virtual void beginMoveXY(int prm_VB);

    static void transactShot(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor);

    /**オプション追加*/
    void equipOption();

    virtual ~MyShip();

    static bool isDoublePushedDown(int prm_VB);

};

}
#endif /*MYSHIP_H_*/

