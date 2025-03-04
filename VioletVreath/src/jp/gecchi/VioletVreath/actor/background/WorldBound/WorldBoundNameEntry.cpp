#include "WorldBoundNameEntry.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

WorldBoundNameEntry::WorldBoundNameEntry(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBoundNameEntry_0") {
    _class_name = "WorldBoundNameEntry";
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSky_cubemap.dds");
}

void WorldBoundNameEntry::onCreateModel() {

}

void WorldBoundNameEntry::initialize() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
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
    getAlphaFader()->behave();
}

void WorldBoundNameEntry::processJudgement() {
}

void WorldBoundNameEntry::fadein() {
    activate();
    setAlpha(getAlphaFader()->getBottom());
    getAlphaFader()->transitionLinearUntil(1.0, 120);
}

void WorldBoundNameEntry::fadeout() {
    getAlphaFader()->transitionLinearUntil(0.0, 120);
    inactivateDelay(120);
}

WorldBoundNameEntry::~WorldBoundNameEntry() {
}

