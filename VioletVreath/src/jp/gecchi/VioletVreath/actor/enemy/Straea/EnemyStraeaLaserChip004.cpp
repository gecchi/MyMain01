#include "EnemyStraeaLaserChip004.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

//GgafDx::TextureConnection* EnemyStraeaLaserChip004::pTexCon1_ = nullptr;
//GgafDx::TextureConnection* EnemyStraeaLaserChip004::pTexCon2_ = nullptr;

EnemyStraeaLaserChip004::EnemyStraeaLaserChip004(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip004)) {
    _class_name = "EnemyStraeaLaserChip004";
    pConn_pSplManuf_ = connectToSplineManufactureManager("GURUGURU");
    pRikishaLeader_ = pConn_pSplManuf_->peek()->createRikishaLeader(callRikisha());
//    if (pTexCon1_ == nullptr) {
//        pTexCon1_ = connectToModelTextureManager("StraeaLaserChip001.png");
//        pTexCon2_ = connectToModelTextureManager("EsperiaLaserChip001.png");
//        pModel->setMaterialTexture(0, pTexCon1_);
//
//    }

}

void EnemyStraeaLaserChip004::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyStraeaLaserChip004::onCreateModel() {

}

void EnemyStraeaLaserChip004::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->setMvVelo(10000);
    pRikisha->setMvAcce(300);
    //pRikisha->forceMvVeloRange(0, 70000);
    pRikisha->linkFaceAngByMvAng(true);
    pRikishaLeader_->stop();
    _force_alpha = 1.50; //最初はちょっと明るめ
}

void EnemyStraeaLaserChip004::processBehaviorHeadChip() {
//    //--->debug
//    if (GgafDx::Input::isPressedKey(DIK_N)) {
//        GgafDx::TextureConnection* a = pModel->_papTextureConnection[0];
//        GgafDx::TextureConnection* b = pModel->_papTextureConnection[1];
//        pModel->_papTextureConnection[0] = b;
//        pModel->_papTextureConnection[1] = a;
//    }
//    if (GgafDx::Input::isPressedKey(DIK_M)) {
//        pModel->setMaterialTexture(0, pTexCon2_);
//    }
//    //<--debug

    if (getActiveFrame() == 2) {
        pRikishaLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
    }
    pRikishaLeader_->behave(); //←途中でちょんぎれたらだめじゃん
    callRikisha()->behave();
}

void EnemyStraeaLaserChip004::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraeaLaserChip004::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyStraeaLaserChip004::~EnemyStraeaLaserChip004() {
    GGAF_DELETE(pRikishaLeader_);
    pConn_pSplManuf_->close();
    //if (pTexCon1_) {
    //    pTexCon1_->close();
    //    pTexCon1_ = nullptr;
    //}
    //if (pTexCon2_) {
    //    pTexCon2_->close();
    //    pTexCon2_ = nullptr;
    //}
}

