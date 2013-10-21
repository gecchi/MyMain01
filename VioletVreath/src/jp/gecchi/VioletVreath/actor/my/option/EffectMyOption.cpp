#include "stdafx.h"
#include "EffectMyOption.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EffectMyOption::EffectMyOption(const char* prm_name, MyOption* prm_pOption) :
        DefaultMeshSetActor(prm_name, "8/option_energy", nullptr) {
    effectBlendOne(); //加算合成するTechnique指定
    pOption_ = prm_pOption;
    setZEnable(true);        //Zバッファは考慮して描画
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setHitAble(false);
//    setScaleR(0.1);
    useProgress(10);
}

void EffectMyOption::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EffectMyOption::initialize() {
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Y, D_ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(1));
    _pScaler->setScale(R_SC(1));
    _pScaler->forceRange(R_SC(1), R_SC(4.0));
//    _pScaler->beat(AXIS_X, 30, 10, 1, -1);
//    _pScaler->beat(AXIS_Y, 30, 15, 1, -1);
//    _pScaler->beat(AXIS_Z, 30, 20, 1, -1);

}

void EffectMyOption::onReset() {
//    _pProg->reset(1);
}

void EffectMyOption::onActive() {

}

void EffectMyOption::processBehavior() {
//    if (_pProg->get() == 1) {
//        _pScaler->beat(30,8,2,-1);
//        _pProg->change(2);
//    }
    positionAs(pOption_);
    _pKurokoA->behave();
    _pScaler->behave();
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
}

