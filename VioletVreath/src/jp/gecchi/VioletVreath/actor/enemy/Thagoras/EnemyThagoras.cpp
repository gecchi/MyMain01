#include "EnemyThagoras.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThagoras::EnemyThagoras(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Thagoras", STATUS(EnemyThagoras)) {
    _class_name = "EnemyThagoras";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    pActor4Sc_ = nullptr;
}

void EnemyThagoras::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyThagoras::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 40000);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(2000);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyThagoras::onActive() {
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
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                pAFader_->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->hasJustChanged()) {
                pKurokoLeader_->start(RELATIVE_COORD,5);
            }
            pKurokoLeader_->behave();
            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinearUntil(0.0, 30);
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
    pAFader_->behave();
    getKuroko()->behave();
    //鼓動を同期
    _sx = pActor4Sc_->_sx;
    _sy = pActor4Sc_->_sy;
    _sz = pActor4Sc_->_sz;
}

void EnemyThagoras::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyThagoras::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
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
