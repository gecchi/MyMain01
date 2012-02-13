#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EffectMyOption::EffectMyOption(const char* prm_name, MyOption* prm_pMyOption) :
        DefaultMeshSetActor(prm_name, "8/option_enagy", NULL) {
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    _pMyOption = prm_pMyOption;
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
    _pKurokoA->setFaceAngVelo(AXIS_X, DEG2ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DEG2ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(1));
    _pScaler->setScale(R2SC(1));
    _pScaler->forceScaleRange(R2SC(1), R2SC(1.5));
    _pScaler->beat(AXIS_X, 30, 10, 1, -1);
    _pScaler->beat(AXIS_Y, 30, 15, 1, -1);
    _pScaler->beat(AXIS_Z, 30, 20, 1, -1);

}

void EffectMyOption::onReset() {
//    _pProg->set(1);
}

void EffectMyOption::onActive() {

}

void EffectMyOption::processBehavior() {
//    if (_pProg->get() == 1) {
//        _pScaler->beat(30,8,2,-1);
//        _pProg->change(2);
//    }
    locateAs(_pMyOption);
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectMyOption::processJudgement() {
}

void EffectMyOption::processPreDraw() {
    setSpecialDrawDepth(_pMyOption->_now_drawdepth-1);//親オプションより後に描画するため
    DefaultMeshSetActor::processPreDraw();
}


void EffectMyOption::onHit(GgafActor* prm_pOtherActor) {
}

EffectMyOption::~EffectMyOption() {
}

