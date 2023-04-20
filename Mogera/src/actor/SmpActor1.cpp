#include "actor/SmpActor1.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"



using namespace GgafLib;
using namespace Mogera;

SmpActor1::SmpActor1(const char* prm_name) :
        GgafLib::DefaultMeshSetActor(prm_name, "MorphTest") { //Guruguru.x ���Q�Ƃ����B
    //���W�ݒ�
//    setMaterialColor(0.0, 1.0, 1.0);
//    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
////    pChecker->setColliAABox_WHD(0, PX_C(100),PX_C(100),PX_C(100));
//    pChecker->setColliSphere(0, PX_C(20));
//    setHitAble(true);
}

void SmpActor1::initialize() {
}

void SmpActor1::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x += PX_C(2); //�E
    }
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(2); //��
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(2); //��
        }
    }
    getLocoVehicle()->behave(); //�ړ��ԗ�������������iZ����]����j
}

void SmpActor1::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("SmpActor1::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

SmpActor1::~SmpActor1() {
}

