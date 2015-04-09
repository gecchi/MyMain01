#include "WorldBoundTransit.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundTransit::WorldBoundTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundTransit") {
    _class_name = "WorldBoundTransit";
    setCubeMapTexture("Default_reflection_cubemap.dds");
}

void WorldBoundTransit::onCreateModel() {

}
void WorldBoundTransit::initialize() {
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
    setHitAble(false);
    positionAs(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBound001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
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

