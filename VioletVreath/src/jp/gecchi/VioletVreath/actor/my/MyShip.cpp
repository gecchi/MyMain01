#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyShip::wk_dist = 0;
angle MyShip::wk_angRx = 0;

#define S_OPTION 0
coord MyShip::lim_top_     =  0;
coord MyShip::lim_bottom_  =  0;
coord MyShip::lim_front_   =  0;
coord MyShip::lim_behaind_ =  0;
coord MyShip::lim_zleft_   =  0;
coord MyShip::lim_zright_  =  0;

MyShip::MyShip(const char* prm_name) :
        DefaultD3DXMeshActor(prm_name, "VicViper", STATUS(MyShip)) {
//DefaultMeshActor(prm_name, "jiki", STATUS(MyShip)) {
//CubeMapMeshActor(prm_name, "wakka", STATUS(MyShip)) {
//DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton", STATUS(MyShip)) {
    _class_name = "MyShip";
    //changeEffectTechnique("DestBlendOne"); //加算合成Technique指定

    //画面の大きさに伴って、移動範囲を決定
    //このあたりはFovXに依存するので微調整。
    int harf_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2;
    int harf_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2;

    lim_top_     =  harf_height + GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*4*LEN_UNIT; //上は、高さ4画面分
    lim_bottom_  = -harf_height - GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*4*LEN_UNIT; //下は、高さ4画面分
    lim_front_   =  harf_width + GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2*LEN_UNIT;   //前は、幅の2画面分
    lim_behaind_ = -harf_width - GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2*LEN_UNIT;   //後ろは、幅の2画面分
    lim_zleft_   =  harf_width + GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2*LEN_UNIT;   //手前は、幅の2画面分
    lim_zright_  = -harf_width - GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2*LEN_UNIT;   //奥は、幅の2画面分
    _TRACE_("MyShip::MyShip 範囲 X("<<lim_behaind_<<" ~ "<<lim_front_<<") Y("<<lim_bottom_<<" ~ "<<lim_top_<<") Z("<<lim_zright_<<" ~ "<<lim_zleft_<<")");

    /** 移動スピードレベルに相応する移動スピード */
    iMoveSpeed_ = 2000;
    //CommonSceneがnewの場合設定
    angRXVelo_BeginMZ_ = 1000; //奥又は手前へ通常Z通常移動開始時のX軸回転角速度の初速度
    angRXAcce_MZ_ = 300; //奥又は手前へ通常Z移動中のX軸回転角速度の初角加速度
    angRXTopVelo_MZ_ = 5000; //奥又は手前へ通常Z移動中のX軸回転角速度の上限角速度
    angRXStop_MZ_ = 90000; //奥又は手前へ通常Z移動中のX軸回転角の目標停止角度

    //angRXVelo_BeginMZT_ = 23000; //奥又は手前へTurbo移動開始時のX軸回転角速度の初速度
    angRXVelo_BeginMZT_ = 40000;

    iMvBtmVelo_MT_ = 0; //Turbo移動中の移動速度の最低速度
    iMvVelo_BeginMT_ = 40000; //Turbo移動開始時の移動速度の初速度
    iMvAcce_MT_ = -200; //Turbo移動中の移動速度の加速度

//    pOptionCtrlr_ = NEW MyOptionController("MY_OPTION_PARENT");
//    addSubLast(pOptionCtrlr_);

    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        pDepo_MyShots001_->addSubLast(pShot);
    }
    addSubGroup(pDepo_MyShots001_);

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        std::string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setPositionSource(this); //位置だけ同期
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);


    pEffectTurbo001_ = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(pEffectTurbo001_);
//    pEffectTurbo002_ = NEW EffectTurbo002("EffectTurbo002");
//    addSubGroup(pEffectTurbo002_);




    //トレース用履歴
    pRing_MyShipGeoHistory4OptCtrlr_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    pRing_MyShipGeoHistory2_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
//    pRing_MyShipGeoOffsetHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (UINT32 i = 0; i < 300; i++) {
        pRing_MyShipGeoHistory4OptCtrlr_->addLast(NEW GgafDxGeoElem(this));
        pRing_MyShipGeoHistory2_->addLast(NEW GgafDxGeoElem(0,0,0));
//        pRing_MyShipGeoOffsetHistory_->addLast(NEW GgafDxGeoElem(this));
    }

    iMoveVelo_ = 0;

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

    _pSeTx->useSe(4);
    _pSeTx->set(0, "se-020");
    _pSeTx->set(1,"laser001", 99);
    _pSeTx->set(2,"fire01", 99);
    _pSeTx->set(3,"bse5", 99);

    iMvVelo_TurboTop_ = 30000;
    iMvVelo_TurboBottom_ = 10000;

    can_control_ = true;
    is_diving_ = false;

    blown_veloX_ = 0;
    blown_veloY_ = 0;
    blown_veloZ_ = 0;
    anti_blown_velo_ = 100;
    way_ = WAY_NONE;
    prev_way_ = WAY_NONE;
    is_just_change_way_ = true;

    mp_.config(600, 100000); //値 100000 で表示は600pxとする。
    mp_.set(100000);         //初期値は100000
    //vreath_ は mp_ のメーターの長さ(px)にあわす。実値を _pStatus の値を参照するように設定。
    vreath_.config(mp_._max_val_px, _pStatus->get(STAT_Stamina), &(_pStatus->_paValue[STAT_Stamina]._int_val));

    //魔法メーター設置
    pMagicMeter_ = NEW MagicMeter("MagicMeter", &mp_, &vreath_);
    pMagicMeter_->locate(PX_C(100), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 100.0f));
    addSubGroup(pMagicMeter_);

}
void MyShip::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void MyShip::initialize() {

    //種別に振り分け
//    getDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pDepo_MyShots001_->extract());
//    getDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pDepo_MyWaves001_->extract());
    //getDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pLaserChipDepo_->extract());

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
    _pScaler->forceScaleRange(1000, 7000);

    //setMaterialColor(1.0, 0.5, 0.5);
    setAlpha(1.0);


    _pKurokoB->forceVxMvVeloRange(-iMvVelo_TurboTop_, iMvVelo_TurboTop_);
    _pKurokoB->forceVyMvVeloRange(-iMvVelo_TurboTop_, iMvVelo_TurboTop_);
    _pKurokoB->forceVzMvVeloRange(-iMvVelo_TurboTop_, iMvVelo_TurboTop_);

    _pKurokoB->setVxMvAcce(0);
    _pKurokoB->setVyMvAcce(0);
    _pKurokoB->setVzMvAcce(0);
    //        _pKurokoA->forceMvVeloRange(iMvBtmVelo_MT_, iMvVelo_BeginMT_);
    //        _pKurokoA->addMvVelo(iMvVelo_BeginMT_);  //速度追加
    //        _pKurokoA->setMvAcce(iMvAcce_MT_);

    _pKurokoA->setFaceAngVelo(AXIS_X, 300);
}


void MyShip::onReset() {
    frame_soft_rapidshot_ = 0;
    is_being_soft_rapidshot_ = false;
    just_shot_ = false;
    is_shooting_laser_ = false;
    frame_shot_pressed_ = 0;
    _X = _Y = _Z = 0;
    way_ = WAY_NONE;
    prev_way_ = WAY_NONE;
    way_switch_.reset();
    _pStatus->reset();

}

void MyShip::onActive() {

}




void MyShip::processBehavior() {

//    ///////////////////////スペキュラテスト
//    if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _pModel->_specular += 0.1;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pModel->_specular -= 0.1;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_O)) {
//        _pModel->specular_power_ += 0.1;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_P)) {
//        _pModel->specular_power_ -= 0.1;
//    }
//    /////////////////////////////////////

    if (!can_control_) {
        return;
    }

    //VAMSystemの実装
    // (Viewpoint Adaptive Moving System 視点適応型移動システム)
    stc_ = VB_PLAY->getBeingPressedStick();
    if (P_VAM->pos_camera_ == VAM_POS_RIGHT) {
        //右サイドビュー(右から左へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //前方
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (P_VAM->pos_camera_ == VAM_POS_LEFT) {
        //左サイドビュー(左から右へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //後方
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    } else if (P_VAM->pos_camera_ == VAM_POS_TOP) {
        //トップビュー(上から下へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //前方
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //後方
        }
    } else if (P_VAM->pos_camera_ == VAM_POS_BOTTOM) {
        //ボトムビュー(下から上へスクロール)
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //後方
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //前方
        }
    } else if (P_VAM->pos_camera_ > VAM_POS_TO_BEHIND) {
        //背後ビュー（奥から手前にスクロール）
        if (VB_PLAY->isPushedDown(VB_UP)) {     // ↑
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //上
        }
        if (VB_PLAY->isPushedDown(VB_RIGHT)) {  // →
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //右
        }
        if (VB_PLAY->isPushedDown(VB_LEFT)) {   // ←
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //左
        }
        if (VB_PLAY->isPushedDown(VB_DOWN)) {   // ↓
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //下
        }
    }
    if (VB_PLAY->isReleasedUp(VB_UP)) {
        way_switch_.OFF_UP();    // ↑ を離す
    }
    if (VB_PLAY->isReleasedUp(VB_RIGHT)) {
        way_switch_.OFF_RIGHT(); // → を離す
    }
    if (VB_PLAY->isReleasedUp(VB_LEFT)) {
        way_switch_.OFF_LEFT();  // ← を離す
    }
    if (VB_PLAY->isReleasedUp(VB_DOWN)) {
        way_switch_.OFF_DOWN();  // ↓ を離す
    }
    MoveWay prev_way = way_;
    way_ = (MoveWay)(way_switch_.getIndex()); //上記を考慮された方向値が入る
    if (prev_way != way_) {
        is_just_change_way_ = true;
    } else {
        is_just_change_way_ = false;
    }
    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
        int tmp = iMoveSpeed_;
        iMoveSpeed_ = iMoveSpeed_ / 8; //オプション操作中移動は遅い
        (this->*paFuncMove[way_])();   //方向値に応じた移動処理メソッドを呼び出す
        iMoveSpeed_ = tmp;
    } else {
        (this->*paFuncMove[way_])();   //方向値に応じた移動処理メソッドを呼び出す
    }

    if (VB_PLAY->isPushedDown(VB_TURBO)) {
        //ターボ開始時
        EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
         if (pTurbo002) {
             pTurbo002->locatedBy(this);
             pTurbo002->activate();
         }
        (this->*paFuncTurbo[way_])();
    } else {
        //Notターボ開始時
        if (VB_PLAY->isBeingPressed(VB_TURBO)) {
            //ターボを押し続けることで、移動距離を伸ばす
            _pKurokoB->_veloVxMv *= 0.95;
            _pKurokoB->_veloVyMv *= 0.95;
            _pKurokoB->_veloVzMv *= 0.95;
        } else {
            _pKurokoB->_veloVxMv *= 0.9;
            _pKurokoB->_veloVyMv *= 0.9;
            _pKurokoB->_veloVzMv *= 0.9;
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

    //左右が未入力なら、機体を水平にする（但し勢いよく回っていない場合に限る。setStopTarget_FaceAngの第4引数より角速度がゆるい場合受け入れ）
    if (VB_PLAY->isBeingPressed(VB_LEFT) || VB_PLAY->isBeingPressed(VB_RIGHT)) {

    } else {

        angle dist = _pKurokoA->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < D180ANG) {
            _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
        } else if (-1*D180ANG < dist && dist < 0) {
            _pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_);
        }
        _pKurokoA->setMvAcce(0);
        _pKurokoA->setStopTarget_FaceAng(AXIS_X, 0, TURN_BOTH, angRXTopVelo_MZ_);
    }

    ////////////////////////////////////////////////////



    //座標に反映
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pScaler->behave();
    _pSeTx->behave();

    //吹っ飛び
    if (GgafUtil::abs(blown_veloX_) < 1000) {
        blown_veloX_ = 0;
    } else if (blown_veloX_ > 0) {
        blown_veloX_ -= 1000;
    } else if (blown_veloX_ < 0) {
        blown_veloX_ += 1000;
    }
    if (GgafUtil::abs(blown_veloY_) < 1000) {
        blown_veloY_ = 0;
    } else if (blown_veloY_ > 0) {
        blown_veloY_ -= 1000;
    } else if (blown_veloY_ < 0) {
        blown_veloY_ += 1000;
    }
    if (GgafUtil::abs(blown_veloZ_) < 1000) {
        blown_veloZ_ = 0;
    } else if (blown_veloZ_ > 0) {
        blown_veloZ_ -= 1000;
    } else if (blown_veloZ_ < 0) {
        blown_veloZ_ += 1000;
    }
    _X += blown_veloX_;
    _Y += blown_veloY_;
    _Z += blown_veloZ_;


    if (!is_diving_) {
        if (_Y > MyShip::lim_top_) {
            _Y = MyShip::lim_top_;
        }
        if (_Y < MyShip::lim_bottom_ ) {
            _Y = MyShip::lim_bottom_;
        }

        if (_X > MyShip::lim_front_) {
            _X = MyShip::lim_front_;
        }
        if (_X < MyShip::lim_behaind_) {
            _X = MyShip::lim_behaind_;
        }

        if (_Z > MyShip::lim_zleft_) {
            _Z = MyShip::lim_zleft_;
        }
        if (_Z < MyShip::lim_zright_) {
            _Z = MyShip::lim_zright_;
        }
    }



    pRing_MyShipGeoHistory2_->next()->set(this);
    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
        GgafDxGeoElem* pGeoMyShipPrev = pRing_MyShipGeoHistory2_->getPrev();
        _X_local += (_X - pGeoMyShipPrev->_X);
        _Y_local += (_Y - pGeoMyShipPrev->_Y);
        _Z_local += (_Z - pGeoMyShipPrev->_Z);
    } else {
        pRing_MyShipGeoHistory4OptCtrlr_->next()->set(_X - _X_local ,
                                                      _Y - _Y_local ,
                                                      _Z - _Z_local);
    }


//    _pStatus->get(STAT_Stamina);
}

void MyShip::processJudgement() {
    if (!can_control_) {
        return;
    }
    //自機消滅テスト
    if (VB_PLAY->isBeingPressed(VB_BUTTON8)) {
        _TRACE_("自機消滅テスト");
        throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }


    //ショット関連処理
    is_shooting_laser_ = false;
    if (VB_PLAY->isBeingPressed(VB_SHOT1)) {
        frame_shot_pressed_ ++;
        if (frame_shot_pressed_ > 30) { //12フレーム押しっぱなしでレーザーへ
            is_shooting_laser_ = true;
        }
    } else {
        frame_shot_pressed_ = 0;
    }

    //レーザー発射
    if (is_shooting_laser_) {
        if (VB_PLAY->isBeingPressed(VB_SHOT1)) {
            LaserChip* pLaserChip = pLaserChipDepo_->dispatch();
            if (pLaserChip) {
                if (pLaserChip->_pChip_front == NULL) {
                    _pSeTx->play3D(1);
                }
            }
        }
    }

    //ソフト連射
    //1プッシュで4F毎に最大3発
    if (VB_PLAY->isPushedDown(VB_SHOT1) && !VB_PLAY->isBeingPressed(VB_POWERUP)) {
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
                _pSeTx->play3D(2);
                pShot->locatedBy(this);
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
    MyOptionController** papOptCtrlr = P_MYSHIP_SCENE->papOptionCtrlr_;
    //光子魚雷発射
    if (VB_PLAY->isBeingPressed(VB_SHOT2)) {
        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
            papOptCtrlr[i]->pOption_->pTorpedoCtrlr_->fire();
        }

//        bool can_fire = true;
//        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
//            if (papOptCtrlr[i]->pOption_->pTorpedoCtrlr_->in_firing_) {
//                can_fire = false;
//                break;
//            }
//        }
//        if (can_fire) {
//            for (int i = 0; i < MyOptionController::now_option_num_; i++) {
//                if (i == 0) {
//                    _pSeTx->play3D(3);
//                }
//                papOptCtrlr[i]->pOption_->pTorpedoCtrlr_->fire();
//            }
//        }
    }



}

void MyShip::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここに消滅エフェクト
    }

    //壁の場合特別な処理
    if (pOther->getKind() & KIND_CHIKEI) {

        blown_veloX_ = (GgafUtil::sign(_pColliChecker->_blown_sgn_vX)*(10000+GgafUtil::abs(_pKurokoB->_veloVxMv)));
        blown_veloY_ = (GgafUtil::sign(_pColliChecker->_blown_sgn_vY)*(10000+GgafUtil::abs(_pKurokoB->_veloVyMv)));
        blown_veloZ_ = (GgafUtil::sign(_pColliChecker->_blown_sgn_vZ)*(10000+GgafUtil::abs(_pKurokoB->_veloVzMv)));
    }
    if (pOther->getKind() & KIND_ITEM)  {
    } else {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        _pSeTx->play3D(0);
    }

    if (pOther->getKind() & KIND_ITEM)  {

    }
}



void MyShip::doNotingMoveInput() {

}
void MyShip::setMoveSpeedLv(int lv) {
        //lv_MoveSpeed_ = lv;
        iMoveSpeed_ = PX_C(lv);
    }

void MyShip::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {

    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_FINISH) {

    }
}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(pRing_MyShipGeoHistory4OptCtrlr_);
    DELETE_IMPOSSIBLE_NULL(pRing_MyShipGeoHistory2_);
}

