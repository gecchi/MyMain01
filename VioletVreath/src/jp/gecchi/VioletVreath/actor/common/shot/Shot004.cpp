#include "stdafx.h"
#include "Shot004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "Shot004", STATUS(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    view_in_ = false;
}

void Shot004::initialize() {
    setHitAble(false);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(16));
}
void Shot004::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
    _pKuroko->setMvVelo(30000);
    _pKuroko->setMvAcce(1000);
    _pKuroko->relateFaceWithMvAng(true);
}

void Shot004::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pKuroko->behave();
}

void Shot004::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActiveFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト
        sayonara();
    }
}

Shot004::~Shot004() {
}
