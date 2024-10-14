#include "SmpActor2.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;

SmpActor2::SmpActor2(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x Ç™éQè∆Ç≥ÇÍÇÈÅB
    addModel("donatu");
    //ç¿ïWê›íË
    setMaterialColor(1.0, 1.0, 0.0);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(8);
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
//    pChecker->addCollisionArea(1);
//    pChecker->setColliAAPyramid_WHD(0, ox + (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PYRAMID_NNN);

//    coord ox = PX_C(-50);
//    coord oy = PX_C(-50);
//    coord oz = PX_C(-50);
//    coord w = PX_C(100);
//    coord h = PX_C(100);
//    coord d = PX_C(100);
//    pChecker->addCollisionArea(1);
//    pChecker->setColliAAPrism_WHD(0, ox + (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PRISM_XY_NN);

    setHitAble(true);


}


void SmpActor2::initialize() {
}

void SmpActor2::processBehavior() {
    NaviVehicle* pNaviVehicle = getNaviVehicle();


    if (GgafDx::Input::isPressedKey(DIK_SPACE)) {
        setPosition(0, 0, 0);
        pNaviVehicle->setVeloZero();
        pNaviVehicle->setAcceZero();
    }

    if (GgafDx::Input::isPressedKey(DIK_A)) {
        changeModelByIndex(0);
    }
    if (GgafDx::Input::isPressedKey(DIK_B)) {
		changeModelByIndex(1);
    }



//    _TRACE_("x,y,z="<<_x<<", "<<_y<<", "<<_z);
    pNaviVehicle->behave();
    getLocusVehicle()->behave();
}

void SmpActor2::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpActor2::onHit!!!! ëäéËÅÅ"<<prm_pOtherActor->getName()<<"");
}

SmpActor2::~SmpActor2() {
}

