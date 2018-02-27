#include "actor/SmpActor1.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "MgrGod.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

SmpActor1::SmpActor1(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x が参照される。
    //座標設定
    setMaterialColor(0.0, 1.0, 1.0);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_WHD(0, PX_C(100),PX_C(100),PX_C(100));
    setHitAble(true);
}

void SmpActor1::initialize() {
}

void SmpActor1::processBehavior() {
    VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    if (GgafDxInput::isPressedKey(DIK_Z)) {
        _x += PX_C(2); //右
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
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

void SmpActor1::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("SmpActor1::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SmpActor1::~SmpActor1() {
}
