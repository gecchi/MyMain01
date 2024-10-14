#include "BoardTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/BoardTest.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"


using namespace GgafLib;
using namespace Mogera;


BoardTest::BoardTest(const char* prm_name) :
        DefaultFramedBoardActor(prm_name, "_chk_TestDefaultFramedBoardActorModel") {
    _class_name = "BoardTest";
}

void BoardTest::onCreateModel() {
}

void BoardTest::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
    GgafDx::UvFlipper* pFrameUvFlipper = getFrameUvFlipper();
    int ptn[8] = {0, 8, 16, 24, 32, 40, 48, 56 };
    pFrameUvFlipper->customizePtnOrder(ptn, 8);
    pFrameUvFlipper->exec(FLIP_CUSTOMIZED_LOOP, 30);
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(R_SC(0.1), R_SC(1.5));
    pScaler->beat(300, 100, 100, 100, -1);
//    setWidth(PX_C(32*4));
//    setHeight(PX_C(32*5));
}

void BoardTest::onActive() {
}

void BoardTest::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        addWidth(-PX_C(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        addWidth(PX_C(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        addHeight(PX_C(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_Z)) {
        addHeight(-PX_C(1));
    }

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
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest::processJudgement() {
}

void BoardTest::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
}

void BoardTest::onInactive() {
}

BoardTest::~BoardTest() {
}

