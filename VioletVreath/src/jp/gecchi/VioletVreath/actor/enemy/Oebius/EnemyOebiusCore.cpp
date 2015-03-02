#include "EnemyOebiusCore.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius001.h"
#include "EnemyOebiusController.h"

#include "jp/ggaf/dxcore/util/GgafDxInput.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyOebiusCore::EnemyOebiusCore(const char* prm_name, EnemyOebiusController* prm_pController) :
        DefaultMorphMeshActor(prm_name, "1/OebiusCore", STATUS(EnemyOebiusCore)) {
    _class_name = "EnemyOebiusCore";
    pAFader_ = NEW GgafDxAlphaFader(this);
    pController_ = prm_pController;

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_002");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);

}

void EnemyOebiusCore::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebiusCore::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyOebiusCore::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOebiusCore::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(1.0, 30);
                pKuroko->setSpinAngVelo(D_ANG(3));
            }
            if (pProg->arriveAt(10)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }

        case PROG_WAIT01: {
            if (pProg->isJustChanged()) {
                pKuroko->keepOnTurningFaceAngTwd(P_MYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (pProg->arriveAt(3600)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->arriveAt(60)) {
                sayonara();
                pProg->changeNothing(); //‚¨‚µ‚Ü‚¢I
            }
            break;
        }
        default :
            break;
    }

    UTIL::updateEnemyRankPoint(this); //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    pAFader_->behave();
    getKuroko()->behave();
}

void EnemyOebiusCore::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOebiusCore::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
    }
}

void EnemyOebiusCore::onInactive() {
    sayonara();
    pController_->pOebiusCore_ = nullptr;
}

EnemyOebiusCore::~EnemyOebiusCore() {
    GGAF_DELETE(pAFader_);
}
