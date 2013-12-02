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
void Mikata001::onActive() {
    _TRACE_("Mikata001::onActive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::processBehavior() {
    VirtualButton* vb = P_WORLD->vb_;

    if (vb->isBeingPressed(VB_RIGHT)) {
        _x += PX_C(2); //右
    }
    if (vb->isBeingPressed(VB_LEFT)) {
        _x -= PX_C(2); //左
    }
    if (vb->isBeingPressed(VB_UP)) {
        _y += PX_C(2); //上
    }
    if (vb->isBeingPressed(VB_DOWN)) {
        _y -= PX_C(2); //下
    }









    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        _pKurokoA->_slide_mv_flg = false;
        _pKurokoA->addMvVelo(PX_C(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        _pKurokoA->_slide_mv_flg = false;
        _pKurokoA->addMvVelo(-PX_C(2));
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        _pKurokoA->slideMvByVD(
                        PX_C(10) , PX_C(0), PX_C(-320) - _x,
                        0.3, 0.6,
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        _pKurokoA->slideMvByVD(
                        PX_C(10) , PX_C(0), PX_C(320) - _x,
                        0.3, 0.6,
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
        _pKurokoA->slideMvByDT(
                PX_C(0) , PX_C(-320) - _x, 120,
                0.3, 0.6,
                true
            );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
        _pKurokoA->slideMvByDT(
                PX_C(0) , PX_C(320) - _x, 120,
                0.3, 0.6,
                true
            );
    }
    _pKurokoA->behave(); //黒衣Aを活動させる（Z軸回転する）
}

void Mikata001::onInactive() {
    _TRACE_("Mikata001::onInactive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::onHit(GgafCore::GgafActor* prm_pOtherActor) {
    _TRACE_("ヒット！");
}

Mikata001::~Mikata001() {
}
