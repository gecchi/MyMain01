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
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    _pKuroko->relateFaceWithMvAng(true);
    useProgress(PROG_BANPEI);
}

void EnemyEbe::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEbe::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
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
    _pStatus->reset();
    setHitAble(true);
    _pKuroko->setMvAcce(0);
    _pProg->reset(PROG_MOVE01_1);
}

void EnemyEbe::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_MOVE01_1: {
            if ((int)(_pProg->getFrameInProgress()) > (int)(PX_C(300) / ABS(_pKuroko->_veloMv))) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (_pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD);
            }
            if (pKurokoLeader_->isFinished()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (_pProg->isJustChanged()) {
                _pKuroko->turnMvAngTwd(_x - PX_C(300), _y, _z,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKuroko->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyEbe::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyEbe::~EnemyEbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


