#include "actor/SmpActor1.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAngAssistant.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

SmpActor1::SmpActor1(const char* prm_name) :
        GgafLib::DefaultMeshSetActor(prm_name, "MorphTest") { //Guruguru.x が参照される。
    //座標設定
//    setMaterialColor(0.0, 1.0, 1.0);
//    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
////    pChecker->setColliAABox_WHD(0, PX_C(100),PX_C(100),PX_C(100));
//    pChecker->setColliSphere(0, PX_C(20));
//    setHitAble(true);
}

void SmpActor1::initialize() {
}

void SmpActor1::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x += PX_C(2); //右
    }
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(2); //奥
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(2); //右
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(2); //左
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(2); //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(2); //下
        }
    }
    getLocusVehicle()->behave(); //移動車両を活動させる（Z軸回転する）
}

void SmpActor1::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpActor1::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SmpActor1::~SmpActor1() {
}

