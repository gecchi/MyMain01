#include "stdafx.h"
#include "EnemyAntiope.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyAntiope";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(_BANPEI_-1);
}

void EnemyAntiope::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAntiope::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyAntiope::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             _pAFader->setAlpha(0);
             _pKurokoA->stopMv();
             _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(10));
             _pKurokoB->setZeroVxyzMvVelo();
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _pAFader->fadeLinerUntil(1.0, 30);
             }
             if (_pProg->getFrameInProgress() == 30) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 _pKurokoA->setMvVelo(30000);
                 _pKurokoA->setMvAcce(-1000);
                 _pKurokoB->setVxyzMvVelo(mv_velo_twd_._X, mv_velo_twd_._Y, mv_velo_twd_._Z);
             }

             if (_pKurokoA->_veloMv <= (-30000 + 1000)) {
                 _pKurokoA->stopMv();
                 _pKurokoB->setZeroVxyzMvVelo();
                 _pProg->changeNext();
             }
             break;
         }


         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 _pAFader->fadeLinerUntil(0.0, 15);
             }
             if (_pProg->getFrameInProgress() == 15) {
                 setHitAble(false);
                 sayonara();
             }
             break;
         }
         default:
             break;
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_X<<","<<_Y<<","<<_Z<<"  ("<<_pKurokoA->_veloMv<<") "<<_pKurokoA->_vX<<","<<_pKurokoA->_vY<<","<<_pKurokoA->_vZ<<"");
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pAFader->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
    }
}

void EnemyAntiope::onInactive() {
    sayonara();
}

EnemyAntiope::~EnemyAntiope() {
}
