#include "stdafx.h"
#include "MyMagicEnergy.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyMagicEnergy::MyMagicEnergy(const char* prm_name, MyMagicEnergyCore* prm_pCore) :
        DefaultMeshActor(prm_name, "MagicEnergy") {
    _class_name = "MyMagicEnergy";
    effectBlendOne(); //加算合成するTechnique指定
    pCore_ = prm_pCore;
    setZEnable(true);        //Zバッファは考慮して描画
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setHitAble(false);
    setAlpha(0.9);
}

void MyMagicEnergy::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergy::initialize() {
    _pKuroko->setFaceAngVelo(AXIS_X, 1111);
    _pKuroko->setFaceAngVelo(AXIS_Y, 1333);
    _pKuroko->setFaceAngVelo(AXIS_Z, 1777);
}

void MyMagicEnergy::onActive() {
}

void MyMagicEnergy::processBehavior() {
    positionAs(pCore_);
    setScale(pCore_->_sx);
    _pKuroko->behave();
}

void MyMagicEnergy::processJudgement() {
}

void MyMagicEnergy::processPreDraw() {
    setSpecialDrawDepth(pCore_->_now_drawdepth-1);//コア後に描画するため
    DefaultMeshActor::processPreDraw();
}
int MyMagicEnergy::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyMagicEnergy::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}

void MyMagicEnergy::drawHitArea() {
    //ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

MyMagicEnergy::~MyMagicEnergy() {
}
