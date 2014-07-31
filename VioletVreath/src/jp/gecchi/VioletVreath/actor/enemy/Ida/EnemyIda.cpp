#include "stdafx.h"
#include "EnemyIda.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyIda::EnemyIda(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida", STATUS(EnemyIda)) {
    _class_name = "EnemyIda";
    pScaler_ = NEW GgafDxScaler(this);
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_BANPEI);
}

void EnemyIda::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyIda::initialize() {
    getKuroko()->relateFaceByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyIda::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //ローカル座標系へ

    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            pKuroko->setFaceAngVelo(AXIS_X, D_ANG(4));
            setAlpha(0);
             UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(1.0, 30);
            }
            if (pProg->getFrameInProgress() == 25) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {
            }
            //自機へ向ける
            GgafDxGeometricActor* pTargetActor = P_MYSHIP;
            coord mvx = pTargetActor->_x - _x_final; //_x_finalは絶対座標
            coord mvy = pTargetActor->_y - _y_final;
            coord mvz = pTargetActor->_z - _z_final;
            //ベースまでの(回転×平行移動)行列の逆行列取得
            D3DXMATRIX* pBaseInvMat = _pActor_base->getInvMatWorldRotMv();
            //ローカル座標で向いておくべき方向ベクトル計算
            coord tvx = mvx*pBaseInvMat->_11 + mvy*pBaseInvMat->_21 + mvz*pBaseInvMat->_31;
            coord tvy = mvx*pBaseInvMat->_12 + mvy*pBaseInvMat->_22 + mvz*pBaseInvMat->_32;
            coord tvz = mvx*pBaseInvMat->_13 + mvy*pBaseInvMat->_23 + mvz*pBaseInvMat->_33;

            angle angRz_Target, angRy_Target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target); //RzRyに置き換える
            pKuroko->setRzRyMvAng(angRz_Target, angRy_Target);
            break;
        }
    }

    pAFader_->behave();
    pKuroko->behave();

    changeGeoFinal(); //絶対座標系へ
}

void EnemyIda::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyIda::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
    GGAF_DELETE(pScaler_);
    GGAF_DELETE(pAFader_);
}


