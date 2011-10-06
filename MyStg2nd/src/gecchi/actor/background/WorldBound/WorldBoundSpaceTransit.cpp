#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

WorldBoundSpaceTransit::WorldBoundSpaceTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceTransit") {
    _class_name = "WorldBoundSpaceTransit";
}
void WorldBoundSpaceTransit::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ =  ((P_CAM->_zf-P_CAM->_zn)*1000)*0.989;
    setCubeMapTexture("Torus_cubemap.dds");
}

void WorldBoundSpaceTransit::onActive() {
}

void WorldBoundSpaceTransit::processBehavior() {
}
void WorldBoundSpaceTransit::processJudgement() {
}

WorldBoundSpaceTransit::~WorldBoundSpaceTransit() {
}

