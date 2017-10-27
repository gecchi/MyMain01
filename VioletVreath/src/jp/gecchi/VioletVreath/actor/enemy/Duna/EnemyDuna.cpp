#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
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
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //‰ÁZ‡¬
    setScaleR(0.3);
    useProgress(PROG_BANPEI);
    nprog_ = 0;
}

void EnemyDuna::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 40000);
}

void EnemyDuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
//    if (pProg->hasJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"¨"<<pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    GgafProgress* const pProg = getProgress();
    if (pProg->hasJustChanged()) {
        pAxesMover->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
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

         //  ’¼‘O‚ÌˆÚ“®‚ª
         //
         //      | ª        « |        |ª  «|
         //       _          ^    or    _©^
         //         _  ©  ^              P
         //           PPP
         //  ‚¾‚Á‚½ê‡
         //             ¨
         //           QQQ                         ¨
         //         ^  ©  _                       Q
         //       ^          _                   ^©_
         //   ª | «        ª | «           ª |«  ª| «
         //   ‡@             ‡A                ‡D      ‡E
         //
         //
         //   ‡C             ‡B                ‡G      ‡F
         //   « | ª        « |  ª          « |ª  «| ª
         //       _          ^                   _©^
         //         _  ©  ^                       P
         //           PPP                         ¨
         //             ¨
         //
         //  ‡@ EEE PROG_MOVE_ORDER_LARGE_SEMIARC_CW       ‡•ûŒüA  ‘å‰~ŒÊˆÚ“®AŒv‰ñ‚è
         //  ‡A EEE PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      ‡•ûŒüA  ‘å‰~ŒÊˆÚ“®A”¼Œv‰ñ‚è
         //  ‡B EEE PROG_MOVE_REV_LARGE_SEMIARC_CW         •ûŒü”½“]A‘å‰~ŒÊˆÚ“®AŒv‰ñ‚è
         //  ‡C EEE PROG_MOVE_REV_LARGE_SEMIARC_CCW        •ûŒü”½“]A‘å‰~ŒÊˆÚ“®A”¼Œv‰ñ‚è
         //  ‡D EEE PROG_MOVE_ORDER_SMALL_SEMIARC_CW       ‡•ûŒüA  ¬‰~ŒÊˆÚ“®AŒv‰ñ‚è
         //  ‡E EEE PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      ‡•ûŒüA  ¬‰~ŒÊˆÚ“®A”¼Œv‰ñ‚è
         //  ‡F EEE PROG_MOVE_REV_SMALL_SEMIARC_CW         •ûŒü”½“]A¬‰~ŒÊˆÚ“®AŒv‰ñ‚è
         //  ‡G EEE PROG_MOVE_REV_SMALL_SEMIARC_CCW        •ûŒü”½“]A¬‰~ŒÊˆÚ“®A”¼Œv‰ñ‚è

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //‡@
             if (pProg->hasJustChanged()) {
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //‡@‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CCW: { //‡A
             if (pProg->hasJustChanged()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //‡A‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CW: {  //‡B
             if (pProg->hasJustChanged()) {
                 //‚Ü‚¸ŠJnó‘Ô‚Ì^— •ûŒü‚ÉŒü‚­
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //‡B‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CCW: {  //‡C
             if (pProg->hasJustChanged()) {
                 //‚Ü‚¸ŠJnó‘Ô‚Ì^— •ûŒü‚ÉŒü‚­
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //‡C‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }






         case PROG_MOVE_ORDER_SMALL_SEMIARC_CW: {  //‡D
             if (pProg->hasJustChanged()) {
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //‡D‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_SMALL_SEMIARC_CCW: { //‡E
             if (pProg->hasJustChanged()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //‡E‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CW: {  //‡F
             if (pProg->hasJustChanged()) {
                 //‚Ü‚¸ŠJnó‘Ô‚Ì^— •ûŒü‚ÉŒü‚­
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //‡F‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CCW: {  //‡G
             if (pProg->hasJustChanged()) {
                 //‚Ü‚¸ŠJnó‘Ô‚Ì^— •ûŒü‚ÉŒü‚­
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //‰~ŒÊˆÚ“®
                 pKuroko->turnRzMvAngTo(pKuroko->_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //‡G‚ÌŸ‚Ì“®ì
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  ‡@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  ‡A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  ‡B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  ‡C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  ‡D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  ‡E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  ‡F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  ‡G
                         );
             }
             break;
         }

         default: {
             break;
         }
     }

    pKuroko->behave();
    pAxesMover->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDuna::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰ó‚³‚ê‚½(ƒXƒ^ƒ~ƒi <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //”j‰ó‚³‚ê‚È‚©‚Á‚½(ƒXƒ^ƒ~ƒi > 0)
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate ã‘‚«Bnum_fire_*5 ‚Ì 5 ‚Æ“¯‚¶’l‚É‚·‚é‚±‚Æ
}

EnemyDuna::~EnemyDuna() {
}
