#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

WorldBoundSpace001::WorldBoundSpace001(const char* prm_name) : WorldBoundActor(prm_name, "0/WorldBoundSpace001") {
    _class_name = "WorldBoundSpace001";
//    _base_u = 0;
//    _base_v = 0;
}
void WorldBoundSpace001::initialize() {
    //    _pUvFlipper->setRotation(16, 1/16.0, 1/16.0);
    //    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    //    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    //    _pUvFlipper->setActivePtnNo(0);
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    //WorldBoundSpace001ΜfΝΌaDIRECTX£1(10px)Ε ι
    _SX = _SY = _SZ =  ((P_CAM->_zf-P_CAM->_zn)*1000)*0.989;
    setCubeMapTexture("BkSpacae_cubemap.dds");
}

void WorldBoundSpace001::onActive() {
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
}

void WorldBoundSpace001::processBehavior() {
//    _pUvFlipper->setBaseUv(_base_u,_base_v);
//    _base_u += 0.005;
//    _base_v += 0.002;
//    _pUvFlipper->behave();
}
void WorldBoundSpace001::processJudgement() {
}

WorldBoundSpace001::~WorldBoundSpace001() {
}

