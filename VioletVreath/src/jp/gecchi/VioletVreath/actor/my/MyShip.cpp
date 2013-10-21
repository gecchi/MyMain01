#include "stdafx.h"
#include "MyShip.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyShip::wk_dist = 0;
angle MyShip::wk_angRx = 0;

#define S_OPTION 0
coord MyShip::lim_Y_top_     =  0;
coord MyShip::lim_Y_bottom_  =  0;
coord MyShip::lim_X_front_   =  0;
coord MyShip::lim_X_behaind_ =  0;
coord MyShip::lim_Z_left_   =  0;
coord MyShip::lim_Z_right_  =  0;

MyShip::MyShip(const char* prm_name) :
        DefaultD3DXMeshActor(prm_name, "VicViper", STATUS(MyShip)) {
//DefaultMeshActor(prm_name, "jiki", STATUS(MyShip)) {
//CubeMapMeshActor(prm_name, "wakka", STATUS(MyShip)) {
//DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton", STATUS(MyShip)) {
    _class_name = "MyShip";
    //effectBlendOne(); //加算合成Technique指定

    //画面の大きさに伴って、移動範囲を決定
    //このあたりはFovXに依存するので微調整。
    coord harf_width  = PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2;
    coord harf_height = PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2;

    lim_Y_top_     =  harf_height + PX_C(PROPERTY::GAME_BUFFER_HEIGHT*4);  //上は、高さ4画面分
    lim_Y_bottom_  = -harf_height - PX_C(PROPERTY::GAME_BUFFER_HEIGHT*4);  //下は、高さ4画面分
    lim_X_front_   =  harf_width  + PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //前は、幅の2画面分
    lim_X_behaind_ = -harf_width  - PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //後ろは、幅の2画面分
    lim_Z_left_   =  harf_width  + PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //手前は、幅の2画面分
    lim_Z_right_  = -harf_width  - PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //奥は、幅の2画面分
    _TRACE_("MyShip::MyShip 範囲 X("<<lim_X_behaind_<<" ~ "<<lim_X_front_<<") Y("<<lim_Y_bottom_<<" ~ "<<lim_Y_top_<<") Z("<<lim_Z_right_<<" ~ "<<lim_Z_left_<<")");

    /** 移動スピードレベルに相応する移動スピード */
    iMoveSpeed_ = 2000;
    //CommonSceneがnewの場合設定
    angRXVelo_BeginMZ_ = 1000; //奥又は手前へ通常Z通常移動開始時のX軸回転角速度の初速度
    angRXAcce_MZ_ = 300; //奥又は手前へ通常Z移動中のX軸回転角速度の初角加速度
    angRXTopVelo_MZ_ = 5000; //奥又は手前へ通常Z移動中のX軸回転角速度の上限角速度
    angRXStop_MZ_ = 90000; //奥又は手前へ通常Z移動中のX軸回転角の目標停止角度
    angRXVelo_BeginMZT_ = 20000;//奥又は手前へTurbo移動開始時のX軸回転角速度の初速度

    iMvBtmVelo_MT_ = 0; //Turbo移動中の移動速度の最低速度
    veloBeginMT_ = 40000; //Turbo移動開始時の移動速度の初速度
    acce_MT_ = -200; //Turbo移動中の移動速度の加速度

//    pOptionCtrler_ = NEW MyOptionController("MY_OPTION_PARENT");
//    addSubLast(pOptionCtrler_);

//    //debug ---->
//    pDepo_TestGuShot_ = NEW GgafActorDepository("Depo_TestGuShot");
//    for (int i = 0; i < 25; i++) { //テストグー弾ストック
//        pDepo_TestGuShot_->addSubLast(NEW TestGuShot("TestGuShot"));
//    }
//    addSubGroup(pDepo_TestGuShot_);
//    pDepo_TestChokiShot_ = NEW GgafActorDepository("Depo_TestChokiShot");
//    for (int i = 0; i < 25; i++) { //テストチョキ弾ストック
//        pDepo_TestChokiShot_->addSubLast(NEW TestChokiShot("TestChokiShot"));
//    }
//    addSubGroup(pDepo_TestChokiShot_);
//    pDepo_TestPaShot_ = NEW GgafActorDepository("Depo_TestPaShot");
//    for (int i = 0; i < 25; i++) { //テストパー弾ストック
//        pDepo_TestPaShot_->addSubLast(NEW TestPaShot("TestPaShot"));
//    }
//    addSubGroup(pDepo_TestPaShot_);
//    pDepo_TestNomalShot_ = NEW GgafActorDepository("Depo_TestNomalShot");
//    for (int i = 0; i < 25; i++) { //テストノーマル弾ストック
//        pDepo_TestNomalShot_->addSubLast(NEW TestNomalShot("TestNomalShot"));
//    }
//    addSubGroup(pDepo_TestNomalShot_);
//    //<---- debug


    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        pDepo_MyShots001_->put(pShot);
    }
    addSubGroup(pDepo_MyShots001_);

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "MyStraightLaserChip001("+XTOS(i)+")";
        pChip = NEW MyStraightLaserChip001(name.c_str());
        pChip->setPositionSource(this); //位置だけ同期
        pLaserChipDepo_->put(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    //ロックオンコントローラー
    pLockonCtrler_ = NEW MyLockonController("MySHipLockonController");
    addSubGroup(pLockonCtrler_);

    //フォトンコントローラー
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    addSubGroup(pTorpedoCtrler_);

    pEffectTurbo001_ = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(pEffectTurbo001_);
//    pEffectTurbo002_ = NEW EffectTurbo002("EffectTurbo002");
//    addSubGroup(pEffectTurbo002_);




    //トレース用履歴
    pRing_MyShipGeoHistory4OptCtrler_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    pRing_MyShipGeoHistory2_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
//    pRing_MyShipGeoOffsetHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (uint32_t i = 0; i < 300; i++) {
        pRing_MyShipGeoHistory4OptCtrler_->addLast(NEW GgafDxGeoElem(this));
        pRing_MyShipGeoHistory2_->addLast(NEW GgafDxGeoElem(0,0,0));
//        pRing_MyShipGeoOffsetHistory_->addLast(NEW GgafDxGeoElem(this));
    }


    //     X   Y   Z
    //    -----------
    //    -1  -1  -1
    //     0   0   0    の全体を+1して3進数で扱う
    //    +1  +1  +1

    //それぞれのスイッチの状態に応じた処理の関数テーブル配列。
    ////////////// X  Y  Z
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

    _pSeTx->set(SE_DAMAGED, "WAVE_MY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_MY_SE_EXPLOSION_001");
    _pSeTx->set(SE_TURBO, "WAVE_MY_TURBO_001");
    _pSeTx->set(SE_FIRE_LASER,   "WAVE_MY_FIRE_LASER_001");
    _pSeTx->set(SE_FIRE_SHOT,    "WAVE_MY_FIRE_SHOT_001");
    _pSeTx->set(SE_FIRE_TORPEDO, "WAVE_MY_FIRE_TORPEDO_001");

    veloTurboTop_ = 30000;
    veloTurboBottom_ = 10000;

    frame_soft_rapidshot_ = 0;
    is_being_soft_rapidshot_ = false;
    just_shot_ = false;
    is_shooting_laser_ = false;
    can_shoot_laser_ = false;
    frame_shot_pressed_ = 0;

    can_control_ = true;
    is_diving_ = false;

    blown_veloX_ = 0;
    blown_veloY_ = 0;
    blown_veloZ_ = 0;
    way_ = WAY_NONE;
    prev_way_ = WAY_NONE;
    stc_ = VB_NEUTRAL_STC;
    is_just_change_way_ = true;

    //MP初期値
    mp_ = MY_SHIP_START_MP;
    //mp_を変えると、内部参照する MpBar の表示が連動して変わる

    //Vreathは実値を _pStatus のSTAT_Stamina値を参照するように設定。
//    vreath_.link( &(_pStatus->_paValue[STAT_Stamina]._int_val) );
    //STAT_Staminaが減れば、vreath_ が変化し、それを内部参照する VreathBar の表示が連動して変わる

    //魔法メーター設置
    pMagicMeter_ = NEW MagicMeter("MagicMeter", &mp_, &(_pStatus->_paValue[STAT_Stamina]._int_val) );
    pMagicMeter_->position(PX_C(100), PX_C(PROPERTY::GAME_BUFFER_HEIGHT) - (pMagicMeter_->height_) - PX_C(16+16+16));
    addSubGroup(pMagicMeter_);

    r_blown_velo_attenuate_ = 0.8;

    invincible_frames_ = 60 * 10;

    trace_delay_count_ = 0;
    is_trace_waiting_ = false;
}
void MyShip::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void MyShip::initialize() {
    _TRACE_("MyShip::initialize()");

    //種別に振り分け
//    getSceneDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pDepo_MyShots001_->extract());
//    getSceneDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pDepo_MyWaves001_->extract());
    //getSceneDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pLaserChipDepo_->extract());

    setHitAble(true);
    _pColliChecker->makeCollision(1);
//    _pColliChecker->setColliSphere(0, -100000, -50000, 20000, 100000);
// _pColliChecker->setColliAAB(0, -100000, -50000, 20000, 10000, 40000, 80000);
      _pColliChecker->setColliAAB_Cube(0, 40000);
//    _pColliChecker->setColliSphere(1, 0,-100000,0, 30000, true, true, true);
//    _pColliChecker->setColliSphere(2, 0,100000,0, 30000, true, true, true);
//    _pColliChecker->setColliSphere(3, 0,0,-100000, 30000, true, true, true);
//    _pColliChecker->setColliSphere(4, 0,0,100000, 30000, true, true, true);

    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(1000);
    _pScaler->forceRange(1000, 7000);

    //setMaterialColor(1.0, 0.5, 0.5);
    setAlpha(1.0);

    _pKurokoB->forceVxyzMvVeloRange(-veloTurboTop_, veloTurboTop_);
    _pKurokoB->setZeroVxyzMvAcce();
    //        _pKurokoA->forceMvVeloRange(iMvBtmVelo_MT_, veloBeginMT_);
    //        _pKurokoA->addMvVelo(veloBeginMT_);  //速度追加
    //        _pKurokoA->setMvAcce(acce_MT_);

    _pKurokoA->setFaceAngVelo(AXIS_X, 300);
}


void MyShip::onReset() {
    _TRACE_("MyShip::onReset()");
    frame_soft_rapidshot_ = 0;
    is_being_soft_rapidshot_ = false;
    just_shot_ = false;
    is_shooting_laser_ = false;
    can_shoot_laser_ = false;
    frame_shot_pressed_ = 0;
    _X = _Y = _Z = 0;
    way_ = WAY_NONE;
    prev_way_ = WAY_NONE;
    way_switch_.reset();

    mp_ = MY_SHIP_START_MP;
    _pStatus->reset();
}

void MyShip::onActive() {
    _TRACE_("MyShip::onActive()");
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
}
void MyShip::onInactive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
//    pLaserChipDepo_->reset();
}
void MyShip::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    int pos_camera = P_VAM->pos_camera_;

    if (!can_control_) {
        return;
    }

    //息切れ
    if (_pStatus->get(STAT_Stamina) < 0) {
        _pStatus->set(STAT_Stamina, 0);
        return; //操作不可
    }

    //VAMSystemの実装
    // (Viewpoint Adaptive Moving System 視点適応型移動システム)
    stc_ = pVbPlay->getBeingPressedStick();
    if (pos_camera == VAM_POS_RIGHT) {
        //右サイドビュー(右から左へスクロール)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //前方
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pos_camera == VAM_POS_LEFT) {
        //左サイドビュー(左から右へスクロール)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //後方
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (pos_camera == VAM_POS_TOP) {
        //トップビュー(上から下へスクロール)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //前方
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
    } else if (pos_camera == VAM_POS_BOTTOM) {
        //ボトムビュー(下から上へスクロール)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //後方
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
    } else if (pos_camera > VAM_POS_TO_BEHIND) {
        //背後ビュー（奥から手前にスクロール）
        if (pVbPlay->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    }
    if (pVbPlay->isReleasedUp(VB_UP)) {
        way_switch_.OFF_UP();    // ↑ を離す
    }
    if (pVbPlay->isReleasedUp(VB_RIGHT)) {
        way_switch_.OFF_RIGHT(); // → を離す
    }
    if (pVbPlay->isReleasedUp(VB_LEFT)) {
        way_switch_.OFF_LEFT();  // ← を離す
    }
    if (pVbPlay->isReleasedUp(VB_DOWN)) {
        way_switch_.OFF_DOWN();  // ↓ を離す
    }
    MoveWay prev_way = way_;
    way_ = (MoveWay)(way_switch_.getIndex()); //上記を考慮された方向値が入る
    if (prev_way != way_) {
        is_just_change_way_ = true;
    } else {
        is_just_change_way_ = false;
    }
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        int tmp = iMoveSpeed_;
        iMoveSpeed_ /= 8; //オプション操作中移動は遅い
        (this->*paFuncMove[way_])();   //方向値に応じた移動処理メソッドを呼び出す
        iMoveSpeed_ = tmp;
    } else {
        (this->*paFuncMove[way_])();   //方向値に応じた移動処理メソッドを呼び出す
    }

    if (pVbPlay->isPushedDown(VB_TURBO)) {
        UTIL::activateProperEffect01Of(this); //ターボ開始のエフェクト
        (this->*paFuncTurbo[way_])(); //方向値に応じたターボ開始処理メソッドを呼び出す
        _pSeTx->play3D(SE_TURBO);
    } else {
        //Notターボ開始時
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //ターボボタンを押し続けることで、速度減衰がゆるやかになり、
            //移動距離を伸ばす
            _pKurokoB->_veloVxMv *= 0.99;
            _pKurokoB->_veloVyMv *= 0.99;
            _pKurokoB->_veloVzMv *= 0.99;
        } else {
            //ターボを離した場合、速度減衰。
            _pKurokoB->_veloVxMv *= 0.8;
            _pKurokoB->_veloVyMv *= 0.8;
            _pKurokoB->_veloVzMv *= 0.8;
        }
    }

    //スピンが勢いよく回っているならば速度を弱める
    angvelo MZ = angRXTopVelo_MZ_-3000; //3000は通常旋回時に速度を弱めてangRXTopVelo_MZ_を超えないようにするため、やや手前で減速すると言う意味（TODO:要調整）。
    if (_pKurokoA->_angveloFace[AXIS_X] >= MZ) {
        _pKurokoA->_angveloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_*2);
    } else if (_pKurokoA->_angveloFace[AXIS_X] <= -MZ) {
        _pKurokoA->_angveloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_*2);
    }

    //左右が未入力なら、機体を水平にする（但し勢いよく回っていない場合に限る。setStopTargetFaceAngの第4引数より角速度がゆるい場合受け入れ）
    if (pVbPlay->isBeingPressed(VB_LEFT) || pVbPlay->isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pKurokoA->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < D180ANG) {
            _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
        } else if (-1*D180ANG < dist && dist < 0) {
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_);
        }
        _pKurokoA->setMvAcce(0);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, 0, TURN_BOTH, angRXTopVelo_MZ_);
    }

    ////////////////////////////////////////////////////

    //座標に反映
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pScaler->behave();
    _pSeTx->behave();

    if (invincible_frames_ > 0) {
        setHitAble(false);
        invincible_frames_ --;
        if (getActiveFrame() % 2 == 0) {
            setAlpha(0.6);
        } else {
            setAlpha(0);
        }
        if (invincible_frames_ == 0) {
            setHitAble(true);
            setAlpha(1.0);
        }
    } else {

    }
    //吹っ飛び
    if (ABS(blown_veloX_) < PX_C(1)) {
        blown_veloX_ = 0;
    } else {
        _X += blown_veloX_;
        blown_veloX_ *= r_blown_velo_attenuate_;
    }
    if (ABS(blown_veloY_) < PX_C(1)) {
        blown_veloY_ = 0;
    } else {
        _Y += blown_veloY_;
        blown_veloY_ *= r_blown_velo_attenuate_;
    }
    if (ABS(blown_veloZ_) < PX_C(1)) {
        blown_veloZ_ = 0;
    } else {
        _Z += blown_veloZ_;
        blown_veloZ_ *= r_blown_velo_attenuate_;
    }

    if (is_diving_) {
        //突入モーション時は、移動範囲制御無し
    } else {
        //通常移動範囲制御
        if (_Y > MyShip::lim_Y_top_) {
            _Y = MyShip::lim_Y_top_;
        } else if (_Y < MyShip::lim_Y_bottom_ ) {
            _Y = MyShip::lim_Y_bottom_;
        }

        if (_X > MyShip::lim_X_front_) {
            _X = MyShip::lim_X_front_;
        } else if (_X < MyShip::lim_X_behaind_) {
            _X = MyShip::lim_X_behaind_;
        }

        if (_Z > MyShip::lim_Z_left_) {
            _Z = MyShip::lim_Z_left_;
        } else if (_Z < MyShip::lim_Z_right_) {
            _Z = MyShip::lim_Z_right_;
        }
    }


    //オプションのために座標情報保存
    pRing_MyShipGeoHistory2_->next()->set(this);
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        GgafDxGeoElem* pGeoMyShipPrev = pRing_MyShipGeoHistory2_->getPrev();
        //(_X_local, _Y_local, _Z_local) は、初期位置(0,0,0) から、
        //VB_OPTIONを押している間のみ移動した増分座標を保持。
        _X_local += (_X - pGeoMyShipPrev->X); //移動増分
        _Y_local += (_Y - pGeoMyShipPrev->Y);
        _Z_local += (_Z - pGeoMyShipPrev->Z);
    } else {
        //(_X_local, _Y_local, _Z_local) はVB_OPTIONを離した時の初期位置(0,0,0) からの増分座標がはいっている。
        //したがって、pRing_MyShipGeoHistory4OptCtrler_は、
        //自機の絶対座標履歴から、VB_OPTION を押した場合の増分座標を除外した移動座標履歴（絶対座標）となる。
        //この履歴の座標に(_X_local, _Y_local, _Z_local) に(_X_local, _Y_local, _Z_local)座標を足せば、自機の座標と同値
        GgafDxGeoElem* pGeo = pRing_MyShipGeoHistory4OptCtrler_->getCurrent();
        if (pGeo->X == _X - _X_local && pGeo->Y == _Y - _Y_local && pGeo->Z == _Z - _Z_local) {
            //移動していない場合
            trace_delay_count_++;
            if (trace_delay_count_ > TRACE_DELAY_WAIT_FRAME) { //1秒間トレースな状態を維持できるようにする。
                pRing_MyShipGeoHistory4OptCtrler_->next()->set(_X - _X_local,
                                                               _Y - _Y_local,
                                                               _Z - _Z_local );
                is_trace_waiting_ = false;
            } else {
                is_trace_waiting_ = true;
            }
        } else {
            trace_delay_count_ = 0;
            pRing_MyShipGeoHistory4OptCtrler_->next()->set(_X - _X_local,
                                                           _Y - _Y_local,
                                                           _Z - _Z_local );
            is_trace_waiting_ = false;
        }

    }

    //毎フレームの呼吸の消費
    _pStatus->minus(STAT_Stamina, MY_SHIP_VREATH_COST);
}

void MyShip::processJudgement() {
    if (!can_control_) {
        return;
    }
    VirtualButton* pVbPlay = VB_PLAY;



    //debug ---->
//    if (GgafDxInput::isPushedDownKey(DIK_W)) {
//        TestGuShot* pShot = (TestGuShot*)pDepo_TestGuShot_->dispatch();
//        if (pShot) {
//            pShot->positionAs(this);
//        }
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_E)) {
//        TestChokiShot* pShot = (TestChokiShot*)pDepo_TestChokiShot_->dispatch();
//        if (pShot) {
//            pShot->positionAs(this);
//        }
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_R)) {
//        TestPaShot* pShot = (TestPaShot*)pDepo_TestPaShot_->dispatch();
//        if (pShot) {
//            pShot->positionAs(this);
//        }
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_T)) {
//        TestNomalShot* pShot = (TestNomalShot*)pDepo_TestNomalShot_->dispatch();
//        if (pShot) {
//            pShot->positionAs(this);
//        }
//    }
    //<---- debug


    //debug ---->
//#ifdef MY_DEBUG
//    if (GgafDxInput::isPushedDownKey(DIK_W)) {
//        MyStraightLaserChip001::chengeTex(0);
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_E)) {
//        MyStraightLaserChip001::chengeTex(1);
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_R)) {
//        MyStraightLaserChip001::chengeTex(2);
//    }
//#endif
    //<---- debug


    //自機消滅テスト
//    if (pVbPlay->isBeingPressed(VB_BUTTON8)) {
//        _TRACE_("自機消滅テスト");
//        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
//    }



    //ショット関連処理
    is_shooting_laser_ = false;
    if (pVbPlay->isBeingPressed(VB_SHOT1)) {
        frame_shot_pressed_ ++;
        if (can_shoot_laser_) {
            if (frame_shot_pressed_ > 30) { //30フレーム押しっぱなしでレーザーへ
                is_shooting_laser_ = true;
            }
        }
    } else {
        frame_shot_pressed_ = 0;
        pLockonCtrler_->releaseAllLockon(); //ロックオン解除
    }

    //レーザー発射
    if (is_shooting_laser_) {
        if (pVbPlay->isBeingPressed(VB_SHOT1)) {
            LaserChip* pLaserChip = pLaserChipDepo_->dispatch();
            if (pLaserChip) {
                if (pLaserChip->_pChip_front == nullptr) {
                    _pSeTx->play3D(SE_FIRE_LASER);
                }
            }
        } else {

        }
    }

    //ソフト連射
    //1プッシュで4F毎に最大3発
    if (pVbPlay->isPushedDown(VB_SHOT1) && !pVbPlay->isBeingPressed(VB_POWERUP)) {
        is_being_soft_rapidshot_ = true;
        if (frame_soft_rapidshot_ >= SOFT_RAPIDSHOT_INTERVAL) {
            //SOFT_RAPIDSHOT_INTERVAL フレームより遅い場合
            //連射と連射のつなぎ目が無いようにする
            frame_soft_rapidshot_ = frame_soft_rapidshot_ % SOFT_RAPIDSHOT_INTERVAL;
        } else {
            //SOFT_RAPIDSHOT_INTERVAL フレームより速い連射の場合
            //これを受け入れて強制的に発射できる(手動連射のほうが速く連射できるようにしたい。)
            frame_soft_rapidshot_ = 0;
        }
    }
    just_shot_ = false;
    if (is_being_soft_rapidshot_) {
        if (frame_soft_rapidshot_ % SOFT_RAPIDSHOT_INTERVAL == 0) {
            just_shot_ = true;//たった今ショットしましたフラグ
            MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
            if (pShot) {
                _pSeTx->play3D(SE_FIRE_SHOT);
                pShot->positionAs(this);
            }
            if (frame_soft_rapidshot_ >= SOFT_RAPIDSHOT_INTERVAL*(SOFT_RAPIDSHOT_NUM-1)) {
                //SOFT_RAPIDSHOT_NUM 発打ち終えたらソフト連射終了
                is_being_soft_rapidshot_ = false;
            }
        }
    }
    if (is_being_soft_rapidshot_) {
        frame_soft_rapidshot_++;
    }

    //光子魚雷発射
    if (pVbPlay->isBeingPressed(VB_SHOT2)) {
        if (this->pTorpedoCtrler_->fire()) {
            _pSeTx->play3D(MyShip::SE_FIRE_TORPEDO);
        }
    }
//    if (pVbPlay->isBeingPressed(VB_SHOT2)) {
//        MyOptionController** papOptCtrler = P_MYSHIP_SCENE->papOptionCtrler_;
//        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
//            if (papOptCtrler[i]->pOption_->pTorpedoCtrler_->fire()) {
//                papOptCtrler[i]->pOption_->_pSeTx->play3D(MyOption::SE_FIRE_TORPEDO);
//            }
//        }
//
////        bool can_fire = true;
////        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
////            if (papOptCtrler[i]->pOption_->pTorpedoCtrler_->in_firing_) {
////                can_fire = false;
////                break;
////            }
////        }
////        if (can_fire) {
////            for (int i = 0; i < MyOptionController::now_option_num_; i++) {
////                if (i == 0) {
////                    _pSeTx->play3D(3);
////                }
////                papOptCtrler[i]->pOption_->pTorpedoCtrler_->fire();
////            }
////        }
//    }

}

void MyShip::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    int vreath = _pStatus->get(STAT_Stamina);
    if (UTIL::calcMyStamina(this, pOther) <= 0) {
        //自機爆発開催
        setHitAble(false);
        _pSeTx->play3D(SE_EXPLOSION);
        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }
    int damage = vreath - _pStatus->get(STAT_Stamina);
    if (damage > 0){
        pMagicMeter_->pDamageDispBar_->addDamage(damage);
    }

    //壁の場合特別な処理
    if (pOther->getKind() & KIND_CHIKEI) {
        //吹っ飛び方向を考える。
        //現在の移動の逆方向（吹っ飛び威力は２倍に）
        GgafDxGeoElem* pGeoMyShipPrev = pRing_MyShipGeoHistory2_->getPrev();
        float vx1,vy1,vz1;
        coord dX1 = -(_X - pGeoMyShipPrev->X);
        coord dY1 = -(_Y - pGeoMyShipPrev->Y);
        coord dZ1 = -(_Z - pGeoMyShipPrev->Z);
        if (dX1 == 0 && dY1 == 0 && dZ1 == 0) {
            vx1 = vy1 = vz1 = 0;
        } else {
            UTIL::getNormalizeVector(dX1, dY1, dZ1,
                                     vx1, vy1, vz1 );
        }
        float vx2, vy2, vz2;
        coord dX2,dY2,dZ2;
        if ( pOther->instanceOf(Obj_WallPartsActor)) {
            if ((pOther->_pChecker->_pCollisionArea->_papColliPart[0]->_shape_kind) & COLLI_AAPRISM) {
                //プリズム壁
                ColliAAPrism* pPrism = (ColliAAPrism*)(pOther->_pChecker->_pCollisionArea->_papColliPart[0]);
                int pos_prism = pPrism->_pos_prism;
                if (pos_prism & POS_PRISM_XY) {
                    if (pos_prism & POS_PRISM_pp) {
                        //            ↑ y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ┌───┐
                        //        │＼こち│
                        // x- ←  │  ＼ら│  → x+
                        //        │    ＼│
                        //        └───┘
                        // (_x1,_y1)      (_x2,_y1)
                        //            ↓ y-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            ↑ y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ┌───┐
                        //        │こち／│
                        // x- ←  │ら／  │  → x+
                        //        │／    │
                        //        └───┘
                        // (_x1,_y1)      (_x2,_y1)
                        //            ↓ y-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            ↑ y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ┌───┐
                        //        │    ／│
                        // x- ←  │  ／こ│  → x+
                        //        │／ちら│
                        //        └───┘
                        // (_x1,_y1)      (_x2,_y1)
                        //            ↓ y-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else { // のこりは POS_PRISM_nn
                        //            ↑ y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ┌───┐
                        //        │＼    │
                        // x- ←  │こ＼  │  → x+
                        //        │ちら＼│
                        //        └───┘
                        // (_x1,_y1)      (_x2,_y1)
                        //            ↓ y-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    }

                } else if (pos_prism & POS_PRISM_YZ) {

                    if (pos_prism & POS_PRISM_pp) {
                        //            ↑ z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ┌───┐
                        //        │＼こち│
                        // y- ←  │  ＼ら│  → y+
                        //        │    ＼│
                        //        └───┘
                        // (_y1,_z1)      (_y2,_z1)
                        //            ↓ z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            ↑ z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ┌───┐
                        //        │こち／│
                        // y- ←  │ら／  │  → y+
                        //        │／    │
                        //        └───┘
                        // (_y1,_z1)      (_y2,_z1)
                        //            ↓ z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            ↑ z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ┌───┐
                        //        │    ／│
                        // y- ←  │  ／こ│  → y+
                        //        │／ちら│
                        //        └───┘
                        // (_y1,_z1)      (_y2,_z1)
                        //            ↓ z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    } else { // のこりは POS_PRISM_nn
                        //            ↑ z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ┌───┐
                        //        │＼    │
                        // y- ←  │こ＼  │  → y+
                        //        │ちら＼│
                        //        └───┘
                        // (_y1,_z1)      (_y2,_z1)
                        //            ↓ z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    }

                } else if (pos_prism & POS_PRISM_ZX) {
                    if (pos_prism & POS_PRISM_pp) {
                        //            ↑ x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ┌───┐
                        //        │＼こち│
                        // z- ←  │  ＼ら│  → z+
                        //        │    ＼│
                        //        └───┘
                        // (_z1,_x1)      (_z2,_x1)
                        //            ↓ x-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            ↑ x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ┌───┐
                        //        │こち／│
                        // z- ←  │ら／  │  → z+
                        //        │／    │
                        //        └───┘
                        // (_z1,_x1)      (_z2,_x1)
                        //            ↓ x-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            ↑ x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ┌───┐
                        //        │    ／│
                        // z- ←  │  ／こ│  → z+
                        //        │／ちら│
                        //        └───┘
                        // (_z1,_x1)      (_z2,_x1)
                        //            ↓ x-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else { // のこりは POS_PRISM_nn
                        //            ↑ x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ┌───┐
                        //        │＼    │
                        // z- ←  │こ＼  │  → z+
                        //        │ちら＼│
                        //        └───┘
                        // (_z1,_x1)      (_z2,_x1)
                        //            ↓ x-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y                ));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    }
                } else {

                }
            } else {
                //プリズム以外の壁
                dX2 = (_X - pOther->_X);
                dY2 = (_Y - pOther->_Y);
                dZ2 = (_Z - pOther->_Z);
            }
        } else {
            GgafDxCollisionArea* pCollisionArea = pOther->_pChecker->_pCollisionArea;
            if (pCollisionArea->_hit_colli_part_index >= 0) {
                GgafDxCollisionPart* pPart = pCollisionArea->_papColliPart[pCollisionArea->_hit_colli_part_index];
                dX2 = (_X - (pOther->_X + pPart->_cx));
                dY2 = (_Y - (pOther->_Y + pPart->_cy));
                dZ2 = (_Z - (pOther->_Z + pPart->_cz));
            } else {
                dX2 = (_X - pOther->_X);
                dY2 = (_Y - pOther->_Y);
                dZ2 = (_Z - pOther->_Z);
            }
        }

        if (dX2 == 0 && dY2 == 0 && dZ2 == 0) {
            vx2 = vy2 = vz2 = 0;
        } else {
            UTIL::getNormalizeVector(dX2, dY2, dZ2,
                                     vx2, vy2, vz2 );
        }

        float vx3, vy3, vz3;
        UTIL::getNormalizeVector(
                    vx1+vx2, vy1+vy2, vz1+vz2,
                    vx3, vy3, vz3);
        setBlownVelo(vx3*PX_C(40), vy3*PX_C(40), vz3*PX_C(40), 0.8);
        setInvincibleFrames(120);
    }
    if (pOther->getKind() & KIND_ITEM)  {
    } else {
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void MyShip::doNotingMoveInput() {

}

void MyShip::setMoveSpeedLv(int lv) {
        //lv_MoveSpeed_ = lv;
        iMoveSpeed_ = PX_C(lv);
    }

void MyShip::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

void MyShip::setBlownVelo(velo prm_blown_veloX, velo prm_blown_veloY, velo prm_blown_veloZ, double prm_r_blown_velo_attenuate) {
    blown_veloX_ += prm_blown_veloX;
    blown_veloY_ += prm_blown_veloY;
    blown_veloZ_ += prm_blown_veloZ;
    r_blown_velo_attenuate_ = prm_r_blown_velo_attenuate;
}

void MyShip::setInvincibleFrames(int prm_frames) {
    setHitAble(false);
    invincible_frames_ = prm_frames;
}


void MyShip::move_WAY_NONE() {
}

void MyShip::move_WAY_UP() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D90ANG, 0);
    }
    _Y += iMoveSpeed_;
}

void MyShip::move_WAY_UP_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, 0);
    }
    _Y += iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_UP_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D135ANG, 0);
    }
    _Y += iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, 0);
    }
    _X += iMoveSpeed_;
}

void MyShip::move_WAY_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D180ANG, 0);
    }
    _X -= iMoveSpeed_;
}

void MyShip::move_WAY_DOWN() {
    _pKurokoA->setRzRyMvAng(D270ANG, 0);
    _Y -= iMoveSpeed_;
}

void MyShip::move_WAY_DOWN_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D255ANG, 0);
    }
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_DOWN_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, 0);
    }
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D270ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_, TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_;
}

void MyShip::move_WAY_ZLEFT_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D315ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2)); //反時計回り
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D90ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*angRXStop_MZ_, TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_;
}

void MyShip::move_WAY_ZRIGHT_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D135ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_UP() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/2);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _Y += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_DOWN() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/2);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);

    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_UP() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _Y += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_DOWN() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_UP_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG+D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/3);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/3), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _X += iMoveSpeed_ * NANAME3D_RATE;
    _Y += iMoveSpeed_ * NANAME3D_RATE;
    _Z += iMoveSpeed_ * NANAME3D_RATE;
}

void MyShip::move_WAY_ZLEFT_UP_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG-D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/3);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/3), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _X -= iMoveSpeed_ * NANAME3D_RATE;
    _Y += iMoveSpeed_ * NANAME3D_RATE;
    _Z += iMoveSpeed_ * NANAME3D_RATE;
}

void MyShip::move_WAY_ZLEFT_DOWN_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG+D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/3);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/3), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);

    }
    _X += iMoveSpeed_ * NANAME3D_RATE;
    _Y -= iMoveSpeed_ * NANAME3D_RATE;
    _Z += iMoveSpeed_ * NANAME3D_RATE;
}


void MyShip::move_WAY_ZLEFT_DOWN_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG-D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/3);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/3), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);

    }
    _X -= iMoveSpeed_ * NANAME3D_RATE;
    _Y -= iMoveSpeed_ * NANAME3D_RATE;
    _Z += iMoveSpeed_ * NANAME3D_RATE;
}


void MyShip::move_WAY_ZRIGHT_UP_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG-D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/3));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/3)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _X += iMoveSpeed_ * NANAME3D_RATE;
    _Y += iMoveSpeed_ * NANAME3D_RATE;
    _Z -= iMoveSpeed_ * NANAME3D_RATE;
}

void MyShip::move_WAY_ZRIGHT_UP_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG+D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/3));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/3)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _X -= iMoveSpeed_ * NANAME3D_RATE;
    _Y += iMoveSpeed_ * NANAME3D_RATE;
    _Z -= iMoveSpeed_ * NANAME3D_RATE;
}

void MyShip::move_WAY_ZRIGHT_DOWN_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG-D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/3));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/3)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _X += iMoveSpeed_ * NANAME3D_RATE;
    _Z -= iMoveSpeed_ * NANAME3D_RATE;
    _Y -= iMoveSpeed_ * NANAME3D_RATE;
}

void MyShip::move_WAY_ZRIGHT_DOWN_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG+D45ANG);
        //旋廻
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/3));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/3)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _X -= iMoveSpeed_ * NANAME3D_RATE;
    _Z -= iMoveSpeed_ * NANAME3D_RATE;
    _Y -= iMoveSpeed_ * NANAME3D_RATE;
}


/////////////////TURBO_BEGIN

void MyShip::turbo_WAY_NONE() {
}


void MyShip::turbo_WAY_UP() {
    _pKurokoA->setRzRyMvAng(D90ANG, 0);
    _pKurokoB->addVyMvVelo(veloBeginMT_);
}

void MyShip::turbo_WAY_UP_FRONT() {
    _pKurokoA->setRzRyMvAng(D45ANG, 0);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
}

void MyShip::turbo_WAY_UP_BEHIND() {
    _pKurokoA->setRzRyMvAng(D135ANG, 0);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
}

void MyShip::turbo_WAY_FRONT() {
    _pKurokoA->setRzRyMvAng(0, 0);
    _pKurokoB->addVxMvVelo(veloBeginMT_);
}

void MyShip::turbo_WAY_BEHIND() {
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoB->addVxMvVelo(-veloBeginMT_);
}

void MyShip::turbo_WAY_DOWN() {
    _pKurokoA->setRzRyMvAng(D270ANG, 0);
    _pKurokoB->addVyMvVelo(-veloBeginMT_);
}

void MyShip::turbo_WAY_DOWN_BEHIND() {
    _pKurokoA->setRzRyMvAng(D255ANG, 0);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
}

void MyShip::turbo_WAY_DOWN_FRONT() {
    _pKurokoA->setRzRyMvAng(D315ANG, 0);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
}

void MyShip::turbo_WAY_ZLEFT() {
    _pKurokoB->addVzMvVelo(veloBeginMT_);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_FRONT() {
    _pKurokoA->setRzRyMvAng(0, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_BEHIND() {
    _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_FRONT() {
    _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT() {
    _pKurokoA->setRzRyMvAng(0, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_BEHIND() {
    _pKurokoA->setRzRyMvAng(0, D135ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_UP() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_DOWN() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_UP() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_DOWN() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_UP_FRONT() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG+D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_UP_BEHIND() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG-D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_DOWN_FRONT() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG+D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZLEFT_DOWN_BEHIND() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG-D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_UP_FRONT() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG-D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_UP_BEHIND() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG+D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_DOWN_FRONT() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG-D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

void MyShip::turbo_WAY_ZRIGHT_DOWN_BEHIND() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG+D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //旋廻
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //勢いよく回転開始
}

MyShip::~MyShip() {
    GGAF_DELETE(pRing_MyShipGeoHistory4OptCtrler_);
    GGAF_DELETE(pRing_MyShipGeoHistory2_);
}

