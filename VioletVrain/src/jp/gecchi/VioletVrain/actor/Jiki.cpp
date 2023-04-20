#include "Jiki.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World.h"
#include "jp/gecchi/VioletVrain/VvCaretaker.h"



using namespace GgafLib;
using namespace VioletVrain;

enum {
    LOCKON001_PHASE_FIRST_LOCK ,
    LOCKON001_PHASE_LOCK       ,
    LOCKON001_PHASE_RELEASE    ,
    PHASE_BANPEI,
};

Jiki::Jiki(const char* prm_name) :
        VvMyActor<DefaultSpriteActor>(prm_name, "Lockon001", (void*)Jiki::resetJikiStatus) {
    _class_name = "Jiki";
//    defineRotMvWorldMatrix_Billboard(); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setCullingDraw(false);
    setHitAble(true);
}

void Jiki::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
////    pChecker->set2DColliSquare(0, PX_C(128));
////    pChecker->set2DColliCircle(0, PX_C(32));
//    pChecker->set2DColliRightTriangle_WH(0, PX_C(60), PX_C(70), PX_C(250), PX_C(150), POS_R_TRIANGLE_NN);

    pChecker->addCollisionArea(4);
    coord ox = PX_C(30);
    coord oy = PX_C(40);
    coord w = PX_C(50);
    coord h = PX_C(70);
    pChecker->set2DColliRightTriangle_WH(0, ox - (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_PP);
    pChecker->set2DColliRightTriangle_WH(1, ox - (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_PN);
    pChecker->set2DColliRightTriangle_WH(2, ox + (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_NP);
    pChecker->set2DColliRightTriangle_WH(3, ox + (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_NN);
}

void Jiki::onReset() {
    getPhase()->reset(LOCKON001_PHASE_RELEASE);
}

void Jiki::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getLocoVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void Jiki::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    VirtualButton* pVb = &(pCARETAKER->getSpacetime()->getWorld()->vb_);
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
    getUvFlipper()->behave();
    pLocoVehicle->behave();
}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}

Jiki::~Jiki() {
}


