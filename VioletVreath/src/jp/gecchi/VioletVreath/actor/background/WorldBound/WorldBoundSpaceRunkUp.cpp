#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpaceRankUp::WorldBoundSpaceRankUp(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceRankUp") {
    _class_name = "WorldBoundSpaceRankUp";
    setCubeMapTexture("Sylvia_cubemap.dds");
}

void WorldBoundSpaceRankUp::onCreateModel() {

}
void WorldBoundSpaceRankUp::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R_SC(dxworld_r/dxmodel_r)*0.989;
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

