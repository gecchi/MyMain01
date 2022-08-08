#include "WorldBoundRankUp.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

WorldBoundRankUp::WorldBoundRankUp(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBoundRankUp_0") {
    _class_name = "WorldBoundRankUp";
    setCubeMapTexture("Ratislavia_cubemap.dds");
}

void WorldBoundRankUp::onCreateModel() {

}
void WorldBoundRankUp::initialize() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //���E���E�����a
    dxcoord world_bound_model_r = 1.0f; //WorldBound001�̃��f���͔��aDIRECTX����1�̋��ł���
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundRankUp::onActive() {
}

void WorldBoundRankUp::processBehavior() {
}
void WorldBoundRankUp::processJudgement() {
}

WorldBoundRankUp::~WorldBoundRankUp() {
}

