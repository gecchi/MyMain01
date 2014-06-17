#include "stdafx.h"
#include "actor/Mikata001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Mikata001::Mikata001(const char* prm_name) :
        GgafLib::DefaultMorphMeshActor(prm_name, "1/Halia") { //Guruguru.x が参照される。
    pColorist = NEW GgafDxColorist(this);
}

void Mikata001::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, PX_C(40));
    pColorist->forceRange(0, 4.0);
    setHitAble(true);
    setScaleR(0.5);
    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    setRyFaceAng(D_ANG(90));
//    getKuroko()->setFaceAngVelo(AXIS_Z, D_ANG(2));
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
        getMorpher()->asst()->morphByDt(1, 1.0 - _weight[1], 60, 0.3, 0.5, 0.00, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)!!!!!");
        getMorpher()->asst()->morphByDt(1,0.0 - _weight[1], 60, 0.3, 0.5, 0.00, true);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)!!!!!");
        getMorpher()->asst()->morphByVd(1,0.04, 1.0 - _weight[1],  0.4, 0.5, 0.00, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)!!!!!");
        getMorpher()->asst()->morphByVd(1,0.04, 0.0 - _weight[1], 0.4, 0.5, 0.00, true);
    }




//
//
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
//        getKuroko()->addMvVelo(PX_C(2));
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
//        getKuroko()->addMvVelo(-PX_C(2));
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
//        getKuroko()->asstA()->slideMvByVd(PX_C(10), PX_C(-320)-_x, 0.3, 0.7, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
//        getKuroko()->asstA()->slideMvByVd(PX_C(10), PX_C(320) - _x, 0.4, 0.6, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
//        getKuroko()->asstA()->slideMvByDt(PX_C(-320) - _x, 120, 0.3, 0.6, PX_C(0), true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
//        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
//        getKuroko()->asstA()->slideMvByDt(PX_C(320) - _x, 120, 0.3, 0.6, PX_C(0), true);
//    }



//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)) {
//        setMorphWeight(1,0.7);
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
//        getMorpher()->transitionLinerUntil(1, 1.0, 180);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
//        getMorpher()->transitionLinerUntil(1, 0.0, 180);
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
//        getMorpher()->transitionLinerStep(1, 1.0, 0.01);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
//        getMorpher()->transitionLinerStep(1, 0.0, -0.01);
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
//        getMorpher()->transitionAcceStep(1, 1.0, 0.001, 0.001);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)) {
//        getMorpher()->transitionAcceStep(1, 0.0, -0.001, -0.001);
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
//        getMorpher()->transitionLinerLoop(1, 120, 3, true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_G)) {
//        getMorpher()->transitionLinerLoop(1, 120, 3, false);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_H)) {
//        getMorpher()->beat(1, 120, 40, 30, 20, 4);
//    }
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_J)) {
//        getMorpher()->beat(1, 40, 0, 20, 0, 4);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_K)) {
//        getMorpher()->beat(1, 60, 10, 0, 40, 3);
//    }


    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)) {
        setMaterialColor(1.0, 1.0, 1.0);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        pColorist->transitionLinerUntil(4.0, 180);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        pColorist->transitionLinerUntil(0.0, 180);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        pColorist->transitionLinerStep(4.0, 0.01);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        pColorist->transitionLinerStep(0.0, -0.01);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        pColorist->transitionAcceStep(4.0, 0.001, 0.001);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)) {
        pColorist->transitionAcceStep(0.0, -0.001, -0.001);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        pColorist->transitionLinerLoop(120, 3, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_G)) {
        pColorist->transitionLinerLoop(120, 3, false);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_H)) {
        pColorist->beat(120, 40, 30, 20, 4);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_J)) {
        pColorist->beat(40, 0, 20, 0, 4);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_K)) {
        pColorist->beat(60, 10, 0, 40, 3);
    }

    pColorist->behave();
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
    getMorpher()->behave();
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
    GGAF_DELETE(pColorist);
}
