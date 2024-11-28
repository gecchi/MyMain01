#include "EnemyGlaja.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Glaja/EnemyGlajaLance001.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    MPH_OPEN = 1,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_MOVE02 ,
    PHASE_OPEN ,
    PHASE_FIRE ,
    PHASE_CLOSE ,
    PHASE_BANPEI,
};

EnemyGlaja::EnemyGlaja(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Glaja_1", StatusReset(EnemyGlaja)) {
    _class_name = "EnemyGlaja";
    pConn_pShot_ = connectToDepositoryManager("GlajaLance001");
    effectBlendOne(); //加算合成
    setScaleR(0.3);
    num_fire_ = 0;
}

void EnemyGlaja::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyGlaja::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyGlaja::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyGlaja::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_INIT: {
             setHitAble(false);
             setAlpha(0);
             pLocusVehicle->keepOnTurningFaceAngTwd(pMyShip,
                                               D_ANG(2), 0, TURN_CLOSE_TO, false);
             setMorphWeight(0.0);
             pPhase->changeNext();
             break;
         }
         case PHASE_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pPhase->hasJustChanged()) {
                 pEffectEntry = (EffectBlink*)UTIL::activateCommonEffectOf(this, STAT_EntryEffectKind);
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

         case PHASE_MOVE01: {
             if (pPhase->hasJustChanged()) {
                 next_pos_.set(
                             pMyShip->_x + PX_C(300) + RND(PX_C(-100), PX_C(100)),
                             pMyShip->_y + RND(PX_C(-400), PX_C(400)),
                             pMyShip->_z + RND(PX_C(-400), PX_C(400))
                           ); //次の移動目標座標
                 //スィーっとnext_pos_へ移動
                 pLocusVehicle->setMvAngTwd(&next_pos_);
                 velo Vt = RF_EnemyGlaja_MvVelo(G_RANK);
                 velo Ve = 100;
                 coord D = UTIL::getDistance(this, &next_pos_);
                 pLocusVehicle->asstMv()->slideByVd(Vt, D, 0.1, 0.5, Ve, true);
             }

             if (pLocusVehicle->asstMv()->hasJustFinishedSliding()) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE02: {
             if (pPhase->hasJustChanged()) {
             }
             if (pPhase->hasArrivedFrameAt(60)) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_OPEN: {
             if (pPhase->hasJustChanged()) {
                 getMorpher()->transitionLinearUntil(MPH_OPEN, 1.0, 30);
             }
             if (pPhase->hasArrivedFrameAt(30)) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_FIRE: {
             if (pPhase->hasJustChanged()) {
                 num_fire_ = RF_EnemyGlaja_ShotWay(G_RANK);
                 UTIL::shotWay004(
                     this,
                     pConn_pShot_->peek(),
                     PX_C(5),
                     num_fire_, D180ANG,
                     0, 0, // 初期速度はショット側の onActive() で設定される。
                     1, 0, 0.0f,
                     EnemyGlaja::onDispatchedShot
                 );

             }
             if (pPhase->getFrame() >= num_fire_*5) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_CLOSE: {
             if (pPhase->hasJustChanged()) {
                 getMorpher()->transitionLinearUntil(MPH_OPEN, 0.0, 30);
             }
             if (pPhase->hasArrivedFrameAt(30)) {
                 pPhase->change(PHASE_MOVE01); //繰り返し
             }
             break;
         }

         default: {
             break;
         }
     }
    pLocusVehicle->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
//_TRACE_("EnemyGlaja f:"<<getBehaveingFrame()<<"  pPhase="<<pPhase->getCurrent()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyGlaja::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyGlaja::onInactive() {
}

void EnemyGlaja::onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate 上書き。num_fire_*5 の 5 と同じ値にすること
}

EnemyGlaja::~EnemyGlaja() {
    pConn_pShot_->close();
}

