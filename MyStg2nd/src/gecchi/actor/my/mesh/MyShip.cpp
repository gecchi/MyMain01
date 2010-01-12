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

//MyShip::MyShip(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "Flora") {
MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "jiki") {
//MyShip::MyShip(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "MyShip";
    MyStgUtil::resetMyShipStatus(this);
    //setTechnique("DestBlendOne"); //加算合成Technique指定

    GameGlobal::init();
    GameGlobal::_pMyShip = this;
    //画面の大きさに伴って、移動範囲を決定
    _lim_top     = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*3*LEN_UNIT / 2;
    _lim_bottom  = -(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*3*LEN_UNIT / 2);
    _lim_front   = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2 * 2.0;
    _lim_behaind = -(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2 * 0.5);
    _lim_zleft   = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*3*LEN_UNIT / 2;
    _lim_zright  = -(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*3*LEN_UNIT / 2);

    /** 移動スピードレベル */
    _lv_MoveSpeed = 2;
    /** 移動スピードレベルに相応する移動スピード */
    _iMoveSpeed = 7000;
    //CommonSceneがnewの場合設定

    _angRXVelo_BeginMZ = 1000; //奥又は手前へ通常Z通常移動開始時のX軸回転角速度の初速度
    _angRXAcce_MZ = 300; //奥又は手前へ通常Z移動中のX軸回転角速度の初角加速度
    _angRXTopVelo_MZ = 5000; //奥又は手前へ通常Z移動中のX軸回転角速度の上限角速度
    _angRXStop_MZ = 90000; //奥又は手前へ通常Z移動中のX軸回転角の目標停止角度

    _angRXVelo_BeginMZT = 23000; //奥又は手前へTurbo移動開始時のX軸回転角速度の初速度

    _iMvBtmVelo_MT = 0; //Turbo移動中の移動速度の最低速度
    _iMvVelo_BeginMT = _iMoveSpeed * 2; //Turbo移動開始時の移動速度の初速度
    _iMvAcce_MT = -200; //Turbo移動中の移動速度の加速度

    _way = WAY_FRONT;
    MyOptionParent* pMyOptionParent = NEW MyOptionParent("MY_OPTION_PARENT");
    addSubLast(pMyOptionParent);

    _pDispatcher_MyShots001 = NEW ActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubLast(_pDispatcher_MyShots001); //仮サブ

    _pDispatcher_MyWaves001 = NEW ActorDispatcher("RotWave001");
    MyWave001* pWave;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateImmediately();
        _pDispatcher_MyWaves001->addSubLast(pWave);
    }
    addSubLast(_pDispatcher_MyWaves001); //仮サブ

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
        stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setPositionSource(this); //位置だけ同期
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipDispatcher);


    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }




    //     X   Y   Z
    //    -----------
    //    -1  -1  -1
    //     0   0   0    の全体を+1して3進数で扱う
    //    +1  +1  +1

    //それぞれのスイッチの状態に応じた処理の関数テーブル配列。
    /////////////// X  Y  Z
    fpaMoveFunc[TN(-1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    fpaMoveFunc[TN(-1,-1, 0)] = &MyShip::move_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    fpaMoveFunc[TN(-1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    fpaMoveFunc[TN(-1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    fpaMoveFunc[TN(-1, 0, 0)] = &MyShip::move_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    fpaMoveFunc[TN(-1, 0, 1)] = &MyShip::move_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    fpaMoveFunc[TN(-1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    fpaMoveFunc[TN(-1, 1, 0)] = &MyShip::move_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    fpaMoveFunc[TN(-1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    fpaMoveFunc[TN( 0,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    fpaMoveFunc[TN( 0,-1, 0)] = &MyShip::move_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    fpaMoveFunc[TN( 0,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    fpaMoveFunc[TN( 0, 0,-1)] = &MyShip::move_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    fpaMoveFunc[TN( 0, 0, 0)] = &MyShip::move_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    fpaMoveFunc[TN( 0, 0, 1)] = &MyShip::move_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    fpaMoveFunc[TN( 0, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    fpaMoveFunc[TN( 0, 1, 0)] = &MyShip::move_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    fpaMoveFunc[TN( 0, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    fpaMoveFunc[TN( 1,-1,-1)] = &MyShip::move_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    fpaMoveFunc[TN( 1,-1, 0)] = &MyShip::move_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    fpaMoveFunc[TN( 1,-1, 1)] = &MyShip::move_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    fpaMoveFunc[TN( 1, 0,-1)] = &MyShip::move_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    fpaMoveFunc[TN( 1, 0, 0)] = &MyShip::move_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    fpaMoveFunc[TN( 1, 0, 1)] = &MyShip::move_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    fpaMoveFunc[TN( 1, 1,-1)] = &MyShip::move_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    fpaMoveFunc[TN( 1, 1, 0)] = &MyShip::move_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    fpaMoveFunc[TN( 1, 1, 1)] = &MyShip::move_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26


    fpaTurboFunc[TN(-1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_BEHIND;   //TN(-1,-1,-1) =  WAY_ZRIGHT_DOWN_BEHIND  = 0
    fpaTurboFunc[TN(-1,-1, 0)] = &MyShip::turbo_WAY_DOWN_BEHIND;          //TN(-1,-1, 0) =  WAY_DOWN_BEHIND         = 1
    fpaTurboFunc[TN(-1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_BEHIND;    //TN(-1,-1, 1) =  WAY_ZLEFT_DOWN_BEHIND   = 2
    fpaTurboFunc[TN(-1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_BEHIND;        //TN(-1, 0,-1) =  WAY_ZRIGHT_BEHIND       = 3
    fpaTurboFunc[TN(-1, 0, 0)] = &MyShip::turbo_WAY_BEHIND;               //TN(-1, 0, 0) =  WAY_BEHIND              = 4
    fpaTurboFunc[TN(-1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_BEHIND;         //TN(-1, 0, 1) =  WAY_ZLEFT_BEHIND        = 5
    fpaTurboFunc[TN(-1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_BEHIND;     //TN(-1, 1,-1) =  WAY_ZRIGHT_UP_BEHIND    = 6
    fpaTurboFunc[TN(-1, 1, 0)] = &MyShip::turbo_WAY_UP_BEHIND;            //TN(-1, 1, 0) =  WAY_UP_BEHIND           = 7
    fpaTurboFunc[TN(-1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_BEHIND;      //TN(-1, 1, 1) =  WAY_ZLEFT_UP_BEHIND     = 8
    fpaTurboFunc[TN( 0,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN;          //TN( 0,-1,-1) =  WAY_ZRIGHT_DOWN         = 9
    fpaTurboFunc[TN( 0,-1, 0)] = &MyShip::turbo_WAY_DOWN;                 //TN( 0,-1, 0) =  WAY_DOWN                = 10
    fpaTurboFunc[TN( 0,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN;           //TN( 0,-1, 1) =  WAY_ZLEFT_DOWN          = 11
    fpaTurboFunc[TN( 0, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT;               //TN( 0, 0,-1) =  WAY_ZRIGHT              = 12
    fpaTurboFunc[TN( 0, 0, 0)] = &MyShip::turbo_WAY_NONE;                 //TN( 0, 0, 0) =  WAY_NONE                = 13
    fpaTurboFunc[TN( 0, 0, 1)] = &MyShip::turbo_WAY_ZLEFT;                //TN( 0, 0, 1) =  WAY_ZLEFT               = 14
    fpaTurboFunc[TN( 0, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP;            //TN( 0, 1,-1) =  WAY_ZRIGHT_UP           = 15
    fpaTurboFunc[TN( 0, 1, 0)] = &MyShip::turbo_WAY_UP;                   //TN( 0, 1, 0) =  WAY_UP                  = 16
    fpaTurboFunc[TN( 0, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP;             //TN( 0, 1, 1) =  WAY_ZLEFT_UP            = 17
    fpaTurboFunc[TN( 1,-1,-1)] = &MyShip::turbo_WAY_ZRIGHT_DOWN_FRONT;    //TN( 1,-1,-1) =  WAY_ZRIGHT_DOWN_FRONT   = 18
    fpaTurboFunc[TN( 1,-1, 0)] = &MyShip::turbo_WAY_DOWN_FRONT;           //TN( 1,-1, 0) =  WAY_DOWN_FRONT          = 19
    fpaTurboFunc[TN( 1,-1, 1)] = &MyShip::turbo_WAY_ZLEFT_DOWN_FRONT;     //TN( 1,-1, 1) =  WAY_ZLEFT_DOWN_FRONT    = 20
    fpaTurboFunc[TN( 1, 0,-1)] = &MyShip::turbo_WAY_ZRIGHT_FRONT;         //TN( 1, 0,-1) =  WAY_ZRIGHT_FRONT        = 21
    fpaTurboFunc[TN( 1, 0, 0)] = &MyShip::turbo_WAY_FRONT;                //TN( 1, 0, 0) =  WAY_FRONT               = 22
    fpaTurboFunc[TN( 1, 0, 1)] = &MyShip::turbo_WAY_ZLEFT_FRONT;          //TN( 1, 0, 1) =  WAY_ZLEFT_FRONT         = 23
    fpaTurboFunc[TN( 1, 1,-1)] = &MyShip::turbo_WAY_ZRIGHT_UP_FRONT;      //TN( 1, 1,-1) =  WAY_ZRIGHT_UP_FRONT     = 24
    fpaTurboFunc[TN( 1, 1, 0)] = &MyShip::turbo_WAY_UP_FRONT;             //TN( 1, 1, 0) =  WAY_UP_FRONT            = 25
    fpaTurboFunc[TN( 1, 1, 1)] = &MyShip::turbo_WAY_ZLEFT_UP_FRONT;       //TN( 1, 1, 1) =  WAY_ZLEFT_UP_FRONT      = 26


    useSe1("se-020");


    char rankstr[80] = {0} ;// 全て0で初期化
    MyStgUtil::getRankStr(99999, rankstr);
    _TRACE_("RANKSTR:"<<rankstr);
}

void MyShip::onActive() {
    MyStgUtil::resetMyShipStatus(this);

}


void MyShip::initialize() {



    //種別に振り分け
    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyShots001->extract());
    getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pDispatcher_MyWaves001->extract());
    //getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -20000, -20000, -20000, 20000, 20000, 20000);
    _pMover->setMoveVelocity(0);
    _pScaler->setScale(1000);
    _pScaler->setScaleRange(1000, 900000);

    _pMover->setVxMoveVeloRenge(-_iMvVelo_BeginMT, _iMvVelo_BeginMT);
    _pMover->setVyMoveVeloRenge(-_iMvVelo_BeginMT, _iMvVelo_BeginMT);
    _pMover->setVzMoveVeloRenge(-_iMvVelo_BeginMT, _iMvVelo_BeginMT);

    _pMover->setVxMoveVeloAcceleration(0);
    _pMover->setVyMoveVeloAcceleration(0);
    _pMover->setVzMoveVeloAcceleration(0);

    //        _pMover->setMoveVeloRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    //        _pMover->addMoveVelocity(_iMvVelo_BeginMT);  //速度追加
    //        _pMover->setMoveVeloAcceleration(_iMvAcce_MT);
}

void MyShip::processBehavior() {

///////////スケーリングテスト////////////////
    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pScaler->addScale(2000);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pScaler->addScale(-2000);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
        _pScaler->intoTargetScaleAccelerationStep(3000, 0, 3);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _pScaler->loopLiner(20, -1);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_5)) {
        _pScaler->loopLiner(10, 5);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_6)) {
        _pScaler->beat(20, 2 ,5, -1);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
        _pScaler->stopImmediately();
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pScaler->resetScale();
    }
    _pScaler->behave();
///////////スケーリングテスト////////////////

    //オリジナルシステム VAMSystemの実装
    // (Viewpoint Adaptive Moving System 視点適応型移動システム)
    _stc = VB::getBeingPressedStick();
    if (pWORLD->_pos_camera == CAM_POS_RIGHT) {
        //右サイドビュー(右から左へスクロール)
        if (VB::isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB::isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //前方
        }
        if (VB::isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
        if (VB::isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pWORLD->_pos_camera == CAM_POS_LEFT) {
        //左サイドビュー(左から右へスクロール)
        if (VB::isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB::isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //後方
        }
        if (VB::isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
        if (VB::isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pWORLD->_pos_camera == CAM_POS_TOP) {
        //トップビュー(上から下へスクロール)
        if (VB::isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //前方
        }
        if (VB::isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB::isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB::isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
    } else if (pWORLD->_pos_camera == CAM_POS_BOTTOM) {
        //ボトムビュー(下から上へスクロール)
        if (VB::isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //後方
        }
        if (VB::isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB::isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB::isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
    } else if (pWORLD->_pos_camera > CAM_POS_TO_BEHIND) {
        //背後ビュー（奥から手前にスクロール）
        if (VB::isPushedDown(VB_UP)) {     // ↑
            _way_switch.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB::isPushedDown(VB_RIGHT)) {  // →
            _way_switch.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB::isPushedDown(VB_LEFT)) {   // ←
            _way_switch.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB::isPushedDown(VB_DOWN)) {   // ↓
            _way_switch.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    }
    if (VB::isReleasedUp(VB_UP)) {
        _way_switch.OFF_UP();    // ↑ を離す
    }
    if (VB::isReleasedUp(VB_RIGHT)) {
        _way_switch.OFF_RIGHT(); // → を離す
    }
    if (VB::isReleasedUp(VB_LEFT)) {
        _way_switch.OFF_LEFT();  // ← を離す
    }
    if (VB::isReleasedUp(VB_DOWN)) {
        _way_switch.OFF_DOWN();  // ↓ を離す
    }
    _way = (MoveWay)(_way_switch.getIndex()); //上記を考慮された方向値が入る
    (this->*fpaMoveFunc[_way])();             //方向値に応じた移動処理メソッドを呼び出す

    if (VB::isPushedDown(VB_TURBO)) { //ターボ
        (this->*fpaTurboFunc[_way])();
    } else {
        _pMover->_veloVxMove *= 0.95;
        _pMover->_veloVyMove *= 0.95;
        _pMover->_veloVzMove *= 0.95;
    }

    //スピンが勢いよく回っているならば速度を弱める
    if (_pMover->_angveloRotFace[AXIS_X] >= _angRXTopVelo_MZ) {
        _pMover->_angveloRotFace[AXIS_X] *= 0.90;
        //_pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pMover->_angveloRotFace[AXIS_X] <= -1*_angRXTopVelo_MZ) {
        _pMover->_angveloRotFace[AXIS_X] *= 0.90;
        //_pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ*2);
    }

    //左右が未入力なら、機体を水平にする（但し勢いよく回っていない場合に限る。setStopTarget_FaceAngleの第4引数より角速度がゆるい場合受け入れ）
    if (VB::isBeingPressed(VB_LEFT) || VB::isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pMover->getFaceAngleDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < ANGLE180) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, _angRXAcce_MZ);
        } else if (-1*ANGLE180 < dist && dist < 0) {
            _pMover->setFaceAngleVeloAcceleration(AXIS_X, -1*_angRXAcce_MZ);
        }
        _pMover->setMoveVeloAcceleration(0);
        _pMover->setStopTarget_FaceAngle(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
    }

    ////////////////////////////////////////////////////



    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
        _TRACE_("(X,Y,Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
    }


    //座標に反映
    _pMover->behave();



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

    if (isOffscreen()) {
        _TRACE_("MyShip is Offscreen! = ("<<_X<<","<<_Y<<","<<_Z<<")");
    }
    //_TRACE_("_S = "<<_SX<<","<<_SY<<","<<_SZ);
}

void MyShip::processJudgement() {
    //ショット関連処理
    if (VB::isBeingPressed(VB_SHOT2)) {//isBeingPressed

        //ActorDispatcherの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる?。
        MyStraightLaserChip001* pLaser = (MyStraightLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaser != NULL) {
            pLaser->activate();
        }
    }

    //ショットボタン
    if (VB::isPushedDown(VB_SHOT1)) {

        MyWave001* pWave = (MyWave001*)_pDispatcher_MyWaves001->employ();
        if (pWave != NULL) {
            pWave->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->activate();
                pExplo001->setGeometry(this);
            }
        }
    } else if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot != NULL) {
            pShot->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
                pExplo001->activate();
            }
        }
    }
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    //_TRACE_("dep="<< (_fDistance_plnFront)<<"");
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9GeometricActor* pActor_Opponent = (GgafDx9GeometricActor*)prm_pActor_Opponent;
    playSe1();

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(pActor_Opponent);
        pExplo001->activate();
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
    static VB::VBMap* pVBMap;
    DWORD dwFrameApply;
    DWORD dwFrameAgo = 1;
    pVBMap = VB::getPastVBMap(dwFrameAgo);
    //直前は必ず押されていては駄目、ニュートラルでなければだめ
    if ((pVBMap->_state & prm_VB) == 0) {

        dwFrameAgo++;
        //その前の5フレーム以内のどこかで押していなければならない
        dwFrameApply = dwFrameAgo + 7;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state & prm_VB) {
                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //不合格
        }

        //さらにそこから以前5フレーム以内のどこかで押されていては駄目
        dwFrameApply = dwFrameAgo + 7;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if ((pVBMap->_state & prm_VB) == 0) {

                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
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












//////////////////////////////////////////////未使用？









