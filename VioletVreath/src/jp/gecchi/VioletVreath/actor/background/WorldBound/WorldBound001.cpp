#include "WorldBound001.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

WorldBound001::WorldBound001(const char* prm_name) :
        WorldBoundActor(prm_name, "WorldBoundTitle_0") {
    _class_name = "WorldBound001";
    setCubeMapTexture("BkSpace_cubemap.dds");
}

void WorldBound001::onCreateModel() {

}

void WorldBound001::initialize() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    setHitAble(false);
    setPositionAt(pCam);
    setFaceAngZero();
    dxcoord world_r = pCam->getZFar(); //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBound001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    setScaleR((world_r*0.989)/world_bound_model_r);
    //getLocoVehicle()->setRollPitchYawFaceAngVelo(D_ANG(11),D_ANG(7),D_ANG(5)); //‰ñ‚µ‚Ä‚à‚ ‚ñ‚Ü‚èH
}

void WorldBound001::onActive() {
}

void WorldBound001::processBehavior() {
    //getLocoVehicle()->behave();
}

void WorldBound001::processJudgement() {
}

WorldBound001::~WorldBound001() {
}

