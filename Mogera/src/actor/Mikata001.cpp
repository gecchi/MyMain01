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
        GgafLib::DefaultMorphMeshActor(prm_name, "1/Halia") { //Guruguru.x ���Q�Ƃ����B
}

void Mikata001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    setScaleR(0.5);
    //���߂ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKuroko->setFaceAng(AXIS_Y, D_ANG(90));

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
        _x += PX_C(2); //�E
    }
    if (vb->isBeingPressed(VB_LEFT)) {
        _x -= PX_C(2); //��
    }
    if (vb->isBeingPressed(VB_UP)) {
        _y += PX_C(2); //��
    }
    if (vb->isBeingPressed(VB_DOWN)) {
        _y -= PX_C(2); //��
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







    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        _pKuroko->addMvVelo(PX_C(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        _pKuroko->addMvVelo(-PX_C(2));
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        _pKuroko->hlprA()->slideMvByVd(PX_C(10), PX_C(-320)-_x, 0.3, 0.7, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        _pKuroko->hlprA()->slideMvByVd(PX_C(10), PX_C(320) - _x, 0.4, 0.6, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
        _pKuroko->hlprA()->slideMvByDt(PX_C(-320) - _x, 120, 0.3, 0.6, PX_C(0), true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
        _pKuroko->hlprA()->slideMvByDt(PX_C(320) - _x, 120, 0.3, 0.6, PX_C(0), true);
    }





    _pKuroko->behave(); //���߂�����������iZ����]����j
    _pMorpher->behave();
//    _TRACE_("Mikata001:after _x="<<_x);
//_TRACE_("Mikata001:after  _weight[1]="<<_weight[1]<<"");
//_TRACE_("-----------------------------------------");
}

void Mikata001::onInactive() {
    _TRACE_("Mikata001::onInactive()!!! _frame_of_life="<<_frame_of_life<<" _frame_of_behaving_since_onActive="<<_frame_of_behaving_since_onActive);
}

void Mikata001::onHit(GgafCore::GgafActor* prm_pOtherActor) {
    _TRACE_("�q�b�g�I");
}

Mikata001::~Mikata001() {
}
