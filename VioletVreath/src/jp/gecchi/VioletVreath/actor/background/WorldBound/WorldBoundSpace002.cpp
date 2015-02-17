#include "WorldBoundSpace002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpace002::WorldBoundSpace002(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpace002") {
    _class_name = "WorldBoundSpace002";
    base_u_ = 0;
    base_v_ = 0;
}
void WorldBoundSpace002::initialize() {
    Camera* pCam = P_GOD->getUniverse()->getCamera();
    //    getUvFlipper()->setRotation(16, 1/16.0, 1/16.0);
    //    getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
    //    getUvFlipper()->setFlipPtnRange(0, 16*16-1);
    //    getUvFlipper()->setActivePtn(0);
    setHitAble(false);
    positionAs(pCam);
    setFaceAng(0, 0, 0);
    dxcoord world_r = pCam->getZFar(); //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBoundSpace002::onActive() {
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
}

void WorldBoundSpace002::processBehavior() {
//    getUvFlipper()->setBaseUv(base_u_,base_v_);
//    base_u_ += 0.005;
//    base_v_ += 0.005;
//    getUvFlipper()->behave();
}
void WorldBoundSpace002::processJudgement() {
}

WorldBoundSpace002::~WorldBoundSpace002() {
}

