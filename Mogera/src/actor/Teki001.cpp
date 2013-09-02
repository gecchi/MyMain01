#include "stdafx.h"
#include "actor/Teki001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace Mogera;
using GgafLib::CollisionChecker3D;

Teki001::Teki001(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void Teki001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    //����A�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void Teki001::processBehavior() {
    _pKurokoA->behave(); //����A������������iZ����]����j
}

Teki001::~Teki001() {
}
