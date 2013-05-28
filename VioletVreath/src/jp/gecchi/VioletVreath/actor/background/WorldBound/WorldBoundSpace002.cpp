#include "stdafx.h"
#include "WorldBoundSpace002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

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
    //    _pUvFlipper->setRotation(16, 1/16.0, 1/16.0);
    //    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5);
    //    _pUvFlipper->setFlipPtnRange(0, 16*16-1);
    //    _pUvFlipper->setActivePtn(0);
    setHitAble(false);
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //¢ŠE‹«ŠE‹…”¼Œa
    dxcoord dxmodel_r = 1.0f; //WorldBoundSpace001‚Ìƒ‚ƒfƒ‹‚Í”¼ŒaDIRECTX‹——£1‚Ì‹…‚Å‚ ‚é
    _SX = _SY = _SZ = R_SC(dxworld_r/dxmodel_r)*0.989;
}

void WorldBoundSpace002::onActive() {
    //_pUvFlipper->exec(FLIP_ORDER_LOOP, 5);
}

void WorldBoundSpace002::processBehavior() {
//    _pUvFlipper->setBaseUv(base_u_,base_v_);
//    base_u_ += 0.005;
//    base_v_ += 0.005;
//    _pUvFlipper->behave();
}
void WorldBoundSpace002::processJudgement() {
}

WorldBoundSpace002::~WorldBoundSpace002() {
}

