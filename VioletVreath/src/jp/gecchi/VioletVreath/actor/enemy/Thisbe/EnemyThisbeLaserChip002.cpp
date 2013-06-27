#include "stdafx.h"
#include "EnemyThisbeLaserChip002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

frame EnemyThisbeLaserChip002::end_active_frame_ = INT_MAX;

EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip002", STATUS(EnemyThisbeLaserChip002)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufConnection_ = connect_SplineManufactureManager("EnemyThisbeLaserChip002"); //ヒルベルト曲線
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(_pKurokoA);
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pNearestScrollingScene_ = nullptr;
}

void EnemyThisbeLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyThisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    _pKurokoA->relateMvFaceAng(true);
}

void EnemyThisbeLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyThisbeLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyThisbeLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }

    pKurokoLeader_->behave();
    _pKurokoA->behave();

    if (pKurokoLeader_->isFinished()) {
        EnemyThisbeLaserChip002::end_active_frame_ = getActiveFrame(); //終了フレームセット
        sayonara();
    }
}

void EnemyThisbeLaserChip002::processBehavior() {

    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoLeader_->_X_begin -= pNearestScrollingScene_->getScrollSpeed();
    }
    RefractionLaserChip::processBehavior();

    if (getActiveFrame() == EnemyThisbeLaserChip002::end_active_frame_) {
        sayonara();
    }
}

void EnemyThisbeLaserChip002::processJudgement() {
    if (isOutOfUniverse()) {
        if (_X >= GgafDxUniverse::_X_gone_right) {
            //WALL内実験
        } else {
            sayonara();
        }
    }
}

void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

EnemyThisbeLaserChip002::~EnemyThisbeLaserChip002() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}


