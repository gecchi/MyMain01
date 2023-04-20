#include "ItemBoardTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/ItemBoardTest.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"


using namespace GgafLib;
using namespace Mogera;


ItemBoardTest::ItemBoardTest(const char* prm_name) :
        DefaultBoardSetActor(prm_name, "_chk_TestDefaultBoardActorModel") {
    _class_name = "ItemBoardTest";
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, 1.0);
    setHitAble(true);
}

void ItemBoardTest::onCreateModel() {
}

void ItemBoardTest::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
}

void ItemBoardTest::onActive() {
}

void ItemBoardTest::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;

    if (GgafDx::Input::isPressedKey(DIK_1)) {
         setAlign(ALIGN_RIGHT, VALIGN_TOP);
     }
     if (GgafDx::Input::isPressedKey(DIK_2)) {
         setAlign(ALIGN_CENTER, VALIGN_TOP);
     }
     if (GgafDx::Input::isPressedKey(DIK_3)) {
         setAlign(ALIGN_LEFT, VALIGN_TOP);
     }
     if (GgafDx::Input::isPressedKey(DIK_4)) {
         setAlign(ALIGN_RIGHT, VALIGN_MIDDLE);
     }
     if (GgafDx::Input::isPressedKey(DIK_5)) {
         setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
     }
     if (GgafDx::Input::isPressedKey(DIK_6)) {
         setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
     }
     if (GgafDx::Input::isPressedKey(DIK_7)) {
         setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
     }
     if (GgafDx::Input::isPressedKey(DIK_8)) {
         setAlign(ALIGN_CENTER, VALIGN_BOTTOM);
     }
     if (GgafDx::Input::isPressedKey(DIK_9)) {
         setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
     }


    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
//        if (pVb->isPressed(0, VB_UP)) {
//          _z += PX_C(2); //奥
//        }
//        if (pVb->isPressed(0, VB_DOWN)) {
//          _z -= PX_C(2); //手前
//        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
          _x += PX_C(2); //右
        }
        if (pVb->isPressed(0, VB_LEFT)) {
          _x -= PX_C(2); //左
        }
        if (pVb->isPressed(0, VB_UP)) {
          _y -= PX_C(2); //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
          _y += PX_C(2); //下
        }
    }
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void ItemBoardTest::processJudgement() {
}

void ItemBoardTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("ItemBoardTestがひっとおお！！！！！！！！！！！！！！！！！！！！！！！！！！！！");
}

void ItemBoardTest::onInactive() {
}

ItemBoardTest::~ItemBoardTest() {
}

