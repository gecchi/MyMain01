#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

WorldBoundSpace002::WorldBoundSpace002(const char* prm_name) : WorldBoundActor(prm_name, "WorldBound_TEST") {
    _class_name = "WorldBoundSpace002";
}
void WorldBoundSpace002::initialize() {
    //    _pUvFlipper->setTextureUvRotation(16, 1/16.0, 1/16.0);
    //    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    //    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    //    _pUvFlipper->setPtnNo(0);
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = ((pCAM->_zf-pCAM->_zn)*1000)*0.999;
}

void WorldBoundSpace002::onActive() {
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
}

void WorldBoundSpace002::processBehavior() {
    setGeometry(pCAM);
    //_pUvFlipper->behave();
}
void WorldBoundSpace002::processJudgement() {
}

WorldBoundSpace002::~WorldBoundSpace002() {
}

