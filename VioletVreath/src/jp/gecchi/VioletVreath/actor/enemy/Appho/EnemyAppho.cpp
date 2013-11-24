#include "stdafx.h"
#include "EnemyAppho.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAppho::EnemyAppho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Appho", STATUS(EnemyAppho)) {
    _class_name = "EnemyAppho";
    _sx=_sy=_sz=100;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAppho::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAppho::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyAppho::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             _pAFader->setAlpha(0);
             _pKurokoA->setMvVelo(0);
             _pKurokoA->relateFaceWithMvAng(true);
             _pKurokoA->setMvAngTwd(&hanging_pos_);
             _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
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
                 //滞留ポイントへGO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 _pKurokoA->slideMvByVD(mv_velo,
                                        RND(-PX_C(0.5),PX_C(0.5)),
                                        d, 0.2, 0.8);
             }
             //滞留ポイントまで移動中
             if (_pProg->getFrameInProgress() % 32U == 0) {
                 //ちょくちょく自機を見つめる
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP, D_ANG(0.5), 0,
                                           TURN_CLOSE_TO, true);
             }
             if (_pKurokoA->isJustFinishSlidingMv()) {
                 _pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pKurokoA->_veloMv<<","<<_pKurokoA->_accMv);
             break;
         }

         case PROG_MOVE02: {
             if (_pProg->isJustChanged()) {
                 //移動方向と向きの連携解除
                 _pKurokoA->relateFaceWithMvAng(false);
                 //滞留ポイント到着、ふらふら気ままな方向へ移動させる
                 _pKurokoA->turnMvAngTwd(_x + RND(-PX_C(100),PX_C(100)),
                                         _y + RND(-PX_C(100),PX_C(100)),
                                         _z + RND(-PX_C(100),PX_C(100)),
                                         100, 0, TURN_CLOSE_TO, false);
                 //ゆっくり自機の方へ向かせる
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //滞留中
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (_pProg->getFrameInProgress() == 180) {
                 //自機の方に向いたら敵弾発射！
                 int shot_num = RF_EnemyAppho_ShotWay(G_RANK); //弾数、ランク変動
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //弾速、ランク変動
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxDrawableActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //ばらつかせ。activate タイミング上書き！
                         pShot->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z],
                                                        _pKurokoA->_angFace[AXIS_Y]);
                         pShot->_pKurokoA->setMvVelo(shot_velo);
                         pShot->_pKurokoA->setMvAcce(100);
                     }
                 }
             }
             if (_pProg->getFrameInProgress() == 240) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //さよなら準備
             if (_pProg->isJustChanged()) {
                 //ゆっくりさよならポイントへ向ける
                 _pKurokoA->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(10);
             }
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //さよなら～
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), 0, TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(100+(G_RANK*200));
             }
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }
         default:
             break;
     }

    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAppho::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
}
