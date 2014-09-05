#include "WorldBoundSpace001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpace001::WorldBoundSpace001(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundTitle") {
    _class_name = "WorldBoundSpace001";
    setCubeMapTexture("BkSpace_cubemap.dds");
}

void WorldBoundSpace001::onCreateModel() {

}

void WorldBoundSpace001::initialize() {
    setHitAble(false);
    positionAs(P_CAM);
    setFaceAng(0, 0, 0);
    dxcoord world_r = P_CAM->_zf; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord world_bound_model_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    setScaleR((world_r*0.989)/world_bound_model_r);
    //getKuroko()->setFaceAngVelo(D_ANG(11),D_ANG(5),D_ANG(7)); //‰ñ‚µ‚Ä‚à‚ ‚ñ‚Ü‚èH
}

void WorldBoundSpace001::onActive() {
}

void WorldBoundSpace001::processBehavior() {
    //getKuroko()->behave();
}

void WorldBoundSpace001::processJudgement() {
}

WorldBoundSpace001::~WorldBoundSpace001() {
}

