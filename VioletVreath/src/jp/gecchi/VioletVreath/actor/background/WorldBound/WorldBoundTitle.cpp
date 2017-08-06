#include "WorldBoundTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

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
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
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
    pAFader_->behave();
}
void WorldBoundTitle::processJudgement() {
}

void WorldBoundTitle::fadein() {
    setAlpha(pAFader_->getBottom());
    pAFader_->transitionLinearUntil(1.0, 120);
}

WorldBoundTitle::~WorldBoundTitle() {
    GGAF_DELETE(pAFader_);
}

