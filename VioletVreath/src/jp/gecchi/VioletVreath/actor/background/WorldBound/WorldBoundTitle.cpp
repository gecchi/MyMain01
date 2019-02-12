#include "WorldBoundTitle.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

WorldBoundTitle::WorldBoundTitle(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBoundTitle_0") {
    _class_name = "WorldBoundTitle";
    //setCubeMapTexture("BkSky_cubemap.dds");
    setCubeMapTexture("BkSpace_cubemap.dds");
}

void WorldBoundTitle::onCreateModel() {

}

void WorldBoundTitle::initialize() {
    const Camera* const pCam = pGOD->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //���E���E�����a
    dxcoord world_bound_model_r = 1.0f; //WorldBound001�̃��f���͔��aDIRECTX����1�̋��ł���
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundTitle::onActive() {
}

void WorldBoundTitle::processBehavior() {
    getAlphaFader()->behave();
}
void WorldBoundTitle::processJudgement() {
}

void WorldBoundTitle::fadein() {
    setAlpha(getAlphaFader()->getBottom());
    getAlphaFader()->transitionLinearUntil(1.0, 120);
}

WorldBoundTitle::~WorldBoundTitle() {
}

