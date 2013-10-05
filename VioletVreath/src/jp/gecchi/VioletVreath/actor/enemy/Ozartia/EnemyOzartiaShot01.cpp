#include "stdafx.h"
#include "EnemyOzartiaShot01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaShot01::EnemyOzartiaShot01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaShot01)) {
    _class_name = "EnemyOzartiaShot01";
}

void EnemyOzartiaShot01::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    _pProg->reset(PROG_INIT);
}

void EnemyOzartiaShot01::onActive() {
    _pStatus->reset();
}

void EnemyOzartiaShot01::processBehavior() {
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //本体移動系の処理 ここから --->
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 15);
            }
            if (_pProg->getFrameInProgress() == 8) {
                setHitAble(true);
                _pProg->change(PROG_MOVE01);
            }
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 60*10) {
                _pProg->change(PROG_LEAVE);
            }
            break;
        }
        case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 _pAFader->fadeLinerUntil(0.0, 15);
             }
             if (_pProg->getFrameInProgress() == 60) {
                 sayonara();
                 _pProg->changeNothing(); //おしまい！
             }
             break;
         }
        default :
            break;
    }
    _pKurokoA->behave();
}

void EnemyOzartiaShot01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOzartiaShot01::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
//        _pSeTx->play3D(ERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyOzartiaShot01::onInactive() {
    sayonara();
}

EnemyOzartiaShot01::~EnemyOzartiaShot01() {
}
