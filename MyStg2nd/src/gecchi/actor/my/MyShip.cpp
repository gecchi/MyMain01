#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
int MyShip::wk_dist = 0;
angle MyShip::wk_angRx = 0;

#define S_OPTION 0
int MyShip::_lim_top     =  0;
int MyShip::_lim_bottom  =  0;
int MyShip::_lim_front   =  0;
int MyShip::_lim_behaind =  0;
int MyShip::_lim_zleft   =  0;
int MyShip::_lim_zright  =  0;

MyShip::MyShip(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "VicViper") {
//MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "jiki") {
//MyShip::MyShip(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "MyShip";
    MyStgUtil::resetMyShipStatus(_pStatus);
    //chengeEffectTechnique("DestBlendOne"); //加算合成Technique指定

    GameGlobal::init();
    GameGlobal::_pMyShip = this;
    //画面の大きさに伴って、移動範囲を決定
    //このあたりはFovXに依存するので微調整。
    _lim_top     = GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2;      //上下は画面高さの大体５画面分
    _lim_bottom  = -(GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2);
    _lim_front   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2 ;    //前は画面幅の大体5画面分
    _lim_behaind = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*2*LEN_UNIT / 2 ); //後は画面幅の大体2画面分
    _lim_zleft   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2;       //奥手前は画面幅の大体５画面分
    _lim_zright  = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2);

    /** 移動スピードレベル */
    _lv_MoveSpeed = 2;
    /** 移動スピードレベルに相応する移動スピード */
    _iMoveSpeed = 5000;
    //CommonSceneがnewの場合設定
    _angRXVelo_BeginMZ = 1000; //奥又は手前へ通常Z通常移動開始時のX軸回転角速度の初速度
    _angRXAcce_MZ = 300; //奥又は手前へ通常Z移動中のX軸回転角速度の初角加速度
    _angRXTopVelo_MZ = 5000; //奥又は手前へ通常Z移動中のX軸回転角速度の上限角速度
    _angRXStop_MZ = 90000; //奥又は手前へ通常Z移動中のX軸回転角の目標停止角度

    //_angRXVelo_BeginMZT = 23000; //奥又は手前へTurbo移動開始時のX軸回転角速度の初速度
    _angRXVelo_BeginMZT = 40000;

    _iMvBtmVelo_MT = 0; //Turbo移動中の移動速度の最低速度
    _iMvVelo_BeginMT = 40000; //Turbo移動開始時の移動速度の初速度
    _iMvAcce_MT = -200; //Turbo移動中の移動速度の加速度

    _way = WAY_FRONT;
    _pMyOptionController = NEW MyOptionController("MY_OPTION_PARENT");
    addSubLast(_pMyOptionController);

    _pDispatcher_MyShots001 = NEW GgafActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubGroup(_pDispatcher_MyShots001);

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setPositionSource(this); //位置だけ同期
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipDispatcher);


    _pEffectTurbo001 = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(_pEffectTurbo001);
//    _pEffectTurbo002 = NEW EffectTurbo002("EffectTurbo002");
//    addSubGroup(_pEffectTurbo002);
    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (UINT32 i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }

    _iMoveVelo = 0;

    //     X   Y   Z
    //    -----------
    //    -1  -1  -1
    //     0   0   0    の全体を+1して3進数で扱う
    //    +1  +1  +1

    //それぞれのスイッチの状態に応じた処理の関数テーブル配列。
    /////////////// X  Y  Z
    paFuncMove[TN(-1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    paFuncMove[TN(-1,-1, 0)] = &MyShip::move_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    paFuncMove[TN(-1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    paFuncMove[TN(-1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    paFuncMove[TN(-1, 0, 0)] = &MyShip::move_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    paFuncMove[TN(-1, 0, 1)] = &MyShip::move_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    paFuncMove[TN(-1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    paFuncMove[TN(-1, 1, 0)] = &MyShip::move_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    paFuncMove[TN(-1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    paFuncMove[TN( 0,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    paFuncMove[TN( 0,-1, 0)] = &MyShip::move_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    paFuncMove[TN( 0,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    paFuncMove[TN( 0, 0,-1)] = &MyShip::move_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    paFuncMove[TN( 0, 0, 0)] = &MyShip::move_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    paFuncMove[TN( 0, 0, 1)] = &MyShip::move_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    paFuncMove[TN( 0, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    paFuncMove[TN( 0, 1, 0)] = &MyShip::move_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    paFuncMove[TN( 0, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    paFuncMove[TN( 1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    paFuncMove[TN( 1,-1, 0)] = &MyShip::move_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    paFuncMove[TN( 1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    paFuncMove[TN( 1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    paFuncMove[TN( 1, 0, 0)] = &MyShip::move_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    paFuncMove[TN( 1, 0, 1)] = &MyShip::move_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    paFuncMove[TN( 1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    paFuncMove[TN( 1, 1, 0)] = &MyShip::move_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    paFuncMove[TN( 1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26


    paFuncTurbo[TN(-1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    paFuncTurbo[TN(-1,-1, 0)] = &MyShip::turbo_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    paFuncTurbo[TN(-1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    paFuncTurbo[TN(-1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    paFuncTurbo[TN(-1, 0, 0)] = &MyShip::turbo_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    paFuncTurbo[TN(-1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    paFuncTurbo[TN(-1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    paFuncTurbo[TN(-1, 1, 0)] = &MyShip::turbo_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    paFuncTurbo[TN(-1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    paFuncTurbo[TN( 0,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    paFuncTurbo[TN( 0,-1, 0)] = &MyShip::turbo_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    paFuncTurbo[TN( 0,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    paFuncTurbo[TN( 0, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    paFuncTurbo[TN( 0, 0, 0)] = &MyShip::turbo_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    paFuncTurbo[TN( 0, 0, 1)] = &MyShip::turbo_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    paFuncTurbo[TN( 0, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    paFuncTurbo[TN( 0, 1, 0)] = &MyShip::turbo_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    paFuncTurbo[TN( 0, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    paFuncTurbo[TN( 1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    paFuncTurbo[TN( 1,-1, 0)] = &MyShip::turbo_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    paFuncTurbo[TN( 1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    paFuncTurbo[TN( 1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    paFuncTurbo[TN( 1, 0, 0)] = &MyShip::turbo_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    paFuncTurbo[TN( 1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    paFuncTurbo[TN( 1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    paFuncTurbo[TN( 1, 1, 0)] = &MyShip::turbo_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    paFuncTurbo[TN( 1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26

    _pSeTransmitter->useSe(4);
    _pSeTransmitter->set(0, "se-020");
    _pSeTransmitter->set(1,"laser001", 99);
    _pSeTransmitter->set(2,"fire01", 99);
    _pSeTransmitter->set(3,"bse5", 99);
    char rankstr[80] = {0} ;// 全て0で初期化
    MyStgUtil::getRankStr(99999, rankstr);
    _TRACE_("RANKSTR:"<<rankstr);


    _iMvVelo_TurboTop = 30000;
    _iMvVelo_TurboBottom = 10000;

    _frame_soft_rapidshot = 0;
    _is_being_soft_rapidshot = false;
    _just_shot = false;
    _is_shooting_laser = false;
    _frame_shot_pressed = 0;

}

void MyShip::onActive() {
    MyStgUtil::resetMyShipStatus(_pStatus);
}


void MyShip::initialize() {



    //種別に振り分け
//    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyShots001->extract());
//    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyWaves001->extract());
    //getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 10000);
//    _pCollisionChecker->setColliAAB(0, -20000, -20000, -20000, 20000, 20000, 20000);
//    _pCollisionChecker->setColliSphere(1, 0,-100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(2, 0,100000,0, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(3, 0,0,-100000, 30000, true, true, true);
//    _pCollisionChecker->setColliSphere(4, 0,0,100000, 30000, true, true, true);

    _pMover->setMvVelo(0);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 7000);

    _pMover->forceVxMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pMover->forceVyMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);
    _pMover->forceVzMvVeloRange(-_iMvVelo_TurboTop, _iMvVelo_TurboTop);

    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    //        _pMover->forceMvVeloRange(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    //        _pMover->addMvVelo(_iMvVelo_BeginMT);  //速度追加
    //        _pMover->setMvAcce(_iMvAcce_MT);

    _pMover->setFaceAngVelo(AXIS_X, 300);
}

void MyShip::processBehavior() {

    //VAMSystemの実装
    // (Viewpoint Adaptive Moving System 視点適応型移動システム)
    _stc = VB_PLAY->getBeingPressedStick();
    if (pCOMMONSCENE->_pos_camera == CAM_POS_RIGHT) {
        //右サイドビュー(右から左へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //前方
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pCOMMONSCENE->_pos_camera == CAM_POS_LEFT) {
        //左サイドビュー(左から右へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //後方
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pCOMMONSCENE->_pos_camera == CAM_POS_TOP) {
        //トップビュー(上から下へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //前方
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
    } else if (pCOMMONSCENE->_pos_camera == CAM_POS_BOTTOM) {
        //ボトムビュー(下から上へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //後方
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
    } else if (pCOMMONSCENE->_pos_camera > CAM_POS_TO_BEHIND) {
        //背後ビュー（奥から手前にスクロール）
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    }
    if (VB_PLAY->isReleasedUp(VB_UP)) {
        _way_switch.OFF_UP();    // ↑ を離す
    }
    if (VB_PLAY->isReleasedUp(VB_RIGHT)) {
        _way_switch.OFF_RIGHT(); // → を離す
    }
    if (VB_PLAY->isReleasedUp(VB_LEFT)) {
        _way_switch.OFF_LEFT();  // ← を離す
    }
    if (VB_PLAY->isReleasedUp(VB_DOWN)) {
        _way_switch.OFF_DOWN();  // ↓ を離す
    }
    _way = (MoveWay)(_way_switch.getIndex()); //上記を考慮された方向値が入る

    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
        int tmp = _iMoveSpeed;
        _iMoveSpeed = _iMoveSpeed / 8; //オプション操作中移動は遅い
        (this->*paFuncMove[_way])();   //方向値に応じた移動処理メソッドを呼び出す
        _iMoveSpeed = tmp;
    } else {
        (this->*paFuncMove[_way])();   //方向値に応じた移動処理メソッドを呼び出す
    }

    if (VB_PLAY->isPushedDown(VB_TURBO)) {
        //ターボ開始時
        EffectTurbo002* pTurbo002 = (EffectTurbo002*)pCOMMONSCENE->_pDispatcher_EffectTurbo002->employForce();
         if (pTurbo002 != NULL) {
             pTurbo002->setGeometry(this);
             pTurbo002->activate();
         }
        (this->*paFuncTurbo[_way])();
    } else {
        //Notターボ開始時
        if (VB_PLAY->isBeingPressed(VB_TURBO)) {
            //ターボを押し続けることで、移動距離を伸ばす
            _pMover->_veloVxMv *= 0.95;
            _pMover->_veloVyMv *= 0.95;
            _pMover->_veloVzMv *= 0.95;
        } else {
            _pMover->_veloVxMv *= 0.9;
            _pMover->_veloVyMv *= 0.9;
            _pMover->_veloVzMv *= 0.9;
        }
    }

    //スピンが勢いよく回っているならば速度を弱める
    angvelo MZ = _angRXTopVelo_MZ-3000; //3000は通常旋回時に速度を弱めて_angRXTopVelo_MZを超えないようにするため、やや手前で減速すると言う意味（TODO:要調整）。
    if (_pMover->_angveloFace[AXIS_X] >= MZ) {
        _pMover->_angveloFace[AXIS_X] *= 0.93;
        //_pMover->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pMover->_angveloFace[AXIS_X] <= -MZ) {
        _pMover->_angveloFace[AXIS_X] *= 0.93;
        //_pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ*2);
    }

    //左右が未入力なら、機体を水平にする（但し勢いよく回っていない場合に限る。setStopTarget_FaceAngの第4引数より角速度がゆるい場合受け入れ）
    if (VB_PLAY->isBeingPressed(VB_LEFT) || VB_PLAY->isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pMover->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < ANGLE180) {
            _pMover->setFaceAngAcce(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 < dist && dist < 0) {
            _pMover->setFaceAngAcce(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setMvAcce(0);
        _pMover->setStopTarget_FaceAng(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
    }

    ////////////////////////////////////////////////////

    //座標に反映
    _pMover->behave();
    _pSeTransmitter->behave();

    if (_Y > MyShip::_lim_top) {
        _Y = MyShip::_lim_top;
    }
    if (_Y < MyShip::_lim_bottom ) {
        _Y = MyShip::_lim_bottom;
    }

    if (_X > MyShip::_lim_front) {
        _X = MyShip::_lim_front;
    }
    if (_X < MyShip::_lim_behaind) {
        _X = MyShip::_lim_behaind;
    }

    if (_Z > MyShip::_lim_zleft) {
        _Z = MyShip::_lim_zleft;
    }
    if (_Z < MyShip::_lim_zright) {
        _Z = MyShip::_lim_zright;
    }
    _pRing_GeoHistory->next()->set(this);
}

void MyShip::processJudgement() {
    //ショット関連処理
    _is_shooting_laser = false;
    if (VB_PLAY->isBeingPressed(VB_SHOT1)) {
        _frame_shot_pressed ++;
        if (_frame_shot_pressed > 30) { //12フレーム押しっぱなしでレーザーへ
            _is_shooting_laser = true;
        }
    } else {
        _frame_shot_pressed = 0;
    }


    if (_is_shooting_laser) {
        if (VB_PLAY->isBeingPressed(VB_SHOT1)) {//isBeingPressed
            //GgafActorDispatcherの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる?。
            MyStraightLaserChip001* pLaser = (MyStraightLaserChip001*)_pLaserChipDispatcher->employ();
            if (pLaser != NULL) {
                pLaser->activate();
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                }
            }
        }
    }

    //ソフト連射
    //1プッシュで4F毎に16フレーム(最大4発)
    if (VB_PLAY->isPushedDown(VB_SHOT1)) {
        _is_being_soft_rapidshot = true;
        if (_frame_soft_rapidshot >= 4) {
            //４フレームより遅い場合
            //連射と連射のつなぎ目が無いようにする
            _frame_soft_rapidshot = _frame_soft_rapidshot % 4;
        } else {
            //４フレームより速い連射の場合
            //これを受け入れて強制的に発射できる
            _frame_soft_rapidshot = 0;
        }
    }
    _just_shot = false;
    if (_is_being_soft_rapidshot) {
        if (_frame_soft_rapidshot % 4 == 0) {
            _just_shot = true;//たった今ショットしましたフラグ
            MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
            if (pShot != NULL) {
                _pSeTransmitter->play3D(2);
                pShot->setGeometry(this);
                pShot->activate();
            }
            if (_frame_soft_rapidshot >= 12) {
                //4発打ち終えたらソフト連射終了
                _is_being_soft_rapidshot = false;
            }
        }
    }
    if (_is_being_soft_rapidshot) {
        _frame_soft_rapidshot++;
    }


    //    if (VB_PLAY->isPushedDown(VB_SHOT2)) {
    if (VB_PLAY->isBeingPressed(VB_SHOT2)) {
        bool can_fire = true;
        for (int i = 0; i < _pMyOptionController->_now_option_num; i++) {
            if (_pMyOptionController->_papMyOption[i]->_pTorpedoController->_in_firing) {
                can_fire = false;
                break;
            }
        }
        if (can_fire) {
            _pSeTransmitter->play3D(3);
            for (int i = 0; i < _pMyOptionController->_now_option_num; i++) {
                _pMyOptionController->_papMyOption[i]->_pTorpedoController->fire();
            }
        }
    }



}

void MyShip::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    _pSeTransmitter->play3D(0);
    EffectExplosion001* pExplo001 = (EffectExplosion001*)pCOMMONSCENE->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(pOther);
        pExplo001->activate();
    }
    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここに消滅エフェクト


    }

}



void MyShip::doNotingMoveInput() {

}

void MyShip::transactShot(GgafDx9GeometricActor* prm_pActor) {

}

void MyShip::equipOption() {
//
//    if (_state.eq_option >= EQ_MAX_OPTION) {
//        return;
//    }
//    MyOption* pOption = (MyOption*)_pSubFirst;
//    for (int i = 0; i < _state.eq_option; i++) {
//        pOption = (MyOption*)(pOption->getNext());
//    }
//    if (_state.eq_option == 0) {
//        pOption->setRadicalActor(this);
//    } else {
//        pOption->setRadicalActor((GgafDx9GeometricActor*)pOption->getPrev());
//    }
//
//    _state.eq_option++;
//    pOption->activate();

}




bool MyShip::isDoublePushedDown(vbsta prm_VB) {
    //過去に遡りながら検証
    frame frame_Apply;
    frame frame_Ago = 1;
    VirtualButton::VBMap* pVBMap = VB_PLAY->getPastVBMap(frame_Ago);
    //直前は必ず押されていては駄目、ニュートラルでなければだめ
    if ((pVBMap->_state & prm_VB) == 0) {

        frame_Ago++;
        //その前の5フレーム以内のどこかで押していなければならない
        frame_Apply = frame_Ago + 7;//許容フレーム
        for ( ; frame_Ago < frame_Apply; frame_Ago++) {
            pVBMap = VB_PLAY->getPastVBMap(frame_Ago);
            if (pVBMap->_state & prm_VB) {
                break;
            }
        }
        if (frame_Ago >= frame_Apply) {
            return false; //不合格
        }

        //さらにそこから以前5フレーム以内のどこかで押されていては駄目
        frame_Apply = frame_Ago + 7;//許容フレーム
        for ( ; frame_Ago < frame_Apply; frame_Ago++) {
            pVBMap = VB_PLAY->getPastVBMap(frame_Ago);
            if ((pVBMap->_state & prm_VB) == 0) {

                break;
            }
        }
        if (frame_Ago >= frame_Apply) {
            return false; //不合格
        }
        return true;

    } else {
        return false;
    }

}


MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);

}

