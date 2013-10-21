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
    //effectBlendOne(); //���Z����Technique�w��

    //��ʂ̑傫���ɔ����āA�ړ��͈͂�����
    //���̂������FovX�Ɉˑ�����̂Ŕ������B
    coord harf_width  = PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2;
    coord harf_height = PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2;

    lim_Y_top_     =  harf_height + PX_C(PROPERTY::GAME_BUFFER_HEIGHT*4);  //��́A����4��ʕ�
    lim_Y_bottom_  = -harf_height - PX_C(PROPERTY::GAME_BUFFER_HEIGHT*4);  //���́A����4��ʕ�
    lim_X_front_   =  harf_width  + PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //�O�́A����2��ʕ�
    lim_X_behaind_ = -harf_width  - PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //���́A����2��ʕ�
    lim_Z_left_   =  harf_width  + PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //��O�́A����2��ʕ�
    lim_Z_right_  = -harf_width  - PX_C(PROPERTY::GAME_BUFFER_WIDTH*2);   //���́A����2��ʕ�
    _TRACE_("MyShip::MyShip �͈� X("<<lim_X_behaind_<<" ~ "<<lim_X_front_<<") Y("<<lim_Y_bottom_<<" ~ "<<lim_Y_top_<<") Z("<<lim_Z_right_<<" ~ "<<lim_Z_left_<<")");

    /** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
    iMoveSpeed_ = 2000;
    //CommonScene��new�̏ꍇ�ݒ�
    angRXVelo_BeginMZ_ = 1000; //�����͎�O�֒ʏ�Z�ʏ�ړ��J�n����X����]�p���x�̏����x
    angRXAcce_MZ_ = 300; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏��p�����x
    angRXTopVelo_MZ_ = 5000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏���p���x
    angRXStop_MZ_ = 90000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p�̖ڕW��~�p�x
    angRXVelo_BeginMZT_ = 20000;//�����͎�O��Turbo�ړ��J�n����X����]�p���x�̏����x

    iMvBtmVelo_MT_ = 0; //Turbo�ړ����̈ړ����x�̍Œᑬ�x
    veloBeginMT_ = 40000; //Turbo�ړ��J�n���̈ړ����x�̏����x
    acce_MT_ = -200; //Turbo�ړ����̈ړ����x�̉����x

//    pOptionCtrler_ = NEW MyOptionController("MY_OPTION_PARENT");
//    addSubLast(pOptionCtrler_);

//    //debug ---->
//    pDepo_TestGuShot_ = NEW GgafActorDepository("Depo_TestGuShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�O�[�e�X�g�b�N
//        pDepo_TestGuShot_->addSubLast(NEW TestGuShot("TestGuShot"));
//    }
//    addSubGroup(pDepo_TestGuShot_);
//    pDepo_TestChokiShot_ = NEW GgafActorDepository("Depo_TestChokiShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�`���L�e�X�g�b�N
//        pDepo_TestChokiShot_->addSubLast(NEW TestChokiShot("TestChokiShot"));
//    }
//    addSubGroup(pDepo_TestChokiShot_);
//    pDepo_TestPaShot_ = NEW GgafActorDepository("Depo_TestPaShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�p�[�e�X�g�b�N
//        pDepo_TestPaShot_->addSubLast(NEW TestPaShot("TestPaShot"));
//    }
//    addSubGroup(pDepo_TestPaShot_);
//    pDepo_TestNomalShot_ = NEW GgafActorDepository("Depo_TestNomalShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�m�[�}���e�X�g�b�N
//        pDepo_TestNomalShot_->addSubLast(NEW TestNomalShot("TestNomalShot"));
//    }
//    addSubGroup(pDepo_TestNomalShot_);
//    //<---- debug


    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        pDepo_MyShots001_->put(pShot);
    }
    addSubGroup(pDepo_MyShots001_);

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        std::string name = "MyStraightLaserChip001("+XTOS(i)+")";
        pChip = NEW MyStraightLaserChip001(name.c_str());
        pChip->setPositionSource(this); //�ʒu��������
        pLaserChipDepo_->put(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    //���b�N�I���R���g���[���[
    pLockonCtrler_ = NEW MyLockonController("MySHipLockonController");
    addSubGroup(pLockonCtrler_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    addSubGroup(pTorpedoCtrler_);

    pEffectTurbo001_ = NEW EffectTurbo001("EffectTurbo001");
    addSubGroup(pEffectTurbo001_);
//    pEffectTurbo002_ = NEW EffectTurbo002("EffectTurbo002");
//    addSubGroup(pEffectTurbo002_);




    //�g���[�X�p����
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
    //     0   0   0    �̑S�̂�+1����3�i���ň���
    //    +1  +1  +1

    //���ꂼ��̃X�C�b�`�̏�Ԃɉ����������̊֐��e�[�u���z��B
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

    //MP�����l
    mp_ = MY_SHIP_START_MP;
    //mp_��ς���ƁA�����Q�Ƃ��� MpBar �̕\�����A�����ĕς��

    //Vreath�͎��l�� _pStatus ��STAT_Stamina�l���Q�Ƃ���悤�ɐݒ�B
//    vreath_.link( &(_pStatus->_paValue[STAT_Stamina]._int_val) );
    //STAT_Stamina������΁Avreath_ ���ω����A���������Q�Ƃ��� VreathBar �̕\�����A�����ĕς��

    //���@���[�^�[�ݒu
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

    //��ʂɐU�蕪��
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
    //        _pKurokoA->addMvVelo(veloBeginMT_);  //���x�ǉ�
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
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
}
void MyShip::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
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

    //���؂�
    if (_pStatus->get(STAT_Stamina) < 0) {
        _pStatus->set(STAT_Stamina, 0);
        return; //����s��
    }

    //VAMSystem�̎���
    // (Viewpoint Adaptive Moving System ���_�K���^�ړ��V�X�e��)
    stc_ = pVbPlay->getBeingPressedStick();
    if (pos_camera == VAM_POS_RIGHT) {
        //�E�T�C�h�r���[(�E���獶�փX�N���[��)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ��
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // ��
            way_switch_.ON_RIGHT(SW_ADD, SW_NOP, SW_NOP); //�O��
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ��
            way_switch_.ON_LEFT(SW_SUB, SW_NOP, SW_NOP);  //���
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ��
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (pos_camera == VAM_POS_LEFT) {
        //���T�C�h�r���[(������E�փX�N���[��)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ��
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // ��
            way_switch_.ON_RIGHT(SW_SUB, SW_NOP, SW_NOP); //���
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ��
            way_switch_.ON_LEFT(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ��
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    } else if (pos_camera == VAM_POS_TOP) {
        //�g�b�v�r���[(�ォ�牺�փX�N���[��)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ��
            way_switch_.ON_UP(SW_ADD, SW_NOP, SW_NOP);    //�O��
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // ��
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ��
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ��
            way_switch_.ON_DOWN(SW_SUB, SW_NOP, SW_NOP);  //���
        }
    } else if (pos_camera == VAM_POS_BOTTOM) {
        //�{�g���r���[(�������փX�N���[��)
        if (pVbPlay->isPushedDown(VB_UP)) {     // ��
            way_switch_.ON_UP(SW_SUB, SW_NOP, SW_NOP);    //���
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // ��
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ��
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ��
            way_switch_.ON_DOWN(SW_ADD, SW_NOP, SW_NOP);  //�O��
        }
    } else if (pos_camera > VAM_POS_TO_BEHIND) {
        //�w��r���[�i�������O�ɃX�N���[���j
        if (pVbPlay->isPushedDown(VB_UP)) {     // ��
            way_switch_.ON_UP(SW_NOP, SW_ADD, SW_NOP);    //��
        }
        if (pVbPlay->isPushedDown(VB_RIGHT)) {  // ��
            way_switch_.ON_RIGHT(SW_NOP, SW_NOP, SW_SUB); //�E
        }
        if (pVbPlay->isPushedDown(VB_LEFT)) {   // ��
            way_switch_.ON_LEFT(SW_NOP, SW_NOP, SW_ADD);  //��
        }
        if (pVbPlay->isPushedDown(VB_DOWN)) {   // ��
            way_switch_.ON_DOWN(SW_NOP, SW_SUB, SW_NOP);  //��
        }
    }
    if (pVbPlay->isReleasedUp(VB_UP)) {
        way_switch_.OFF_UP();    // �� �𗣂�
    }
    if (pVbPlay->isReleasedUp(VB_RIGHT)) {
        way_switch_.OFF_RIGHT(); // �� �𗣂�
    }
    if (pVbPlay->isReleasedUp(VB_LEFT)) {
        way_switch_.OFF_LEFT();  // �� �𗣂�
    }
    if (pVbPlay->isReleasedUp(VB_DOWN)) {
        way_switch_.OFF_DOWN();  // �� �𗣂�
    }
    MoveWay prev_way = way_;
    way_ = (MoveWay)(way_switch_.getIndex()); //��L���l�����ꂽ�����l������
    if (prev_way != way_) {
        is_just_change_way_ = true;
    } else {
        is_just_change_way_ = false;
    }
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        int tmp = iMoveSpeed_;
        iMoveSpeed_ /= 8; //�I�v�V�������쒆�ړ��͒x��
        (this->*paFuncMove[way_])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
        iMoveSpeed_ = tmp;
    } else {
        (this->*paFuncMove[way_])();   //�����l�ɉ������ړ��������\�b�h���Ăяo��
    }

    if (pVbPlay->isPushedDown(VB_TURBO)) {
        UTIL::activateProperEffect01Of(this); //�^�[�{�J�n�̃G�t�F�N�g
        (this->*paFuncTurbo[way_])(); //�����l�ɉ������^�[�{�J�n�������\�b�h���Ăяo��
        _pSeTx->play3D(SE_TURBO);
    } else {
        //Not�^�[�{�J�n��
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //�^�[�{�{�^�������������邱�ƂŁA���x���������₩�ɂȂ�A
            //�ړ�������L�΂�
            _pKurokoB->_veloVxMv *= 0.99;
            _pKurokoB->_veloVyMv *= 0.99;
            _pKurokoB->_veloVzMv *= 0.99;
        } else {
            //�^�[�{�𗣂����ꍇ�A���x�����B
            _pKurokoB->_veloVxMv *= 0.8;
            _pKurokoB->_veloVyMv *= 0.8;
            _pKurokoB->_veloVzMv *= 0.8;
        }
    }

    //�X�s���������悭����Ă���Ȃ�Α��x����߂�
    angvelo MZ = angRXTopVelo_MZ_-3000; //3000�͒ʏ���񎞂ɑ��x����߂�angRXTopVelo_MZ_�𒴂��Ȃ��悤�ɂ��邽�߁A����O�Ō�������ƌ����Ӗ��iTODO:�v�����j�B
    if (_pKurokoA->_angveloFace[AXIS_X] >= MZ) {
        _pKurokoA->_angveloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_*2);
    } else if (_pKurokoA->_angveloFace[AXIS_X] <= -MZ) {
        _pKurokoA->_angveloFace[AXIS_X] *= 0.93;
        //_pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_*2);
    }

    //���E�������͂Ȃ�A�@�̂𐅕��ɂ���i�A�������悭����Ă��Ȃ��ꍇ�Ɍ���BsetStopTargetFaceAng�̑�4�������p���x����邢�ꍇ�󂯓���j
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

    //���W�ɔ��f
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
    //�������
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
        //�˓����[�V�������́A�ړ��͈͐��䖳��
    } else {
        //�ʏ�ړ��͈͐���
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


    //�I�v�V�����̂��߂ɍ��W���ۑ�
    pRing_MyShipGeoHistory2_->next()->set(this);
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        GgafDxGeoElem* pGeoMyShipPrev = pRing_MyShipGeoHistory2_->getPrev();
        //(_X_local, _Y_local, _Z_local) �́A�����ʒu(0,0,0) ����A
        //VB_OPTION�������Ă���Ԃ݈̂ړ������������W��ێ��B
        _X_local += (_X - pGeoMyShipPrev->X); //�ړ�����
        _Y_local += (_Y - pGeoMyShipPrev->Y);
        _Z_local += (_Z - pGeoMyShipPrev->Z);
    } else {
        //(_X_local, _Y_local, _Z_local) ��VB_OPTION�𗣂������̏����ʒu(0,0,0) ����̑������W���͂����Ă���B
        //���������āApRing_MyShipGeoHistory4OptCtrler_�́A
        //���@�̐�΍��W��������AVB_OPTION ���������ꍇ�̑������W�����O�����ړ����W�����i��΍��W�j�ƂȂ�B
        //���̗����̍��W��(_X_local, _Y_local, _Z_local) ��(_X_local, _Y_local, _Z_local)���W�𑫂��΁A���@�̍��W�Ɠ��l
        GgafDxGeoElem* pGeo = pRing_MyShipGeoHistory4OptCtrler_->getCurrent();
        if (pGeo->X == _X - _X_local && pGeo->Y == _Y - _Y_local && pGeo->Z == _Z - _Z_local) {
            //�ړ����Ă��Ȃ��ꍇ
            trace_delay_count_++;
            if (trace_delay_count_ > TRACE_DELAY_WAIT_FRAME) { //1�b�ԃg���[�X�ȏ�Ԃ��ێ��ł���悤�ɂ���B
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

    //���t���[���̌ċz�̏���
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


    //���@���Ńe�X�g
//    if (pVbPlay->isBeingPressed(VB_BUTTON8)) {
//        _TRACE_("���@���Ńe�X�g");
//        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
//    }



    //�V���b�g�֘A����
    is_shooting_laser_ = false;
    if (pVbPlay->isBeingPressed(VB_SHOT1)) {
        frame_shot_pressed_ ++;
        if (can_shoot_laser_) {
            if (frame_shot_pressed_ > 30) { //30�t���[���������ςȂ��Ń��[�U�[��
                is_shooting_laser_ = true;
            }
        }
    } else {
        frame_shot_pressed_ = 0;
        pLockonCtrler_->releaseAllLockon(); //���b�N�I������
    }

    //���[�U�[����
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

    //�\�t�g�A��
    //1�v�b�V����4F���ɍő�3��
    if (pVbPlay->isPushedDown(VB_SHOT1) && !pVbPlay->isBeingPressed(VB_POWERUP)) {
        is_being_soft_rapidshot_ = true;
        if (frame_soft_rapidshot_ >= SOFT_RAPIDSHOT_INTERVAL) {
            //SOFT_RAPIDSHOT_INTERVAL �t���[�����x���ꍇ
            //�A�˂ƘA�˂̂Ȃ��ڂ������悤�ɂ���
            frame_soft_rapidshot_ = frame_soft_rapidshot_ % SOFT_RAPIDSHOT_INTERVAL;
        } else {
            //SOFT_RAPIDSHOT_INTERVAL �t���[����葬���A�˂̏ꍇ
            //������󂯓���ċ����I�ɔ��˂ł���(�蓮�A�˂̂ق��������A�˂ł���悤�ɂ������B)
            frame_soft_rapidshot_ = 0;
        }
    }
    just_shot_ = false;
    if (is_being_soft_rapidshot_) {
        if (frame_soft_rapidshot_ % SOFT_RAPIDSHOT_INTERVAL == 0) {
            just_shot_ = true;//���������V���b�g���܂����t���O
            MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
            if (pShot) {
                _pSeTx->play3D(SE_FIRE_SHOT);
                pShot->positionAs(this);
            }
            if (frame_soft_rapidshot_ >= SOFT_RAPIDSHOT_INTERVAL*(SOFT_RAPIDSHOT_NUM-1)) {
                //SOFT_RAPIDSHOT_NUM ���ł��I������\�t�g�A�ˏI��
                is_being_soft_rapidshot_ = false;
            }
        }
    }
    if (is_being_soft_rapidshot_) {
        frame_soft_rapidshot_++;
    }

    //���q��������
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
    //�����Ƀq�b�g�G�t�F�N�g
    int vreath = _pStatus->get(STAT_Stamina);
    if (UTIL::calcMyStamina(this, pOther) <= 0) {
        //���@�����J��
        setHitAble(false);
        _pSeTx->play3D(SE_EXPLOSION);
        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }
    int damage = vreath - _pStatus->get(STAT_Stamina);
    if (damage > 0){
        pMagicMeter_->pDamageDispBar_->addDamage(damage);
    }

    //�ǂ̏ꍇ���ʂȏ���
    if (pOther->getKind() & KIND_CHIKEI) {
        //������ѕ������l����B
        //���݂̈ړ��̋t�����i������шЗ͂͂Q�{�Ɂj
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
                //�v���Y����
                ColliAAPrism* pPrism = (ColliAAPrism*)(pOther->_pChecker->_pCollisionArea->_papColliPart[0]);
                int pos_prism = pPrism->_pos_prism;
                if (pos_prism & POS_PRISM_XY) {
                    if (pos_prism & POS_PRISM_pp) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ���_������
                        // x- ��  ��  �_�焠  �� x+
                        //        ��    �_��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        �������^��
                        // x- ��  ����^  ��  �� x+
                        //        ���^    ��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ��    �^��
                        // x- ��  ��  �^����  �� x+
                        //        ���^���焠
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    } else { // �̂���� POS_PRISM_nn
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ���_    ��
                        // x- ��  �����_  ��  �� x+
                        //        ������_��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z               ));
                    }

                } else if (pos_prism & POS_PRISM_YZ) {

                    if (pos_prism & POS_PRISM_pp) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ���_������
                        // y- ��  ��  �_�焠  �� y+
                        //        ��    �_��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        �������^��
                        // y- ��  ����^  ��  �� y+
                        //        ���^    ��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ��    �^��
                        // y- ��  ��  �^����  �� y+
                        //        ���^���焠
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y + pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    } else { // �̂���� POS_PRISM_nn
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ���_    ��
                        // y- ��  �����_  ��  �� y+
                        //        ������_��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_X - (pOther->_X               ));
                        dY2 = (_Y - (pOther->_Y - pPrism->_hdy));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    }

                } else if (pos_prism & POS_PRISM_ZX) {
                    if (pos_prism & POS_PRISM_pp) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ���_������
                        // z- ��  ��  �_�焠  �� z+
                        //        ��    �_��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_np) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        �������^��
                        // z- ��  ����^  ��  �� z+
                        //        ���^    ��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_X - (pOther->_X + pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    } else if (pos_prism & POS_PRISM_pn) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ��    �^��
                        // z- ��  ��  �^����  �� z+
                        //        ���^���焠
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y               ));
                        dZ2 = (_Z - (pOther->_Z + pPrism->_hdz));
                    } else { // �̂���� POS_PRISM_nn
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ���_    ��
                        // z- ��  �����_  ��  �� z+
                        //        ������_��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_X - (pOther->_X - pPrism->_hdx));
                        dY2 = (_Y - (pOther->_Y                ));
                        dZ2 = (_Z - (pOther->_Z - pPrism->_hdz));
                    }
                } else {

                }
            } else {
                //�v���Y���ȊO�̕�
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
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_, TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_;
}

void MyShip::move_WAY_ZLEFT_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D315ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2)); //�����v���
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, (angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _X += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D90ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*angRXAcce_MZ_);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*angRXStop_MZ_, TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_;
}

void MyShip::move_WAY_ZRIGHT_BEHIND() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(0, D135ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _X -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_UP() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/2);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ - (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _Y += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_DOWN() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, angRXAcce_MZ_/2);
        _pKurokoA->setStopTargetFaceAng(AXIS_X, angRXStop_MZ_ + (angRXStop_MZ_/2), TURN_COUNTERCLOCKWISE, angRXTopVelo_MZ_);

    }
    _Z += iMoveSpeed_ * NANAME2D_RATE;
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_UP() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ - (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _Y += iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZRIGHT_DOWN() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
        //����
        _pKurokoA->setFaceAngAcce(AXIS_X, -1*(angRXAcce_MZ_/2));
        _pKurokoA->setStopTargetFaceAng(AXIS_X, -1*(angRXStop_MZ_ + (angRXStop_MZ_/2)), TURN_CLOCKWISE, angRXTopVelo_MZ_);
    }
    _Z -= iMoveSpeed_ * NANAME2D_RATE;
    _Y -= iMoveSpeed_ * NANAME2D_RATE;
}

void MyShip::move_WAY_ZLEFT_UP_FRONT() {
    if (is_just_change_way_) {
        _pKurokoA->setRzRyMvAng(D45ANG, D270ANG+D45ANG);
        //����
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
        //����
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
        //����
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
        //����
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
        //����
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
        //����
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
        //����
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
        //����
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
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_FRONT() {
    _pKurokoA->setRzRyMvAng(0, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_BEHIND() {
    _pKurokoA->setRzRyMvAng(D180ANG, D45ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_FRONT() {
    _pKurokoA->setRzRyMvAng(D180ANG, D135ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT() {
    _pKurokoA->setRzRyMvAng(0, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_BEHIND() {
    _pKurokoA->setRzRyMvAng(0, D135ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_UP() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_DOWN() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_UP() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_DOWN() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME2D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME2D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_UP_FRONT() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG+D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_UP_BEHIND() {
    _pKurokoA->setRzRyMvAng(D45ANG, D270ANG-D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_DOWN_FRONT() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG+D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZLEFT_DOWN_BEHIND() {
    _pKurokoA->setRzRyMvAng(D315ANG, D270ANG-D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_UP_FRONT() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG-D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_UP_BEHIND() {
    _pKurokoA->setRzRyMvAng(D45ANG, D90ANG+D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_DOWN_FRONT() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG-D45ANG);
    _pKurokoB->addVxMvVelo(veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

void MyShip::turbo_WAY_ZRIGHT_DOWN_BEHIND() {
    _pKurokoA->setRzRyMvAng(D315ANG, D90ANG+D45ANG);
    _pKurokoB->addVxMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVzMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    _pKurokoB->addVyMvVelo(-veloBeginMT_ * NANAME3D_RATE);
    //����
    _pKurokoA->setFaceAngVelo(AXIS_X, -angRXVelo_BeginMZT_*NANAME3D_RATE); //�����悭��]�J�n
}

MyShip::~MyShip() {
    GGAF_DELETE(pRing_MyShipGeoHistory4OptCtrler_);
    GGAF_DELETE(pRing_MyShipGeoHistory2_);
}

