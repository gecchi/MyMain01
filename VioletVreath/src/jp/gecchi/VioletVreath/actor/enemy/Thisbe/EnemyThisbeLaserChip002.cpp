#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip002", STATUS(EnemyThisbeLaserChip002)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufConnection_ = connectToSplineManufactureManager("EnemyThisbeLaserChip002"); //ヒルベルト曲線
    pKurokoStepper_ = pSplManufConnection_->peek()->createSplineKurokoStepper(_pKurokoA);
    pKurokoStepper_->adjustCoordOffset(PX_C(100), 0, 0);
    end_active_frame_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyThisbeLaserChip002::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
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
    end_active_frame_ = (_frame_standstill_refraction * _num_refraction     ) +
                        (_frame_between_refraction    * (_num_refraction-1) ) +
                        1; //

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
        pKurokoStepper_->start(SplineKurokoStepper::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
        //prm_num_refraction = 0 は、発射口→pKurokoStepper_->_point_index = 0 の点への移動直前処理
    }
    if (pKurokoStepper_->isStepping()) {
        _pKurokoA->setMvVelo(pKurokoStepper_->getSegmentDistance(prm_num_refraction));
    } else {
        //最後のリフレクションだった場合
        _pKurokoA->setMvVelo(0); //ちょっと sayonara() まで待機
    }
    //pKurokoStepper_->behave(); 内部で pKurokoA->_veloMv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pKurokoStepper_->behave(); の前に pKurokoA->setMvVelo() で設定しなければいけない。
    pKurokoStepper_->behave();
    _pKurokoA->behave();
}

void EnemyThisbeLaserChip002::processBehavior() {
    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoStepper_->_X_begin -= pNearestScrollingScene_->getScrollSpeed();
    }

    RefractionLaserChip::processBehavior();
    if (getActiveFrame() == end_active_frame_+5) {
        sayonara();
    }
}

void EnemyThisbeLaserChip002::processJudgement() {
    // 上のend_active_frame_ +5 で sayonara するんで判定不要。
//    if (isOutOfUniverse()) {
//        if (_X >= GgafDxUniverse::_X_gone_right) {
//            //WALL内実験
//        } else {
//            sayonara();
//        }
//    }
}

void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyThisbeLaserChip002::~EnemyThisbeLaserChip002() {
    GGAF_DELETE(pKurokoStepper_);
    pSplManufConnection_->close();
}


