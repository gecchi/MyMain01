#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundNameEntry::WorldBoundNameEntry(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundNameEntry") {
    _class_name = "WorldBoundNameEntry";
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSky_cubemap.dds");
}

void WorldBoundNameEntry::onCreateModel() {

}

void WorldBoundNameEntry::initialize() {
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundNameEntry‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R_SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundNameEntry::onActive() {
}

void WorldBoundNameEntry::processBehavior() {
    _pAFader->behave();
}

void WorldBoundNameEntry::processJudgement() {
}

void WorldBoundNameEntry::fadein() {
    activate();
    _pAFader->setAlphaToBottom();
    _pAFader->fadeLinerUntil(1.0, 120);
}

void WorldBoundNameEntry::fadeout() {
    _pAFader->fadeLinerUntil(0.0, 120);
    inactivateDelay(120);
}

WorldBoundNameEntry::~WorldBoundNameEntry() {
}

