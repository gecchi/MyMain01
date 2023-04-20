#include "SmpPieGraphSprite.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"
#include "jp/ggaf/dx/model/RegularPolygonSpriteModel.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
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
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(20));
    setHitAble(true);
}

void SmpPieGraphSprite::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 30);
    getColorist()->beat(RED,120,50,5,50,-1);
}

void SmpPieGraphSprite::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
    }

    if (pVb->isPressed(0, VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(2); //��
        }
    }
    getColorist()->behave();
    getUvFlipper()->behave();
    getLocoVehicle()->behave(); //�ړ��ԗ�������������iZ����]����j
}

void SmpPieGraphSprite::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

SmpPieGraphSprite::~SmpPieGraphSprite() {
}

