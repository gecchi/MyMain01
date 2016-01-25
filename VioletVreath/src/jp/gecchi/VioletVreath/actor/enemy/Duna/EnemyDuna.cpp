#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define REV_TURN_ANGVELO (D_ANG(30))
#define LARGE_SEMIARC_ANGVELO (D_ANG(3))
#define SMALL_SEMIARC_ANGVELO (D_ANG(6))
#define SEMIARC_ANG (D_ANG(200))
EnemyDuna::EnemyDuna(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Duna", STATUS(EnemyDuna)) {
    _class_name = "EnemyDuna";
    pAFader_ = NEW GgafDxAlphaFader(this);
    pAxsMver_ = NEW GgafDxAxesMover(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //â¡éZçáê¨
    setScaleR(0.3);
    useProgress(PROG_BANPEI);
}

void EnemyDuna::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 40000);
}

void EnemyDuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
//    if (pProg->hasJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"Å®"<<pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    if (pProg->hasJustChanged()) {
        pAxsMver_->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->linkFaceAngByMvAng(false);
            pKuroko->keepOnTurningFaceAngTwd(pMyShip,
                                             D_ANG(2), 0, TURN_CLOSE_TO,false);
            //pKuroko->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
            pKuroko->setMvVelo(PX_C(6));
            pKuroko->setRzRyMvAng(0, D90ANG);
            pKuroko->setRzMvAngVelo(D_ANG(12));
            pKuroko->setRzMvAngAcce(D_ANG(0.05));
            setMorphWeight(0.0);
            pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             EffectBlink* pEffectEntry = nullptr;
             if (pProg->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons = pEffectEntry->getFrameOfSummonsBegin();
             static const frame summoning_frames = pEffectEntry->getSummoningFrames();
             if (pProg->hasArrivedAt(frame_of_summons)) {
                 pAFader_->transitionLinerUntil(1.0, summoning_frames);
             }
             if (pProg->hasArrivedAt(frame_of_summons + summoning_frames)) {
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
                 pKuroko->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
                 pKuroko->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
             }
             if (!pKuroko->isTurningMvAng() && !pKuroko->isTurningFaceAng()) {
                 pKuroko->linkFaceAngByMvAng(true);
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
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

    pKuroko->behave();
    pAxsMver_->behave();
    getMorpher()->behave();
    pAFader_->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDuna::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //îjâÛÇ≥ÇÍÇΩéû(ÉXÉ^É~Éi <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //îjâÛÇ≥ÇÍÇ»Ç©Ç¡ÇΩéû(ÉXÉ^É~Éi > 0)
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate è„èëÇ´ÅBnum_fire_*5 ÇÃ 5 Ç∆ìØÇ∂ílÇ…Ç∑ÇÈÇ±Ç∆
}

EnemyDuna::~EnemyDuna() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}
