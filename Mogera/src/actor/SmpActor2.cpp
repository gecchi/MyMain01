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
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x ���Q�Ƃ����B
    //���W�ݒ�
    setMaterialColor(1.0, 1.0, 0.0);
    CollisionChecker* pChecker = getCollisionChecker();
//    pChecker->createCollisionArea(8);
//    coord ox = PX_C(20);
//    coord oy = PX_C(30);
//    coord oz = PX_C(40);
//    coord w = PX_C(100);
//    coord h = PX_C(130);
//    coord d = PX_C(170);
//    pChecker->setColliAAPyramid_WHD(0, ox + (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PYRAMID_nnn);
//    pChecker->setColliAAPyramid_WHD(1, ox + (w/2), oy + (h/2), oz - (d/2), w, h, d, POS_PYRAMID_nnp);
//    pChecker->setColliAAPyramid_WHD(2, ox + (w/2), oy - (h/2), oz + (d/2), w, h, d, POS_PYRAMID_npn);
//    pChecker->setColliAAPyramid_WHD(3, ox + (w/2), oy - (h/2), oz - (d/2), w, h, d, POS_PYRAMID_npp);
//    pChecker->setColliAAPyramid_WHD(4, ox - (w/2), oy + (h/2), oz + (d/2), w, h, d, POS_PYRAMID_pnn);
//    pChecker->setColliAAPyramid_WHD(5, ox - (w/2), oy + (h/2), oz - (d/2), w, h, d, POS_PYRAMID_pnp);
//    pChecker->setColliAAPyramid_WHD(6, ox - (w/2), oy - (h/2), oz + (d/2), w, h, d, POS_PYRAMID_ppn);
//    pChecker->setColliAAPyramid_WHD(7, ox - (w/2), oy - (h/2), oz - (d/2), w, h, d, POS_PYRAMID_ppp);

    coord ox = PX_C(-50);
    coord oy = PX_C(-50);
    coord oz = PX_C(-50);
    coord w = PX_C(100);
    coord h = PX_C(100);
    coord d = PX_C(100);
    pChecker->createCollisionArea(1);
    pChecker->setColliAAPyramid_WHD(0, ox - (w/2), oy - (h/2), oz - (d/2), w, h, d, POS_PYRAMID_ppp);

    setHitAble(true);
}

void SmpActor2::initialize() {
}

void SmpActor2::processBehavior() {
    if (GgafDxInput::isPressedKey(DIK_D)) {
        _x += PX_C(2); //�E
    }
    if (GgafDxInput::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //��
    }
    if (GgafDxInput::isPressedKey(DIK_W)) {
        _y += PX_C(2); //��
    }
    if (GgafDxInput::isPressedKey(DIK_S)) {
        _y -= PX_C(2); //��
    }

    if (GgafDxInput::isPressedKey(DIK_R)) {
        _z -= PX_C(2); //��O
    }
    if (GgafDxInput::isPressedKey(DIK_F)) {
        _z += PX_C(2); //��
    }
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

void SmpActor2::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("SmpActor2::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

SmpActor2::~SmpActor2() {
}

