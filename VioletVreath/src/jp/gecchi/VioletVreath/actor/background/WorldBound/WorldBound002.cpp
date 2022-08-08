#include "WorldBound002.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

WorldBound002::WorldBound002(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBound002_0") {
    _class_name = "WorldBound002";
    base_u_ = 0;
    base_v_ = 0;
}
void WorldBound002::initialize() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //    getUvFlipper()->locatePatternNo(16, 1/16.0, 1/16.0);
    //    getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
    //    getUvFlipper()->setFlipPtnRange(0, 16*16-1);
    //    getUvFlipper()->setActivePtn(0);
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBound001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    setScaleR((world_r*0.989)/world_bound_model_r);
}

void WorldBound002::onActive() {
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
}

void WorldBound002::processBehavior() {
//    getUvFlipper()->setBaseUv(base_u_,base_v_);
//    base_u_ += 0.005;
//    base_v_ += 0.005;
//    getUvFlipper()->behave();
}
void WorldBound002::processJudgement() {
}

WorldBound002::~WorldBound002() {
}

