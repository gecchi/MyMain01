#include "EffectCondensation001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "Lockon001") {
    _class_name = "EffectCondensation001";
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix_Billboard(); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectCondensation001::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
}

void EffectCondensation001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //�X�P�[�����O�E�͈�
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    getVecDriver()->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectCondensation001::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();

    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler->isTransitioning()) {
        //�k��������ABeat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //�������[�v
    }
    getUvFlipper()->behave();
    getVecDriver()->behave();
    pScaler->behave();
}

void EffectCondensation001::processJudgement() {
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}

