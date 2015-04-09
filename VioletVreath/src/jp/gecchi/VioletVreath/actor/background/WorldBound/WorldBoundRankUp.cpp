#include "WorldBoundRankUp.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundRankUp::WorldBoundRankUp(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundRankUp") {
    _class_name = "WorldBoundRankUp";
    setCubeMapTexture("Ratislavia_cubemap.dds");
}

void WorldBoundRankUp::onCreateModel() {

}
void WorldBoundRankUp::initialize() {
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
    setHitAble(false);
    positionAs(pCam);
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

