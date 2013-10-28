#include "stdafx.h"
#include "EnemyGeria.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGeria::EnemyGeria(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Geria", STATUS(EnemyGeria)) {
    _class_name = "EnemyGeria";
    iMovePatternNo_ = 0;
    max_shots_ = 1;
    shot_num_ = 0;
    can_Shot_ = false;
    do_Shot_ = false;
    velo_mv_begin_ = 0;
    frame_when_shot_ = 0;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_SHOT_001");     //発射
}

void EnemyGeria::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.5, 2.0);
//    _pModel->_pTexBlinker->setPower(0.5);
//    _pModel->_pTexBlinker->beat(60, 3, 1, -1);
//    _pModel->blink_threshold_ = 0.8;
}

void EnemyGeria::initialize() {
    setHitAble(false);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 45000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->forceMvVeloRange(1, _pKurokoA->_veloMv);
}

void EnemyGeria::onActive() {
    _pStatus->reset();
    setHitAble(true);
    do_Shot_ = false;
    can_Shot_ = true;
    shot_num_ = 0;
    frame_when_shot_ = 0;
    velo_mv_begin_ = _pKurokoA->_veloTopMv; //初期移動速度を保存
    _pKurokoA->setMvVelo(velo_mv_begin_); //再加速
    _pKurokoA->setFaceAng(AXIS_X, 0);
    //_pKurokoA->turnMvAngTwd(P_MYSHIP, 50, 0, TURN_CLOSE_TO, false);
}

void EnemyGeria::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (do_Shot_) {
        if (getActiveFrame() == frame_when_shot_) {
            _pKurokoA->setMvVelo(PX_C(3)); //減速
            _pKurokoA->turnRxSpinAngTo(D180ANG, D_ANG(3), 0, TURN_CLOCKWISE);
        } else if (getActiveFrame() == frame_when_shot_ + 60) {
            MyShip* pM = P_MYSHIP;
            GgafDxGeometricActor* pLast =
              UTIL::shotWay001(_x, _y, _z,
                               pM->_x, pM->_y, pM->_z,
                               getCommonDepository(Shot004),
                               PX_C(10),
                               10000, 100,
                               3, 5, 0.9,
                               EnemyGeria::callbackDispatched);
            if (pLast) {
                shot_num_++;
                do_Shot_ = false;
                effectFlush(2); //フラッシュ
                _pSeTx->play3D(SE_FIRE);
            }
//                GgafDxDrawableActor* pShot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                if (pShot) {
//                    shot_num_++;
//                    pShot->positionAs(this);
//                    pShot->_pKurokoA->relateFaceWithMvAng(true);
//                    pShot->_pKurokoA->setMvAngTwd(P_MYSHIP);
//                    pShot->reset();
//                    do_Shot_ = false;
//                    effectFlush(2); //フラッシュ
//                    _pSeTx->play3D(1);
//                }

            _pKurokoA->setMvVelo(velo_mv_begin_); //再加速
        }
    } else {
        if (can_Shot_) {
            MyShip* pM = P_MYSHIP;
            if (pM->_z - 500000 < _z && _z < pM->_z + 500000 &&
                pM->_y - 500000 < _y && _y < pM->_y + 500000 &&
                max_shots_ > shot_num_
            ) {
                frame_when_shot_ = getActiveFrame() + RND(0,60) + 1;
                do_Shot_ = true;
            }
        }
    }
    _pKurokoA->behave();
}

void EnemyGeria::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGeria::onInactive() {
    setHitAble(false);
}

void EnemyGeria::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

EnemyGeria::~EnemyGeria() {
}

void EnemyGeria::callbackDispatched(GgafDxDrawableActor* prm_pDispatched, int prm_dispatched_seq, int prm_set_seq) {
}

