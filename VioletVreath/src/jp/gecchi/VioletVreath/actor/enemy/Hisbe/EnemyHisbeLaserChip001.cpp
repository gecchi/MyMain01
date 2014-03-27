#include "stdafx.h"
#include "EnemyHisbeLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip001::EnemyHisbeLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "HisbeLaserChip001", STATUS(EnemyHisbeLaserChip001)) {
    _class_name = "EnemyHisbeLaserChip001";
    pSplManufConnection_ = connect_SplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(getKuroko());
    pNearestScrollingScene_ = nullptr;
}

void EnemyHisbeLaserChip001::initialize() {
//    registerHitAreaCube_AutoGenMidColli(20000);
    setScaleR(5.0);
    setAlpha(0.9);
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyHisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(30000);
    pKuroko->forceRzRyMvAngVeloRange(-D_ANG(45), D_ANG(45));
    pKuroko->relateFaceByMvAng(true);
    //位置と向きはEnemyHisbeが設定
    pKurokoLeader_->stop();
}

void EnemyHisbeLaserChip001::processBehaviorHeadChip() {
    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoLeader_->_x_start -= pNearestScrollingScene_->getScrollSpeed();
    }

    if (getActiveFrame() == 2) {
        pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    pKurokoLeader_->behave();
    getKuroko()->behave();
}

void EnemyHisbeLaserChip001::processJudgement() {
    if (isOutOfUniverse()) {
        if (_x >= GgafDxUniverse::_x_gone_right) {
            //WALL内実験
        } else {
            sayonara();
        }
    }
}

void EnemyHisbeLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

EnemyHisbeLaserChip001::~EnemyHisbeLaserChip001() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}

