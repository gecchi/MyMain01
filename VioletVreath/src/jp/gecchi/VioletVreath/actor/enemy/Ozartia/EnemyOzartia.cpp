#include "stdafx.h"
#include "EnemyOzartia.h"

#include "EnemyOzartiaShot01.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartia::EnemyOzartia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ozartia", STATUS(EnemyOzartia)) {
    _class_name = "EnemyOzartia";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG1_LEAVE);
    pProg2_ = createProgress(PROG2_SHOT04);
    is_hit_ = false;

    pDepo_Shot01_ = NEW GgafActorDepository("Depo_OzartiaBlock");
    for (int i = 0; i < 9; i++) {
        std::string name = "EnemyOzartiaShot01("+XTOS(i)+")";
        pDepo_Shot01_->addSubLast(NEW EnemyOzartiaShot01(name.c_str()));
        Sleep(1);
    }

}

void EnemyOzartia::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 2000);
    _pKurokoA->forceMvVeloRange(PX_C(15));
}

void EnemyOzartia::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyOzartia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //本体移動系の処理 ここから --->
    switch (_pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 15) {
                setHitAble(true);
                _pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (_pProg->isJustChanged()) {
            }
            if (is_hit_ || _pProg->getFrameInProgress() == 10*60) {
                //ヒットするか、しばらくボーっとしてると移動開始
                _pProg->changeProbability(25, PROG1_MOVE01,
                                          25, PROG1_MOVE02,
                                          25, PROG1_MOVE03,
                                          25, PROG1_MOVE04 );
            }
            break;
        }
        case PROG1_MOVE01: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case PROG1_LEAVE: {
            if (_pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                _pAFader->fadeLinerUntil(0.0, 30);
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
    //<-- 本体移動系の処理 ここまで

    //ショット発射系処理 ここから --->
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
    pProg2_->update();
    //<-- ショット発射系処理 ここまで

    _pAFader->behave();
    _pKurokoA->behave();
    is_hit_ = false;
}

void EnemyOzartia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOzartia::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
    is_hit_ = true;
}

void EnemyOzartia::onInactive() {
    sayonara();
}

EnemyOzartia::~EnemyOzartia() {
}








