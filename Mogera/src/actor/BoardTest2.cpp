#include "BoardTest2.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "actor/BoardTest2.h"
#include "MgrCaretaker.h"



using namespace GgafLib;
using namespace Mogera;


BoardTest2::BoardTest2(const char* prm_name) :
        DefaultRegularPolygonBoardActor(prm_name, "12,CW,BoardTest2") {
    _class_name = "BoardTest2";
}

void BoardTest2::onCreateModel() {
}

void BoardTest2::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
//    GgafDx::Scaler* const pScaler = getScaler();
//    pScaler->setRange(R_SC(0.1), R_SC(1.5));
//    pScaler->beat(300, 100, 100, 100, -1);
//    setWidth(PX_C(32*4));
//    setHeight(PX_C(32*5));
}

void BoardTest2::onActive() {
}

void BoardTest2::processBehavior() {
     VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_C)) {
        setDrawFanNum(getDrawFanNum() + 1);
    }
    if (GgafDx::Input::isPressedKey(DIK_V)) {
        setDrawFanNum(getDrawFanNum() - 1);
    }
    if (GgafDx::Input::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_B)) {
        addRzFaceAng(D_ANG(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_N)) {
        addRzFaceAng(D_ANG(-1));
    }

    if (GgafDx::Input::isPressedKey(DIK_Q)) {
        setAlign(ALIGN_LEFT);
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        setAlign(ALIGN_CENTER);
    }
    if (GgafDx::Input::isPressedKey(DIK_E)) {
        setAlign(ALIGN_RIGHT);
    }

    if (GgafDx::Input::isPressedKey(DIK_A)) {
        setValign(VALIGN_TOP);
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        setValign(VALIGN_MIDDLE);
    }
    if (GgafDx::Input::isPressedKey(DIK_D)) {
        setValign(VALIGN_BOTTOM);
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
            _y -= PX_C(2); //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y += PX_C(2); //下
        }
    }

    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest2::processJudgement() {
}

void BoardTest2::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void BoardTest2::onInactive() {
}

BoardTest2::~BoardTest2() {
}


