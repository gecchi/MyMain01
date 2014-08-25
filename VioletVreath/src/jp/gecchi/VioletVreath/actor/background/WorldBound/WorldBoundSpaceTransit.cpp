#include "WorldBoundSpaceTransit.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

WorldBoundSpaceTransit::WorldBoundSpaceTransit(const char* prm_name) :
        WorldBoundActor(prm_name, "0/WorldBoundSpaceTransit") {
    _class_name = "WorldBoundSpaceTransit";
    setCubeMapTexture("Default_reflection_cubemap.dds");
}

void WorldBoundSpaceTransit::onCreateModel() {

}
void WorldBoundSpaceTransit::initialize() {
    setHitAble(false);
    _x = _y = _z = 0;
    _rx = _ry = _rz = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //���E���E�����a
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001�̃��f���͔��aDIRECTX����1�̋��ł���
    _sx = _sy = _sz = R_SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundSpaceTransit::onActive() {
}

void WorldBoundSpaceTransit::processBehavior() {
}
void WorldBoundSpaceTransit::processJudgement() {
}

WorldBoundSpaceTransit::~WorldBoundSpaceTransit() {
}

