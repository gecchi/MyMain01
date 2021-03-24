#include "EnemyDuna.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/GeoDriver.h"
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
    PROG_INIT   ,
    PROG_ENTRY_EFFECT,
    PROG_ENTRY_MOVE01,
    PROG_ENTRY_MOVE02,
    PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
    PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
    PROG_MOVE_REV_LARGE_SEMIARC_CW,
    PROG_MOVE_REV_LARGE_SEMIARC_CCW,
    PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
    PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
    PROG_MOVE_REV_SMALL_SEMIARC_CW,
    PROG_MOVE_REV_SMALL_SEMIARC_CCW,
    PROG_CLOSE ,
    PROG_BANPEI,
};

EnemyDuna::EnemyDuna(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Duna_1", StatusReset(EnemyDuna)) {
    _class_name = "EnemyDuna";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //���Z����
    setScaleR(0.3);
    nprog_ = 0;
}

void EnemyDuna::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyDuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
//    if (pProg->hasJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"��"<<pProg->get()<<"");
//    }

    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    GgafDx::GeoDriver* const pGeoDriver = callGeoDriver();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->hasJustChanged()) {
        pGeoDriver->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pVecDriver->linkFaceAngByMvAng(false);
            pVecDriver->keepOnTurningFaceAngTwd(pMyShip,
                                             D_ANG(2), 0, TURN_CLOSE_TO,false);
            //pVecDriver->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
            pVecDriver->setMvVelo(PX_C(6));
            pVecDriver->setRzRyMvAng(0, D90ANG);
            pVecDriver->setRzMvAngVelo(D_ANG(12));
            pVecDriver->setRzMvAngAcce(D_ANG(0.05));
            setMorphWeight(0.0);
            pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             EffectBlink* pEffectEntry = nullptr;
             if (pProg->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE01: {
             if (pProg->hasJustChanged()) {
             }
             _x -= PX_C(10);
             if (_x < pMyShip->_x + PX_C(1000)) {
                 pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE02: {
             if (pProg->hasJustChanged()) {
                 pVecDriver->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
                 pVecDriver->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
             }
             if (!pVecDriver->isTurningMvAng() && !pVecDriver->isTurningFaceAng()) {
                 pVecDriver->linkFaceAngByMvAng(true);
                 pProg->changeProbab(
                              0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
                             25, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
                             25, PROG_MOVE_REV_LARGE_SEMIARC_CW,
                              0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,
                              0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
                             25, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
                             25, PROG_MOVE_REV_SMALL_SEMIARC_CW,
                              0, PROG_MOVE_REV_SMALL_SEMIARC_CCW
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
         //  �@ �E�E�E PROG_MOVE_ORDER_LARGE_SEMIARC_CW       �������A  ��~�ʈړ��A���v���
         //  �A �E�E�E PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      �������A  ��~�ʈړ��A�����v���
         //  �B �E�E�E PROG_MOVE_REV_LARGE_SEMIARC_CW         �������]�A��~�ʈړ��A���v���
         //  �C �E�E�E PROG_MOVE_REV_LARGE_SEMIARC_CCW        �������]�A��~�ʈړ��A�����v���
         //  �D �E�E�E PROG_MOVE_ORDER_SMALL_SEMIARC_CW       �������A  ���~�ʈړ��A���v���
         //  �E �E�E�E PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      �������A  ���~�ʈړ��A�����v���
         //  �F �E�E�E PROG_MOVE_REV_SMALL_SEMIARC_CW         �������]�A���~�ʈړ��A���v���
         //  �G �E�E�E PROG_MOVE_REV_SMALL_SEMIARC_CCW        �������]�A���~�ʈړ��A�����v���

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (pProg->hasJustChanged()) {
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //�@�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CCW: { //�A
             if (pProg->hasJustChanged()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //�A�̎��̓���
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CW: {  //�B
             if (pProg->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //�B�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CCW: {  //�C
             if (pProg->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //�C�̎��̓���
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }






         case PROG_MOVE_ORDER_SMALL_SEMIARC_CW: {  //�D
             if (pProg->hasJustChanged()) {
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //�D�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_SMALL_SEMIARC_CCW: { //�E
             if (pProg->hasJustChanged()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //�E�̎��̓���
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CW: {  //�F
             if (pProg->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //�F�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CCW: {  //�G
             if (pProg->hasJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //�~�ʈړ�
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //�G�̎��̓���
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         default: {
             break;
         }
     }

    pVecDriver->behave();
    pGeoDriver->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDuna::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
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
