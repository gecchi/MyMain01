#include "Jiki.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "scene/HgrSpacetime.h"
#include "scene/HgrSpacetime/HgrWorld.h"
#include "HgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

Jiki::Jiki(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Jiki";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���

    setAlpha(0.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B
    setHitAble(true);
    useProgress(PROG_BANPEI);
}

void Jiki::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������

    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
//    pChecker->setColliAABox_Cube(0, PX_C(128));
    pChecker->setColliSphere(0, PX_C(64));

}


void Jiki::onReset() {
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Jiki::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //��]

}

void Jiki::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    VirtualButton* pVb = &(P_GOD->getSpacetime()->getWorld()->vb_);
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

    getUvFlipper()->behave();
    pKuroko->behave();

}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}

void Jiki::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("Jiki::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}
Jiki::~Jiki() {
}

