#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001") {
    _class_name = "EffectLaserRefraction001";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectLaserRefraction001::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //_pUvFlipper->setPtnNoToTop();
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    setAlpha(0.5);
    _pScaler->setScale(6*1000);
    _pKuroko->setFaceAngVelo(AXIS_X, 3*1000);
    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
}

void EffectLaserRefraction001::processBehavior() {
    _pScaler->addScale(100);

    //_pUvFlipper->behave();
    _pKuroko->behave();
    _pScaler->behave();
}

void EffectLaserRefraction001::processJudgement() {
//    if (_fAlpha < 0) {
//        sayonara();
//    }
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
