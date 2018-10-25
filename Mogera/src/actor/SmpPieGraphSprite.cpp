#include "SmpPieGraphSprite.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonSpriteModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
};

SmpPieGraphSprite::SmpPieGraphSprite(const char* prm_name) :
        GgafLib::PieGraphSpriteActor(prm_name, "36/CCW/RegularPolygon") { //正９角形で反時計回り描画
    //座標設定
    int angle_num = ((GgafDxRegularPolygonSpriteModel*)getModel())->getAngleNum();
    linkVariable(&_x);
    graduate(-PX_C(50), PX_C(50), 0, angle_num); //現在値で画面表示は600pxとする。
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
    if (GgafDxInput::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
    }

    if (pVb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(VB_UP)) {
            _z += PX_C(2); //奥
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //右
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //左
        }
        if (pVb->isPressed(VB_UP)) {
            _y += PX_C(2); //上
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //下
        }
    }
    getColorist()->behave();
    getUvFlipper()->behave();
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

void SmpPieGraphSprite::onHit(const GgafActor* prm_pOtherActor) {
}

SmpPieGraphSprite::~SmpPieGraphSprite() {
}

