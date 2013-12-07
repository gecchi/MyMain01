#include "stdafx.h"
#include "actor/Mikata001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAsstA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Mikata001::Mikata001(const char* prm_name) :
        GgafLib::DefaultMorphMeshActor(prm_name, "1/Halia") { //Guruguru.x が参照される。
                pAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);
                pMorpherAsstA_= NEW GgafDxMorpherAsstA(_pMorpher);
}

void Mikata001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    setScaleR(0.5);
    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    _pKuroko->setFaceAng(AXIS_Y, D_ANG(90));

//    _pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(2));

    //acc_x._value = _x;
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


    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_1)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_1)!!!!!");
        pMorpherAsstA_->morphByDt(1, 1.0 - _weight[1], 90, 0.5, 0.5, 0.02, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_2)!!!!!");
        pMorpherAsstA_->morphByDt(1,0.0 - _weight[1], 90, 0.5, 0.5, 0.02, true);
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_3)!!!!!");
        pMorpherAsstA_->morphByVd(1,0.04, 1.0 - _weight[1],  0.4, 0.5, 0.02, true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_4)!!!!!");
        pMorpherAsstA_->morphByVd(1,0.04, 0.0 - _weight[1], 0.4, 0.5, 0.02, true);
    }







    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        pAsstA_->_smthMv._prm._flg = false;
        _pKuroko->addMvVelo(PX_C(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        pAsstA_->_smthMv._prm._flg = false;
        _pKuroko->addMvVelo(-PX_C(2));
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        pAsstA_->slideMvByVd(PX_C(10), PX_C(-320)-_x, 0.3, 0.6, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        pAsstA_->slideMvByVd(PX_C(10), PX_C(320) - _x, 0.3, 0.6, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
        pAsstA_->slideMvByDt(PX_C(-320) - _x, 120, 0.3, 0.6, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
        pAsstA_->slideMvByDt(PX_C(320) - _x, 120, 0.3, 0.6, PX_C(0), true);
    }





    pAsstA_->behave();
    _pKuroko->behave(); //黒衣を活動させる（Z軸回転する）
    pMorpherAsstA_->behave();
    _pMorpher->behave();
}

void Mikata001::onInactive() {
    _TRACE_("Mikata001::onInactive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::onHit(GgafCore::GgafActor* prm_pOtherActor) {
    _TRACE_("ヒット！");
}

Mikata001::~Mikata001() {
    GGAF_DELETE(pAsstA_);
}
