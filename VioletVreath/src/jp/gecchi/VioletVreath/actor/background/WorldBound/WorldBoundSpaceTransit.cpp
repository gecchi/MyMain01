#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpaceTransit::WorldBoundSpaceTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceTransit") {
    _class_name = "WorldBoundSpaceTransit";
    setCubeMapTexture("Torus_cubemap.dds");
}

void WorldBoundSpaceTransit::onCreateModel() {

}
void WorldBoundSpaceTransit::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R2SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundSpaceTransit::onActive() {
}

void WorldBoundSpaceTransit::processBehavior() {
}
void WorldBoundSpaceTransit::processJudgement() {
}

WorldBoundSpaceTransit::~WorldBoundSpaceTransit() {
}

