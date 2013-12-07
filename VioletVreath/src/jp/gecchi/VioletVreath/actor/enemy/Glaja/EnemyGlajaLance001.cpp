#include "stdafx.h"
#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "GlajaLance001", STATUS(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    effectBlendOne(); //加算合成
    setZEnable(true);
    setZWriteEnable(false);
    useProgress(PROG_BANPEI);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    _pColliChecker->makeCollision(3);
    _pColliChecker->setColliAAB_Cube(0, PX_C(20));
    _pColliChecker->setColliAAB_Cube(1, -PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);
    _pColliChecker->setColliAAB_Cube(2, PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);

}
void EnemyGlajaLance001::onReset() {

}

void EnemyGlajaLance001::onActive() {
    _pKuroko->setMvAcce(0);
    _pKuroko->setMvVelo(PX_C(3));
    _pKuroko->setFaceAng(0,
                          RND(D_ANG(0), D_ANG(360)),
                          RND(D_ANG(0), D_ANG(360)) );
    _pKuroko->setFaceAngVelo(D_ANG(33), D_ANG(15), D_ANG(20));
    _pKuroko->relateFaceWithMvAng(true);
    _pColliChecker->disable(1);
    _pColliChecker->disable(2);
    _pScaler->reset();
    _pScaler->behave();
    _pStatus->reset();
    setAlpha(0.99);
    _pProg->reset(PROG_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(true, false);
            //_pKuroko->setMvAngTwd(&turning_pos_);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {

            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_AIM_ANIME01: {
            if (_pProg->isJustChanged()) {
                //シャキーンと槍になる！（伸びる！）
                _pKuroko->stopMv();
                _pKuroko->setFaceAngVelo(0, 0, 0);
                _pScaler->scaleAcceStep(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
            }
            if (!_pScaler->isScaling()) {
                //槍の両端当たり判定出現
                _pColliChecker->enable(1);
                _pColliChecker->enable(2);
                _pProg->changeNext();
             }

             break;
        }
        case PROG_AIM_ANIME02: {
            if (_pProg->isJustChanged()) {
                //自機にグルンと向く
                _pKuroko->turnFaceAngTwd(pMyShip,
                                          D_ANG(20),0,TURN_ANTICLOSE_TO,false);
            }
            if (!_pKuroko->isTurningFaceAng()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (_pProg->isJustChanged()) {
                _pKuroko->setMvAngByFaceAng(); //今向いてる方向にこれから移動する
                _pKuroko->setMvVelo(-PX_C(2)); //ちょっとバックして貯めを表現
                _pKuroko->setFaceAng(AXIS_X, D_ANG(27)); //スピンスピン
            }
            if (_pProg->getFrameInProgress() >= 10) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE03: {
            if (_pProg->isJustChanged()) {
                //ズキューーンと移動
                _pKuroko->setMvVelo(PX_C(60));
            }
            //画面外 or HIT まで待機
            break;
        }

        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                //HIT後消えるまで
            }
            addAlpha(-1.0/90.0); //sayonara(90);だから
            break;
        }
    }
    //座標に反映
    _pScaler->behave();
    _pKuroko->behave();
}

void EnemyGlajaLance001::processJudgement() {
    if (isOutOfView()) {
        if (getActiveFrame() > 60) {
            sayonara();
        }
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGlajaLance001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト
        _pKuroko->stopMv();
        sayonara(90);
        _pProg->change(PROG_LEAVE);
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
}
