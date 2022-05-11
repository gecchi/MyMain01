#include "EnemyDuna.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
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
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    effectBlendOne(); //加算合成
    setScaleR(0.3);
    step_ = 0;
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
    getPhase()->reset(PHASE_INIT);
}

void EnemyDuna::processBehavior() {
//    if (pPhase->hasJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pPhase->getPrevWhenChanged()<<"→"<<pPhase->getCurrent()<<"");
//    }

    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafDx::AxisVehicle* const pAxisVehicle = getAxisVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->hasJustChanged()) {
        pAxisVehicle->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pVecVehicle->linkFaceAngByMvAng(false);
            pVecVehicle->keepOnTurningFaceAngTwd(pMyShip,
                                             D_ANG(2), 0, TURN_CLOSE_TO,false);
            //pVecVehicle->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
            pVecVehicle->setMvVelo(PX_C(6));
            pVecVehicle->setRzRyMvAng(0, D90ANG);
            pVecVehicle->setRzMvAngVelo(D_ANG(12));
            pVecVehicle->setRzMvAngAcce(D_ANG(0.05));
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
                 pVecVehicle->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
                 pVecVehicle->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
             }
             if (!pVecVehicle->isTurningMvAng() && !pVecVehicle->isTurningFaceAng()) {
                 pVecVehicle->linkFaceAngByMvAng(true);
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

         //  直前の移動が
         //
         //      | ↑        ↓ |        |↑  ↓|
         //       ＼          ／    or    ＼←／
         //         ＼  ←  ／              ￣
         //           ￣￣￣
         //  だった場合
         //             →
         //           ＿＿＿                         →
         //         ／  ←  ＼                       ＿
         //       ／          ＼                   ／←＼
         //   ↑ | ↓        ↑ | ↓           ↑ |↓  ↑| ↓
         //   �@             �A                �D      �E
         //
         //
         //   �C             �B                �G      �F
         //   ↓ | ↑        ↓ |  ↑          ↓ |↑  ↓| ↑
         //       ＼          ／                   ＼←／
         //         ＼  ←  ／                       ￣
         //           ￣￣￣                         →
         //             →
         //
         //  �@ ・・・ PHASE_MOVE_ORDER_LARGE_SEMIARC_CW       順方向、  大円弧移動、時計回り
         //  �A ・・・ PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW      順方向、  大円弧移動、半時計回り
         //  �B ・・・ PHASE_MOVE_REV_LARGE_SEMIARC_CW         方向反転、大円弧移動、時計回り
         //  �C ・・・ PHASE_MOVE_REV_LARGE_SEMIARC_CCW        方向反転、大円弧移動、半時計回り
         //  �D ・・・ PHASE_MOVE_ORDER_SMALL_SEMIARC_CW       順方向、  小円弧移動、時計回り
         //  �E ・・・ PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW      順方向、  小円弧移動、半時計回り
         //  �F ・・・ PHASE_MOVE_REV_SMALL_SEMIARC_CW         方向反転、小円弧移動、時計回り
         //  �G ・・・ PHASE_MOVE_REV_SMALL_SEMIARC_CCW        方向反転、小円弧移動、半時計回り

         case PHASE_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (pPhase->hasJustChanged()) {
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecVehicle->isTurningMvAng()) {
                 //�@の次の動作
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
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecVehicle->isTurningMvAng()) {
                 //�Aの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pVecVehicle->isTurningMvAng()) {
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pVecVehicle->isTurningMvAng()) {
                 //�Bの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pVecVehicle->isTurningMvAng()) {
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pVecVehicle->isTurningMvAng()) {
                 //�Cの次の動作
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
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecVehicle->isTurningMvAng()) {
                 //�Dの次の動作
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
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecVehicle->isTurningMvAng()) {
                 //�Eの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pVecVehicle->isTurningMvAng()) {
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pVecVehicle->isTurningMvAng()) {
                 //�Fの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pVecVehicle->isTurningMvAng()) {
                 //円弧移動
                 pVecVehicle->turnRzMvAngTo(pVecVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pVecVehicle->isTurningMvAng()) {
                 //�Gの次の動作
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

    pVecVehicle->behave();
    pAxisVehicle->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pPhase="<<pPhase->getCurrent()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDuna::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate 上書き。num_fire_*5 の 5 と同じ値にすること
}

EnemyDuna::~EnemyDuna() {
}
