#include "WorldBoundSpaceTransit.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpaceTransit::WorldBoundSpaceTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceTransit") {
    _class_name = "WorldBoundSpaceTransit";
    setCubeMapTexture("Default_reflection_cubemap.dds");
}

void WorldBoundSpaceTransit::onCreateModel() {

}
void WorldBoundSpaceTransit::initialize() {
    setHitAble(false);
    positionAs(P_CAM);
    setFaceAng(0, 0, 0);
    dxcoord world_r = P_CAM->getZFar(); //’E«EΌa
    dxcoord world_bound_model_r = 1.0f; //WorldBoundSpace001ΜfΝΌaDIRECTX£1ΜΕ ι
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundSpaceTransit::onActive() {
}

void WorldBoundSpaceTransit::processBehavior() {
}
void WorldBoundSpaceTransit::processJudgement() {
}

WorldBoundSpaceTransit::~WorldBoundSpaceTransit() {
}

