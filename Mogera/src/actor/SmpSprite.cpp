#include "SmpSprite.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

SmpSprite::SmpSprite(const char* prm_name) :
        GgafLib::DefaultFramedSpriteActor(prm_name, "_chk_TestDefaultFramedSpriteActorModel") {
    //座標設定
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(20));
    setHitAble(true);


}

void SmpSprite::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
    GgafDx::UvFlipper* pFrameUvFlipper = getFrameUvFlipper();
    int ptn[8] = {0, 8, 16, 24, 32, 40, 48, 56 };
    pFrameUvFlipper->customizePtnOrder(ptn, 8);
    pFrameUvFlipper->exec(FLIP_CUSTOMIZED_LOOP, 30);
}

void SmpSprite::processBehavior() {

    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
//    if (GgafDx::Input::isPressedKey(DIK_C)) {
//        setDrawFanNum(getDrawFanNum() + 1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_V)) {
//        setDrawFanNum(getDrawFanNum() - 1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_Z)) {
//        setBeginAngPos(getBeginAngPos() + D_ANG(1));
//    }
//    if (GgafDx::Input::isPressedKey(DIK_X)) {
//        setBeginAngPos(getBeginAngPos() - D_ANG(1));
//    }
//    if (GgafDx::Input::isPressedKey(DIK_B)) {
//        addRzFaceAng(D_ANG(1));
//    }
//    if (GgafDx::Input::isPressedKey(DIK_N)) {
//        addRzFaceAng(D_ANG(-1));
//    }

//    if (GgafDx::Input::isPressedKey(DIK_Q)) {
//        setAlign(ALIGN_LEFT);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_W)) {
//        setAlign(ALIGN_CENTER);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_E)) {
//        setAlign(ALIGN_RIGHT);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_A)) {
//        setValign(VALIGN_TOP);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_S)) {
//        setValign(VALIGN_MIDDLE);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_D)) {
//        setValign(VALIGN_BOTTOM);
//    }
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

    if (GgafDx::Input::isPressedKey(DIK_O)) {
        addRzFaceAng(D_ANG(1));
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
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
    getLocoVehicle()->behave(); //移動車両を活動させる（Z軸回転する）
}

void SmpSprite::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpSprite::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SmpSprite::~SmpSprite() {
}

