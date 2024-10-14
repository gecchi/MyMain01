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
    effectBlendOne(); //â¡éZçáê¨
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
//        _TRACE_("EnemyDuna::"<<pPhase->getPrevWhenChanged()<<"Å®"<<pPhase->getCurrent()<<"");
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

         //  íºëOÇÃà⁄ìÆÇ™
         //
         //      | Å™        Å´ |        |Å™  Å´|
         //       Å_          Å^    or    Å_Å©Å^
         //         Å_  Å©  Å^              ÅP
         //           ÅPÅPÅP
         //  ÇæÇ¡ÇΩèÍçá
         //             Å®
         //           ÅQÅQÅQ                         Å®
         //         Å^  Å©  Å_                       ÅQ
         //       Å^          Å_                   Å^Å©Å_
         //   Å™ | Å´        Å™ | Å´           Å™ |Å´  Å™| Å´
         //   á@             áA                áD      áE
         //
         //
         //   áC             áB                áG      áF
         //   Å´ | Å™        Å´ |  Å™          Å´ |Å™  Å´| Å™
         //       Å_          Å^                   Å_Å©Å^
         //         Å_  Å©  Å^                       ÅP
         //           ÅPÅPÅP                         Å®
         //             Å®
         //
         //  á@ ÅEÅEÅE PHASE_MOVE_ORDER_LARGE_SEMIARC_CW       èáï˚å¸ÅA  ëÂâ~å à⁄ìÆÅAéûåvâÒÇË
         //  áA ÅEÅEÅE PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW      èáï˚å¸ÅA  ëÂâ~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áB ÅEÅEÅE PHASE_MOVE_REV_LARGE_SEMIARC_CW         ï˚å¸îΩì]ÅAëÂâ~å à⁄ìÆÅAéûåvâÒÇË
         //  áC ÅEÅEÅE PHASE_MOVE_REV_LARGE_SEMIARC_CCW        ï˚å¸îΩì]ÅAëÂâ~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áD ÅEÅEÅE PHASE_MOVE_ORDER_SMALL_SEMIARC_CW       èáï˚å¸ÅA  è¨â~å à⁄ìÆÅAéûåvâÒÇË
         //  áE ÅEÅEÅE PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW      èáï˚å¸ÅA  è¨â~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áF ÅEÅEÅE PHASE_MOVE_REV_SMALL_SEMIARC_CW         ï˚å¸îΩì]ÅAè¨â~å à⁄ìÆÅAéûåvâÒÇË
         //  áG ÅEÅEÅE PHASE_MOVE_REV_SMALL_SEMIARC_CCW        ï˚å¸îΩì]ÅAè¨â~å à⁄ìÆÅAîºéûåvâÒÇË

         case PHASE_MOVE_ORDER_LARGE_SEMIARC_CW: {  //á@
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //á@ÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }

         case PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW: { //áA
             if (pPhase->hasJustChanged()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //áAÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_LARGE_SEMIARC_CW: {  //áB
             if (pPhase->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //áBÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_LARGE_SEMIARC_CCW: {  //áC
             if (pPhase->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //áCÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                              10, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }






         case PHASE_MOVE_ORDER_SMALL_SEMIARC_CW: {  //áD
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //áDÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }

         case PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW: { //áE
             if (pPhase->hasJustChanged()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 //áEÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_SMALL_SEMIARC_CW: {  //áF
             if (pPhase->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //áFÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PHASE_MOVE_REV_SMALL_SEMIARC_CCW: {  //áG
             if (pPhase->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 step_ = 0;
             }
             if (step_ == 0 && !pLocusVehicle->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pLocusVehicle->turnRzMvAngTo(pLocusVehicle->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 step_ = 1;
             }
             if (step_ == 1 && !pLocusVehicle->isTurningMvAng()) {
                 //áGÇÃéüÇÃìÆçÏ
                 pPhase->changeProbab(
                              40, PHASE_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PHASE_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                              30, PHASE_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PHASE_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PHASE_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                               0, PHASE_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PHASE_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
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
        //îjâÛÇ≥ÇÍÇΩéû(ÉXÉ^É~Éi <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //îjâÛÇ≥ÇÍÇ»Ç©Ç¡ÇΩéû(ÉXÉ^É~Éi > 0)
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate è„èëÇ´ÅBnum_fire_*5 ÇÃ 5 Ç∆ìØÇ∂ílÇ…Ç∑ÇÈÇ±Ç∆
}

EnemyDuna::~EnemyDuna() {
}
