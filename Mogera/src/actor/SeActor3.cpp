#include "actor/SeActor3.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAngAssistant.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"


using namespace GgafLib;
using namespace Mogera;

SeActor3::SeActor3(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x が参照される。
    //座標設定
    setMaterialColor(0.0, 1.0, 1.0);
//    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
//    pChecker->setColliSphere(0, PX_C(20));
//    setHitAble(true);
    GgafDx::SeTransmitterForActor* se = getSeXmtr();
    se->set(0, "SE_ENEMY_FIRE_LASER_001");
    se->set(1, "SE_ENEMY_FIRE_LASER_002");
}

void SeActor3::initialize() {
}

void SeActor3::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    static int D = 20;
    if (GgafDx::Input::isPushedDownKey(DIK_1)) {
        getSeXmtr()->play3D(0, true);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_2)) {
        getSeXmtr()->stop(0);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_3)) {
        getSeXmtr()->play3D(1);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_Q)) {
        setPosition(0, 0, 0);
    }
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(D); //奥
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(D); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(D); //右
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(D); //左
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(D); //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(D); //下
        }
    }
    getLocusVehicle()->behave(); //移動車両を活動させる（Z軸回転する）
    getSeXmtr()->behave(); //３D効果活動
}

void SeActor3::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SeActor3::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SeActor3::~SeActor3() {
}

