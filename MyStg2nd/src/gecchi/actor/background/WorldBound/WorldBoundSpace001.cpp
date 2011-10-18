#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

WorldBoundSpace001::WorldBoundSpace001(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpace001") {
    _class_name = "WorldBoundSpace001";
    setCubeMapTexture("BkSpace_cubemap.dds");
//    setCubeMapTexture("BkSky_cubemap.dds");
//    _base_u = 0;
//    _base_v = 0;
}

void WorldBoundSpace001::onCreateModel() {

}

void WorldBoundSpace001::initialize() {
    //    _pUvFlipper->setRotation(16, 1/16.0, 1/16.0);
    //    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    //    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    //    _pUvFlipper->setActivePtnNo(0);
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;

    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R2Sc(dxworld_r/dxmodel_r)*0.989;


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

