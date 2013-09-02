#include "stdafx.h"
#include "actor/Mikata001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Mikata001::Mikata001(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void Mikata001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    //黒衣AにキャラのZ軸回転の角速度を設定(毎フレーム2度)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void Mikata001::processBehavior() {
    VirtualButton* vb = P_WORLD->vb_;

    if (vb->isBeingPressed(VB_RIGHT)) {
        _X += PX_C(2); //右
    }
    if (vb->isBeingPressed(VB_LEFT)) {
        _X -= PX_C(2); //左
    }
    if (vb->isBeingPressed(VB_UP)) {
        _Y += PX_C(2); //上
    }
    if (vb->isBeingPressed(VB_DOWN)) {
        _Y -= PX_C(2); //下
    }
    _pKurokoA->behave(); //黒衣Aを活動させる（Z軸回転する）
}

void Mikata001::onHit(GgafCore::GgafActor* prm_pOtherActor) {
    _TRACE_("ヒット！");
}

Mikata001::~Mikata001() {
}
