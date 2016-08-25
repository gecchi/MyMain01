#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
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
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //加算合成
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
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"→"<<pProg->get()<<"");
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
         //  �@ ・・・ PROG_MOVE_ORDER_LARGE_SEMIARC_CW       順方向、  大円弧移動、時計回り
         //  �A ・・・ PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      順方向、  大円弧移動、半時計回り
         //  �B ・・・ PROG_MOVE_REV_LARGE_SEMIARC_CW         方向反転、大円弧移動、時計回り
         //  �C ・・・ PROG_MOVE_REV_LARGE_SEMIARC_CCW        方向反転、大円弧移動、半時計回り
         //  �D ・・・ PROG_MOVE_ORDER_SMALL_SEMIARC_CW       順方向、  小円弧移動、時計回り
         //  �E ・・・ PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      順方向、  小円弧移動、半時計回り
         //  �F ・・・ PROG_MOVE_REV_SMALL_SEMIARC_CW         方向反転、小円弧移動、時計回り
         //  �G ・・・ PROG_MOVE_REV_SMALL_SEMIARC_CCW        方向反転、小円弧移動、半時計回り

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (pProg->hasJustChanged()) {
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�@の次の動作
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
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�Aの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�Bの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�Cの次の動作
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
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�Dの次の動作
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
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�Eの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�Fの次の動作
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
                 //まず開始状態の真裏方向に向く
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //円弧移動
                 pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�Gの次の動作
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
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
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

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate 上書き。num_fire_*5 の 5 と同じ値にすること
}

EnemyDuna::~EnemyDuna() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}
