#include "stdafx.h"
#include "EnemyEtis.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEtis::EnemyEtis(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Etis", STATUS(EnemyEtis)) {
    _class_name = "EnemyEtis";
    width_X_ = 220*2*LEN_UNIT;
    height_Z_ = 220*2*LEN_UNIT;
    depth_Y_ = 36*2*LEN_UNIT;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyEtis::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEtis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_X_ - depth_Y_) ; i+= depth_Y_) {
        nArea++;
    }
    _pColliChecker->makeCollision(nArea);
    for (int i = 0, n = 0; i < width_X_-depth_Y_; i += depth_Y_, n++) {
        _pColliChecker->setColliAAB(n,
                                    i - ((depth_Y_/2.0)/1.5)-(width_X_/2.0 - depth_Y_/2.0), -((depth_Y_/2.0)/1.5), -(height_Z_/2.0),
                                    i + ((depth_Y_/2.0)/1.5)-(width_X_/2.0 - depth_Y_/2.0),  ((depth_Y_/2.0)/1.5),  (height_Z_/2.0),
                                    false, false, true );
    }
}

void EnemyEtis::onActive() {
    _pStatus->reset();
    setAlpha(1.0);
    _pKurokoA->setMvVelo(0);
    _pKurokoB->setVxMvVelo(-3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
    static coord renge_Y = (MyShip::lim_Y_top_ - MyShip::lim_Y_bottom_) * 3;
    static coord renge_Z = (MyShip::lim_Z_left_ - MyShip::lim_Z_right_) * 3;
    _X = GgafDxUniverse::_X_gone_right - 1000;
    _Y = RND(-(renge_Y/2) , +(renge_Y/2));
    _Z = RND(-(renge_Z/2) , +(renge_Z/2));
    setHitAble(true);
}

void EnemyEtis::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //À•W‚É”½‰f
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pSeTx->behave();
}

void EnemyEtis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEtis::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyEtis::onInactive() {
    sayonara();
}

EnemyEtis::~EnemyEtis() {
}

