#include "SmpSprite.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

SmpSprite::SmpSprite(const char* prm_name) :
        GgafLib::DefaultFramedSpriteActor(prm_name, "_chk_TestDefaultFramedSpriteActorModel") {
    //���W�ݒ�
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(20));
    setHitAble(true);


}

void SmpSprite::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
    GgafDx::UvFlipper* pFrameUvFlipper = getFrameUvFlipper();
    static int ptn[8] = {0, 8, 16, 24, 32, 40, 48, 56 };
    pFrameUvFlipper->customizePtnOrder(ptn, 8);
    pFrameUvFlipper->exec(FLIP_CUSTOMIZED_LOOP, 30);

}

void SmpSprite::processBehavior() {
    addRzFaceAng(D_ANG(1));
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
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

    if (GgafDx::Input::isPressedKey(DIK_R)) {
        setWidth(PX_C(64));
    }
    if (GgafDx::Input::isPressedKey(DIK_T)) {
        setWidth(PX_C(32));
    }

    if (pVb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(VB_UP)) {
            _z += PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_UP)) {
            _y += PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //��
        }
    }
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
    getVecDriver()->behave(); //�͎Ԃ�����������iZ����]����j
}

void SmpSprite::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpSprite::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

SmpSprite::~SmpSprite() {
}

