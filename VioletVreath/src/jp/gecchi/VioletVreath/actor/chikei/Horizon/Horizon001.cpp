#include "Horizon001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Horizon001::Horizon001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Horizon001", nullptr) {
    _class_name = "Horizon001";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
//    setZWriteEnable(false);  //Zバッファは書き込み無し
//    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-3);
    drawAnyFar(true);//遠くても表示
    chip_width_ = PX_C(256);
}

void Horizon001::onCreateModel() {
}

void Horizon001::initialize() {
    setAlpha(0.99);
    position(0, PX_C(-100), 0);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    pChecker->setColliAAB(0, pSpacetime->_x_gone_left  + (chip_width_*2),
                                  0,
                                  pSpacetime->_z_gone_near  + (chip_width_*2),
                                  pSpacetime->_x_gone_right - (chip_width_*2),
                                  pSpacetime->_y_gone_bottom - (chip_width_*2),
                                  pSpacetime->_z_gone_far - (chip_width_*2));
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

