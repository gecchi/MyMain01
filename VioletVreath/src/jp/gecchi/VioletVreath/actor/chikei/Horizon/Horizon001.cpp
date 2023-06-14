#include "Horizon001.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;


Horizon001::Horizon001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Horizon001") {
    _class_name = "Horizon001";
    setHitAble(false);
    setZEnableDraw(true);        //Zバッファは考慮
//    setZWriteEnable(false);  //自身のZバッファを書き込みしない
//    setSpecialRenderDepthIndex(RENDER_DEPTH_FAR_INDEX-3);
    chip_width_ = PX_C(256);
}

void Horizon001::onCreateModel() {
    getModel()->drawAnyFar();//遠くても表示
}

void Horizon001::initialize() {
    setCullingDraw(false);
    setPosition(0, PX_C(-100), 0);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    pChecker->setColliAABox(0, pSpacetime->_x_bound_left  + (chip_width_*2),
                                  0,
                                  pSpacetime->_z_bound_near  + (chip_width_*2),
                                  pSpacetime->_x_bound_right - (chip_width_*2),
                                  pSpacetime->_y_bound_bottom - (chip_width_*2),
                                  pSpacetime->_z_bound_far - (chip_width_*2));
    setBumpMapTexture("bumpstar_nmap.bmp");
}
void Horizon001::processBehavior() {
    _x = _x - PX_C(8);
    if (ABS(_x) >= chip_width_) {
        _x = 0;
    }
}

Horizon001::~Horizon001() {
}

