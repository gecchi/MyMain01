#include "SmpActor2.h"

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

SmpActor2::SmpActor2(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x が参照される。
    //座標設定
    setMaterialColor(1.0, 1.0, 0.0);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAAPyramid_WHD(0, PX_C(100),PX_C(100),PX_C(100), POS_PYRAMID_nnn);
//    pChecker->setColliAABox_WHD(0, PX_C(32),PX_C(48),PX_C(64));
    setHitAble(true);
}

void SmpActor2::initialize() {
}

void SmpActor2::processBehavior() {
    if (GgafDxInput::isPressedKey(DIK_D)) {
        _x += PX_C(2); //右
    }
    if (GgafDxInput::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //左
    }
    if (GgafDxInput::isPressedKey(DIK_W)) {
        _y += PX_C(2); //上
    }
    if (GgafDxInput::isPressedKey(DIK_S)) {
        _y -= PX_C(2); //下
    }

    if (GgafDxInput::isPressedKey(DIK_R)) {
        _z -= PX_C(2); //手前
    }
    if (GgafDxInput::isPressedKey(DIK_F)) {
        _z += PX_C(2); //奥
    }
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

void SmpActor2::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("SmpActor2::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

SmpActor2::~SmpActor2() {
}
