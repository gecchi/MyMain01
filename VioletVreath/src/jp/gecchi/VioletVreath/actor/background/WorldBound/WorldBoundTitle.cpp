#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundTitle::WorldBoundTitle(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundTitle") {
    _class_name = "WorldBoundTitle";
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSpace_cubemap.dds");
}

void WorldBoundTitle::onCreateModel() {

}

void WorldBoundTitle::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundTitle‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R2SC(dxworld_r/dxmodel_r)*0.989;


}

void WorldBoundTitle::onActive() {
}

void WorldBoundTitle::processBehavior() {
    _pFader->behave();
}
void WorldBoundTitle::processJudgement() {
}

void WorldBoundTitle::fadein() {
    _pFader->setAlphaToBottom();
    _pFader->intoTargetAlphaLinerUntil(1.0, 120);
}

WorldBoundTitle::~WorldBoundTitle() {
}

