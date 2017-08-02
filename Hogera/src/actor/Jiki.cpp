#include "Jiki.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

Jiki::Jiki(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Jiki";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���

    setAlpha(0.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(false); //�����蔻�薳��
//    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
//    pSe->set(0, "WAVE_LOCKON_001"); //���ʉ���`
    useProgress(PROG_BANPEI);
}

void Jiki::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
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


    getUvFlipper()->behave();
    pKuroko->behave();

}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}


Jiki::~Jiki() {
}

