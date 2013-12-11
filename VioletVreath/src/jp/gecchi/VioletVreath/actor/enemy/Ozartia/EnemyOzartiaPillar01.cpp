#include "stdafx.h"
#include "EnemyOzartiaPillar01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaPillar01::EnemyOzartiaPillar01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaPillar01)) {
    _class_name = "EnemyOzartiaPillar01";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void EnemyOzartiaPillar01::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    _pProg->reset(PROG_INIT);
}

void EnemyOzartiaPillar01::onActive() {
    _pStatus->reset();
}

void EnemyOzartiaPillar01::processBehavior() {
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //本体移動系の処理 ここから --->
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            pAFader_->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                pAFader_->fadeLinerUntil(1.0, 15);
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
                 pAFader_->fadeLinerUntil(0.0, 15);
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
    _pKuroko->behave();
}

void EnemyOzartiaPillar01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOzartiaPillar01::onHit(GgafActor* prm_pOtherActor) {
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

void EnemyOzartiaPillar01::onInactive() {
    sayonara();
}

EnemyOzartiaPillar01::~EnemyOzartiaPillar01() {
    GGAF_DELETE(pAFader_);
}
