#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

WorldBoundSpaceRankUp::WorldBoundSpaceRankUp(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceRankUp") {
    _class_name = "WorldBoundSpaceRankUp";
    setCubeMapTexture("Torus_cubemap.dds");
}

void WorldBoundSpaceRankUp::onCreateModel() {

}
void WorldBoundSpaceRankUp::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ =  ((P_CAM->_zf-P_CAM->_zn)*1000)*0.989;
    _RX = -10000;
}

void WorldBoundSpaceRankUp::onActive() {
}

void WorldBoundSpaceRankUp::processBehavior() {
}
void WorldBoundSpaceRankUp::processJudgement() {
}

WorldBoundSpaceRankUp::~WorldBoundSpaceRankUp() {
}

