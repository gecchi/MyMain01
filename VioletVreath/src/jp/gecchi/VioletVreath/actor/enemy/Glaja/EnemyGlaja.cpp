#include "stdafx.h"
#include "EnemyGlaja.h"

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
#include "jp/gecchi/VioletVreath/actor/enemy/Glaja/EnemyGlajaLance001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlaja::EnemyGlaja(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Glaja", STATUS(EnemyGlaja)) {
    _class_name = "EnemyGlaja";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pConn_Shot_ = connect_DepositoryManager("GlajaLance001");
    effectBlendOne(); //加算合成
    setScaleR(0.3);
    useProgress(PROG_CLOSE);
}

void EnemyGlaja::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyGlaja::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyGlaja::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyGlaja::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             _pAFader->setAlpha(0);
             _pKurokoA->keepOnTurningFaceAngTwd(pMyShip,
                                                D_ANG(1), 0, TURN_CLOSE_TO,false);
             _pMorpher->setWeight(0.0);
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->fadeLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 next_pos_.set(
                             pMyShip->_X + PX_C(300) + RND(PX_C(-100), PX_C(100)),
                             pMyShip->_Y + RND(PX_C(-400), PX_C(400)),
                             pMyShip->_Z + RND(PX_C(-400), PX_C(400))
                           ); //次の移動目標座標
                 //スィーっとnext_pos_へ移動
                 _pKurokoA->setMvAngTwd(&next_pos_);
                 velo mv_velo = RF_EnemyGlaja_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &next_pos_);
                 _pKurokoA->slideMvByVD(mv_velo, 100, d, 0.1, 0.5, true);
             }

             if (_pKurokoA->isJustFinishSlidingMv()) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE02: {
             if (_pProg->isJustChanged()) {
             }
             if (_pProg->getFrameInProgress() == 60) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_OPEN: {
             if (_pProg->isJustChanged()) {
                 _pMorpher->morphLinerUntil(MPH_OPEN, 1.0, 30);
             }
             if (_pProg->getFrameInProgress() == 30) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_FIRE: {
             if (_pProg->isJustChanged()) {
                 num_fire_ = RF_EnemyGlaja_ShotWay(G_RANK);
                 UTIL::shotWay004(
                     this,
                     pConn_Shot_->peek(),
                     PX_C(5),
                     num_fire_, D180ANG,
                     0, 0, // 初期速度はショット側の onActive() で設定される。
                     1, 0, 0.0f,
                     EnemyGlaja::onDispatchedShot
                 );

             }
             if (_pProg->getFrameInProgress() >= num_fire_*5) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_CLOSE: {
             if (_pProg->isJustChanged()) {
                 _pMorpher->morphLinerUntil(MPH_OPEN, 0.0, 30);
             }
             if (_pProg->getFrameInProgress() == 30) {
                 _pProg->change(PROG_MOVE01); //繰り返し
             }
             break;
         }

         default:
             break;
     }

    _pKurokoA->behave();
    _pMorpher->behave();
    _pAFader->behave();
//_TRACE_("EnemyGlaja f:"<<getBehaveingFrame()<<"  pProg="<<_pProg->get()<<"   X,Y,Z="<<_X<<","<<_Y<<","<<_Z<<" ");
}

void EnemyGlaja::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGlaja::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyGlaja::onInactive() {
    sayonara();
}

void EnemyGlaja::onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate 上書き。num_fire_*5 の 5 と同じ値にすること
}

EnemyGlaja::~EnemyGlaja() {
    pConn_Shot_->close();
}
