#include "MyMagicEnergy.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

MyMagicEnergy::MyMagicEnergy(const char* prm_name, MyMagicEnergyCore* prm_pCore) :
        DefaultMeshActor(prm_name, "MagicEnergy") {
    _class_name = "MyMagicEnergy";
    effectBlendOne(); //加算合成するTechnique指定
    pCore_ = prm_pCore;
    setZEnableDraw(true);        //Zバッファは考慮して描画
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setHitAble(false);
    setCullingDraw(false);
}

void MyMagicEnergy::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergy::initialize() {
    getLocusVehicle()->setRollPitchYawFaceAngVelo(2111, 2333, 2777);
}

void MyMagicEnergy::onActive() {
}

void MyMagicEnergy::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->behave();
    setPositionAt(pCore_);
    setScaleAt(pCore_);
}

void MyMagicEnergy::processJudgement() {
}

void MyMagicEnergy::processPreDraw() {
    setSpecialRenderDepthIndex(pCore_->_now_drawdepth-1);//コア後に描画するため
    DefaultMeshActor::processPreDraw();
}

int MyMagicEnergy::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyMagicEnergy::isOutOfSpacetime() const {
    //ゲーム座標範囲外判定無し
    return false;
}

void MyMagicEnergy::drawHitArea() {
    //WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
}

MyMagicEnergy::~MyMagicEnergy() {
}
