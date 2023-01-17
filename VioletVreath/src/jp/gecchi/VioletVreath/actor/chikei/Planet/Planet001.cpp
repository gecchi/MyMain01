#include "Planet001.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "Planet001Atmosphere.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"



using namespace GgafLib;
using namespace VioletVreath;


Planet001::Planet001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001") {
    _class_name = "Planet001";
    setHitAble(false);
    setZEnableDraw(true);        //Zバッファは考慮
    setZWriteEnable(false);  //自身のZバッファを書き込みしない

    drawAnyFar(true);//遠くても表示
    //大気圏エフェクトスプライト
    pAtmosphere_ = NEW Planet001Atmosphere("P001ATMOS");
    appendChild(pAtmosphere_);

    pAtmosphere_->setSpecialRenderDepthFar(-2);
    setSpecialRenderDepthFar(-3);

}

void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    setCullingDraw(false);
    Spacetime* pSpacetime = pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right*10;
    setScale(1000*1000);
    setRzFaceAng(D90ANG - D_ANG(30));
    setRyFaceAng(D45ANG);
    getVecVehicle()->setRollFaceAngVelo(500); //自転の速さ

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->setPositionAt(this);
}
void Planet001::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();

//    //巨大オブジェクト移動テスト
//    if (GgafDx::Input::isPressedKey(DIK_I)) {
//        _x += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_O)) {
//        _x += PX_C(1000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_U)) {
//        _x -= PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_Y)) {
//        _x -= PX_C(1000);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_8)) {
//        _y += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_J)) {
//        _y -= PX_C(100);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_M)) {
//        _y -= PX_C(1000);
//    }
//
//
//    if (GgafDx::Input::isPressedKey(DIK_9)) {
//        _z += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_K)) {
//        _z -= PX_C(100);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_0)) {
//        addScale(10000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_L)) {
//        addScale(-10000);
//    }
//
//    if (GgafDx::Input::isPushedDownKey(DIK_O)) {
//        _TRACE_("Planet001  "<<_x<<","<<_y<<","<<_z<<" scale="<<_rx);
//    }
    //_x = _x - PX_C(1);
    pVecVehicle->behave();

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->setPositionAt(this);
}

Planet001::~Planet001() {
}

