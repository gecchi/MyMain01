#include "EnemyStraeaLaserChip004.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

//GgafDx::TextureConnection* EnemyStraeaLaserChip004::pTexCon1_ = nullptr;
//GgafDx::TextureConnection* EnemyStraeaLaserChip004::pTexCon2_ = nullptr;

EnemyStraeaLaserChip004::EnemyStraeaLaserChip004(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip004)) {
    _class_name = "EnemyStraeaLaserChip004";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("GURUGURU");
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
//    if (pTexCon1_ == nullptr) {
//        pTexCon1_ = connectToTextureManager("StraeaLaserChip001.png");
//        pTexCon2_ = connectToTextureManager("EsperiaLaserChip001.png");
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
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(10000);
    pLocusVehicle->setMvAcce(300);
    //pLocusVehicle->forceMvVeloRange(0, 70000);
    pLocusVehicle->linkFaceAngByMvAng(true);
    pVehicleLeader_->stop();
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
        pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
    }
    pVehicleLeader_->behave(); //←途中でちょんぎれたらだめじゃん
    getLocusVehicle()->behave();
}

void EnemyStraeaLaserChip004::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyStraeaLaserChip004::~EnemyStraeaLaserChip004() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
    //if (pTexCon1_) {
    //    pTexCon1_->close();
    //    pTexCon1_ = nullptr;
    //}
    //if (pTexCon2_) {
    //    pTexCon2_->close();
    //    pTexCon2_ = nullptr;
    //}
}

