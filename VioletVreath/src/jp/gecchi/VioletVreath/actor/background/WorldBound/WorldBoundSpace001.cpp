#include "stdafx.h"
#include "WorldBoundSpace001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

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
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;

    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //’E«EΌa
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001ΜfΝΌaDIRECTX£1ΜΕ ι
    _SX = _SY = _SZ = R_SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundSpace001::onActive() {
}

void WorldBoundSpace001::processBehavior() {
}

void WorldBoundSpace001::processJudgement() {
}

WorldBoundSpace001::~WorldBoundSpace001() {
}

