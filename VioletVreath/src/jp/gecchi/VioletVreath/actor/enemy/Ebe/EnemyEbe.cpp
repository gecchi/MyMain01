#include "EnemyEbe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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

EnemyEbe::EnemyEbe(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ebe", STATUS(EnemyEbe)) {
    _class_name = "EnemyEbe";
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //”š”­
    getKuroko()->relateFaceByMvAng(true);
    useProgress(PROG_BANPEI);
}

void EnemyEbe::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEbe::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEbe::config(
        SplineKurokoLeader* prm_pKurokoLeader,
        GgafActorDepository* prm_pDepo_shot,
        GgafActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}

void EnemyEbe::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyEbe‚ÍƒXƒvƒ‰ƒCƒ“•K{‚Å‚·config‚µ‚Ä‰º‚³‚¢");
    }
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvAcce(0);
    getProgress()->reset(PROG_MOVE01_1);
}

void EnemyEbe::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE01_1: {
            if ((int)(pProg->getFrame()) > (int)(PX_C(300) / ABS(pKuroko->_velo_mv))) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD);
            }
            pKurokoLeader_->behave();

            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (pProg->isJustChanged()) {
                pKuroko->turnMvAngTwd(_x - PX_C(300), _y, _z,
                                      D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pKuroko->behave();
}

void EnemyEbe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEbe::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyEbe::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyEbe::~EnemyEbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


