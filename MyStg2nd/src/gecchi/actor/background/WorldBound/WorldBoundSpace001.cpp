#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

WorldBoundSpace001::WorldBoundSpace001(const char* prm_name) : WorldBoundActor(prm_name, "WorldBound_TEST") {
    _class_name = "WorldBoundSpace001";
}
void WorldBoundSpace001::initialize() {
    //    _pUvFlipper->setTextureUvRotation(16, 1/16.0, 1/16.0);
    //    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    //    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    //    _pUvFlipper->setPtnNo(0);
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = 500*1000;
}

void WorldBoundSpace001::onActive() {
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
}

void WorldBoundSpace001::processBehavior() {
    //_pUvFlipper->behave();
}
void WorldBoundSpace001::processJudgement() {
}

WorldBoundSpace001::~WorldBoundSpace001() {
}
