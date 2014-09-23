#include "EnemyOebius.h"

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
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyOebius::EnemyOebius(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Oebius", STATUS(EnemyOebius)) {
    _class_name = "EnemyOebius";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
}

void EnemyOebius::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebius::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setFaceAngVelo(AXIS_X, 2000);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyOebius::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOebius::processBehavior() {
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
                pKuroko->setMvVelo(PX_C(3));
            }
            if (pProg->getFrameInProgress() == 10) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE_BEGIN: {
            if (pProg->isJustChanged()) {

            }
            if (pProg->getFrameInProgress() == 60) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION, 2);
            }
            pKurokoLeader_->behave(); //スプライン移動を振る舞い

            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE_AFTER: {
            if (pProg->isJustChanged()) {
//                _TRACE_(getName() << ":isFinished x,y,z="<<_x<<","<<_y<<","<<_z<<"");
                position(pKurokoLeader_->_x_start, pKurokoLeader_->_y_start, pKurokoLeader_->_z_start);
//                _TRACE_(getName() << ":補正       x,y,z="<<_x<<","<<_y<<","<<_z<<"");
                pKuroko->setRzRyMvAng(pKurokoLeader_->_ang_rz_mv_start, pKurokoLeader_->_ang_ry_mv_start);
                pKuroko->setMvVelo(PX_C(3));
                pKuroko->turnRyMvAngTo(pKuroko->_ang_ry_mv + D_ANG(30),D_ANG(2),0,TURN_CLOSE_TO);
            }
            if (!pKuroko->isTurningMvAng()) {
                pProg->change(PROG_MOVE_BEGIN);
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->getFrameInProgress() == 60) {
                sayonara();
                pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);

    pAFader_->behave();
    getKuroko()->behave();
}

void EnemyOebius::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOebius::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyOebius::onInactive() {
    sayonara();
}

EnemyOebius::~EnemyOebius() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
