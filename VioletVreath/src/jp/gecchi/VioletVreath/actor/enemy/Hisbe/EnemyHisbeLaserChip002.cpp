#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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

frame EnemyHisbeLaserChip002::end_active_frame_ = INT_MAX;

EnemyHisbeLaserChip002::EnemyHisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "HisbeLaserChip002", STATUS(EnemyHisbeLaserChip002)) {
    _class_name = "EnemyHisbeLaserChip002";
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pNearestScrollingScene_ = nullptr;
}

void EnemyHisbeLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyHisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    getKuroko()->relateFaceByMvAng(true);
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyHisbeLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }

    pKurokoLeader_->behave();
    getKuroko()->behave();

    if (pKurokoLeader_->isFinished()) {
        EnemyHisbeLaserChip002::end_active_frame_ = getActiveFrame(); //終了フレームセット
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {

    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoLeader_->_x_start -= pNearestScrollingScene_->getScrollSpeed();
    }
    RefractionLaserChip::processBehavior();
    if (getActiveFrame() == EnemyHisbeLaserChip002::end_active_frame_) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

bool EnemyHisbeLaserChip002::isOutOfUniverse() const {
    //EnemyHisbe出現時（壁ブロック配置時）はX軸方向の大抵空間外のため
    if (GgafDxUniverse::_x_gone_left < _x) {
        //if (_x < GgafDxUniverse::_x_gone_right) {
            if (GgafDxUniverse::_y_gone_bottom < _y) {
                if (_y < GgafDxUniverse::_y_gone_top) {
                    if (GgafDxUniverse::_z_gone_near < _z) {
                        if (_z < GgafDxUniverse::_z_gone_far) {
                            return false;
                        }
                    }
                }
            }
        //}
    }
    return true;

}
void EnemyHisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyHisbeLaserChip002::~EnemyHisbeLaserChip002() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}


