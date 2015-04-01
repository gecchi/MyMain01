#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
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
    pScrollingScene_ = nullptr;
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
    pScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
    if (pScrollingScene_->_pFuncScrolling != WalledScene::scrollX) {
        pScrollingScene_ = nullptr;
    }
}

void EnemyHisbeLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }
    pKurokoLeader_->behave();
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {
    if (_is_leader) {
        if (pScrollingScene_) {
            pKurokoLeader_->_x_start_in_loop -= pScrollingScene_->getScrollSpeed();
        }
    }
    RefractionLaserChip::processBehavior();
}

void EnemyHisbeLaserChip002::processJudgement() {
    if (!_is_leader) {
        if (!getFrontChip()) {
            sayonara();
        }
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

bool EnemyHisbeLaserChip002::isOutOfSpacetime() const {
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    //EnemyHisbe出現時（壁ブロック配置時）はX軸方向の大抵空間外のため
    if (pSpacetime->_x_gone_left < _x) {
        //if (_x < pSpacetime->_x_gone_right) {
            if (pSpacetime->_y_gone_bottom < _y) {
                if (_y < pSpacetime->_y_gone_top) {
                    if (pSpacetime->_z_gone_near < _z) {
                        if (_z < pSpacetime->_z_gone_far) {
                            return false;
                        }
                    }
                }
            }
        //}
    }
    return true;

}
void EnemyHisbeLaserChip002::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
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


