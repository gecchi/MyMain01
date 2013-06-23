#include "stdafx.h"
#include "EnemyAida.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAida::EnemyAida(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Aida", STATUS(EnemyAida)) {
    _class_name = "EnemyAida";
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //”š”­
    useProgress(PROG_MOVE01_1);
}

void EnemyAida::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAida::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAida::onActive() {
    _pStatus->reset();
    setHitAble(true);
}

void EnemyAida::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;
    /*
    switch (_pProg->get()) {
        case PROG_MOVE01_1: {
            if ((int)(_pProg->getFrameInProgress()) > (int)(PX_C(300) / ABS(_pKurokoA->_veloMv))) {
                _pProg->changeNext();
            }
            break;
        }
    }
    */
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();
}

void EnemyAida::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAida::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAida::onInactive() {
}

EnemyAida::~EnemyAida() {
}


