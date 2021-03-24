#include "SmpPieGraphSprite.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"
#include "jp/ggaf/dx/model/RegularPolygonSpriteModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
};

SmpPieGraphSprite::SmpPieGraphSprite(const char* prm_name) :
        GgafLib::PieGraphSpriteActor(prm_name, "36,CCW,RegularPolygon") { //���X�p�`�Ŕ����v���`��
    //���W�ݒ�
    int angle_num = ((GgafDx::RegularPolygonSpriteModel*)getModel())->getAngleNum();
    linkVariable(&_x);
    scale(-PX_C(50), PX_C(50), 0, angle_num); //���ݒl�ŉ�ʕ\����600px�Ƃ���B
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(20));
    setHitAble(true);
}

void SmpPieGraphSprite::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 30);
    getColorist()->beat(RED,120,50,5,50,-1);
}

void SmpPieGraphSprite::processBehavior() {
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
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
    getColorist()->behave();
    getUvFlipper()->behave();
    callVecDriver()->behave(); //�͎Ԃ�����������iZ����]����j
}

void SmpPieGraphSprite::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

SmpPieGraphSprite::~SmpPieGraphSprite() {
}

