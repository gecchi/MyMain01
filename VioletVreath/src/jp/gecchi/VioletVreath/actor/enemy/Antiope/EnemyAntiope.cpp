#include "stdafx.h"
#include "EnemyAntiope.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyAntiope";
    pAFader_ = NEW GgafDxAlphaFader(this);
    pAxsMver_ = NEW GgafDxAxesMover(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAntiope::onCreateModel() {
//    GgafDxModel* pModel = getModel();
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAntiope::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAntiope::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setAlpha(0);
             pKuroko->stopMv();
             pKuroko->setFaceAngVelo(AXIS_X, D_ANG(10));
             pAxsMver_->setZeroVxyzMvVelo();
             UTIL::activateEntryEffectOf(this);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (pProg->isJustChanged()) {
                 pAFader_->transitionLinerUntil(1.0, 30);
             }
             if (pProg->getFrameInProgress() == 30) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (pProg->isJustChanged()) {
                 pKuroko->setMvVelo(30000);
                 pKuroko->setMvAcce(-1000);
                 pAxsMver_->setVxyzMvVelo(mv_velo_twd_.x, mv_velo_twd_.y, mv_velo_twd_.z);
             }

             if (pKuroko->_veloMv <= (-30000 + 1000)) {
                 pKuroko->stopMv();
                 pAxsMver_->setZeroVxyzMvVelo();
                 pProg->changeNext();
             }
             break;
         }

         case PROG_LEAVE: {
             if (pProg->isJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAFader_->transitionLinerUntil(0.0, 15);
             }
             if (pProg->getFrameInProgress() == 15) {
                 setHitAble(false);
                 sayonara();
             }
             break;
         }

         default: {
             break;
         }
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_x<<","<<_y<<","<<_z<<"  ("<<_pKuroko->_veloMv<<") "<<_pKuroko->_vX<<","<<_pKuroko->_vY<<","<<_pKuroko->_vZ<<"");
    pKuroko->behave();
    pAxsMver_->behave();
    pAFader_->behave();
}

void EnemyAntiope::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAntiope::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        getSeTx()->play3D(SE_EXPLOSION);
    }
}

void EnemyAntiope::onInactive() {
    sayonara();
}

EnemyAntiope::~EnemyAntiope() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}
