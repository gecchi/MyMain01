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
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x ���Q�Ƃ����B
    //���W�ݒ�
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
        _x += PX_C(2); //�E
    }
    if (pVb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(VB_UP)) {
            _z += PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_UP)) {
            _y += PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //��
        }
    }
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

void SmpActor1::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("SmpActor1::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

SmpActor1::~SmpActor1() {
}
