#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyAntiope";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(10);
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
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             _pAFader->setAlpha(0);
             _pKurokoA->setMvVelo(0);
             _pKurokoA->setMvAcce(0);
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
             if (getAlpha() > 0.5) {
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
                 _pKurokoA->setMvVelo(0);
                 _pKurokoA->setMvAcce(0);
                 _pKurokoB->setZeroVxyzMvVelo();
                 _pProg->changeNext();
             }
             break;
         }


         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 _pAFader->fadeLinerUntil(0.0, 10);
             }
             if (getAlpha() < 0.5) {
                 setHitAble(false);
             }
             if (getAlpha() < 0.01) {
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    }
}

void EnemyAntiope::onInactive() {
    sayonara();
}

EnemyAntiope::~EnemyAntiope() {
}
