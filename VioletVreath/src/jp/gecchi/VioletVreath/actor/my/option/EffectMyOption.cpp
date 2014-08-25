#include "EffectMyOption.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EffectMyOption::EffectMyOption(const char* prm_name, MyOption* prm_pOption) :
        DefaultMeshSetActor(prm_name, "8/EffectMyOption", nullptr) {
    effectBlendOne(); //加算合成するTechnique指定
    pScaler_ = NEW GgafDxScaler(this);
    pOption_ = prm_pOption;
    setZEnable(true);        //Zバッファは考慮して描画
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setHitAble(false);
//    setScaleR(0.1);
    useProgress(10);
}

void EffectMyOption::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EffectMyOption::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_X, D_ANG(5));
    pKuroko->setFaceAngVelo(AXIS_Y, D_ANG(3));
    pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
    setScale(R_SC(1));
    pScaler_->forceRange(R_SC(1), R_SC(4.0));
//    pScaler_->beat(AXIS_X, 30, 10, 1, -1);
//    pScaler_->beat(AXIS_Y, 30, 15, 1, -1);
//    pScaler_->beat(AXIS_Z, 30, 20, 1, -1);

}

void EffectMyOption::onReset() {
//    pProg->reset(1);
}

void EffectMyOption::onActive() {

}

void EffectMyOption::processBehavior() {
//    if (pProg->get() == 1) {
//        pScaler_->beat(30,8,2,-1);
//        pProg->change(2);
//    }
    positionAs(pOption_);
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectMyOption::processJudgement() {
}

void EffectMyOption::processPreDraw() {
    setSpecialDrawDepth(pOption_->_now_drawdepth-1);//親オプションより後に描画するため
    DefaultMeshSetActor::processPreDraw();
}


void EffectMyOption::onHit(GgafActor* prm_pOtherActor) {
}

EffectMyOption::~EffectMyOption() {
    GGAF_DELETE(pScaler_);
}

