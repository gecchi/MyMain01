#include "WorldBoundSpaceRankUp.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpaceRankUp::WorldBoundSpaceRankUp(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceRankUp") {
    _class_name = "WorldBoundSpaceRankUp";
    setCubeMapTexture("Ratislavia_cubemap.dds");
}

void WorldBoundSpaceRankUp::onCreateModel() {

}
void WorldBoundSpaceRankUp::initialize() {
    Camera* pCam = P_GOD->getUniverse()->getCamera();
    setHitAble(false);
    positionAs(pCam);
    setFaceAng(0, 0, 0);
    dxcoord world_r = pCam->getZFar(); //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundSpaceRankUp::onActive() {
}

void WorldBoundSpaceRankUp::processBehavior() {
}
void WorldBoundSpaceRankUp::processJudgement() {
}

WorldBoundSpaceRankUp::~WorldBoundSpaceRankUp() {
}

