#include "MyShip.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MySnipeShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinBase.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"

using namespace GgafLib;
using namespace VioletVreath;

coord MyShip::lim_y_top_     =  0;
coord MyShip::lim_y_bottom_  =  0;
coord MyShip::lim_x_infront_ =  0;
coord MyShip::lim_x_behaind_ =  0;
coord MyShip::lim_z_left_    =  0;
coord MyShip::lim_z_right_   =  0;

uint32_t MyShip::shot2_matrix_[4][MYSHIP_SHOT_MATRIX] = {
    {
            8,           //  0001000
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
            8            //  0001000
    },
    {
            0,           //  0000000
            2,           //  0000010
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
           32,           //  0100000
            0            //  0000000
    },
    {
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
           65,           //  1000001
            0,           //  0000000
            0,           //  0000000
            0            //  0000000
    },
    {
            0,           //  0000000
           32,           //  0100000
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
            2,           //  0000010
            0            //  0000000

    }
};

uint32_t MyShip::shot3_matrix_[2][MYSHIP_SHOT_MATRIX] = {
    {
            8,           //  0001000
            0,           //  0000000
            0,           //  0000000
           65,           //  1000001
            0,           //  0000000
            0,           //  0000000
            8            //  0001000
    },
    {
            0,           //  0000000
           34,           //  0100010
            0,           //  0000000
            0,           //  0000000
            0,           //  0000000
           34,           //  0100010
            0            //  0000000
    }
};

/** �\�t�g�A�ː��ŁA�P�v�b�V���Ō����Ƃ��o����A�ː� */
#define SOFT_RAPIDSHOT_NUM       (3)
/** �\�t�g�A�ː��ł̃V���b�g�ƃV���b�g�̊Ԋu */
#define SOFT_RAPIDSHOT_INTERVAL  (4)

enum {
    SE_DAMAGED     ,
    SE_EXPLOSION   ,
    SE_TURBO       ,
    SE_CANT_TURBO  ,
    SE_FIRE_LASER  ,
    SE_FIRE_SHOT   ,
    SE_FIRE_TORPEDO,
};


MyShip::MyShip(const char* prm_name) :
        VvMyActor<DefaultD3DXMeshActor>(prm_name, "VicViper", StatusReset(MyShip)) {
//DefaultMeshActor(prm_name, "jiki") {
//CubeMapMeshActor(prm_name, "wakka") {
//DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "MyShip";

    //effectBlendOne(); //���Z����Technique�w��

    //��ʂ̑傫���ɔ����āA�ړ��͈͂�����
    //���̂������FovX�Ɉˑ�����̂Ŕ������B
    static const coord game_buffer_width  = PX_C(CONFIG::GAME_BUFFER_WIDTH);
    static const coord game_buffer_height = PX_C(CONFIG::GAME_BUFFER_HEIGHT);
    MyShip::lim_y_top_     =  (game_buffer_height/2) + game_buffer_height*4;  //��́A����4��ʕ������Ȃ��̈�܂ňړ��\
    MyShip::lim_y_bottom_  = -(game_buffer_height/2) - game_buffer_height*4;  //���́A����4��ʕ������Ȃ��̈�܂ňړ��\
    MyShip::lim_x_infront_ =  (game_buffer_width/2)  + game_buffer_width*2;   //�O�́A����2��ʕ������Ȃ��̈�܂ňړ��\
    MyShip::lim_x_behaind_ = -(game_buffer_width/2)  - game_buffer_width*1;   //���́A���̂P��ʕ������Ȃ��̈�܂ňړ��\
    MyShip::lim_z_left_    =  (game_buffer_height/2) + game_buffer_height*4;   //��O�́A����4��ʕ������Ȃ��̈�܂ňړ��\
    MyShip::lim_z_right_   = -(game_buffer_height/2) - game_buffer_height*4;   //���́A����4��ʕ������Ȃ��̈�܂ňړ��\
    _TRACE_("MyShip �͈� X("<<MyShip::lim_x_behaind_<<" �` "<<MyShip::lim_x_infront_<<")  Y("<<MyShip::lim_y_bottom_<<" �` "<<MyShip::lim_y_top_<<")  Z("<<MyShip::lim_z_right_<<" �` "<<MyShip::lim_z_left_<<")");


    //CommonScene��new�̏ꍇ�ݒ�
    angRxVelo_BeginMZ_ = 1000;   //�����͎�O�֒ʏ�Z�ʏ�ړ��J�n����X����]�p���x�̏����x
    angRxAcce_MZ_ = 300;         //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏��p�����x
    angRxTopVelo_MZ_ = 5000;     //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏���p���x
    angRxStop_MZ_ = 90000;       //�����͎�O�֒ʏ�Z�ړ�����X����]�p�̖ڕW��~�p�x
    angRxVelo_BeginMZT_ = 20000; //�����͎�O��Turbo�ړ��J�n����X����]�p���x�̏����x

    mv_speed_ = 0;
    veloBeginMT_ = 0;
    setMoveSpeed(2000);


//    //debug ---->
//    pDepo_TestGuShot_ = NEW GgafCore::ActorDepository("Depo_TestGuShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�O�[�e�X�g�b�N
//        pDepo_TestGuShot_->appendChild(NEW TestGuShot("TestGuShot"));
//    }
//    appendGroupChild(pDepo_TestGuShot_);
//    pDepo_TestChokiShot_ = NEW GgafCore::ActorDepository("Depo_TestChokiShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�`���L�e�X�g�b�N
//        pDepo_TestChokiShot_->appendChild(NEW TestChokiShot("TestChokiShot"));
//    }
//    appendGroupChild(pDepo_TestChokiShot_);
//    pDepo_TestPaShot_ = NEW GgafCore::ActorDepository("Depo_TestPaShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�p�[�e�X�g�b�N
//        pDepo_TestPaShot_->appendChild(NEW TestPaShot("TestPaShot"));
//    }
//    appendGroupChild(pDepo_TestPaShot_);
//    pDepo_TestNomalShot_ = NEW GgafCore::ActorDepository("Depo_TestNomalShot");
//    for (int i = 0; i < 25; i++) { //�e�X�g�m�[�}���e�X�g�b�N
//        pDepo_TestNomalShot_->appendChild(NEW TestNomalShot("TestNomalShot"));
//    }
//    appendGroupChild(pDepo_TestNomalShot_);
//    //<---- debug


    pDepo_MyShots001_ = NEW GgafCore::ActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 50; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivate();
        pDepo_MyShots001_->put(pShot);
    }
    appendGroupChild(pDepo_MyShots001_);

    pDepo_MySnipeShots001_ = NEW GgafCore::ActorDepository("RotShot001");
    MySnipeShot001* pSnipeShot;
    for (int i = 0; i < 5; i++) { //���e�X�g�b�N
        pSnipeShot = NEW MySnipeShot001("MY_MySnipeShot001");
        pSnipeShot->inactivate();
        pDepo_MySnipeShots001_->put(pSnipeShot);
    }
    appendGroupChild(pDepo_MySnipeShots001_);

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 80; i++) { //���[�U�[�X�g�b�N
        std::string name = "MyStraightLaserChip001("+XTOS(i)+")";
        pChip = NEW MyStraightLaserChip001(name.c_str());
        pChip->setPositionSource(this); //�ʒu��������
        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(80, 25);
    appendGroupChild(pLaserChipDepo_);

    //���b�N�I���R���g���[���[
    pLockonCtrler_ = NEW MyLockonController("MySHipLockonController");
    appendGroupChild(pLockonCtrler_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    appendGroupChild(pTorpedoCtrler_);

    pEffectTurbo001_ = NEW EffectTurbo001("EffectTurbo001");
    appendGroupChild(pEffectTurbo001_);
//    pEffectTurbo002_ = NEW EffectTurbo002("EffectTurbo002");
//    appendGroupChild(pEffectTurbo002_);

    pMyMagicEnergyCore_ = NEW MyMagicEnergyCore("MyMagicEnergyCore");
    appendGroupChild(pMyMagicEnergyCore_);

    //26�����Ɉړ������ꍇ�̎��@�̌X����`
    pSenakai_ = &(senakai_[13]);
    pSenakai_[DIR26(-1,-1,-1)] = -D_ANG(120);
    pSenakai_[DIR26(-1,-1, 0)] =  0;
    pSenakai_[DIR26(-1,-1, 1)] =  D_ANG(120);
    pSenakai_[DIR26(-1, 0,-1)] = -D90ANG;
    pSenakai_[DIR26(-1, 0, 0)] =  0;
    pSenakai_[DIR26(-1, 0, 1)] =  D90ANG;
    pSenakai_[DIR26(-1, 1,-1)] = -D_ANG(30);
    pSenakai_[DIR26(-1, 1, 0)] =  0;
    pSenakai_[DIR26(-1, 1, 1)] =  D_ANG(30);
    pSenakai_[DIR26( 0,-1,-1)] = -D135ANG;
    pSenakai_[DIR26( 0,-1, 0)] =  0;
    pSenakai_[DIR26( 0,-1, 1)] =  D135ANG;
    pSenakai_[DIR26( 0, 0,-1)] = -D90ANG;
    pSenakai_[DIR26( 0, 0, 0)] =  0;
    pSenakai_[DIR26( 0, 0, 1)] =  D90ANG;
    pSenakai_[DIR26( 0, 1,-1)] = -D45ANG;
    pSenakai_[DIR26( 0, 1, 0)] =  0;
    pSenakai_[DIR26( 0, 1, 1)] =  D45ANG;
    pSenakai_[DIR26( 1,-1,-1)] = -D_ANG(120);
    pSenakai_[DIR26( 1,-1, 0)] =  0;
    pSenakai_[DIR26( 1,-1, 1)] =  D_ANG(120);
    pSenakai_[DIR26( 1, 0,-1)] = -D90ANG;
    pSenakai_[DIR26( 1, 0, 0)] =  0;
    pSenakai_[DIR26( 1, 0, 1)] =  D90ANG;
    pSenakai_[DIR26( 1, 1,-1)] = -D_ANG(30);
    pSenakai_[DIR26( 1, 1, 0)] =  0;
    pSenakai_[DIR26( 1, 1, 1)] =  D_ANG(30);

    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_DAMAGED     , "SE_MY_DAMAGED_001");
    pSeXmtr->set(SE_EXPLOSION   , "SE_MY_SE_EXPLOSION_001");
    pSeXmtr->set(SE_TURBO       , "SE_MY_TURBO_001");
    pSeXmtr->set(SE_CANT_TURBO  , "SE_MY_CANT_TURBO_001");
    pSeXmtr->set(SE_FIRE_LASER  , "SE_MY_FIRE_LASER_001");
    pSeXmtr->set(SE_FIRE_SHOT   , "SE_MY_FIRE_SHOT_001");
    pSeXmtr->set(SE_FIRE_TORPEDO, "SE_MY_FIRE_TORPEDO_001");

    veloTurboTop_ = 30000;
    veloTurboBottom_ = 10000;

    is_being_soft_rapidshot_ = false;
    soft_rapidshot_shot_count_ = 0;
    soft_rapidshot_push_cnt_ = 0;
    soft_rapidshot_shot_count_in_one_push_ = 0;
    soft_rapidshot_frames_in_one_push = 0;
    is_snipe_shot_ = false;

    is_just_shot_ = false;
    is_shooting_laser_ = false;
    can_shoot_laser_ = false;
    frame_shot_pressed_ = 0;

    can_control_ = true;
    is_diving_ = false;

    blown_veloX_ = 0;
    blown_veloY_ = 0;
    blown_veloZ_ = 0;
    mv_way_sgn_x_ = 0;
    mv_way_sgn_y_ = 0;
    mv_way_sgn_z_ = 0;
    mv_way_ = DIR26(mv_way_sgn_x_, mv_way_sgn_y_, mv_way_sgn_z_);
    prev_way_ = mv_way_;
    is_just_change_mv_way_ = false;

    //MP�����l
    mp_ = MY_SHIP_START_MP;
    //mp_��ς���ƁA�����Q�Ƃ��� MpBar �̕\�����A�����ĕς��

    //Vreath�͎��l�� getStatus() ��STAT_Stamina�l���Q�Ƃ���悤�ɐݒ�B
//    vreath_.link( &(getStatus()->_paValue[STAT_Stamina]._int_val) );
    //STAT_Stamina������΁Avreath_ ���ω����A���������Q�Ƃ��� VreathBar �̕\�����A�����ĕς��

    //���@���[�^�[�ݒu
    pMagicMeter_ = NEW MagicMeter("MagicMeter", &mp_, &(getStatus()->_value[STAT_Stamina]._int_val) );
    pMagicMeter_->setPosition(PX_C(100), PX_C(CONFIG::GAME_BUFFER_HEIGHT) - (pMagicMeter_->height_) - PX_C(16+16+16));
    appendGroupChild(pMagicMeter_);

    r_blown_velo_decay_ = 0.8;

    invincible_frames_ = 0;

    trace_delay_count_ = 0;
    is_trace_waiting_ = false;

    shot_level_ = 1;

    prev_x_ = _x;
    prev_y_ = _y;
    prev_z_ = _z;
}

void MyShip::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyShip::initialize() {
    _TRACE_(FUNC_NAME<<"");

    //��ʂɐU�蕪��
//    bringSceneMediator()->appendGroupChild(KIND_MY_SHOT_NOMAL, pDepo_MyShots001_->extract());
//    bringSceneMediator()->appendGroupChild(KIND_MY_SHOT_NOMAL, pDepo_MyWaves001_->extract());
    //bringSceneMediator()->appendGroupChild(KIND_MY_SHOT_NOMAL, pLaserChipDepo_->extract());

    setHitAble(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
//    pChecker->setColliSphere(0, -100000, -50000, 20000, 100000);
// pChecker->setColliAABox(0, -100000, -50000, 20000, 10000, 40000, 80000);
//    pChecker->setColliSphere(1, 0,-100000,0, 30000, true, true, true);
//    pChecker->setColliSphere(2, 0,100000,0, 30000, true, true, true);
//    pChecker->setColliSphere(3, 0,0,-100000, 30000, true, true, true);
//    pChecker->setColliSphere(4, 0,0,100000, 30000, true, true, true);

//    pChecker->setColliAACube(0, 40000);
/////////////TEST
      pChecker->setColliAACube(0, PX_C(40));

    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setMvVelo(0);

    //setMaterialColor(1.0, 0.5, 0.5);
    setAlpha(1.0);
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    pCoordVehicle->forceVeloXYZRange(-veloTurboTop_, veloTurboTop_);
    pCoordVehicle->setAcceXYZZero();

    getLocoVehicle()->setRollFaceAngVelo(300);
}


void MyShip::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    is_being_soft_rapidshot_ = false;
    soft_rapidshot_shot_count_ = 0;
    soft_rapidshot_push_cnt_ = 0;
    soft_rapidshot_shot_count_in_one_push_ = 0;
    soft_rapidshot_frames_in_one_push = 0;
    is_snipe_shot_ = false;
    is_being_soft_rapidshot_ = false;
    is_just_shot_ = false;
    is_shooting_laser_ = false;
    can_shoot_laser_ = false;
    frame_shot_pressed_ = 0;
    _x = _y = _z = 0;
    mv_way_sgn_x_ = 0;
    mv_way_sgn_y_ = 0;
    mv_way_sgn_z_ = 0;
    mv_way_ = DIR26(mv_way_sgn_x_, mv_way_sgn_y_, mv_way_sgn_z_);
//    mv_way_switch_.reset();

    mp_ = MY_SHIP_START_MP;
    getStatus()->reset();

    setInvincibleFrames(60 * 10); //�o�ꎞ�̖��G����
}

void MyShip::onActive() {
    _TRACE_(FUNC_NAME<<"");
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����q�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
}
void MyShip::onInactive() {
    _TRACE_(FUNC_NAME<<"");
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����q�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
//    pLaserChipDepo_->reset();
}
void MyShip::processBehavior() {
    VirtualButton* pVbPlay = VV_VB_PLAY;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    //���싑��
    if (!can_control_) {
        return;
    }
    updateMoveWay();
    if (getStatus()->get(STAT_Stamina) < 0) {
        //���؂�
    } else {
        if (pVbPlay->isPressed(0, VV_VB_OPTION)) {
            int tmp = mv_speed_;
            mv_speed_ /= 8; //�I�v�V�������쒆�ړ��͒x��
            moveNomal();
            mv_speed_ = tmp;
        } else {
            moveNomal();
        }

        if (pVbPlay->isPushedDown(0, VV_VB_TURBO)) {
            if (pCoordVehicle->_velo_x == 0 && pCoordVehicle->_velo_y == 0 && pCoordVehicle->_velo_z == 0) {
                //�^�[�{�ړ����S�ɏI�����Ȃ��Ǝ��̃^�[�{�͎��s�s��
                moveTurbo();
                UTIL::activateProperEffect01Of(this); //�^�[�{�J�n�̃G�t�F�N�g
                getSeXmtr()->play3D(SE_TURBO);
            } else {
                //�^�[�{�ړ���
                getSeXmtr()->play3D(SE_CANT_TURBO);
            }
        } else {
            //Not�^�[�{�J�n��
            if (pVbPlay->isPressed(0, VV_VB_TURBO)) {
                //�^�[�{�{�^�������������邱�ƂŁA���x���������₩�ɂȂ�A
                //�ړ�������L�΂�
                pCoordVehicle->_velo_x *= 0.96;
                pCoordVehicle->_velo_y *= 0.96;
                pCoordVehicle->_velo_z *= 0.96;
            } else {
                //�^�[�{�𗣂����ꍇ�A���x�����B
                pCoordVehicle->_velo_x *= 0.8;
                pCoordVehicle->_velo_y *= 0.8;
                pCoordVehicle->_velo_z *= 0.8;
            }
            if (ABS(pCoordVehicle->_velo_x) <= 2) {
                pCoordVehicle->_velo_x = 0;
            }
            if (ABS(pCoordVehicle->_velo_y) <= 2) {
                pCoordVehicle->_velo_y = 0;
            }
            if (ABS(pCoordVehicle->_velo_z) <= 2) {
                pCoordVehicle->_velo_z = 0;
            }
        }

        if (pVbPlay->isDoublePushedDown(0, VV_VB_OPTION,8,8) ) {
            pCoordVehicle->setXYZZero(); //�^�[�{�ړ����ł���~����B�i�^�[�{�L�����Z���I�ɂȂ�I�j
        }
    }

    //�X�s���������悭����Ă���Ȃ�Α��x����߂�
    angvelo MZ = angRxTopVelo_MZ_-3000; //3000�͒ʏ���񎞂ɑ��x����߂�angRxTopVelo_MZ_�𒴂��Ȃ��悤�ɂ��邽�߁A����O�Ō�������ƌ����Ӗ��iTODO:�v�����j�B
    if (pLocoVehicle->_angvelo_face[AXIS_X] >= MZ) {
        pLocoVehicle->_angvelo_face[AXIS_X] *= 0.93;
        //_getLocoVehicle()->setFaceAngAcce(AXIS_X, -1*angRxAcce_MZ_*2);
    } else if (pLocoVehicle->_angvelo_face[AXIS_X] <= -MZ) {
        pLocoVehicle->_angvelo_face[AXIS_X] *= 0.93;
        //_getLocoVehicle()->setFaceAngAcce(AXIS_X, angRxAcce_MZ_*2);
    }

    //���񂵂Ȃ��ړ������̏ꍇ�A�@�̂𐅕��ɂ���i�A�������悭����Ă��Ȃ��ꍇ�Ɍ���BsetStopTargetFaceAng�̑�4�������p���x����邢�ꍇ�󂯓���j
    if (pSenakai_[mv_way_] == 0) {
        angle dist = pLocoVehicle->getFaceAngDistance(AXIS_X, 0, TURN_CLOSE_TO);
        if (0 <= dist && dist < D180ANG) {
            getLocoVehicle()->setFaceAngAcce(AXIS_X, angRxAcce_MZ_);
        } else if (-1*D180ANG < dist && dist < 0) {
            getLocoVehicle()->setFaceAngAcce(AXIS_X, -1*angRxAcce_MZ_);
        }
        pLocoVehicle->setMvAcce(0);
        pLocoVehicle->setStopTargetFaceAng(AXIS_X, 0, TURN_BOTH, angRxTopVelo_MZ_);
    }

    ////////////////////////////////////////////////////

    //���W�ɔ��f
    pLocoVehicle->behave();
    pCoordVehicle->behave();
    getSeXmtr()->behave();

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
        _x += blown_veloX_;
        blown_veloX_ *= r_blown_velo_decay_;
    }
    if (ABS(blown_veloY_) < PX_C(1)) {
        blown_veloY_ = 0;
    } else {
        _y += blown_veloY_;
        blown_veloY_ *= r_blown_velo_decay_;
    }
    if (ABS(blown_veloZ_) < PX_C(1)) {
        blown_veloZ_ = 0;
    } else {
        _z += blown_veloZ_;
        blown_veloZ_ *= r_blown_velo_decay_;
    }


    if (is_diving_) {
        //�˓����[�V�������́A�ړ��͈͐��䖳��
    } else {
        //�ʏ�ړ��͈͐���
        if (_y > MyShip::lim_y_top_) {
            _y = MyShip::lim_y_top_;
        } else if (_y < MyShip::lim_y_bottom_ ) {
            _y = MyShip::lim_y_bottom_;
        }

        if (_x > MyShip::lim_x_infront_) {
            _x = MyShip::lim_x_infront_;
        } else if (_x < MyShip::lim_x_behaind_) {
            _x = MyShip::lim_x_behaind_;
        }

        if (_z > MyShip::lim_z_left_) {
            _z = MyShip::lim_z_left_;
        } else if (_z < MyShip::lim_z_right_) {
            _z = MyShip::lim_z_right_;
        }
    }

    //���t���[���̌ċz�̏���
    getStatus()->minus(STAT_Stamina, MY_SHIP_VREATH_COST);

    //�V���b�g�֘A����
    is_shooting_laser_ = false;
    if (pVbPlay->isPressed(0, VV_VB_SHOT1)) {
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
        if (pVbPlay->isPressed(0, VV_VB_SHOT1)) {
            LaserChip* pLaserChip = pLaserChipDepo_->dispatch();
            if (pLaserChip) {
                if (pLaserChip->getInfrontChip() == nullptr) {
                    getSeXmtr()->play3D(SE_FIRE_LASER);
                }
            }
        } else {

        }
    }

    //�\�t�g�A��
    //�P�v�b�V���ڂ̏��e�݂̂P���̂ݔ��˂̃X�i�C�v�V���b�g�B
    //�Q�v�b�V���ڈȍ~�\�t�g�A�ˁA�P�v�b�V����4F���ɍő�3��
    if (pVbPlay->isPushedDown(0, VV_VB_SHOT1) && !pVbPlay->isPressed(0, VV_VB_POWERUP)) {
        if (is_being_soft_rapidshot_) {
            if (soft_rapidshot_frames_in_one_push >= SOFT_RAPIDSHOT_INTERVAL) {
                //�v�b�V����̃\�t�g�A�˂ɂ��Q���ڂ� SOFT_RAPIDSHOT_INTERVAL �t���[����莟�̃v�b�V�����x���ꍇ
                //�A�˂ƘA�˂̂Ȃ��ڂ������悤�ɉ��o����߂ɁA
                //soft_rapidshot_frames_in_one_push �� SOFT_RAPIDSHOT_INTERVAL �{�̒l�_�n�ŏ��l�ɂ���
                soft_rapidshot_frames_in_one_push = soft_rapidshot_frames_in_one_push % SOFT_RAPIDSHOT_INTERVAL;
                if (soft_rapidshot_frames_in_one_push > 0) {
                    //soft_rapidshot_frames_in_one_push ���^�ǂ�0�Ȃ�΁ASOFT_RAPIDSHOT_NUM ���̒e���\�t�g�A�˂ɂ�蔭�˂���邱�ƂɂȂ邪�A
                    //soft_rapidshot_frames_in_one_push > 0 �Ȃ�΁ASOFT_RAPIDSHOT_NUM-1 ���ɂȂ�P�������Ă��܂��B
                    //����������ׁASOFT_RAPIDSHOT_NUM ���̒e�������Ƃ�ۏ؂��邽�߂ɁAsoft_rapidshot_frames_in_one_push��␳
                    soft_rapidshot_frames_in_one_push -= SOFT_RAPIDSHOT_INTERVAL;
                }
                soft_rapidshot_shot_count_in_one_push_ = 0;
                soft_rapidshot_push_cnt_++;
            } else {
                //�v�b�V����A�\�t�g�A�˂ɂ��Q���ڂ� SOFT_RAPIDSHOT_INTERVAL �t���[����莟�̃v�b�V���������ꍇ
                //������󂯓���ċ����I�ɔ��˂ł���(SOFT_RAPIDSHOT_INTERVAL��葬���蓮�A�˂́A�A�˗D��)
                soft_rapidshot_frames_in_one_push = 0;
                soft_rapidshot_shot_count_in_one_push_ = 0;
                soft_rapidshot_push_cnt_++;
            }
        } else {
            //�\�t�g�A�ˊJ�n�I
            is_being_soft_rapidshot_ = true;
            soft_rapidshot_frames_in_one_push = 0;
            soft_rapidshot_shot_count_in_one_push_ = 0;
            soft_rapidshot_push_cnt_ = 1;
        }
    }

    if (is_being_soft_rapidshot_) {
        //�\�t�g�A�˒��A���ۂɃV���b�g����^�C�~���O�̔���
        if (soft_rapidshot_frames_in_one_push % SOFT_RAPIDSHOT_INTERVAL == 0) {
            //�V���b�g����^�C�~���O�ł͂��邪�A�ʂ����ăV���b�g���Ă��悢���H
            soft_rapidshot_shot_count_++;
            soft_rapidshot_shot_count_in_one_push_++;
            //�\�t�g�A�ˈێ����ԊO����
            if(soft_rapidshot_frames_in_one_push > SOFT_RAPIDSHOT_INTERVAL*(SOFT_RAPIDSHOT_NUM-1)) {
                //�\�t�g�A�ˉ���
                is_being_soft_rapidshot_ = false;
                soft_rapidshot_shot_count_ = 0;
                soft_rapidshot_shot_count_in_one_push_ = 0;
                soft_rapidshot_push_cnt_ = 0;
                is_just_shot_ = false; //�V���b�g������
            } else {
                //�\�t�g�A�ˈێ����ԓ��Ȃ̂�
                is_just_shot_ = true;  //�V���b�g���܂��傤
                soft_rapidshot_frames_in_one_push++;
            }
        } else {
            //�\�t�g�A�˒������A�^�C�~���O������
            is_just_shot_ = false;
            soft_rapidshot_frames_in_one_push++;
        }
    } else {
         //�\�t�g�A�˒��ł���Ȃ�
        is_just_shot_ = false;
    }

    //�X�i�C�v�V���b�g�̔���
    is_snipe_shot_ = false;
    if (is_just_shot_) {
        if (soft_rapidshot_push_cnt_ == 1) { //�ŏ��̃v�b�V���ł���B
            if (soft_rapidshot_shot_count_in_one_push_ == 1) {  //�ŏ��̃v�b�V���̂P���ڂł���
                is_snipe_shot_ = true; //�X�i�C�v�V���b�g�I
            }
            if (2 <= soft_rapidshot_shot_count_in_one_push_ && soft_rapidshot_shot_count_in_one_push_ <= SOFT_RAPIDSHOT_NUM) {
                is_just_shot_ = false; //�X�i�C�v�V���b�g���̃v�b�V���́A���e�ȊO�𖳗����V���b�g���������B
            } else {
                is_just_shot_ = true;
            }
        }
    } else {
    }

    if (is_just_shot_) {
        if (is_snipe_shot_) {
            //�X�i�C�v�V���b�g��
            MySnipeShot001* const pSnipeShot = (MySnipeShot001*)pDepo_MySnipeShots001_->dispatch();
            if (pSnipeShot) {
                getSeXmtr()->play3D(SE_FIRE_SHOT);
                pSnipeShot->setPositionAt(this);
                pSnipeShot->getLocoVehicle()->setRzRyMvAng(_rz, _ry);
                pSnipeShot->getLocoVehicle()->setMvVelo(PX_C(100));
                pSnipeShot->getLocoVehicle()->setMvAcce(100);
            }
        } else {
            //�X�i�C�v�V���b�g�ȊO��
            if (shot_level_ >= 1) {
                MyShot001* const pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
                if (pShot) {
                    getSeXmtr()->play3D(SE_FIRE_SHOT);
                    pShot->setPositionAt(this);
                    pShot->getLocoVehicle()->setRzRyMvAng(_rz, _ry);
                    pShot->getLocoVehicle()->setMvVelo(PX_C(70));
                    pShot->getLocoVehicle()->setMvAcce(80);
                }
            }

            if (shot_level_ == 2) {
                uint32_t i = soft_rapidshot_shot_count_ % 4;
                UTIL::shotWay003(this,
                                 pDepo_MyShots001_ , MyShip::shot2_matrix_[i],
                                 nullptr, nullptr,
                                 nullptr, nullptr,
                                 PX_C(1),
                                 MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
                                 D_ANG(5), D_ANG(5),
                                 PX_C(70), 100,
                                 1, 0, 1.0);
            } else if (shot_level_ >= 3) {
                uint32_t i = soft_rapidshot_shot_count_ % 2;
                UTIL::shotWay003(this,
                                 pDepo_MyShots001_ , MyShip::shot3_matrix_[i],
                                 nullptr, nullptr,
                                 nullptr, nullptr,
                                 PX_C(1),
                                 MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
                                 D_ANG(5), D_ANG(5),
                                 PX_C(70), 100,
                                 1, 0, 1.0);
            }
        }
    }


    //���q��������
    if (pVbPlay->isPushedDown(0, VV_VB_SHOT2)) {
        if (this->pTorpedoCtrler_->fire()) {
            getSeXmtr()->play3D(SE_FIRE_TORPEDO);
        }
    }


    if (prev_x_ == _x && prev_y_ == _y && prev_z_ == _z) {
        is_move_ = false;
    } else {
        is_move_ = true;
    }
    mv_offset_x_ = _x - prev_x_;
    mv_offset_y_ = _y - prev_y_;
    mv_offset_z_ = _z - prev_z_;
    prev_x_ = _x;
    prev_y_ = _y;
    prev_z_ = _z;
}

void MyShip::processJudgement() {
    //TODO:���� TEST
    if (GgafDx::Input::isPushedDownKey(DIK_0)) {
        //���@�����J��
        setHitAble(false);
        getSeXmtr()->play3D(SE_EXPLOSION);
        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }
    //TODO:�_���[�W�e�X�g TEST
    if (GgafDx::Input::isPushedDownKey(DIK_9)) {
        int vreath = getStatus()->get(STAT_Stamina);
        getStatus()->minus(STAT_Stamina, 10000);
        int damage = vreath - getStatus()->get(STAT_Stamina);
        if (damage > 0) {
            pMagicMeter_->pDamageDispBar_->dispDamage(vreath, vreath-damage);
        }
    }
}

void MyShip::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    int vreath = getStatus()->get(STAT_Stamina);
    if (UTIL::calcMyStamina(this, pOther) <= 0) {
        //���@�����J��
        setHitAble(false);
        getSeXmtr()->play3D(SE_EXPLOSION);
        throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
    }
    int damage = vreath - getStatus()->get(STAT_Stamina);
    if (damage > 0) {
        pMagicMeter_->pDamageDispBar_->dispDamage(vreath, vreath-damage);
    }

    //�ǂ̏ꍇ���ʂȏ���
    if (pOther->lookUpKind() & KIND_CHIKEI) {
        //������ѕ������l����B
        //���݂̈ړ��̋t�����i������шЗ͂͂Q�{�Ɂj
        double vx1,vy1,vz1;
        coord dX1 = -mv_offset_x_;
        coord dY1 = -mv_offset_y_;
        coord dZ1 = -mv_offset_z_;
        if (dX1 == 0 && dY1 == 0 && dZ1 == 0) {
            vx1 = vy1 = vz1 = 0;
        } else {
            UTIL::getNormalizedVector(dX1, dY1, dZ1,
                                     vx1, vy1, vz1 );
        }
        double vx2, vy2, vz2;
        coord dX2,dY2,dZ2;
        if ( pOther->instanceOf(Obj_MassWallActor)) {
            GgafLib::MassWallActor* pOtherWall = (GgafLib::MassWallActor*)pOther;
            pos_t pos_info = pOtherWall->_pos_info;
//            GgafDx::CollisionPart** papColli = pOther->_pChecker->_pCollisionArea->_papColliPart;
//            ColliAABox* pBox = (ColliAABox*)(papColli[0]); //[0]BOX,[1]�v���Y��,[2]�s���~�b�h
//            ColliAAPrism* pPrism = (ColliAAPrism*)(papColli[1]); //[0]BOX,[1]�v���Y��,[2]�s���~�b�h
//            ColliAAPyramid* pPyramid = (ColliAAPyramid*)(papColli[2]); //[0]BOX,[1]�v���Y��,[2]�s���~�b�h
//            if (pBox->_is_valid_flg) {
            if (pos_info == 0) {
                //BOX
                dX2 = (_x - pOther->_x);
                dY2 = (_y - pOther->_y);
                dZ2 = (_z - pOther->_z);
//            } else if (pPrism->_is_valid_flg) {
            } else if (POS_PRISM_XY_NN <= pos_info && pos_info <= POS_PRISM_ZX_PP) {
                //�v���Y����
                ColliAAPrism* pPrism = (ColliAAPrism*)(pOtherWall->_pChecker->_pCollisionArea->_papColliPart[0]);
                //������ԏd�S���W��␳
                if (pos_info & POS_PRISM_XY_xx) {
                    if (pos_info & POS_PRISM_xx_PP) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ���_������
                        // x- ��  ��  �_�焠  �� x+
                        //        ��    �_��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_x - (pOther->_x + pPrism->_hdx));
                        dY2 = (_y - (pOther->_y + pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z               ));
                    } else if (pos_info & POS_PRISM_xx_NP) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        �������^��
                        // x- ��  ����^  ��  �� x+
                        //        ���^    ��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_x - (pOther->_x - pPrism->_hdx));
                        dY2 = (_y - (pOther->_y + pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z               ));
                    } else if (pos_info & POS_PRISM_xx_PN) {
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ��    �^��
                        // x- ��  ��  �^����  �� x+
                        //        ���^���焠
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_x - (pOther->_x + pPrism->_hdx));
                        dY2 = (_y - (pOther->_y - pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z               ));
                    } else { // �̂���� POS_PRISM_xx_NN
                        //            �� y+
                        // (_x1,_y2)      (_x2,_y2)
                        //        ����������
                        //        ���_    ��
                        // x- ��  �����_  ��  �� x+
                        //        ������_��
                        //        ����������
                        // (_x1,_y1)      (_x2,_y1)
                        //            �� y-
                        dX2 = (_x - (pOther->_x - pPrism->_hdx));
                        dY2 = (_y - (pOther->_y - pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z               ));
                    }

                } else if (pos_info & POS_PRISM_YZ_xx) {

                    if (pos_info & POS_PRISM_xx_PP) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ���_������
                        // y- ��  ��  �_�焠  �� y+
                        //        ��    �_��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_x - (pOther->_x               ));
                        dY2 = (_y - (pOther->_y + pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z + pPrism->_hdz));
                    } else if (pos_info & POS_PRISM_xx_NP) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        �������^��
                        // y- ��  ����^  ��  �� y+
                        //        ���^    ��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_x - (pOther->_x               ));
                        dY2 = (_y - (pOther->_y - pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z + pPrism->_hdz));
                    } else if (pos_info & POS_PRISM_xx_PN) {
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ��    �^��
                        // y- ��  ��  �^����  �� y+
                        //        ���^���焠
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_x - (pOther->_x               ));
                        dY2 = (_y - (pOther->_y + pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z - pPrism->_hdz));
                    } else { // �̂���� POS_PRISM_xx_NN
                        //            �� z+
                        // (_y1,_z2)      (_y2,_z2)
                        //        ����������
                        //        ���_    ��
                        // y- ��  �����_  ��  �� y+
                        //        ������_��
                        //        ����������
                        // (_y1,_z1)      (_y2,_z1)
                        //            �� z-
                        dX2 = (_x - (pOther->_x               ));
                        dY2 = (_y - (pOther->_y - pPrism->_hdy));
                        dZ2 = (_z - (pOther->_z - pPrism->_hdz));
                    }

                } else if (pos_info & POS_PRISM_ZX_xx) {
                    if (pos_info & POS_PRISM_xx_PP) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ���_������
                        // z- ��  ��  �_�焠  �� z+
                        //        ��    �_��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_x - (pOther->_x + pPrism->_hdx));
                        dY2 = (_y - (pOther->_y               ));
                        dZ2 = (_z - (pOther->_z + pPrism->_hdz));
                    } else if (pos_info & POS_PRISM_xx_NP) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        �������^��
                        // z- ��  ����^  ��  �� z+
                        //        ���^    ��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_x - (pOther->_x + pPrism->_hdx));
                        dY2 = (_y - (pOther->_y               ));
                        dZ2 = (_z - (pOther->_z - pPrism->_hdz));
                    } else if (pos_info & POS_PRISM_xx_PN) {
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ��    �^��
                        // z- ��  ��  �^����  �� z+
                        //        ���^���焠
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_x - (pOther->_x - pPrism->_hdx));
                        dY2 = (_y - (pOther->_y               ));
                        dZ2 = (_z - (pOther->_z + pPrism->_hdz));
                    } else { // �̂���� POS_PRISM_xx_NN
                        //            �� x+
                        // (_z1,_x2)      (_z2,_x2)
                        //        ����������
                        //        ���_    ��
                        // z- ��  �����_  ��  �� z+
                        //        ������_��
                        //        ����������
                        // (_z1,_x1)      (_z2,_x1)
                        //            �� x-
                        dX2 = (_x - (pOther->_x - pPrism->_hdx));
                        dY2 = (_y - (pOther->_y                ));
                        dZ2 = (_z - (pOther->_z - pPrism->_hdz));
                    }
                } else {
                    //�s���~�b�h
                    //TODO:�s���~�b�h�ӂ��Ƃԏd�S
                    dX2 = (_x - pOther->_x);
                    dY2 = (_y - pOther->_y);
                    dZ2 = (_z - pOther->_z);
                }
            } else {

            }
        } else {
            //�ǂ���Ȃ��ꍇ�͒��S���W�Ő�����ԕ�������
            GgafDx::CollisionArea* pActiveCollisionArea = pOther->_pChecker->_pCollisionArea;
            if (pActiveCollisionArea->_hit_colli_part_index >= 0) {
                GgafDx::CollisionPart* pPart = pActiveCollisionArea->_papColliPart[pActiveCollisionArea->_hit_colli_part_index];
                dX2 = (_x - (pOther->_x + pPart->_cx));
                dY2 = (_y - (pOther->_y + pPart->_cy));
                dZ2 = (_z - (pOther->_z + pPart->_cz));
            } else {
                dX2 = (_x - pOther->_x);
                dY2 = (_y - pOther->_y);
                dZ2 = (_z - pOther->_z);
            }
        }

        if (dX2 == 0 && dY2 == 0 && dZ2 == 0) {
            vx2 = vy2 = vz2 = 0;
        } else {
            UTIL::getNormalizedVector(dX2, dY2, dZ2,
                                     vx2, vy2, vz2 );
        }

        double vx3, vy3, vz3;
        UTIL::getNormalizedVector(
                    vx1+vx2, vy1+vy2, vz1+vz2,
                    vx3, vy3, vz3);
        setBlownVelo(vx3*PX_C(40), vy3*PX_C(40), vz3*PX_C(40), 0.8);
        setInvincibleFrames(120);
    }
    if (pOther->lookUpKind() & KIND_ITEM)  {
    } else {
        UTIL::activateExplosionEffectOf(this);
        getSeXmtr()->play3D(SE_DAMAGED);
    }
}


void MyShip::setMoveSpeed(velo prm_speed_velo) {
    //lv_MoveSpeed_ = lv;
    //mv_speed_ = PX_C(lv);
    mv_speed_ = prm_speed_velo;
    veloBeginMT_ = mv_speed_ * 20;
}

void MyShip::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}

void MyShip::setBlownVelo(velo prm_blown_veloX, velo prm_blown_veloY, velo prm_blown_veloZ, double prm_r_blown_velo_attenuate) {
    blown_veloX_ += prm_blown_veloX;
    blown_veloY_ += prm_blown_veloY;
    blown_veloZ_ += prm_blown_veloZ;
    r_blown_velo_decay_ = prm_r_blown_velo_attenuate;
}

void MyShip::setInvincibleFrames(int prm_frames) {
    setHitAble(false);
    invincible_frames_ = prm_frames;
}
void MyShip::updateMoveWay() {
    VirtualButton* pVbPlay = VV_VB_PLAY;
    dir26 pos_camera = pVAM->getPosCam();
    dir26 pos_up = pVAM->getPosUp();
    dir26* pa_dir8 = VamSysCamWorker::cam_to_8dir_[pos_camera]; //�W�����Q�b�g
    //UP������T���B
    int up_idx = 0;
    for (int i = 0; i < 8; i++) {
        if (pos_up == pa_dir8[i]) {
            up_idx = i; //UP�����C���f�b�N�X�ۑ�
        }
    }
    //pa_dir8[up_idx] ����ł���
    bool isPressed_VV_VB_UP    = pVbPlay->isPressed(0, VV_VB_UP);
    bool isPressed_VV_VB_DOWN  = pVbPlay->isPressed(0, VV_VB_DOWN);
    bool isPressed_VV_VB_LEFT  = pVbPlay->isPressed(0, VV_VB_LEFT);
    bool isPressed_VV_VB_RIGHT = pVbPlay->isPressed(0, VV_VB_RIGHT);
    int mv_dir = -1; //���͕����ԍ�0~7(�ォ��E���̂W����)
    if (isPressed_VV_VB_UP) {
        if (isPressed_VV_VB_RIGHT) {
            mv_dir = 1; //�E��
        } else if (isPressed_VV_VB_LEFT) {
            mv_dir = 7; //����
        } else {
            mv_dir = 0; //��
        }
    } else if (isPressed_VV_VB_DOWN) {
        if (isPressed_VV_VB_RIGHT) {
            mv_dir = 3; //�E��
        } else if (isPressed_VV_VB_LEFT) {
            mv_dir = 5; //����
        } else {
            mv_dir = 4; //��
        }
    } else if (isPressed_VV_VB_RIGHT) {
        mv_dir = 2;
    } else if (isPressed_VV_VB_LEFT) {
        mv_dir = 6;
    }
    dir26 new_mv_way = DIR26(0, 0, 0);
    if (mv_dir > -1) {
        int dir_8_idx = (up_idx + mv_dir) % 8;
        new_mv_way = pa_dir8[dir_8_idx];
    }
    prev_way_ = mv_way_;
    mv_way_ = new_mv_way;
    Direction26Util::cnvDirNo2Sgn(mv_way_,
                                  mv_way_sgn_x_, mv_way_sgn_y_, mv_way_sgn_z_);
    is_just_change_mv_way_ = (prev_way_ != mv_way_ ? true : false);
}

void MyShip::moveNomal() {
    const dir26 mv_way = mv_way_;
    double vx,vy,vz;
    Direction26Util::cnvDirNo2Vec(mv_way, vx, vy, vz);
    _x += mv_speed_ * vx;
    _y += mv_speed_ * vy;
    _z += mv_speed_ * vz;
    if (is_just_change_mv_way_) {
        angle rz, ry;
        Direction26Util::cnvDirNo2RzRy(mv_way, rz, ry);
        getLocoVehicle()->setRzRyMvAng(rz, ry);
        //����
        int sgn_turn = pSenakai_[mv_way] > pSenakai_[prev_way_] ? 1 : -1;
        if (sgn_turn != 0) {
            getLocoVehicle()->setFaceAngAcce(AXIS_X, sgn_turn*angRxAcce_MZ_);
            getLocoVehicle()->setStopTargetFaceAng(AXIS_X, pSenakai_[mv_way],
                                              TURN_CLOSE_TO,
                                              angRxTopVelo_MZ_);
        }
    }
}

void MyShip::moveTurbo() {
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    double vx,vy,vz;
    Direction26Util::cnvDirNo2Vec(mv_way_, vx, vy, vz);
    pCoordVehicle->addVeloX(veloBeginMT_ * vx);
    pCoordVehicle->addVeloY(veloBeginMT_ * vy);
    pCoordVehicle->addVeloZ(veloBeginMT_ * vz);
    angle rz, ry;
    Direction26Util::cnvDirNo2RzRy(mv_way_, rz, ry);
    getLocoVehicle()->setRzRyMvAng(rz, ry);

    //����
    angle senkai = pSenakai_[mv_way_];
    if (senkai != 0) {
        double senkai_spin_speed_rate = (1.0 * D90ANG / senkai); //���񎞁A90�x-90�x�ɌX���ꍇ 1.0�A1.0 �ƂȂ�B
        getLocoVehicle()->setRollFaceAngVelo(angRxVelo_BeginMZT_ * senkai_spin_speed_rate);
    }
}

MyShip::~MyShip() {
}


