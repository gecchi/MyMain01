#include "EnemyOebius.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
#include "FormationOebius.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE_BEGIN ,
    PHASE_CURVE ,
    PHASE_SCATTER ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

EnemyOebius::EnemyOebius(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Oebius", StatusReset(EnemyOebius)) {
    _class_name = "EnemyOebius";
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    scatter_flg_ = false;
    delay_ = 0;
}

void EnemyOebius::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebius::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->forceMvVeloRange(PX_C(15));
}

void EnemyOebius::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyOebius::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = (EffectBlink*)UTIL::activateCommonEffectOf(this, STAT_EntryEffectKind);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_MOVE_BEGIN: {
            if (pPhase->hasJustChanged()) {

            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_CURVE: {
            if (pPhase->hasJustChanged()) {
                getLocusVehicle()->setMvAcce(0); //加速度がある場合は切っておく
                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, -1); //-1は無限ループ
            }
            //FormationOebiusの回転移動に追従
            FormationOebius* pFormation = (FormationOebius*)getFormation();
            pVehicleLeader_->setStartPosition(pFormation->_x, pFormation->_y, pFormation->_z);
            pVehicleLeader_->setStartAngle(pFormation->_rx, pFormation->_ry, pFormation->_rz);
            //カーブ移動するようにDriverを操作
            pVehicleLeader_->behave();

            if (scatter_flg_) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_SCATTER: {
            if (pPhase->hasJustChanged()) {
                delay_ = RND(0, 120);
            }
            if (pPhase->hasArrivedFrameAt(delay_)) {
                //散り散りになる
                pVehicleLeader_->stop();
                pLocusVehicle->turnRzRyMvAngTo(RND_ABOUT(pLocusVehicle->_rz_mv, D_ANG(90)), RND_ABOUT(pLocusVehicle->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pLocusVehicle->setMvAcce(100);
            }

            if (pPhase->hasArrivedFrameAt(delay_ + 200)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                UTIL::activateCommonEffectOf(this, STAT_LeaveEffectKind);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pPhase->hasArrivedFrameAt(60)) {
                sayonara();
                pPhase->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pLocusVehicle->behave();
}

void EnemyOebius::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOebius::onInactive() {
    if (getBehaveingFrame() > 10) {
        //EnemyOebiusCoreに管理されている。初めはInactive()であるため。
        sayonara();
    }
}
void EnemyOebius::scatter() {
    //Formationから指示がある。
    scatter_flg_ = true;
}

EnemyOebius::~EnemyOebius() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
