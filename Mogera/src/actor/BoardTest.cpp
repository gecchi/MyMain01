#include "BoardTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
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
    VirtualButton* pVb = P_CARETAKER->getSpacetime()->pVb_;
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


    if (pVb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
//        if (pVb->isPressed(VB_UP)) {
//          _z += PX_C(2); //��
//        }
//        if (pVb->isPressed(VB_DOWN)) {
//          _z -= PX_C(2); //��O
//        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(VB_RIGHT)) {
          _x += PX_C(2); //�E
        }
        if (pVb->isPressed(VB_LEFT)) {
          _x -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_UP)) {
          _y -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
          _y += PX_C(2); //��
        }
    }
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest::processJudgement() {
}

void BoardTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void BoardTest::onInactive() {
}

BoardTest::~BoardTest() {
}

