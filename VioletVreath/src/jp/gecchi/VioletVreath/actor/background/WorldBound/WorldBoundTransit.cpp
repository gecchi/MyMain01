#include "WorldBoundTransit.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

WorldBoundTransit::WorldBoundTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBoundTransit_0") {
    _class_name = "WorldBoundTransit";
    setCubeMapTexture("Default_reflection_cubemap.dds");
}

void WorldBoundTransit::onCreateModel() {

}
void WorldBoundTransit::initialize() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //’E«EΌa
    dxcoord world_bound_model_r = 1.0f; //WorldBound001ΜfΝΌaDIRECTX£1ΜΕ ι
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundTransit::onActive() {
}

void WorldBoundTransit::processBehavior() {
}
void WorldBoundTransit::processJudgement() {
}

WorldBoundTransit::~WorldBoundTransit() {
}

