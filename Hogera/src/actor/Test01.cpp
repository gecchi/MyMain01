#include "Test01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "HgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

enum {
    LOCKON001_PROG_FIRST_LOCK ,
    LOCKON001_PROG_LOCK       ,
    LOCKON001_PROG_RELEASE    ,
    PROG_BANPEI,
};

Test01::Test01(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Test01";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���

    setAlpha(0.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(true);
    useProgress(PROG_BANPEI);
}

void Test01::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������

    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(2);
//    pChecker->setColliAABox_Cube(0, PX_C(128));
    pChecker->setColliSphere(0, PX_C(64));
    pChecker->setColliAABox(1, PX_C(-128), PX_C(-128), PX_C(-1), PX_C(-64), PX_C(-64), PX_C(1), false, false, true);
}


void Test01::onReset() {
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Test01::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //��]

}

void Test01::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();


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

    getUvFlipper()->behave();
    pKuroko->behave();

}

void Test01::processJudgement() {
}

void Test01::onInactive() {
}

void Test01::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("Test01::onHit!!!! ���聁"<<prm_pOtherActor->getName()<<"");
}

Test01::~Test01() {
}

