#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//GgafDxCore::GgafDxTextureConnection* EnemyAstraeaLaserChip004::pTexCon1_ = nullptr;
//GgafDxCore::GgafDxTextureConnection* EnemyAstraeaLaserChip004::pTexCon2_ = nullptr;

EnemyAstraeaLaserChip004::EnemyAstraeaLaserChip004(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip004)) {
    _class_name = "EnemyAstraeaLaserChip004";
    pSplManufConnection_ = connectToSplineManufactureManager("GURUGURU");
    pKurokoStepper_ = pSplManufConnection_->peek()->createSplineKurokoStepper(_pKurokoA);
//    if (pTexCon1_ == nullptr) {
//        pTexCon1_ = connectToModelTextureManager("AstraeaLaserChip001.png");
//        pTexCon2_ = connectToModelTextureManager("HesperiaLaserChip001.png");
//        _pModel->setMaterialTexture(0, pTexCon1_);
//
//    }

}

void EnemyAstraeaLaserChip004::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyAstraeaLaserChip004::onCreateModel() {

}

void EnemyAstraeaLaserChip004::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateMvFaceAng(true);
    pKurokoStepper_->stop();
    _force_alpha = 1.50; //最初はちょっと明るめ
}

void EnemyAstraeaLaserChip004::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyAstraeaLaserChip004::processBehaviorHeadChip() {
//    //--->debug
//    if (GgafDxInput::isBeingPressedKey(DIK_N)) {
//        GgafDxTextureConnection* a = _pModel->_papTextureConnection[0];
//        GgafDxTextureConnection* b = _pModel->_papTextureConnection[1];
//        _pModel->_papTextureConnection[0] = b;
//        _pModel->_papTextureConnection[1] = a;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_M)) {
//        _pModel->setMaterialTexture(0, pTexCon2_);
//    }
//    //<--debug

    if (getActiveFrame() == 2) {
        pKurokoStepper_->start(SplineKurokoStepper::RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    pKurokoStepper_->behave(); //←途中でちょんぎれたらだめじゃん
    _pKurokoA->behave();
}

void EnemyAstraeaLaserChip004::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyAstraeaLaserChip004::~EnemyAstraeaLaserChip004() {
    GGAF_DELETE(pKurokoStepper_);
    pSplManufConnection_->close();
    //if (pTexCon1_) {
    //    pTexCon1_->close();
    //    pTexCon1_ = nullptr;
    //}
    //if (pTexCon2_) {
    //    pTexCon2_->close();
    //    pTexCon2_ = nullptr;
    //}
}

