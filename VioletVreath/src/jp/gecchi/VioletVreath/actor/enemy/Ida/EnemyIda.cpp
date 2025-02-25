#include "EnemyIda.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_ENTRY,
    PHASE_MOVE01,
    PHASE_BANPEI,
};

EnemyIda::EnemyIda(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ida", StatusReset(EnemyIda)) {
    _class_name = "EnemyIda";
}

void EnemyIda::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyIda::initialize() {
    getLocusVehicle()->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyIda::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //ローカル座標系へ

    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            pLocusVehicle->setRollFaceAngVelo(D_ANG(4));
            setAlpha(0);
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
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE01: {
            if (pPhase->hasJustChanged()) {
            }
            //自機へ向ける
            GgafDx::GeometricActor* pTargetActor = pMYSHIP;
            coord mvx = pTargetActor->_x - _x_final; //_x_finalは絶対座標
            coord mvy = pTargetActor->_y - _y_final;
            coord mvz = pTargetActor->_z - _z_final;
            //ベースまでの(回転×平行移動)行列の逆行列取得
            D3DXMATRIX* pBaseInvMat = _pActor_base->getInvMatWorldRotMv();
            //ローカル座標で向いておくべき方向ベクトル計算
            coord tvx = mvx*pBaseInvMat->_11 + mvy*pBaseInvMat->_21 + mvz*pBaseInvMat->_31;
            coord tvy = mvx*pBaseInvMat->_12 + mvy*pBaseInvMat->_22 + mvz*pBaseInvMat->_32;
            coord tvz = mvx*pBaseInvMat->_13 + mvy*pBaseInvMat->_23 + mvz*pBaseInvMat->_33;

            angle rz_target, ry_target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target); //RzRyに置き換える
            pLocusVehicle->setRzRyMvAng(rz_target, ry_target);
            break;
        }
    }

    getAlphaFader()->behave();
    pLocusVehicle->behave();

    changeGeoFinal(); //絶対座標系へ
}

void EnemyIda::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
}


