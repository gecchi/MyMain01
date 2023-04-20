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
        GgafLib::PieGraphSpriteActor(prm_name, "36,CCW,RegularPolygon") { //正９角形で反時計回り描画
    //座標設定
    int angle_num = ((GgafDx::RegularPolygonSpriteModel*)getModel())->getAngleNum();
    linkVariable(&_x);
    scale(-PX_C(50), PX_C(50), 0, angle_num); //現在値で画面表示は600pxとする。
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
    getColorist()->behave();
    getUvFlipper()->behave();
    getLocoVehicle()->behave(); //移動車両を活動させる（Z軸回転する）
}

void SmpPieGraphSprite::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

SmpPieGraphSprite::~SmpPieGraphSprite() {
}

