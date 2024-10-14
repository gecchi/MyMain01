#include "EnemyDuna.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

#define REV_TURN_ANGVELO (D_ANG(30))
#define LARGE_SEMIARC_ANGVELO (D_ANG(3))
#define SMALL_SEMIARC_ANGVELO (D_ANG(6))
#define SEMIARC_ANG (D_ANG(200))

enum {
    MPH_OPEN = 1,
};
enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY_EFFECT,
    PHASE_ENTRY_MOVE01,
    PHASE_ENTRY_MOVE02,
    PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,
    PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW,
    PHASE_MOVE_REV_LARGE_SEMIARC_CW,
    PHASE_MOVE_REV_LARGE_SEMIARC_CCW,
    PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,
    PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW,
    PHASE_MOVE_REV_SMALL_SEMIARC_CW,
    PHASE_MOVE_REV_SMALL_SEMIARC_CCW,
    PHASE_CLOSE ,
    PHASE_BANPEI,
};

EnemyDuna::EnemyDuna(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Duna", StatusReset(EnemyDuna)) {
    _class_name = "EnemyDuna";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    effectBlendOne(); //���Z����
    setScaleR(0.3);
    step_ = 0;
}

void EnemyDuna::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyDuna::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyDuna::processBehavior() {
//    if (pPhase->hasJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pPhase->getPrevWhenChanged()<<"��"<<pPhase->getCurrent()<<"");
//    }

    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->hasJustChanged()) {
        pCoordVehicle->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pLocusVehicle->linkFaceAngByMvAng(false);
            pLocusVehicle->keepOnTurningFaceAngTwd(pMyShip,
                                             D_ANG(2), 0, TURN_CLOSE_TO,false);
            //pLocusVehicle->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
            pLocusVehicle->setMvVelo(PX_C(6));
            pLocusVehicle->setRzRyMvAng(0, D90ANG);
            pLocusVehicle->setRzMvAngVelo(D_ANG(12));
            pLocusVehicle->setRzMvAngAcce(D_ANG(0.05));
            setMorphWeight(0.0);
            pPhase->changeNext();
            break;
        }
         case PHASE_ENTRY_EFFECT: {
             EffectBlink* pEffectEntry = nullptr;
             if (pPhase->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                 setHitAble(true);
                 pPhase->changeNext();
             }
             break;
         }
         case PHASE_ENTRY_MOVE01: {
             if (pPhase->hasJustChanged()) {
             }
             _x -= PX_C(10);
             if (_x < pMyShip->_x + PX_C(1000)) {
                 pPhase->changeNext();
             }
             break;
         }
         case PHASE_ENTRY_MOVE02: {
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
                 pLocusVehicle->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
             }
             if (!pLocusVehicle->isTurningMvAng() && !pLocusVehicle->isTurningFaceAng()) {
                 pLocusVehicle->linkFaceAngByMvAng(true);
                 pPhase->changeProbab(
                              0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,
                             25, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW,
                             25, PHASE_MOVE_REV_LARGE_SEMIARC_CW,
                              0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,
                              0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,
                             25, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW,
                             25, PHASE_MOVE_REV_SMALL_SEMIARC_CW,
                              0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW
                         );
             }
             break;
         }

         //  ���O�̈ړ���
         //
         //      | ��        �� |        |��  ��|
         //       �_          �^    or    �_���^
         //         �_  ��  �^              �P
         //           �P�P�P
         //  �������ꍇ
         //             ��
         //           �Q�Q�Q                         ��
         //         �^  ��  �_                       �Q
         //       �^          �_                   �^���_
         //   �� | ��        �� | ��           �� |��  ��| ��
         //   �@             �A                �D      �E
         //
         //
         //   �C             �B                �G      �F
         //   �� | ��        �� |  ��          �� |��  ��| ��
         //       �_          �^                   �_���^
         //         �_  ��  �^                       �P
         //           �P�P�P                         ��
         //             ��
         //
         //  �@ �E�E�E PHASE_MOVE_ORDER_LARGE_SEMIARC_CW       �������A  ��~�ʈړ��A���v���
         //  �A �E�E�E PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW      �������A  ��~�ʈړ��A�����v���
         //  �B �E�E�E PHASE_MOVE_REV_LARGE_SEMIARC_CW         �������]�A��~�ʈړ��A���v���
         //  �C �E�E�E PHASE_MOVE_REV_LARGE_SEMIARC_CCW        �������]�A��~�ʈړ��A�����v���
         //  �D �E�E�E PHASE_MOVE_ORDER_SMALL_SEMIARC_CW       �������A  ���~�ʈړ��A���v���
         //  �E �E�E�E PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW      �������A  ���~�ʈړ��A�����v���
         //  �F �E�E�E PHASE_MOVE_REV_SMALL_SEMIARC_CW         �������]�A���~�ʈړ��A���v���
         //  �G �E�E�E PHASE_MOVE_REV_SMALL_SEMIARC_CCW        �������]�A���~�ʈړ��A�����v���

         case PHASE_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //�@�̎��̓���
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW: { //�A
             if (pPhase->hasJustChanged()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //�A�̎��̓���
                 pPhase->changeProbab(
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_LARGE_SEMIARC_CW: {  //�B
             if (pPhase->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //�B�̎��̓���
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_LARGE_SEMIARC_CCW: {  //�C
             if (pPhase->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //�C�̎��̓���
                 pPhase->changeProbab(
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }






         case PHASE_MOVE_ORDER_SMALL_SEMIARC_CW: {  //�D
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //�D�̎��̓���
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW: { //�E
             if (pPhase->hasJustChanged()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //�E�̎��̓���
                 pPhase->changeProbab(
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_SMALL_SEMIARC_CW: {  //�F
             if (pPhase->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //�F�̎��̓���
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_SMALL_SEMIARC_CCW: {  //�G
             if (pPhase->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //�~�ʈړ�
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //�G�̎��̓���
                 pPhase->changeProbab(
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         default: {
             break;
         }
     }

    pLocusVehicle->behave();
    pCoordVehicle->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pPhase="<<pPhase->getCurrent()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDuna::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate �㏑���Bnum_fire_*5 �� 5 �Ɠ����l�ɂ��邱��
}

EnemyDuna::~EnemyDuna() {
}
