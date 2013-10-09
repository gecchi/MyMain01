#include "stdafx.h"
#include "EnemyEsperiaLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEsperiaLaserChip001::EnemyEsperiaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "EsperiaLaserChip001", STATUS(EnemyEsperiaLaserChip001)) {
    _class_name = "EnemyEsperiaLaserChip001";
    tX1_ = tY1_ = tZ1_ = 0;
    tX2_ = tY2_ = tZ2_ = 0;
    begin_Y_ = 0;
    turn_dY_ = 0;
    _pSeTx->set(SE_FIRE , "WAVE_ENEMY_FIRE_LASER_001");
}

void EnemyEsperiaLaserChip001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 20000);
    setHitAble(true, false);
    setScaleR(5.0);
    _pKurokoA->relateFaceWithMvAng(true);
    useProgress(_BANPEI_-1);
}

void EnemyEsperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    begin_Y_ = _Y;
    _pKurokoA->stopTurnMvAngSequence();
    _pKurokoA->setRzRyMvAngVelo(0);
    if (_pChip_front == nullptr) {
        _pKurokoA->setMvAngTwd(tX1_, tY1_, tZ1_);
        _pProg->reset(PROG_MOVE_UP);
    } else {
        _pProg->reset(PROG_NOTHING);
    }
    setAlpha(0.99);
    //次のメンバーは EnemyEsperia 本体側から設定済みが前提
    //turn_dY_;
    //tX1_, tY1_, tZ1_;
    //tX2_, tY2_, tZ2_;
}

void EnemyEsperiaLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyEsperiaLaserChip001::processBehaviorHeadChip() {
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_MOVE_UP: {
            //レーザー上昇
            if (!_pKurokoA->isTurningMvAng()) {

                //補正
                _pKurokoA->turnMvAngTwd(tX1_, tY1_, tZ1_,
                                        D_ANG(5), 0,
                                        TURN_CLOSE_TO, true);
            }

            if (_Y > begin_Y_+turn_dY_ || _pProg->getFrameInProgress() > 300) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN1: {
            //自機より少し上の座標で屈折
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvVelo(_pKurokoA->_veloMv/3); //屈折時少しスローダウン
                _pKurokoA->turnMvAngTwd(tX2_, tY2_, tZ2_,
                                        D_ANG(10), 0,
                                        TURN_CLOSE_TO, true);
            }
            if (!_pKurokoA->isTurningMvAng()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN2: {
            //屈折補正
            if (_pProg->getFrameInProgress() % 8U == 0) {
                _pKurokoA->turnMvAngTwd(tX2_, tY2_, tZ2_,
                                        D_ANG(5), 0,
                                        TURN_CLOSE_TO, true);
            }
            if (_pProg->getFrameInProgress() > 60) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_INTO_MYSHIP: {
            if (_pProg->isJustChanged()) {
                _pSeTx->play3D(SE_FIRE);
                _pKurokoA->setMvVelo(_pKurokoA->_veloMv*2);
            }
            if (_pProg->getFrameInProgress() % 16U == 0) {
                _pKurokoA->turnMvAngTwd(tX2_, tY2_, tZ2_,
                                        100, 0,
                                        TURN_CLOSE_TO, true);
            }
            if (_pProg->getFrameInProgress() > 90) {
                _pKurokoA->stopTurnMvAngSequence();
                _pKurokoA->setRzRyMvAngVelo(0);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_NOTHING: {
            break;
        }
    }
    _pKurokoA->behave();
    _pSeTx->behave();
}

void EnemyEsperiaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyEsperiaLaserChip001::~EnemyEsperiaLaserChip001() {
}

