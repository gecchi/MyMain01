#include "WorldBoundNameEntry.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

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
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //’E«EΌa
    dxcoord world_bound_model_r = 1.0f; //WorldBound001ΜfΝΌaDIRECTX£1ΜΕ ι
    setScaleR((world_r*0.989)/world_bound_model_r);
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
    setAlpha(pAFader_->getBottom());
    pAFader_->transitionLinerUntil(1.0, 120);
}

void WorldBoundNameEntry::fadeout() {
    pAFader_->transitionLinerUntil(0.0, 120);
    inactivateDelay(120);
}

WorldBoundNameEntry::~WorldBoundNameEntry() {
    GGAF_DELETE(pAFader_);
}

