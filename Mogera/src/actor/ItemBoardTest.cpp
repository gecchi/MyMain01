#include "ItemBoardTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/ItemBoardTest.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"


using namespace GgafLib;
using namespace Mogera;


ItemBoardTest::ItemBoardTest(const char* prm_name) :
        DefaultBoardActor(prm_name, "_chk_TestDefaultBoardActorModel") {
    _class_name = "ItemBoardTest";
    CollisionChecker2D_b* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, PX_C(0), PX_C(0), PX_C(32), PX_C(32));
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
    VirtualButton* pVb = P_CARETAKER->getSpacetime()->pVb_;

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
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void ItemBoardTest::processJudgement() {
}

void ItemBoardTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("ItemBoardTest���Ђ��Ƃ����I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I");
}

void ItemBoardTest::onInactive() {
}

ItemBoardTest::~ItemBoardTest() {
}

