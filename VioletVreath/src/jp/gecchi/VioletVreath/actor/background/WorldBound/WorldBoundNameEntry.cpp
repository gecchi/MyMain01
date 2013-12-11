#include "stdafx.h"
#include "WorldBoundNameEntry.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundNameEntry::WorldBoundNameEntry(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundNameEntry") {
    _class_name = "WorldBoundNameEntry";
    pAFader_ = NEW GgafDxAlphaFader(this);
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSky_cubemap.dds");
}

void WorldBoundNameEntry::onCreateModel() {

}

void WorldBoundNameEntry::initialize() {
    setHitAble(false);
    _x = _y = _z = 0;
    _rx = _ry = _rz = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundNameEntry‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _sx = _sy = _sz = R_SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundNameEntry::onActive() {
}

void WorldBoundNameEntry::processBehavior() {
    pAFader_->behave();
}

void WorldBoundNameEntry::processJudgement() {
}

void WorldBoundNameEntry::fadein() {
    activate();
    pAFader_->setToBottom();
    pAFader_->fadeLinerUntil(1.0, 120);
}

void WorldBoundNameEntry::fadeout() {
    pAFader_->fadeLinerUntil(0.0, 120);
    inactivateDelay(120);
}

WorldBoundNameEntry::~WorldBoundNameEntry() {
    GGAF_DELETE(pAFader_);
}

