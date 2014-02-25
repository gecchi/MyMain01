#include "stdafx.h"
#include "actor/Mikata001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Mikata001::Mikata001(const char* prm_name) :
        GgafLib::DefaultMorphMeshActor(prm_name, "1/Halia") { //Guruguru.x が参照される。
}

void Mikata001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    setScaleR(0.5);
    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    setRyFaceAng(D_ANG(90));

//    _pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(2));

    //acc_x._value = _x;
}
void Mikata001::onActive() {
    _TRACE_("Mikata001::onActive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::processBehavior() {
//    _TRACE_("Mikata001:before  _weight[1]="<<_weight[1]<<"");
//    _TRACE_("Mikata001:before _x="<<_x);
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


    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_1)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_1)!!!!!");
        _pMorpher->hlprA()->morphByDt(1, 1.0 - _weight[1], 60, 0.3, 0.5, 0.00, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)!!!!!");
        _pMorpher->hlprA()->morphByDt(1,0.0 - _weight[1], 60, 0.3, 0.5, 0.00, true);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)!!!!!");
        _pMorpher->hlprA()->morphByVd(1,0.04, 1.0 - _weight[1],  0.4, 0.5, 0.00, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)!!!!!");
        _pMorpher->hlprA()->morphByVd(1,0.04, 0.0 - _weight[1], 0.4, 0.5, 0.00, true);
    }




//
//
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
//        _pKuroko->addMvVelo(PX_C(2));
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
//        _pKuroko->addMvVelo(-PX_C(2));
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
//        _pKuroko->hlprA()->slideMvByVd(PX_C(10), PX_C(-320)-_x, 0.3, 0.7, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
//        _pKuroko->hlprA()->slideMvByVd(PX_C(10), PX_C(320) - _x, 0.4, 0.6, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
//        _pKuroko->hlprA()->slideMvByDt(PX_C(-320) - _x, 120, 0.3, 0.6, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
//        _pKuroko->hlprA()->slideMvByDt(PX_C(320) - _x, 120, 0.3, 0.6, PX_C(0), true);
//    }



    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)) {
        setWeight(1,0.7);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _pMorpher->transitionLinerUntil(1, 1.0, 180);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _pMorpher->transitionLinerUntil(1, 0.0, 180);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _pMorpher->transitionLinerStep(1, 1.0, 0.01);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _pMorpher->transitionLinerStep(1, 0.0, -0.01);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _pMorpher->transitionAcceStep(1, 1.0, 0.001, 0.001);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)) {
        _pMorpher->transitionAcceStep(1, 0.0, -0.001, -0.001);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _pMorpher->loopLiner(1, 120, 3, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_G)) {
        _pMorpher->loopLiner(1, 120, 3, false);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_H)) {
        _pMorpher->beat(1, 120, 40, 30, 20, 4);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_J)) {
        _pMorpher->beat(1, 40, 0, 20, 0, 4);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_K)) {
        _pMorpher->beat(1, 60, 10, 0, 40, 3);
    }

    _pKuroko->behave(); //黒衣を活動させる（Z軸回転する）
    _pMorpher->behave();
//    _TRACE_("Mikata001:after _x="<<_x);
//_TRACE_("Mikata001:after  _weight[1]="<<_weight[1]<<"");
//_TRACE_("-----------------------------------------");
}

void Mikata001::onInactive() {
    _TRACE_("Mikata001::onInactive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::onHit(GgafCore::GgafActor* prm_pOtherActor) {
    _TRACE_("ヒット！");
}

Mikata001::~Mikata001() {
}
