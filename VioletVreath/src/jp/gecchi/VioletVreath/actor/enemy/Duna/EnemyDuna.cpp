#include "stdafx.h"
#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"

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
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //â¡éZçáê¨
    setScaleR(0.3);
    useProgress(PROG_CLOSE);
}

void EnemyDuna::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyDuna::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
    //â¡éZÉâÉìÉNÉ|ÉCÉìÉgÇå∏è≠
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

//    if (_pProg->isJustChanged()) {
//        _TRACE_("EnemyDuna::"<<_pProg->getFromProgOnChange()<<"Å®"<<_pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    if (_pProg->isJustChanged()) {
        _pKurokoB->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            _pKurokoA->relateMvFaceAng(false);
            _pKurokoA->keepOnTurningFaceAngTwd(pMyShip,
                                               D_ANG(2), 0, TURN_CLOSE_TO,false);
            //_pKurokoA->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
                         _pKurokoA->setMvVelo(PX_C(6));
            _pKurokoA->setRzRyMvAng(0, D90ANG);
            _pKurokoA->setRzMvAngVelo(D_ANG(12));
            _pKurokoA->setRzMvAngAcce(D_ANG(0.05));
            _pMorpher->setWeight(0.0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->fadeLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE01: {
             if (_pProg->isJustChanged()) {
             }
             _X -= PX_C(10);
             if (_X  < pMyShip->_X + PX_C(1000)) {
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE02: {
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
                 _pKurokoA->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
             }
             if (!_pKurokoA->isTurningMvAng() && !_pKurokoA->isTurningFaceAng()) {
                 _pKurokoA->relateMvFaceAng(true);
                 progress next = EnemyDuna::getProgressProbability(
                                      0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
                                    250, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
                                    250, PROG_MOVE_REV_LARGE_SEMIARC_CW,
                                      0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,
                                      0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
                                    250, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
                                    250, PROG_MOVE_REV_SMALL_SEMIARC_CW,
                                      0, PROG_MOVE_REV_SMALL_SEMIARC_CCW
                                 );
                 _pProg->change(next);
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
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //á@ÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                     100, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CCW: { //áA
             if (_pProg->isJustChanged()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //áAÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                     100, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CW: {  //áB
             if (_pProg->isJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //áBÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                     100, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CCW: {  //áC
             if (_pProg->isJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //áCÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                     100, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                     150, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }





         case PROG_MOVE_ORDER_SMALL_SEMIARC_CW: {  //áD
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //áDÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                     400, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                     300, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                       0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }

         case PROG_MOVE_ORDER_SMALL_SEMIARC_CCW: { //áE
             if (_pProg->isJustChanged()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //áEÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                     400, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                     300, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                       0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CW: {  //áF
             if (_pProg->isJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //áFÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                     400, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                     300, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                       0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CCW: {  //áG
             if (_pProg->isJustChanged()) {
                 //Ç‹Ç∏äJénèÛë‘ÇÃê^ó†ï˚å¸Ç…å¸Ç≠
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //â~å à⁄ìÆ
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //áGÇÃéüÇÃìÆçÏ
                 progress next = EnemyDuna::getProgressProbability(
                                     400, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  á@
                                       0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  áA
                                     300, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  áB
                                       0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  áC
                                     300, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  áD
                                       0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  áE
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  áF
                                       0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  áG
                                 );
                 _pProg->change(next);
             }
             break;
         }
         default:
             break;
     }

    _pKurokoA->behave();
    _pKurokoB->behave();
    _pMorpher->behave();
    _pAFader->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<_pProg->get()<<"   X,Y,Z="<<_X<<","<<_Y<<","<<_Z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyDuna::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //îjâÛéû
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //îÒîjâÛéû
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate è„èëÇ´ÅBnum_fire_*5 ÇÃ 5 Ç∆ìØÇ∂ílÇ…Ç∑ÇÈÇ±Ç∆
}

progress EnemyDuna::getProgressProbability(int p1, progress prog1,
                                           int p2, progress prog2,
                                           int p3, progress prog3,
                                           int p4, progress prog4,
                                           int p5, progress prog5,
                                           int p6, progress prog6,
                                           int p7, progress prog7,
                                           int p8, progress prog8) {
    int r = RND(1,1000);
    if (r <= p1) {
        return prog1;
    } else if ( p1 < r && r <= (p1+p2) ) {
        return prog2;
    } else if ( (p1+p2) < r && r <= (p1+p2+p3) ) {
        return prog3;
    } else if ( (p1+p2+p3) < r && r <= (p1+p2+p3+p4) ) {
        return prog4;
    } else if ( (p1+p2+p3+p4) < r && r <= (p1+p2+p3+p4+p5) ) {
        return prog5;
    } else if ( (p1+p2+p3+p4+p5) < r && r <= (p1+p2+p3+p4+p5+p6) ) {
        return prog6;
    } else if ( (p1+p2+p3+p4+p5+p6) < r && r <= (p1+p2+p3+p4+p5+p6+p7) ) {
        return prog7;
    } else if ( (p1+p2+p3+p4+p5+p6+p7) < r && r <= (p1+p2+p3+p4+p5+p6+p7+p8) ) {
        return prog8;
    } else {
        throwGgafCriticalException("getProgressProbability r="<<r<<"Ç≈òRÇÍÇ‹ÇµÇΩÅBà¯êîÇÃämó¶ÇÃçáåvÇ 100 Ç…ÇµÇƒâ∫Ç≥Ç¢ÅB");
    }
}

EnemyDuna::~EnemyDuna() {
}
