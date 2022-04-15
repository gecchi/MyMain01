#include "SmpActor2.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

SmpActor2::SmpActor2(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x が参照される。
    //座標設定
    setMaterialColor(1.0, 1.0, 0.0);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(8);
    coord ox = PX_C(20);
    coord oy = PX_C(30);
    coord oz = PX_C(40);
    coord w = PX_C(100);
    coord h = PX_C(130);
    coord d = PX_C(170);
    pChecker->setColliAAPyramid_WHD(0, ox + (w*1), oy + (h*1), oz + (d*1), w, h, d, POS_PYRAMID_NNN);
    pChecker->setColliAAPyramid_WHD(1, ox + (w*1), oy + (h*1), oz - (d*1), w, h, d, POS_PYRAMID_NNP);
    pChecker->setColliAAPyramid_WHD(2, ox + (w*1), oy - (h*1), oz + (d*1), w, h, d, POS_PYRAMID_NPN);
    pChecker->setColliAAPyramid_WHD(3, ox + (w*1), oy - (h*1), oz - (d*1), w, h, d, POS_PYRAMID_NPP);
    pChecker->setColliAAPyramid_WHD(4, ox - (w*1), oy + (h*1), oz + (d*1), w, h, d, POS_PYRAMID_PNN);
    pChecker->setColliAAPyramid_WHD(5, ox - (w*1), oy + (h*1), oz - (d*1), w, h, d, POS_PYRAMID_PNP);
    pChecker->setColliAAPyramid_WHD(6, ox - (w*1), oy - (h*1), oz + (d*1), w, h, d, POS_PYRAMID_PPN);
    pChecker->setColliAAPyramid_WHD(7, ox - (w*1), oy - (h*1), oz - (d*1), w, h, d, POS_PYRAMID_PPP);

//    coord ox = PX_C(-50);
//    coord oy = PX_C(-50);
//    coord oz = PX_C(-50);
//    coord w = PX_C(100);
//    coord h = PX_C(100);
//    coord d = PX_C(100);
//    pChecker->createCollisionArea(1);
//    pChecker->setColliAAPyramid_WHD(0, ox + (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PYRAMID_NNN);

//    coord ox = PX_C(-50);
//    coord oy = PX_C(-50);
//    coord oz = PX_C(-50);
//    coord w = PX_C(100);
//    coord h = PX_C(100);
//    coord d = PX_C(100);
//    pChecker->createCollisionArea(1);
//    pChecker->setColliAAPrism_WHD(0, ox + (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PRISM_XY_NN);

    setHitAble(true);
}


void SmpActor2::initialize() {
}

void SmpActor2::processBehavior() {
    if (GgafDx::Input::isPressedKey(DIK_D)) {
        _x += PX_C(2); //右
    }
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //左
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        _y += PX_C(2); //上
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        _y -= PX_C(2); //下
    }

    if (GgafDx::Input::isPressedKey(DIK_R)) {
        _z -= PX_C(2); //手前
    }
    if (GgafDx::Input::isPressedKey(DIK_F)) {
        _z += PX_C(2); //奥
    }
    getVecVehicle()->behave(); //力車を活動させる（Z軸回転する）
}

void SmpActor2::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpActor2::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SmpActor2::~SmpActor2() {
}

