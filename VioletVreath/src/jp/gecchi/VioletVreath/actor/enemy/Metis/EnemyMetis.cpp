#include "stdafx.h"
#include "EnemyMetis.h"

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

EnemyMetis::EnemyMetis(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Metis", STATUS(EnemyMetis)) {
    _class_name = "EnemyMetis";
    width_X_ = 220*2*LEN_UNIT;
    height_Z_ = 220*2*LEN_UNIT;
    depth_Y_ = 36*2*LEN_UNIT;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");

    pConnection_ShotDepo_ = connectToDepositoryManager("Shot004");
    pDepo_Shot_ = pConnection_ShotDepo_->peek();
}

void EnemyMetis::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyMetis::initialize() {
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

void EnemyMetis::onActive() {
    _pStatus->reset();
    setAlpha(1.0);
    _pKurokoA->setMvVelo(0);
    _pKurokoB->setVxMvVelo(-3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
    static coord appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_gone_right - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    setHitAble(true);
}

void EnemyMetis::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //À•W‚É”½‰f
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pSeTx->behave();
}

void EnemyMetis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMetis::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyMetis::onInactive() {
    sayonara();
}

EnemyMetis::~EnemyMetis() {
    pConnection_ShotDepo_->close();
}

