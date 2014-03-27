#include "stdafx.h"
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
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    getKuroko()->relateFaceByMvAng(true);
    useProgress(PROG_BANPEI);
}

void EnemyEbe::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEbe::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEbe::config(
        SplineKurokoLeader* prm_pKurokoLeader,
        GgafActorDepository* prm_pDepo_Shot,
        GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}

void EnemyEbe::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyEbeはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvAcce(0);
    getProgress()->reset(PROG_MOVE01_1);
}

void EnemyEbe::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE01_1: {
            if ((int)(pProg->getFrameInProgress()) > (int)(PX_C(300) / ABS(pKuroko->_veloMv))) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD);
            }
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

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    pKuroko->behave();
}

void EnemyEbe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEbe::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyEbe::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyEbe::~EnemyEbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


