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
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergy::initialize() {
    getKuroko()->setRollPitchYawFaceAngVelo(2111, 2333, 2777);
}

void MyMagicEnergy::onActive() {
}

void MyMagicEnergy::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->behave();
    positionAs(pCore_);
    setScale(pCore_->_sx);
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
    //ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

MyMagicEnergy::~MyMagicEnergy() {
}
