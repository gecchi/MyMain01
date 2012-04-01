#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", NULL) {
    _class_name = "EffectLaserRefraction001";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectLaserRefraction001::initialize() {
//    _pUvFlipper->forcePtnRange(0, 63);
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //_pUvFlipper->setActivePtnToTop();
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    setAlpha(0.5);
    _pScaler->setScale(R2SC(6));
    _pKurokoA->setFaceAngVelo(AXIS_X, DANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    _pScaler->addScale(100);

    //_pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectLaserRefraction001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
