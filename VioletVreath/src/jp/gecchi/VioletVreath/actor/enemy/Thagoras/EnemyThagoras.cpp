#include "EnemyThagoras.h"

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
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThagoras::EnemyThagoras(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Thagoras", STATUS(EnemyThagoras)) {
    _class_name = "EnemyThagoras";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    pActor4Sc_ = nullptr;
}

void EnemyThagoras::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyThagoras::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyThagoras::onActive() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setFaceAngVelo(AXIS_X, 2000);
    pKuroko->forceMvVeloRange(PX_C(15));
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
    pActor4Sc_ = ((FormationThagoras*)(getFormation()))->pActor4Sc_;
}

void EnemyThagoras::processBehavior() {
    GgafProgress* const pProg = getProgress();
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
            }
            if (pProg->hasArrivedAt(10)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD,5);
            }
            pKurokoLeader_->behave();
            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
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
    //鼓動を同期
    _sx = pActor4Sc_->_sx;
    _sy = pActor4Sc_->_sy;
    _sz = pActor4Sc_->_sz;
}

void EnemyThagoras::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThagoras::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyThagoras::onInactive() {
    sayonara();
}

EnemyThagoras::~EnemyThagoras() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
