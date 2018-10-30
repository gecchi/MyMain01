#include "SmpSprite.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

SmpSprite::SmpSprite(const char* prm_name) :
        GgafLib::DefaultRegularPolygonSpriteActor(prm_name, "36/CCW/BoardTest2") {
    //���W�ݒ�
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(20));
    setHitAble(true);
}

void SmpSprite::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 30);

}

void SmpSprite::processBehavior() {
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    if (GgafDxInput::isPressedKey(DIK_C)) {
        setDrawFanNum(getDrawFanNum() + 1);
    }
    if (GgafDxInput::isPressedKey(DIK_V)) {
        setDrawFanNum(getDrawFanNum() - 1);
    }
    if (GgafDxInput::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_B)) {
        addRzFaceAng(D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_N)) {
        addRzFaceAng(D_ANG(-1));
    }

//    if (GgafDxInput::isPressedKey(DIK_Q)) {
//        setAlign(ALIGN_LEFT);
//    }
//    if (GgafDxInput::isPressedKey(DIK_W)) {
//        setAlign(ALIGN_CENTER);
//    }
//    if (GgafDxInput::isPressedKey(DIK_E)) {
//        setAlign(ALIGN_RIGHT);
//    }
//
//    if (GgafDxInput::isPressedKey(DIK_A)) {
//        setValign(VALIGN_TOP);
//    }
//    if (GgafDxInput::isPressedKey(DIK_S)) {
//        setValign(VALIGN_MIDDLE);
//    }
//    if (GgafDxInput::isPressedKey(DIK_D)) {
//        setValign(VALIGN_BOTTOM);
//    }


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
            _y -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y += PX_C(2); //��
        }
    }
    getUvFlipper()->behave();
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

void SmpSprite::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("SmpSprite::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

SmpSprite::~SmpSprite() {
}

