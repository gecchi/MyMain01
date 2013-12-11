#include "stdafx.h"
#include "WorldBoundTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundTitle::WorldBoundTitle(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundTitle") {
    _class_name = "WorldBoundTitle";
    pAFader_ = NEW GgafDxAlphaFader(this);
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSpace_cubemap.dds");
}

void WorldBoundTitle::onCreateModel() {

}

void WorldBoundTitle::initialize() {
    setHitAble(false);
    _x = _y = _z = 0;
    _rx = _ry = _rz = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundTitle‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _sx = _sy = _sz = R_SC(dxworld_r/dxmodel_r)*0.989;


}

void WorldBoundTitle::onActive() {
}

void WorldBoundTitle::processBehavior() {
    pAFader_->behave();
}
void WorldBoundTitle::processJudgement() {
}

void WorldBoundTitle::fadein() {
    pAFader_->setToBottom();
    pAFader_->fadeLinerUntil(1.0, 120);
}

WorldBoundTitle::~WorldBoundTitle() {
    GGAF_DELETE(pAFader_);
}

