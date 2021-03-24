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
    effectBlendOne(); //â¡éZçáê¨
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
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"Å®"<<pProg->get()<<"");
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
         //  á@ ÅEÅEÅE PROG_MOVE_ORDER_LARGE_SEMIARC_CW       èáï˚å¸ÅA  ëÂâ~å à⁄ìÆÅAéûåvâÒÇË
         //  áA ÅEÅEÅE PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      èáï˚å¸ÅA  ëÂâ~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áB ÅEÅEÅE PROG_MOVE_REV_LARGE_SEMIARC_CW         ï˚å¸îΩì]ÅAëÂâ~å à⁄ìÆÅAéûåvâÒÇË
         //  áC ÅEÅEÅE PROG_MOVE_REV_LARGE_SEMIARC_CCW        ï˚å¸îΩì]ÅAëÂâ~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áD ÅEÅEÅE PROG_MOVE_ORDER_SMALL_SEMIARC_CW       èáï˚å¸ÅA  è¨â~å à⁄ìÆÅAéûåvâÒÇË
         //  áE ÅEÅEÅE PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      èáï˚å¸ÅA  è¨â~å à⁄ìÆÅAîºéûåvâÒÇË
         //  áF ÅEÅEÅE PROG_MOVE_REV_SMALL_SEMIARC_CW         ï˚å¸îΩì]ÅAè¨â~å à⁄ìÆÅAéûåvâÒÇË
         //  áG ÅEÅEÅE PROG_MOVE_REV_SMALL_SEMIARC_CCW        ï˚å¸îΩì]ÅAè¨â~å à⁄ìÆÅAîºéûåvâÒÇË

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //á@
             if (pProg->hasJustChanged()) {
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //á@ÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CCW: { //áA
             if (pProg->hasJustChanged()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //áAÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CW: {  //áB
             if (pProg->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //áBÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CCW: {  //áC
             if (pProg->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //áCÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }






         case PROG_MOVE_ORDER_SMALL_SEMIARC_CW: {  //áD
             if (pProg->hasJustChanged()) {
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //áDÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_SMALL_SEMIARC_CCW: { //áE
             if (pProg->hasJustChanged()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pVecDriver->isTurningMvAng()) {
                 //áEÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CW: {  //áF
             if (pProg->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //áFÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CCW: {  //áG
             if (pProg->hasJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pVecDriver->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pVecDriver->turnRzMvAngTo(pVecDriver->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pVecDriver->isTurningMvAng()) {
                 //áGÇÃéüÇÃìÆçÏ
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
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
        //îjâÛÇ≥ÇÍÇΩéû(ÉXÉ^É~Éi <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
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
