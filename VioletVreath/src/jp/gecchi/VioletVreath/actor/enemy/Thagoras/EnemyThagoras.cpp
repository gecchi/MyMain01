#include "stdafx.h"
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
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThagoras::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceWithMvAng(true);
    pKuroko->setFaceAngVelo(AXIS_X, 2000);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyThagoras::onActive() {
    _pStatus->reset();
    getProgress()->reset(PROG_INIT);
    pActor4Sc_ = ((FormationThagoras*)(getFormation()))->pActor4Sc_;
}

void EnemyThagoras::processBehavior() {
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
            }
            if (pProg->getFrameInProgress() == 10) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD,2);
            }
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
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
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

void EnemyThagoras::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyThagoras::onInactive() {
    sayonara();
}

EnemyThagoras::~EnemyThagoras() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
